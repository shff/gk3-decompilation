#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_765C18[];
extern int game_state_base_offset_adjustment __asm__("dword_765C14");
extern int hands_off_state_type_descriptor[15] __asm__("dword_765B90");
extern int action_skipper_type_descriptor[15] __asm__("dword_765BD8");
extern int game_engine_instance_address __asm__("dword_765A2C");
extern uint32_t game_state_transition_callbacks[] __asm__("dword_753FD8");
extern int __cdecl destroy_action_skipper(uint32_t *object);
extern int __cdecl release_hands_off_state(uint32_t *object);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern uint32_t *__thiscall advance_segmented_storage_iterator(
    uint32_t *iterator);
extern uint32_t *__thiscall decrement_segmented_storage_iterator(
    uint32_t *iterator);
extern void __thiscall release_segmented_storage(int storage);
extern unsigned int __thiscall ensure_segmented_storage_capacity(
    uint32_t *storage, int required_slots);
extern int __thiscall resize_game_state_stack(int *stack,
                                               unsigned int count,
                                               int default_value);
extern int __thiscall adjust_segmented_storage_iterator(int *iterator,
                                                        int offset)
    __asm__("sub_41F561");
extern uint32_t *__thiscall initialize_collection_serialization_context(
    uint32_t *context, int serializer, const char *field_name, int flags)
    __asm__("sub_56C570");
extern void __thiscall destroy_collection_serialization_context(int context)
    __asm__("sub_56C720");
extern uint8_t *__cdecl append_string_suffix(uint8_t *result, char *first,
                                             char *suffix)
    __asm__("sub_40157E");
extern char __cdecl serialize_array_count_field(uint8_t *serializer,
                                                const char *field_name,
                                                int *value,
                                                int *default_value)
    __asm__("sub_404836");
extern uint8_t *__cdecl append_string_storage(uint8_t *result, char *first,
                                              uint8_t *second)
    __asm__("sub_404349");
extern int __cdecl format_integer_string(int string_storage, int value)
    __asm__("sub_56CE60");
extern int __cdecl find_string_index(int strings, int count, int value,
                                     char flags) __asm__("sub_55B54A");
extern void __thiscall replace_playing_action_state_lock(int *state_lock,
                                                        int value)
    __asm__("sub_409304");
extern void __thiscall replace_skipping_action_state_lock(int *state_lock,
                                                         int value)
    __asm__("sub_409344");
extern int __thiscall tidy_std_string_storage(char *string_storage,
                                               char mode);
extern char *__thiscall assign_std_string_storage(char *storage,
                                                  const char *value,
                                                  size_t length);
extern int log_engine_message(int engine_address, const char *format, ...);
extern int game_engine_address;
extern int game_state_symbol_default[8] __asm__("dword_6C24D8");
extern char *game_state_names[70] __asm__("off_7534BC");
extern char byte_6A6454;
extern const char Key[4];
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                           const char *field_name,
                                           char *value,
                                           char *default_value);
extern void __thiscall replace_playing_movie_state_lock(int *state_lock,
                                                         int replacement);
extern void __thiscall replace_sidney_hands_off_state_lock(
    int *state_lock, int replacement);
extern int is_game_engine_initialized(void) __asm__("sub_4085E4");
extern int __cdecl log_source_message(int source, int line, int severity,
                                      size_t reserved, const char *format, ...)
    __asm__("sub_5574A3");
extern void __cdecl free_tracked_memory(int address);

int game_state_transition_is_available(void);
uint32_t *__thiscall construct_game_state_stack(uint32_t *stack,
                                                uint8_t *initial_value);
uint32_t *__thiscall push_game_state_stack_value(uint32_t *stack,
                                                  uint32_t *value);
void __thiscall pop_game_state_stack_value(uint32_t *stack);
char __thiscall serialize_game_state_stack(uint8_t *serializer,
                                            const char *field_name,
                                            uint32_t stack, char flags);
char __thiscall read_serialized_game_state_stack_length(
    uint8_t *serializer, uint32_t stack, char *field_context);
char __thiscall read_serialized_game_state_stack_values(
    uint8_t *serializer, int begin, int end, int *current, int capacity,
    char current_page_flag, int page_cursor, int *directory_cursor,
    int directory_capacity, char *field_context);
char __thiscall serialize_game_state_symbol(uint8_t *serializer,
                                             const char *field_name,
                                             int *state,
                                             int *default_state);
char __cdecl serialize_playing_action_state_lock(uint8_t *serializer,
                                                  const char *field_name,
                                                  int *state_lock);
char __cdecl serialize_skipping_action_state_lock(uint8_t *serializer,
                                                   const char *field_name,
                                                   int *state_lock);
char __cdecl serialize_playing_movie_state_lock(uint8_t *serializer,
                                                 const char *field_name,
                                                 int *state_lock);
char __cdecl serialize_sidney_hands_off_state_lock(uint8_t *serializer,
                                                    const char *field_name,
                                                    int *state_lock);
uint32_t *__thiscall allocate_game_state_stack_page(uint32_t *stack);
void __thiscall release_game_state_stack_entry_page(uint32_t *stack);
void __thiscall remove_game_state_stack_entry(uint32_t *stack);

void __thiscall transition_game_state(uint32_t *game_state, int next_state)
{
  int snapshot[2];
  uint32_t *current_state_address = (uint32_t *)(uintptr_t)game_state[9];

  snapshot[0] = game_state[7];
  snapshot[1] = game_state[8];
  adjust_segmented_storage_iterator(snapshot, -1);
  const int previous_state = (int)*current_state_address;
  push_game_state_stack_value(game_state + 2,
                              (uint32_t *)(void *)&next_state);

  const int callback_index = 4 * previous_state + next_state + previous_state;
  void (*transition)(void) =
      (void (*)(void))(uintptr_t)game_state_transition_callbacks[callback_index];
  if (transition)
    transition();
  else
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\GameState.cpp",
               442, 5, 0,
               "GameState :: DoTransition: illegal transition from %d to %d\n",
               previous_state, next_state);
}

void __thiscall return_to_previous_game_state(uint32_t *game_state,
                                               int unused)
{
  (void)unused;
  int snapshot[4];
  snapshot[0] = game_state[7];
  snapshot[1] = game_state[8];
  snapshot[2] = game_state[9];
  snapshot[3] = game_state[10];
  adjust_segmented_storage_iterator(snapshot, -1);
  int *current_state_address = (int *)(uintptr_t)game_state[9];
  const int previous_state = *current_state_address;
  pop_game_state_stack_value(game_state + 2);

  int transition_snapshot[4];
  transition_snapshot[0] = game_state[7];
  transition_snapshot[1] = game_state[8];
  transition_snapshot[2] = game_state[9];
  transition_snapshot[3] = game_state[10];
  adjust_segmented_storage_iterator(transition_snapshot, -1);

  const int next_state = *current_state_address;
  const int callback_index = 4 * previous_state + next_state + previous_state;
  void (*transition)(void) =
      (void (*)(void))(uintptr_t)game_state_transition_callbacks[callback_index];
  if (transition)
    transition();
  else
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\GameState.cpp",
               442, 5, 0,
               "GameState :: DoTransition: illegal transition from %d to %d\n",
               previous_state, next_state);
}

uint32_t *__thiscall set_game_state_and_transition(uint32_t *state_storage,
                                                    int next_state)
{
  uint32_t *application =
      (uint32_t *)(uintptr_t)(uint32_t)game_engine_instance_address;
  uint32_t *game_state = *(uint32_t **)(uintptr_t)(application[273] + 60);
  transition_game_state(game_state, next_state);
  *state_storage = (uint32_t)next_state;
  return state_storage;
}

uint32_t *__thiscall set_game_state_transition_value(uint32_t *state_storage,
                                                      int unused,
                                                      int state)
{
  (void)unused;
  *state_storage = (uint32_t)state;
  return state_storage;
}

void __thiscall restore_previous_game_state(int *state_storage)
{
  if (game_state_transition_is_available()) {
    uint32_t *application =
        (uint32_t *)(uintptr_t)(uint32_t)game_engine_instance_address;
    uint32_t *game_state = *(uint32_t **)(uintptr_t)(application[273] + 60);
    return_to_previous_game_state(game_state, *state_storage);
  }
}

int game_state_transition_is_available(void)
{
  uint32_t *application =
      (uint32_t *)(uintptr_t)(uint32_t)game_engine_instance_address;
  return is_game_engine_initialized()
      && *(uint32_t *)(uintptr_t)(application[273] + 60) != 0;
}

uint32_t *__thiscall construct_game_state(uint32_t *object)
{
  uint32_t state = 0;
  uint8_t initial_value = 0;

  find_or_create_registry_entry(
      unk_765C18,
      (uint32_t)(uintptr_t)object
          + (uint32_t)game_state_base_offset_adjustment);
  construct_game_state_stack(object + 2, &initial_value);
  object[0] = 0;
  object[1] = 0;
  push_game_state_stack_value(object + 2, &state);
  return object;
}

char __thiscall serialize_game_state_fields(uint32_t *object,
                                             uint8_t *serializer,
                                             int serialization_flags)
{
  (void)serialization_flags;
  uint32_t *methods = *(uint32_t **)(void *)serializer;
  ((void (__thiscall *)(uint8_t *, const char *, uint32_t, int *))
      (uintptr_t)methods[68 / 4])(
      serializer, "mActionSkipper", (uint32_t)(uintptr_t)object,
      action_skipper_type_descriptor);
  ((void (__thiscall *)(uint8_t *, const char *, uint32_t, int *))
      (uintptr_t)methods[68 / 4])(
      serializer, "mHandsOff", (uint32_t)(uintptr_t)(object + 1),
      hands_off_state_type_descriptor);
  return serialize_game_state_stack(
      serializer, "mStateStack", (uint32_t)(uintptr_t)(object + 2), 1);
}

int __thiscall clear_game_state_stack(uint32_t *stack)
{
  while (stack[11] != 0)
    remove_game_state_stack_entry(stack);
  return 0;
}

uint32_t *__thiscall construct_game_state_stack(uint32_t *stack,
                                                uint8_t *initial_value)
{
  *(uint8_t *)(void *)stack = *initial_value;
  for (int slot = 1; slot < 12; ++slot)
    stack[slot] = 0;
  return stack;
}

uint32_t *__thiscall push_game_state_stack_value(uint32_t *stack,
                                                  uint32_t *value)
{
  if (stack[11] == 0 || stack[7] == stack[6])
    allocate_game_state_stack_page(stack);
  advance_segmented_storage_iterator(stack + 5);

  int iterator[4] = {
      (int)stack[5], (int)stack[6], (int)stack[7], (int)stack[8]};
  adjust_segmented_storage_iterator(iterator, -1);
  uint32_t *entry = (uint32_t *)(uintptr_t)iterator[2];
  if (entry != NULL)
    *entry = *value;
  ++stack[11];
  return entry;
}

void __thiscall pop_game_state_stack_value(uint32_t *stack)
{
  if (stack[11] != 0) {
    int iterator[4] = {
        (int)stack[5], (int)stack[6], (int)stack[7], (int)stack[8]};
    adjust_segmented_storage_iterator(iterator, -1);
    release_game_state_stack_entry_page(stack);
  }
}

uint32_t *__thiscall allocate_game_state_stack_page(uint32_t *stack)
{
  uint32_t *page = allocate_tracked_memory(4096);
  uint32_t *result;
  uint32_t *page_directory_entry;
  uint32_t *page_begin;
  uint32_t *page_end;
  uint32_t *stack_cursor;

  if (stack[11] != 0) {
    const uint32_t directory_cursor = stack[8];
    if (directory_cursor >= stack[9] + 4 * stack[10] - 8) {
      const int required_slots =
          (int)((directory_cursor - stack[4]) / sizeof(uint32_t)) + 1;
      uint32_t *directory_begin = (uint32_t *)(uintptr_t)
          ensure_segmented_storage_capacity(stack, required_slots);
      page_directory_entry = &directory_begin[required_slots];
      *page_directory_entry = (uint32_t)(uintptr_t)page;
      page_directory_entry[1] = 0;
      stack[1] = directory_begin[0];
      stack[2] = stack[1] + 4096;
      stack[4] = (uint32_t)(uintptr_t)directory_begin;
      result = page;
      page_begin = page;
      page_end = page + 4096 / sizeof(uint32_t);
      stack_cursor = page;
    } else {
      page_directory_entry = (uint32_t *)(uintptr_t)(directory_cursor + 4);
      stack[8] = (uint32_t)(uintptr_t)page_directory_entry;
      *page_directory_entry = (uint32_t)(uintptr_t)page;
      page_directory_entry[1] = 0;
      result = page_directory_entry;
      page_begin = (uint32_t *)(uintptr_t)*page_directory_entry;
      page_end = page_begin + 4096 / sizeof(uint32_t);
      stack_cursor = page;
    }
  } else {
    uint32_t *directory = allocate_tracked_memory(32);
    stack[9] = (uint32_t)(uintptr_t)directory;
    stack[10] = 8;
    directory[3] = 0;
    directory[4] = (uint32_t)(uintptr_t)page;
    directory[5] = 0;
    page_directory_entry = &directory[4];
    page_begin = (uint32_t *)(uintptr_t)*page_directory_entry;
    page_end = page_begin + 4096 / sizeof(uint32_t);
    stack_cursor = page + 512;
    stack[1] = (uint32_t)(uintptr_t)page_begin;
    stack[2] = (uint32_t)(uintptr_t)page_end;
    stack[3] = (uint32_t)(uintptr_t)stack_cursor;
    stack[4] = (uint32_t)(uintptr_t)page_directory_entry;
    result = page_end;
  }

  stack[5] = (uint32_t)(uintptr_t)page_begin;
  stack[6] = (uint32_t)(uintptr_t)page_end;
  stack[7] = (uint32_t)(uintptr_t)stack_cursor;
  stack[8] = (uint32_t)(uintptr_t)page_directory_entry;
  return result;
}

void __thiscall remove_game_state_stack_entry(uint32_t *stack)
{
  int *previous_page = (int *)(uintptr_t)stack[4];
  advance_segmented_storage_iterator(stack + 1);
  if (stack[11]-- == 1) {
    release_segmented_storage((int)(uintptr_t)stack);
  } else if ((uint32_t)(uintptr_t)previous_page != stack[4]) {
    free_tracked_memory(*previous_page);
    *previous_page = 0;
  }
}

void __thiscall release_game_state_stack_entry_page(uint32_t *stack)
{
  int *previous_page = (int *)(uintptr_t)stack[8];
  decrement_segmented_storage_iterator(stack + 5);
  if (stack[11]-- == 1) {
    release_segmented_storage((int)(uintptr_t)stack);
  } else if ((uint32_t)(uintptr_t)previous_page != stack[8]) {
    free_tracked_memory(*previous_page);
    *previous_page = 0;
  }
}

char __thiscall read_serialized_game_state_stack_length(
    uint8_t *serializer, uint32_t stack, char *field_context)
{
  const char *context =
      *(const char **)(uintptr_t)(field_context + sizeof(uint32_t));
  if (context == NULL)
    context = Key;

  int count = *(int *)(uintptr_t)(stack + 44);
  uint8_t count_name_storage[16] = {0};
  const char *count_name = (const char *)(uintptr_t)
      *((uint32_t *)(void *)append_string_suffix(
          count_name_storage, (char *)(uintptr_t)context, "-count") + 1);
  if (count_name == NULL)
    count_name = Key;

  const char result = serialize_array_count_field(
      serializer, count_name, &count, &count);
  tidy_std_string_storage((char *)(void *)count_name_storage, 1);
  resize_game_state_stack((int *)(uintptr_t)stack, (unsigned int)count, 0);
  return result;
}

char __thiscall serialize_game_state_symbol(uint8_t *serializer,
                                             const char *field_name,
                                             int *state,
                                             int *default_state)
{
  uint8_t state_name_storage[16] = {0};
  state_name_storage[0] = (uint8_t)((uintptr_t)field_name >> 24);
  tidy_std_string_storage((char *)(void *)state_name_storage, 0);

  uint32_t *methods = *(uint32_t **)(void *)serializer;
  typedef char (__thiscall *SerializeStringMethod)(
      uint8_t *serializer, const char *field_name, uint8_t *string_storage,
      int flags);
  SerializeStringMethod serialize_string =
      (SerializeStringMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];

  if (serializer[4]) {
    const char *state_name = game_state_names[*state];
    assign_std_string_storage((char *)(void *)state_name_storage, state_name,
                              strlen(state_name));
    serialize_string(serializer, field_name, state_name_storage, 0);
    tidy_std_string_storage((char *)(void *)state_name_storage, 1);
    return 1;
  }

  char result = serialize_string(serializer, field_name, state_name_storage,
                                  0);
  if (result) {
    const char *state_name =
        *(const char **)(void *)(state_name_storage + sizeof(uint32_t));
    if (state_name == NULL)
      state_name = Key;
    const int parsed_state =
        find_string_index((int)(uintptr_t)game_state_names, 5,
                          (int)(uintptr_t)state_name, 0);
    if (parsed_state == -1) {
      log_engine_message(game_engine_address,
                         "Error: unable to convert value '%s' for key '%s'",
                         state_name, field_name);
      result = 0;
      *state = *default_state;
    } else {
      *state = parsed_state;
    }
  } else {
    *state = *default_state;
  }

  tidy_std_string_storage((char *)(void *)state_name_storage, 1);
  return result;
}

char __cdecl serialize_playing_action_state_lock(uint8_t *serializer,
                                                  const char *field_name,
                                                  int *state_lock)
{
  char locked = serializer[4] ? (char)(*state_lock != 0) : 0;
  char result = serialize_boolean_field(serializer, field_name, &locked,
                                        &byte_6A6454);
  if (!serializer[4] && locked) {
    uint32_t *transition = allocate_tracked_memory(sizeof(uint32_t));
    if (transition != NULL)
      set_game_state_transition_value(transition, 0, 1);
    replace_playing_action_state_lock(
        state_lock, (int)(uintptr_t)transition);
  }
  return result;
}

char __cdecl serialize_skipping_action_state_lock(uint8_t *serializer,
                                                   const char *field_name,
                                                   int *state_lock)
{
  char locked = serializer[4] ? (char)(*state_lock != 0) : 0;
  char result = serialize_boolean_field(serializer, field_name, &locked,
                                        &byte_6A6454);
  if (!serializer[4] && locked) {
    uint32_t *transition = allocate_tracked_memory(sizeof(uint32_t));
    if (transition != NULL)
      set_game_state_transition_value(transition, 0, 2);
    replace_skipping_action_state_lock(
        state_lock, (int)(uintptr_t)transition);
  }
  return result;
}

char __cdecl serialize_playing_movie_state_lock(uint8_t *serializer,
                                                 const char *field_name,
                                                 int *state_lock)
{
  char locked = serializer[4] ? (char)(*state_lock != 0) : 0;
  char result = serialize_boolean_field(serializer, field_name, &locked,
                                        &byte_6A6454);
  if (!serializer[4] && locked) {
    uint32_t *transition = allocate_tracked_memory(sizeof(uint32_t));
    if (transition != NULL)
      set_game_state_transition_value(transition, 0, 3);
    replace_playing_movie_state_lock(
        state_lock, (int)(uintptr_t)transition);
  }
  return result;
}

char __cdecl serialize_sidney_hands_off_state_lock(uint8_t *serializer,
                                                    const char *field_name,
                                                    int *state_lock)
{
  char locked = serializer[4] ? (char)(*state_lock != 0) : 0;
  char result = serialize_boolean_field(serializer, field_name, &locked,
                                        &byte_6A6454);
  if (!serializer[4] && locked) {
    uint32_t *transition = allocate_tracked_memory(sizeof(uint32_t));
    if (transition != NULL)
      set_game_state_transition_value(transition, 0, 4);
    replace_sidney_hands_off_state_lock(
        state_lock, (int)(uintptr_t)transition);
  }
  return result;
}

char __thiscall read_serialized_game_state_stack_values(
    uint8_t *serializer, int begin, int end, int *current, int capacity,
    char current_page_flag, int page_cursor, int *directory_cursor,
    int directory_capacity, char *field_context)
{
  int iterator[4] = {begin, end, (int)(uintptr_t)current, capacity};
  int index = 0;
  char success = 1;

  const char *context =
      *(const char **)(uintptr_t)(field_context + sizeof(uint32_t));
  if (context == NULL)
    context = Key;

  (void)current_page_flag;
  (void)page_cursor;
  (void)directory_capacity;

  while ((int *)(uintptr_t)iterator[2] != directory_cursor) {
    int *value = (int *)(uintptr_t)iterator[2];
    uint8_t index_storage[16] = {0};
    uint8_t field_name_storage[16] = {0};
    uint8_t *index_string =
        (uint8_t *)(uintptr_t)format_integer_string(
            (int)(uintptr_t)index_storage, index++);
    const char *field_name = (const char *)(uintptr_t)
        *((uint32_t *)(void *)append_string_storage(
            field_name_storage, (char *)(uintptr_t)context, index_string) + 1);
    if (field_name == NULL)
      field_name = Key;

    if (!serialize_game_state_symbol(serializer, field_name, value,
                                     game_state_symbol_default))
      success = 0;

    tidy_std_string_storage((char *)(void *)field_name_storage, 1);
    tidy_std_string_storage((char *)(void *)index_storage, 1);
    advance_segmented_storage_iterator((uint32_t *)(void *)iterator);
  }
  return success;
}

char __thiscall serialize_game_state_stack(uint8_t *serializer,
                                            const char *field_name,
                                            uint32_t stack, char flags)
{
  uint32_t field_context[6];
  initialize_collection_serialization_context(
      field_context, (int)(uintptr_t)serializer, field_name, flags);

  char success = read_serialized_game_state_stack_length(
      serializer, stack, (char *)(void *)field_context);
  if (!read_serialized_game_state_stack_values(
          serializer,
          *(int *)(uintptr_t)(stack + 4),
          *(int *)(uintptr_t)(stack + 8),
          *(int **)(uintptr_t)(stack + 12),
          *(int *)(uintptr_t)(stack + 16),
          *(char *)(uintptr_t)(stack + 20),
          *(int *)(uintptr_t)(stack + 24),
          *(int **)(uintptr_t)(stack + 28),
          *(int *)(uintptr_t)(stack + 32),
          (char *)(void *)field_context))
    success = 0;

  destroy_collection_serialization_context((int)(uintptr_t)field_context);
  return success;
}

uint32_t *allocate_registered_game_state(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_765C18,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_game_state(void)
{
  uint32_t *memory = allocate_registered_game_state(56);
  return memory ? construct_game_state(memory) : NULL;
}

uint32_t *__thiscall destroy_game_state(uint32_t *object)
{
  destroy_action_skipper(object);
  release_hands_off_state(object + 1);
  clear_game_state_stack(object + 2);
  return erase_map_entry_impl(
      unk_765C18,
      (uint32_t)(uintptr_t)object
          + (uint32_t)game_state_base_offset_adjustment);
}
