#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
  uint32_t reserved;
  uint32_t data;
  uint32_t length;
  uint32_t capacity;
} RuntimeString;

typedef struct {
  uint32_t mode;
  int32_t width;
  int32_t height;
  uint8_t fullscreen;
  uint8_t reserved[3];
  uint32_t unused[4];
  int32_t option_8;
} DisplayOptions;

/* gk3/GK3R_rest.c */
extern uint32_t dword_76C640[16];
extern int dword_76C63C;
extern uint32_t *off_6C1C08;
extern uint32_t *off_6C1C0C;
extern uint32_t *off_6C1C10;

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall erase_map_entry(uint32_t *registry,
                                             uint32_t address);

/* gk3/GK3R_rest.c */
extern void __thiscall construct_ini_settings_backend(
    uint32_t *settings_data);
extern void __thiscall release_and_clear_interface(uint32_t *settings_data);
extern void *__thiscall construct_resource_string(RuntimeString *string,
                                                   UINT resource_id);
extern int game_engine_address;
extern const char Key[4];
extern const char Str1[4];
extern uint32_t *__thiscall initialize_display_options(uint32_t *options);
extern int *__cdecl resolve_display_dimensions(
    int *result, char width_set, int width, char height_set, int height);
extern char __cdecl parse_display_mode_name(char *name, char **mode);
extern char __cdecl parse_iid_string(const char *text, LPIID identifier);
extern int __cdecl parse_window_coordinate(char *value);

/* common/runtime_string.c */
extern void __thiscall destroy_runtime_string(RuntimeString *string);

/* gk3/GK3R_rest.c */
extern char *__thiscall read_string_setting(
    uint32_t **settings, RuntimeString *result, char *section,
    CHAR *name, char *default_value);
extern char __thiscall select_settings_section(uint32_t *store, char *section);
extern char *__thiscall read_integer_setting_or_default(uint32_t *store, char *name,
                                  char *default_value);
extern char __thiscall read_boolean_setting_or_default(uint32_t *store, char *name,
                                  char default_value);

_Static_assert(sizeof(RuntimeString) == 16, "runtime string layout");
_Static_assert(sizeof(DisplayOptions) == 36, "display options size");

static bool open_game_settings_key(HKEY *result, const char *section,
                                  HKEY root)
{
  char path[512];
  const int length = snprintf(path, sizeof(path),
      "Software\\Sierra On-Line\\Gabriel Knight 3\\%s",
      section ? section : "");
  if (length < 0 || (size_t)length >= sizeof(path))
    return false;
  return RegOpenKeyExA(root, path, 0, KEY_QUERY_VALUE, result) == ERROR_SUCCESS;
}

static bool read_registry_dword(const char *section, const char *name,
                                DWORD *value)
{
  const HKEY roots[] = { HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE };
  for (size_t index = 0; index < sizeof(roots) / sizeof(roots[0]); ++index) {
    HKEY key;
    if (!open_game_settings_key(&key, section, roots[index]))
      continue;

    DWORD type = 0;
    DWORD size = sizeof(*value);
    const LSTATUS status = RegQueryValueExA(
        key, name, NULL, &type, (BYTE *)value, &size);
    RegCloseKey(key);
    if (status == ERROR_SUCCESS && type == REG_DWORD
        && size == sizeof(*value))
      return true;
  }
  return false;
}

char *__thiscall read_dword_setting(
    uint32_t **settings, char *section, CHAR *name, char *default_value)
{
  DWORD value;
  if (read_registry_dword(section, name, &value))
    return (char *)(uintptr_t)value;

  uint32_t *store = settings[3];
  select_settings_section(store, section);
  return read_integer_setting_or_default(store, name, default_value);
}

char __thiscall read_boolean_setting(
    uint32_t **settings, char *section, CHAR *name, char default_value)
{
  DWORD value;
  if (read_registry_dword(section, name, &value))
    return value != 0;

  uint32_t *store = settings[3];
  select_settings_section(store, section);
  return read_boolean_setting_or_default(store, name, default_value);
}

uint32_t *__thiscall construct_settings_context(uint32_t *object)
{
  find_or_create_registry_entry(
      dword_76C640,
      (uint32_t)(uintptr_t)((uint8_t *)object + dword_76C63C + 4));
  object[1] = (uint32_t)(uintptr_t)off_6C1C0C;
  construct_ini_settings_backend(object + 2);
  object[0] = (uint32_t)(uintptr_t)off_6C1C08;
  return object;
}

uint32_t *__thiscall destroy_settings_context(uint32_t *object)
{
  object[0] = (uint32_t)(uintptr_t)off_6C1C08;
  object[2] = (uint32_t)(uintptr_t)off_6C1C10;
  release_and_clear_interface(object + 3);
  object[1] = (uint32_t)(uintptr_t)off_6C1C0C;

  const uint32_t address = dword_76C63C
      + (object ? (uint32_t)(uintptr_t)(object + 1) : 0);
  return erase_map_entry(dword_76C640, address);
}

void *__thiscall load_display_options_from_settings(
    uint32_t **settings, void *result)
{
  DisplayOptions options;
  initialize_display_options((uint32_t *)&options);
  if (game_engine_address)
    memcpy(&options,
           (const void *)(uintptr_t)(game_engine_address + 112),
           sizeof(options));

  RuntimeString section = {0};
  RuntimeString key = {0};
  RuntimeString value = {0};
  construct_resource_string(&section, 0x2713);

  construct_resource_string(&key, 0x59E2);
  char *section_name = section.data
      ? (char *)(uintptr_t)section.data : (char *)Key;
  char *setting_name = key.data
      ? (char *)(uintptr_t)key.data : (char *)Key;
  read_string_setting(settings, &value,
                      section_name, (CHAR *)setting_name, (char *)Str1);
  char *mode = (char *)(uintptr_t)options.mode;
  parse_display_mode_name(value.data ? (char *)(uintptr_t)value.data
                                     : (char *)Key,
                          &mode);
  options.mode = (uint32_t)(uintptr_t)mode;
  destroy_runtime_string(&value);
  destroy_runtime_string(&key);

  construct_resource_string(&key, 0x5A28);
  setting_name = key.data ? (char *)(uintptr_t)key.data : (char *)Key;
  int width = (int)(intptr_t)read_dword_setting(
      settings, section_name, (CHAR *)setting_name, NULL);
  destroy_runtime_string(&key);

  construct_resource_string(&key, 0x5A32);
  setting_name = key.data ? (char *)(uintptr_t)key.data : (char *)Key;
  int height = (int)(intptr_t)read_dword_setting(
      settings, section_name, (CHAR *)setting_name, NULL);
  destroy_runtime_string(&key);

  int dimensions[2];
  resolve_display_dimensions(dimensions, width != 0, width,
                             height != 0, height);
  options.width = dimensions[0];
  options.height = dimensions[1];

  construct_resource_string(&key, 0x5A1E);
  setting_name = key.data ? (char *)(uintptr_t)key.data : (char *)Key;
  options.fullscreen = (uint8_t)read_boolean_setting(
      settings, section_name, (CHAR *)setting_name, 1);
  destroy_runtime_string(&key);

  construct_resource_string(&key, 0x59EC);
  setting_name = key.data ? (char *)(uintptr_t)key.data : (char *)Key;
  options.option_8 = (int)(intptr_t)read_dword_setting(
      settings, section_name, (CHAR *)setting_name, NULL);
  destroy_runtime_string(&key);

  if (options.mode == 6) {
    construct_resource_string(&key, 0x59EB);
    setting_name = key.data ? (char *)(uintptr_t)key.data : (char *)Key;
    read_string_setting(settings, &value, section_name,
                        (CHAR *)setting_name, (char *)Str1);
    if (value.length && parse_iid_string(
            (const char *)(uintptr_t)value.data,
            (LPIID)options.unused)) {
      options.mode = 6;
    } else {
      options.mode = 0;
    }
    destroy_runtime_string(&value);
    destroy_runtime_string(&key);
  }

  memcpy(result, &options, sizeof(options));
  destroy_runtime_string(&section);
  return result;
}

int *__thiscall load_window_position_from_settings(
    uint32_t **settings, int *result)
{
  RuntimeString section = {0};
  RuntimeString key = {0};
  RuntimeString value = {0};
  construct_resource_string(&section, 0x2713);
  construct_resource_string(&key, 0x5A64);
  char *section_name = section.data
      ? (char *)(uintptr_t)section.data : (char *)Key;
  char *setting_name = key.data
      ? (char *)(uintptr_t)key.data : (char *)Key;
  read_string_setting(settings, &value, section_name,
                      (CHAR *)setting_name, (char *)Str1);
  result[0] = parse_window_coordinate(
      value.data ? (char *)(uintptr_t)value.data : (char *)Key);
  destroy_runtime_string(&value);
  destroy_runtime_string(&section);
  destroy_runtime_string(&key);

  construct_resource_string(&section, 0x2713);
  construct_resource_string(&key, 0x5A6E);
  section_name = section.data
      ? (char *)(uintptr_t)section.data : (char *)Key;
  setting_name = key.data
      ? (char *)(uintptr_t)key.data : (char *)Key;
  read_string_setting(settings, &value, section_name,
                      (CHAR *)setting_name, (char *)Str1);
  result[1] = parse_window_coordinate(
      value.data ? (char *)(uintptr_t)value.data : (char *)Key);
  destroy_runtime_string(&value);
  destroy_runtime_string(&section);
  destroy_runtime_string(&key);
  return result;
}
