#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* These layouts are from the 32-bit executable. */
typedef struct {
  uint32_t reserved;
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} CommandLineTokens;

typedef struct {
  uint32_t reserved;
  uint32_t text;
  uint32_t size;
  uint32_t capacity;
} CommandLineToken;

typedef struct {
  uint32_t words[4];
} RuntimeString;

typedef struct {
  uint32_t mode;
  int width;
  int height;
  uint8_t fullscreen;
  uint8_t reserved[3];
  uint32_t unused[4];
  int option_8;
} DisplayOptions;

_Static_assert(sizeof(CommandLineTokens) == 16, "command line vector layout");
_Static_assert(sizeof(CommandLineToken) == 16, "command line token layout");

/* gk3/GK3R_rest.c */
extern int game_engine_address;
extern int display_width;
extern int display_height;
extern int framebuffer_height;
extern int requested_window_x;
extern int requested_window_y;
extern char fullscreen_enabled;
extern const char Key[4];

/* C runtime */
extern int __cdecl _strcmpi(const char *left, const char *right);

/* gk3/GK3R_rest.c */
extern int application_instance;
extern uint16_t resource_language_id;

/* platform/settings.c */
extern uint32_t *__thiscall construct_settings_context(uint32_t *object);
extern uint32_t *__thiscall destroy_settings_context(uint32_t *object);
extern void *__thiscall load_display_options_from_settings(uint32_t **object, void *result);
extern int *__thiscall load_window_position_from_settings(uint32_t **object, int *result);

/* platform/command_line_options.c */
extern int __cdecl tokenize_command_line(uint8_t *command_line, int *tokens);
extern int __cdecl matches_localized_command_line_option(
    unsigned int resource_id, char *argument);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* common/runtime_string.c */
extern void __thiscall destroy_runtime_string(RuntimeString *string);

int __thiscall destroy_string_vector(int *token_words)
{
  uint32_t *tokens = (uint32_t *)(void *)token_words;
  const uint32_t begin = tokens[1];
  const uint32_t end = tokens[2];

  for (uint32_t address = begin; address < end;
       address += sizeof(RuntimeString)) {
    RuntimeString *token = (RuntimeString *)(uintptr_t)address;
    destroy_runtime_string(token);
  }

  free_tracked_memory((int)begin);
  tokens[1] = 0;
  tokens[2] = 0;
  tokens[3] = 0;
  return 0;
}

int __cdecl matches_localized_command_line_option(unsigned int resource_id,
                                                   char *argument)
{
  char localized_option[256] = {0};
  HINSTANCE instance = (HINSTANCE)(intptr_t)application_instance;
  HRSRC resource = NULL;

  if (instance && resource_language_id) {
    resource = FindResourceExA(
        instance, (LPCSTR)RT_STRING,
        MAKEINTRESOURCEA((resource_id >> 4) + 1), (WORD)resource_language_id);
  }

  bool loaded_localized_option = false;
  if (resource) {
    HGLOBAL loaded_resource = LoadResource(instance, resource);
    const WCHAR *entry = loaded_resource
        ? (const WCHAR *)LockResource(loaded_resource)
        : NULL;
    if (entry) {
      loaded_localized_option = true;
      for (unsigned int index = 0; index < (resource_id & 0x0F); ++index)
        entry += (unsigned int)*entry + 1;

      const int character_count = *entry++;
      const int byte_count = WideCharToMultiByte(
          CP_ACP, 0, entry, character_count, localized_option,
          (int)sizeof(localized_option) - 1, NULL, NULL);
      if (byte_count > 0)
        localized_option[byte_count] = '\0';
    }
  }
  if (!loaded_localized_option && instance) {
    LoadStringA(instance, resource_id, localized_option,
                (int)sizeof(localized_option));
  }

  const char *option = argument ? argument : Key;
  return option[0] == '-'
      && _strcmpi(localized_option, option + 1) == 0;
}

int __cdecl tokenize_command_line(uint8_t *command_line, int *token_vector)
{
  if (!command_line)
    return 0;

  CommandLineTokens *tokens = (CommandLineTokens *)token_vector;
  uint8_t *token_start = command_line;
  uint8_t *cursor = command_line;
  int token_count = 0;

  for (;;) {
    while (*cursor && *cursor != ' ' && *cursor != '\t'
           && !(*cursor == '/' && cursor[1] == '/'))
      ++cursor;

    if (cursor != token_start) {
      const size_t length = (size_t)(cursor - token_start);
      uint32_t *string_memory = allocate_tracked_memory((int)length + 2);
      uint8_t *string_buffer = (uint8_t *)string_memory;
      string_buffer[0] = 0;
      memcpy(string_buffer + 1, token_start, length);
      string_buffer[length + 1] = '\0';

      if (tokens->end == tokens->capacity) {
        const size_t old_count = tokens->begin
            ? (tokens->end - tokens->begin) / sizeof(CommandLineToken)
            : 0;
        const size_t old_capacity = tokens->begin
            ? (tokens->capacity - tokens->begin) / sizeof(CommandLineToken)
            : 0;
        const size_t new_capacity = old_capacity ? old_capacity * 2 : 4;
        CommandLineToken *new_tokens = (CommandLineToken *)
            allocate_tracked_memory((int)(new_capacity * sizeof(*new_tokens)));
        if (old_count)
          memcpy(new_tokens, (const void *)(uintptr_t)tokens->begin,
                 old_count * sizeof(*new_tokens));
        if (tokens->begin)
          free_tracked_memory((int)tokens->begin);
        tokens->begin = (uint32_t)(uintptr_t)new_tokens;
        tokens->end = tokens->begin
            + (uint32_t)(old_count * sizeof(*new_tokens));
        tokens->capacity = tokens->begin
            + (uint32_t)(new_capacity * sizeof(*new_tokens));
      }

      CommandLineToken *token =
          (CommandLineToken *)(uintptr_t)tokens->end;
      token->reserved = 0;
      token->text = (uint32_t)(uintptr_t)(string_buffer + 1);
      token->size = (uint32_t)length;
      token->capacity = (uint32_t)(length < 16 ? 16 : length);
      tokens->end += sizeof(*token);
      ++token_count;
    }

    if (!*cursor || (*cursor == '/' && cursor[1] == '/'))
      break;

    do {
      ++cursor;
    } while (*cursor == ' ' || *cursor == '\t');
    token_start = cursor;
  }

  return token_count;
}

uint32_t *__thiscall initialize_display_options(uint32_t *address)
{
  DisplayOptions *options = (DisplayOptions *)address;
  memset(options, 0, sizeof(*options));
  options->width = 640;
  options->height = 480;
  options->fullscreen = 1;
  return address;
}

int *__cdecl resolve_display_dimensions(
    int *result, char width_set, int width, char height_set, int height)
{
  static const struct {
    int width;
    int height;
  } common_resolutions[] = {
    { 512, 384 },
    { 640, 480 },
    { 800, 600 },
    { 1024, 768 },
    { 1280, 1024 },
    { 1600, 1200 },
  };

  int resolved_width;
  int resolved_height;
  if (width_set == height_set) {
    resolved_width = width;
    resolved_height = height;
  } else if (width_set) {
    resolved_width = width;
    resolved_height = 0;
    for (size_t index = 0;
         index < sizeof(common_resolutions) / sizeof(common_resolutions[0]);
         ++index) {
      if (common_resolutions[index].width == width) {
        resolved_height = common_resolutions[index].height;
        break;
      }
    }
    if (!resolved_height)
      resolved_height = (int)((double)384 / 512 * width);
  } else {
    resolved_height = height;
    resolved_width = 0;
    for (size_t index = 0;
         index < sizeof(common_resolutions) / sizeof(common_resolutions[0]);
         ++index) {
      if (common_resolutions[index].height == height) {
        resolved_width = common_resolutions[index].width;
        break;
      }
    }
    if (!resolved_width)
      resolved_width = (int)((double)512 / 384 * height);
  }

  if (!resolved_width || !resolved_height) {
    resolved_width = 640;
    resolved_height = 480;
  }
  result[0] = resolved_width;
  result[1] = resolved_height;
  return result;
}

int __cdecl parse_window_coordinate(char *value)
{
  if (!value || !*value || _strcmpi(value, "center") == 0)
    return 0x40000000;
  if (_strcmpi(value, "default") == 0)
    return (int)0x80000000u;
  if (isdigit((unsigned char)*value) || *value == '-')
    return atoi(value);
  return 0x40000000;
}

uint32_t *apply_display_command_line_options(uint8_t *command_line)
{
  uint32_t settings_object[4];
  CommandLineTokens tokens = {0};
  DisplayOptions loaded_options;
  DisplayOptions options;
  int position[2];
  int dimensions[2];
  bool width_set = false;
  bool height_set = false;

  construct_settings_context(settings_object);
  tokenize_command_line(command_line, (int *)&tokens);
  initialize_display_options((uint32_t *)&options);

  if (game_engine_address)
    memcpy(&options, (const void *)(uintptr_t)(game_engine_address + 112), sizeof(options));
  else
    memcpy(&options, load_display_options_from_settings((uint32_t **)settings_object, &loaded_options), sizeof(options));

  int width = options.width;
  int height = options.height;
  CommandLineToken *token = (CommandLineToken *)(uintptr_t)tokens.begin;
  CommandLineToken *end = (CommandLineToken *)(uintptr_t)tokens.end;

  while (token != end) {
    char *argument = (char *)(uintptr_t)token->text;
    if (!argument)
      argument = (char *)Key;

    if (matches_localized_command_line_option(0x59E3, argument)
        || matches_localized_command_line_option(0x59E9, argument)) {
      options.mode = 2;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59E4, argument)) {
      options.mode = 3;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59E8, argument)) {
      options.mode = 0;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59E5, argument)) {
      options.mode = 1;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59E6, argument)) {
      options.mode = 4;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59E7, argument)) {
      options.mode = 5;
      memset(options.unused, 0, sizeof(options.unused));
    } else if (matches_localized_command_line_option(0x59EC, argument)) {
      /* The resource option reads strtok's existing state in the original. */
      options.option_8 = atoi(strtok(NULL, " \t"));
      if (options.option_8)
        options.fullscreen = 1;
      if (options.mode >= 2 && (options.mode <= 3 || options.mode == 6))
        options.mode = 0;
    } else if (argument[0] == '-' && isdigit((unsigned char)argument[1])) {
      options.option_8 = atoi(argument + 1);
      if (options.option_8)
        options.fullscreen = 1;
      if (options.mode >= 2 && (options.mode <= 3 || options.mode == 6))
        options.mode = 0;
    } else if (matches_localized_command_line_option(0x3EB, argument)) {
      options.fullscreen = 0;
    } else if (matches_localized_command_line_option(0x3EC, argument)) {
      options.fullscreen = 1;
    } else if (matches_localized_command_line_option(0x3ED, argument)) {
      if (++token == end)
        break;
      const char *value = (const char *)(uintptr_t)token->text;
      width = atoi(value ? value : Key);
      width_set = true;
    } else if (matches_localized_command_line_option(0x3EE, argument)) {
      if (++token == end)
        break;
      const char *value = (const char *)(uintptr_t)token->text;
      height = atoi(value ? value : Key);
      height_set = true;
    }
    ++token;
  }

  int *adjusted = resolve_display_dimensions(
      dimensions, width_set, width, height_set, height);
  options.width = adjusted[0];
  options.height = adjusted[1];
  if (game_engine_address)
    memcpy((void *)(uintptr_t)(game_engine_address + 112), &options, sizeof(options));

  display_width = options.width;
  display_height = options.height;
  framebuffer_height = options.height;
  fullscreen_enabled = options.fullscreen;

  int *saved_position = load_window_position_from_settings((uint32_t **)settings_object, position);
  int x = saved_position[0];
  int y = saved_position[1];
  token = (CommandLineToken *)(uintptr_t)tokens.begin;

  while (token != end) {
    char *argument = (char *)(uintptr_t)token->text;
    if (!argument)
      argument = (char *)Key;

    if (matches_localized_command_line_option(0x5A64, argument)) {
      if (++token == end)
        break;
      char *value = (char *)(uintptr_t)token->text;
      x = parse_window_coordinate(value ? value : (char *)Key);
    } else if (matches_localized_command_line_option(0x5A6E, argument)) {
      if (++token == end)
        break;
      char *value = (char *)(uintptr_t)token->text;
      y = parse_window_coordinate(value ? value : (char *)Key);
    }
    ++token;
  }

  requested_window_x = x;
  requested_window_y = y;
  destroy_string_vector((int *)&tokens);
  return destroy_settings_context(settings_object);
}
