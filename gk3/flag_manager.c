#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t flag_manager_type_descriptor[];
extern int flag_manager_registry_adjustment;
extern void *__thiscall (*flag_manager_vtable)(void *object, char flags);
extern int game_engine_instance_address;
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                 uint32_t address);
extern void __thiscall destroy_tree_map(uint32_t *map);
extern int *__thiscall find_map_entry_node(uint32_t *map, int *node_address,
                                 int key_context);
extern int *__thiscall find_or_insert_map_entry(int map_address, int *result,
                                 int *key_context);
extern int __thiscall get_map_entry_value_address(void *map, uint32_t *key_context);
extern int __thiscall destroy_byte_vector(int *vector);
extern void __thiscall initialize_flag_map(uint32_t *object);
extern int __thiscall grow_std_string_storage(char *string_storage,
                                              uint32_t capacity, char mode);
extern uint8_t *__thiscall resize_byte_vector(int *vector, unsigned int count,
                                             uint8_t *fill_value);
extern uint32_t *__cdecl allocate_registered_flag_manager(int size);
extern int __thiscall erase_std_string_range(char *string, int position,
                                             int count);
extern uint32_t *__thiscall clear_tree_map(uint32_t *map);
extern uint32_t *__stdcall construct_sheep_case_signature(uint32_t *string, int case_id);
extern char *__thiscall get_noun_vocabulary_string(int id);
extern uint32_t *__thiscall assign_std_string_storage_from_c_string(uint32_t *string, const char *text,
                                       char *temporary);
extern uint32_t *__thiscall assign_std_string_storage(uint32_t *destination,
                                       uint32_t *source);
extern uint32_t *__thiscall append_std_string_storage_bytes(uint32_t *string, const void *text,
                                       int length);
extern char __thiscall is_sheep_source_syntax_valid(int ***sheep_compiler, int source);
extern int __thiscall release_compiled_sheep_reference(uint32_t *sheep_compiler, int compiled_id);
extern int __thiscall mark_compiled_sheep_inactive(uint32_t **sheep_compiler, int compiled_id);
extern int __thiscall compile_sheep_source(int *sheep_compiler, const char *name,
                                 uint32_t *source, uint32_t *compiled);
extern int __thiscall retain_compiled_sheep_source(uint32_t **sheep_compiler, int compiled_id);
extern char __thiscall compiled_sheep_uses_illegal_wait_function(uint32_t *sheep_compiler, int compiled_id,
                                  char rebuild);
extern int __thiscall start_sheep_evaluation(uint32_t **sheep_compiler, int compiled_id,
                                char *signature, int *result, int flags);
extern int __thiscall get_compiled_sheep_entry(uint32_t *sheep_compiler, int compiled_id);
extern int __thiscall get_sheep_evaluation_state(uint32_t *sheep_compiler, int compiled_id);
extern void __thiscall shutdown_sheep_evaluation(uint32_t **sheep_compiler, int compiled_id);
extern int __thiscall process_sheep_machine(int result);
extern int __thiscall is_topic_verb(int verb_id);
extern int __thiscall is_verb_type_4(int verb_id);
extern char *__cdecl get_verb_vocabulary_string(int verb_id);
extern char *__cdecl get_action_vocabulary_string(int token_id);
extern uint32_t *__thiscall get_last_current_noun_collection_entry(uint32_t *object);
extern int *__thiscall find_noun_object_by_id(uint32_t *object, int value);
extern char __thiscall has_applicable_topic_verb(int *object);
extern char __thiscall has_verb_registry_nvc_entry(uint32_t *object, int noun, int verb,
                                 int case_id, char active_ego);
extern char __cdecl is_global_flag_set(int flag_id);
extern int __thiscall write_source_message(const char *source, int line, int severity,
                                 int flags, const char *format, ...);
extern int __cdecl log_source_message(int source_file, int line, int severity,
                              int flags, const char *format, ...);
extern uint32_t *__thiscall begin_interface_debug_log(uint32_t *logger, const char *source,
                                       int line, int severity,
                                       uint32_t *arguments);
extern void __thiscall end_interface_debug_log(uint32_t *logger);
extern void __thiscall write_source_message_from_log_context(uint32_t *logger, char *text, size_t length);
extern uint32_t *__thiscall log_interface_debug_message(uint32_t *string, const char *text);
extern char __thiscall serialize_noun_field(uint8_t *serializer, const char *field_name,
                                  int *value, int *default_value);
extern char __thiscall serialize_verb_field(uint8_t *serializer, const char *field_name,
                                  int *value, int *default_value);
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                            const char *field_name,
                                            char *value, char *default_value);
extern int default_noun_id;
extern int default_verb_id;
extern char default_false_boolean_value;
extern char *Key;
extern uint32_t default_inventory_status_values[];
extern int last_default_inventory_status_value;
int __thiscall rebuild_compiled_sheep_cases(uint32_t *flag_manager);
extern int __thiscall set_flag_bit(uint32_t *state, int index, char enabled);
extern char __thiscall is_game_layer_active(char *layer, int layer_id);
extern int get_inventory_layer_instance(void);
extern int __thiscall refresh_inventory_layer(int object);
extern int __thiscall select_inventory_item_control(uint32_t *object);
extern char *__cdecl get_inventory_item_name(int inventory_id);
extern int __cdecl write_source_message(const char *source, int line, int severity,
                              int flags, const char *format, ...);
extern int __cdecl log_source_message(int source_file, int line, int severity,
                              int flags, const char *format, ...);
extern void __cdecl free_tracked_memory(int address);
char __thiscall set_flag_manager_inventory_status(
    uint32_t *flag_manager, int inventory_id, int status, char notify);

uint32_t *__thiscall initialize_flag_nvc_state(uint32_t *state)
{
  state[0] = 0;
  state[1] = 0;
  *((char *)state + 8) = 0;
  return state;
}

bool __thiscall serialize_flag_nvc_state(uint32_t *state,
                                         uint8_t *serializer, int flags)
{
  const uint32_t *methods = *(const uint32_t **)serializer;
  typedef void (__thiscall *BeginObjectSerialization)(uint8_t *, int);
  typedef void (__thiscall *EndObjectSerialization)(uint8_t *);
  const BeginObjectSerialization begin =
      (BeginObjectSerialization)(uintptr_t)methods[48 / sizeof(uint32_t)];
  const EndObjectSerialization end =
      (EndObjectSerialization)(uintptr_t)methods[52 / sizeof(uint32_t)];

  begin(serializer, flags);
  bool success = serialize_noun_field(serializer, "noun", (int *)state,
                            &default_noun_id) != 0;
  if (!serialize_verb_field(serializer, "verb", (int *)(state + 1), &default_verb_id))
    success = false;
  if (!serialize_boolean_field(serializer, "egoIsGabe",
                                (char *)state + 8, &default_false_boolean_value))
    success = false;
  end(serializer);
  return success;
}

int __cdecl is_gabe_or_grace_scene_active(void)
{
  uint32_t application_engine =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t scene =
      *(uint32_t *)(uintptr_t)(application_engine + 96);
  const int scene_id = *(int *)(uintptr_t)(scene + 32);
  return scene_id == 507 || scene_id == 508;
}

int __cdecl is_flag_enabled(int index)
{
  uint32_t *state = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return ((state[index / 32 + 10] >> (index % 32)) & 1u) != 0;
}

int __cdecl set_flag_enabled(int index, char enabled)
{
  uint32_t *state = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return set_flag_bit(state, index, enabled);
}

int __cdecl get_actor_location(int actor_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return *(int *)(void *)(state + 64 + actor_id * 4);
}

int __cdecl set_actor_location(int actor_id, int location_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  *(int *)(void *)(state + 64 + actor_id * 4) = location_id;
  return (int)(uintptr_t)state;
}

char __cdecl is_actor_on_map(int actor_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return state[actor_id + 200];
}

int __cdecl set_actor_on_map(int actor_id, char on_map)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  state[actor_id + 200] = (uint8_t)on_map;
  return (int)(uintptr_t)state;
}

char __cdecl was_location_visited(int location_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return state[location_id + 6356];
}

int __cdecl set_location_visited(int location_id, char visited)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  state[location_id + 6356] = (uint8_t)visited;
  return (int)(uintptr_t)state;
}

int __cdecl get_global_integer_variable(int variable_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return *(int *)(void *)(state + 6444 + variable_id * 4);
}

int __cdecl set_global_integer_variable(int variable_id, int value)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  *(int *)(void *)(state + 6444 + variable_id * 4) = value;
  return (int)(uintptr_t)state;
}

int __cdecl get_inventory_status(int inventory_id)
{
  uint8_t *state = (uint8_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return *(int *)(void *)(state + 6652 + inventory_id * 4);
}

char __cdecl set_inventory_status(int inventory_id, int value)
{
  uint32_t *state = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 56);
  return set_flag_manager_inventory_status(state, inventory_id, value, 0);
}

int __thiscall get_selected_inventory_item_for_active_ego(
    uint32_t *flag_manager)
{
  uint32_t application = *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t scene = *(uint32_t *)(uintptr_t)(application + 96);
  int scene_id = *(int *)(uintptr_t)(scene + 32);

  if (is_gabe_or_grace_scene_active())
    return (int)flag_manager[1805];
  if (scene_id == 529)
    return (int)flag_manager[1806];

  write_source_message("Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp", 1367,
             6, 0, "Ego is not Gabe or Grace.\n", 0xFFFFFFFF);
  return 0;
}

int __thiscall is_inventory_item_owned_by_active_ego(
    uint32_t *flag_manager, int inventory_id)
{
  int status = (int)flag_manager[inventory_id + 1663];
  if (is_gabe_or_grace_scene_active())
    return status == 3 || status == 4;
  return status == 2 || status == 4;
}

char __thiscall set_selected_inventory_item_for_active_ego(
    uint32_t *flag_manager, int inventory_id)
{
  uint32_t application = *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t scene = *(uint32_t *)(uintptr_t)(application + 96);
  int scene_id = *(int *)(uintptr_t)(scene + 32);

  if (is_gabe_or_grace_scene_active()) {
    if (!is_inventory_item_owned_by_active_ego(flag_manager, inventory_id)) {
      log_source_message(
          (int)(uintptr_t)
              "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp",
          1378, 5, 0, "Gabe does not have %s.",
          get_inventory_item_name(inventory_id));
    }
    flag_manager[1805] = (uint32_t)inventory_id;
  } else if (scene_id == 529) {
    if (!is_inventory_item_owned_by_active_ego(flag_manager, inventory_id)) {
      log_source_message(
          (int)(uintptr_t)
              "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp",
          1386, 5, 0, "Grace does not have %s.",
          get_inventory_item_name(inventory_id));
    }
    flag_manager[1806] = (uint32_t)inventory_id;
  } else {
    write_source_message("Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp", 1392,
               6, 0, "Ego is not Gabe or Grace.\n", 0xFFFFFFFF);
  }

  char active = is_game_layer_active(
      *(char **)(uintptr_t)(application + 72), 8);
  if (active)
    return (char)select_inventory_item_control((uint32_t *)(uintptr_t)get_inventory_layer_instance());
  return active;
}

char __thiscall set_flag_manager_inventory_status(
    uint32_t *flag_manager, int inventory_id, int status, char notify)
{
  flag_manager[inventory_id + 1663] = (uint32_t)status;
  if (get_selected_inventory_item_for_active_ego(flag_manager) == inventory_id
      && !is_inventory_item_owned_by_active_ego(flag_manager, inventory_id)) {
    set_selected_inventory_item_for_active_ego(flag_manager, 0);
  }

  uint32_t application = *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  char active = is_game_layer_active(
      *(char **)(uintptr_t)(application + 72), 8);
  if (active && notify)
    return (char)refresh_inventory_layer(get_inventory_layer_instance());
  return active;
}

char __thiscall get_flag_manager_byte(uint32_t *flag_manager, int index)
{
  return *(uint8_t *)(uintptr_t)(flag_manager[7] + (uint32_t)index);
}

uint8_t *__thiscall increment_flag_manager_byte(uint32_t *flag_manager,
                                                int index)
{
  uint8_t *value = (uint8_t *)(uintptr_t)(flag_manager[7] + (uint32_t)index);
  if (*value != 0xFF)
    ++*value;
  return value;
}

int __thiscall set_flag_manager_byte(uint32_t *flag_manager, int index,
                                     char value)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)flag_manager[7];
  bytes[index] = (uint8_t)value;
  return (int)(uintptr_t)bytes;
}

char __thiscall lookup_flag_manager_nvc_state(uint32_t *flag_manager,
                                               int noun_id, int property_id)
{
  uint32_t key_context[3];
  int node_address = noun_id;

  key_context[0] = (uint32_t)noun_id;
  key_context[1] = (uint32_t)property_id;
  key_context[2] = (uint32_t)is_gabe_or_grace_scene_active();
  find_map_entry_node(flag_manager + 1659, &node_address,
             (int)(uintptr_t)key_context);
  if ((uint32_t)node_address == flag_manager[1660])
    return 0;
  return *(uint8_t *)(uintptr_t)((uint32_t)node_address + 24);
}

int __thiscall get_or_create_flag_manager_nvc_state(
    uint32_t *flag_manager, int noun_id, int property_id)
{
  uint32_t *map = flag_manager + 1659;
  uint32_t lookup_context[3] = {
      (uint32_t)noun_id, (uint32_t)property_id,
      (uint32_t)is_gabe_or_grace_scene_active()};
  int lookup_key = noun_id;
  if (*find_map_entry_node(map, &lookup_key, (int)(uintptr_t)lookup_context)
      == (int)flag_manager[1660]) {
    int insertion_context[4] = {
        (uint32_t)noun_id, (uint32_t)property_id, lookup_context[2], 0};
    int inserted_node[2];
    int *entry = find_or_insert_map_entry((int)(uintptr_t)map, inserted_node,
                            insertion_context);
    int node_address = entry[0];
    *(uint8_t *)(uintptr_t)(node_address + 24) = 1;
    return node_address;
  }

  int insertion_context[4] = {
      (uint32_t)noun_id, (uint32_t)property_id, lookup_context[2], 0};
  int inserted_node[2];
  int node_address = *find_or_insert_map_entry((int)(uintptr_t)map, inserted_node,
                                insertion_context);
  ++*(uint8_t *)(uintptr_t)(node_address + 24);
  return node_address;
}

int __thiscall set_flag_manager_secondary_state(uint32_t *flag_manager,
                                                 int noun_id,
                                                 int property_id, char value)
{
  uint32_t key_context[4] = {
      (uint32_t)noun_id, (uint32_t)property_id,
      (uint32_t)is_gabe_or_grace_scene_active(), 0};
  int result_storage[2];
  int node_address = *find_or_insert_map_entry(
      (int)(uintptr_t)(flag_manager + 6636), result_storage,
      (int *)key_context);
  *(uint8_t *)(uintptr_t)(node_address + 24) = (uint8_t)value;
  return node_address;
}

int __thiscall increment_flag_manager_nvc_state(uint32_t *flag_manager,
                                                int noun_id, int property_id)
{
  uint32_t *map = flag_manager + 1659;
  uint32_t first_key[3] = {(uint32_t)noun_id, (uint32_t)property_id, 0};
  int lookup_key = noun_id;
  if (*find_map_entry_node(map, &lookup_key, (int)(uintptr_t)first_key)
      == (int)flag_manager[1660]) {
    *(uint8_t *)(uintptr_t)get_map_entry_value_address(map, first_key) = 1;
  } else {
    ++*(uint8_t *)(uintptr_t)get_map_entry_value_address(map, first_key);
  }

  uint32_t second_key[4] = {
      (uint32_t)noun_id, (uint32_t)property_id, 1, 0};
  lookup_key = noun_id;
  if (*find_map_entry_node(map, &lookup_key, (int)(uintptr_t)second_key)
      == (int)flag_manager[1660]) {
    int result_storage[2];
    int *entry = find_or_insert_map_entry((int)(uintptr_t)map, result_storage,
                            (int *)second_key);
    int node_address = entry[0];
    *(uint8_t *)(uintptr_t)(node_address + 24) = 1;
    return node_address;
  }

  int result_storage[2];
  int node_address = *find_or_insert_map_entry((int)(uintptr_t)map, result_storage,
                                (int *)second_key);
  ++*(uint8_t *)(uintptr_t)(node_address + 24);
  return node_address;
}

int __thiscall set_flag_manager_nvc_state_pair(uint32_t *flag_manager,
                                                int noun_id, int property_id,
                                                char value)
{
  uint32_t *map = flag_manager + 6636;
  uint32_t first_key[4] = {(uint32_t)noun_id, (uint32_t)property_id, 0, 0};
  int result_storage[2];
  int node_address = *find_or_insert_map_entry((int)(uintptr_t)map, result_storage,
                                (int *)first_key);
  *(uint8_t *)(uintptr_t)(node_address + 24) = (uint8_t)value;

  uint32_t second_key[4] = {
      (uint32_t)noun_id, (uint32_t)property_id, 1, (uint32_t)result_storage[1]};
  node_address = *find_or_insert_map_entry((int)(uintptr_t)map, result_storage,
                             (int *)second_key);
  *(uint8_t *)(uintptr_t)(node_address + 24) = (uint8_t)value;
  return node_address;
}

char __thiscall read_flag_manager_value(uint32_t *flag_manager, int key,
                                         int category)
{
  if (category == 344)
    return get_flag_manager_byte(flag_manager, key);
  return lookup_flag_manager_nvc_state(flag_manager, key, category);
}

uint8_t *__thiscall increment_flag_manager_value(uint32_t *flag_manager,
                                                 int key, int category)
{
  if (category == 344)
    return increment_flag_manager_byte(flag_manager, key);
  return (uint8_t *)(uintptr_t)get_or_create_flag_manager_nvc_state(
      flag_manager, key, category);
}

int __thiscall clear_compiled_sheep_cases(uint32_t *flag_manager)
{
  int compiled_id = (int)flag_manager[1];
  if (compiled_id != -1) {
    erase_std_string_range((char *)(void *)(flag_manager + 2), 0, -1);
    release_compiled_sheep_reference((uint32_t *)(uintptr_t)(
                   *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 88),
               compiled_id);
    mark_compiled_sheep_inactive((uint32_t **)(uintptr_t)(
                   *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 88),
               compiled_id);
    flag_manager[1] = UINT32_MAX;
  }
  return (int)flag_manager[1];
}

int __thiscall add_compiled_sheep_case(uint32_t *flag_manager, int case_id,
                                       char *expression)
{
  char *case_name;
  char *signature;
  const char *signature_text;
  uint32_t *code;
  char initialized_string[16];
  char temporary;
  int signature_length;
  size_t expression_length;
  int current_length;
  int capacity;
  char error_buffer[2000];
  char case_buffer[2000];
  char *signature_data;
  char added;

  if (!*expression) {
    case_name = get_noun_vocabulary_string(case_id);
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp",
               830, 5, 0,
               "Empty case logic for %s found! Fix yer NVCs.\n", case_name);
    return 0;
  }

  code = flag_manager + 2;
  if (!flag_manager[4]) {
    assign_std_string_storage_from_c_string((uint32_t *)(void *)initialized_string,
               "symbols\n{\n\tint n$, v$, c$, m$;\n}\n\ncode\n{\n",
               &temporary);
    assign_std_string_storage(code, (uint32_t *)(void *)initialized_string);
    tidy_std_string_storage(initialized_string, 1);
  }

  signature = (char *)construct_sheep_case_signature((uint32_t *)(void *)initialized_string,
                                 case_id);
  signature_length = (int)strlen("()");
  append_std_string_storage_bytes((uint32_t *)(void *)signature, "()", signature_length);
  signature_data = signature;
  if (!signature_data)
    signature_data = Key;
  signature_text = (const char *)(uintptr_t)flag_manager[3];
  if (!signature_text)
    signature_text = Key;

  if (strstr(signature_text, signature_data)) {
    case_name = get_noun_vocabulary_string(case_id);
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp",
               846, 6, 0,
               "Duplicate case logic for %s found! Fix yer NVCs.\n",
               case_name);
    added = 0;
  } else {
    expression_length = strlen(expression);
    (void)expression_length;
    sprintf(error_buffer,
            "#symbols{int n$,v$,c$,m$;}code{x$(){m$ = %s;}}", expression);
    if (is_sheep_source_syntax_valid((int ***)(uintptr_t)(
                       *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 88),
                   (int)(uintptr_t)error_buffer)) {
      current_length = (int)flag_manager[4];
      capacity = (int)flag_manager[5];
      if (current_length + (int)expression_length + 63 < capacity
          && code[3] < (uint32_t)(capacity + 1024))
        grow_std_string_storage((char *)(void *)code, (uint32_t)(capacity + 1024),
                                0);
      case_name = get_noun_vocabulary_string(case_id);
      sprintf(case_buffer,
              "\t// %s\n\tC%d$()\n\t{\n\t\tm$ = %s;\n\t}\n",
              case_name, case_id, expression);
      append_std_string_storage_bytes(code, case_buffer, (int)strlen(case_buffer));
      added = 1;
    } else {
      added = 0;
    }
  }

  tidy_std_string_storage((char *)(void *)signature, 1);
  return added;
}

void __thiscall finish_compiled_sheep_cases(uint32_t *flag_manager)
{
  append_std_string_storage_bytes(flag_manager + 2, "}\n", 2);
  rebuild_compiled_sheep_cases(flag_manager);
}

int __thiscall rebuild_compiled_sheep_cases(uint32_t *flag_manager)
{
  int compiled_id;
  char *source;
  uint32_t *sheep_compiler = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 88);

  if (!flag_manager[4])
    return 0;

  source = (char *)(uintptr_t)flag_manager[3];
  if (!source)
    source = Key;
  compiled_id = compile_sheep_source((int *)sheep_compiler, "Case Evaluation",
                           (uint32_t *)source,
                           (uint32_t *)(uintptr_t)flag_manager[4]);
  flag_manager[1] = (uint32_t)compiled_id;
  if (compiled_id == -1) {
    write_source_message("Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp", 913, 6,
               0, "Unable to commit/rebuild Sheep cases", 0xFFFFFFFF);
  } else {
    retain_compiled_sheep_source((uint32_t **)sheep_compiler, compiled_id);
  }

  if (compiled_id != -1
      && compiled_sheep_uses_illegal_wait_function(sheep_compiler, compiled_id, 1))
    clear_compiled_sheep_cases(flag_manager);
  return compiled_id;
}

char __thiscall evaluate_compiled_sheep_case(uint32_t *flag_manager,
                                              int noun_id, int verb_id,
                                              int case_id,
                                              uint8_t *condition_matched)
{
  char result = 0;
  *condition_matched = 0;
  if ((int)flag_manager[1] == -1)
    return result;

  uint32_t *sheep_compiler = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092) + 88);
  uint32_t signature_storage[4] = {0};
  uint32_t *signature_object = construct_sheep_case_signature(signature_storage, case_id);
  char *signature = (char *)(uintptr_t)signature_object[1];
  if (!signature)
    signature = Key;
  int evaluation_id = start_sheep_evaluation((uint32_t **)sheep_compiler,
                                 (int)flag_manager[1], signature, NULL, 0);
  tidy_std_string_storage((char *)(void *)signature_object, 1);
  if (evaluation_id == -1)
    return result;

  int *case_data = (int *)(uintptr_t)
      get_compiled_sheep_entry(sheep_compiler, (int)flag_manager[1]);
  uint32_t *evaluation_context =
      (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(case_data + 6);
  evaluation_context[0] = (uint32_t)noun_id;
  evaluation_context[1] = (uint32_t)verb_id;
  evaluation_context[2] = (uint32_t)case_id;
  evaluation_context[3] = 0;

  int evaluation_state = get_sheep_evaluation_state(sheep_compiler, evaluation_id);
  int execution_result = process_sheep_machine(evaluation_state);
  if (execution_result == 2) {
    if (evaluation_context[3] != 0)
      return 1;
  } else {
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp",
               1308, 6, 0,
               "Invalid sheep execution for NVC '%s' '%s' '%s' - result == %d (must be kDone).\\n",
               get_action_vocabulary_string(noun_id), get_verb_vocabulary_string(verb_id),
               get_noun_vocabulary_string(case_id), execution_result);
    shutdown_sheep_evaluation((uint32_t **)sheep_compiler, evaluation_id);
  }
  return result;
}

char __thiscall evaluate_flag_manager_condition(uint32_t *flag_manager,
                                                int noun_id, int verb_id,
                                                int condition_id)
{
  int effective_verb = verb_id;
  uint8_t compiled_match = 0;
  char result;

  if (is_topic_verb(verb_id) && !is_verb_type_4(verb_id)) {
    uint32_t *application =
        (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
    uint32_t *verb_registry = (uint32_t *)(uintptr_t)application[13];
    if (has_verb_registry_nvc_entry(verb_registry, noun_id, verb_id, condition_id,
                   (char)is_gabe_or_grace_scene_active()))
      return 0;
    effective_verb = verb_id;
  }

  result = evaluate_compiled_sheep_case(flag_manager, noun_id, effective_verb,
                                        condition_id, &compiled_match);
  if (result || compiled_match)
    return result;

  if (condition_id <= 283) {
    if (condition_id == 283) {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      int *object = (int *)get_last_current_noun_collection_entry((uint32_t *)(uintptr_t)application[7]);
      int *entry = find_noun_object_by_id((uint32_t *)object, noun_id);
      return has_applicable_topic_verb(entry)
          && lookup_flag_manager_nvc_state(flag_manager, noun_id, 252);
    }
    if (condition_id <= 83) {
      switch (condition_id) {
        case 9:
          return read_flag_manager_value(flag_manager, noun_id,
                                         effective_verb) == 0;
        case 50:
        case 57:
          return read_flag_manager_value(flag_manager, noun_id,
                                         effective_verb) == 1;
        case 58:
          return read_flag_manager_value(flag_manager, noun_id,
                                         effective_verb) == 2;
        case 83:
          return 1;
        default:
          return result;
      }
    }
    if (condition_id == 227) {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      char *layers = (char *)(uintptr_t)application[18];
      return is_game_layer_active(layers, 1)
          || is_game_layer_active(layers, 10);
    }
    if (condition_id == 281 || condition_id == 282) {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      int *object = (int *)get_last_current_noun_collection_entry((uint32_t *)(uintptr_t)application[7]);
      int *entry = find_noun_object_by_id((uint32_t *)object, noun_id);
      int present = has_applicable_topic_verb(entry);
      if (condition_id == 282)
        return present;
      return present && !lookup_flag_manager_nvc_state(flag_manager, noun_id, 252);
    }
    return result;
  }

  if (condition_id > 998) {
    if (condition_id == 1219)
      return read_flag_manager_value(flag_manager, noun_id,
                                     effective_verb) != 0;
    return condition_id == 1484 || condition_id == 1487;
  }

  switch (condition_id) {
    case 998: {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      int *object = (int *)get_last_current_noun_collection_entry((uint32_t *)(uintptr_t)application[7]);
      int *entry = find_noun_object_by_id((uint32_t *)object, noun_id);
      return !has_applicable_topic_verb(entry);
    }
    case 519:
      return (char)is_gabe_or_grace_scene_active();
    case 616: {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      uint32_t *scene = (uint32_t *)(uintptr_t)application[24];
      return (char)(scene[8] == 529);
    }
    case 687: {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      char *layers = (char *)(uintptr_t)application[18];
      return is_game_layer_active(layers, 1)
          || is_game_layer_active(layers, 10)
          || is_game_layer_active(layers, 8);
    }
    case 991: {
      uint32_t *application =
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      return is_game_layer_active((char *)(uintptr_t)application[18], 8);
    }
    default:
      return result;
  }
}

char __thiscall should_run_sheep_case(uint32_t *flag_manager,
                                      uint32_t *actor_id,
                                      int case_context, int case_index,
                                      char advance)
{
  (void)case_context;
  char result = 0;
  int next_index = case_index;
  char condition;
  int ready;

  if (advance && flag_manager[1807] > (uint32_t)case_index)
    return 0;

  switch (case_index) {
    case 0:
      goto matched;
    case 1:
      if (*actor_id != 28
          || !lookup_flag_manager_nvc_state(flag_manager, 276, 174)
          || !lookup_flag_manager_nvc_state(flag_manager, 1024, 118)
          || !lookup_flag_manager_nvc_state(flag_manager, 978, 187)
          || (!lookup_flag_manager_nvc_state(flag_manager, 920, 180)
              && !lookup_flag_manager_nvc_state(flag_manager, 881, 180)
              && !lookup_flag_manager_nvc_state(flag_manager, 880, 180))
          || (uint8_t)lookup_flag_manager_nvc_state(flag_manager, 179, 225) <= 1
          || !lookup_flag_manager_nvc_state(flag_manager, 519, 250)
          || !lookup_flag_manager_nvc_state(flag_manager, 655, 252))
        return 0;
      condition = lookup_flag_manager_nvc_state(flag_manager, 403, 252);
      goto compare_condition;
    case 2:
      if (*actor_id != 28 || !lookup_flag_manager_nvc_state(flag_manager, 2, 285)
          || !lookup_flag_manager_nvc_state(flag_manager, 796, 240)
          || !lookup_flag_manager_nvc_state(flag_manager, 796, 280))
        return 0;
      if ((uint8_t)lookup_flag_manager_nvc_state(flag_manager, 978, 187) > 1)
        goto matched;
      if (is_global_flag_set(64))
        goto matched;
      return 0;
    case 3:
      if (*actor_id != 47
          || ((!lookup_flag_manager_nvc_state(flag_manager, 760, 289)
               && !lookup_flag_manager_nvc_state(flag_manager, 75, 308)
               || !lookup_flag_manager_nvc_state(flag_manager, 1174, 335))
              && !lookup_flag_manager_nvc_state(flag_manager, 666, 285))
          || (uint8_t)lookup_flag_manager_nvc_state(flag_manager, 1306, 71) <= 1)
        return 0;
      ready = (uint8_t)lookup_flag_manager_nvc_state(flag_manager, 179, 71) <= 1;
      goto compare_ready;
    case 4:
      if (*actor_id != 48
          || (!lookup_flag_manager_nvc_state(flag_manager, 760, 289)
              && !lookup_flag_manager_nvc_state(flag_manager, 75, 308))
          || !lookup_flag_manager_nvc_state(flag_manager, 1174, 335)
          || !lookup_flag_manager_nvc_state(flag_manager, 666, 285)
          || !lookup_flag_manager_nvc_state(flag_manager, 1306, 252))
        return 0;
      condition = lookup_flag_manager_nvc_state(flag_manager, 1275, 6);
      goto compare_condition;
    case 5:
      if (*actor_id != 30 || flag_manager[1623] != 6)
        return 0;
      if (lookup_flag_manager_nvc_state(flag_manager, 538, 211))
        goto matched;
      return 0;
    case 6:
      if (*actor_id != 30 || lookup_flag_manager_nvc_state(flag_manager, 179, 255) != 1)
        return 0;
      if (lookup_flag_manager_nvc_state(flag_manager, 796, 291) == 1)
        goto matched;
      return 0;
    case 7:
      if (*actor_id != 33
          || (uint8_t)lookup_flag_manager_nvc_state(flag_manager, 909, 170) <= 1
          || !lookup_flag_manager_nvc_state(flag_manager, 559, 164)
          || !lookup_flag_manager_nvc_state(flag_manager, 732, 187)
          || (uint8_t)lookup_flag_manager_nvc_state(flag_manager, 757, 170) <= 1
          || !lookup_flag_manager_nvc_state(flag_manager, 735, 71))
        return 0;
      *actor_id = 14;
      result = 1;
      goto advance_if_requested;
    case 8:
      if (*actor_id != 30)
        return 0;
      condition = lookup_flag_manager_nvc_state(flag_manager, 866, 303);
      goto compare_condition;
    case 9:
      if (*actor_id != 30 || flag_manager[1616] != 7)
        return 0;
      condition = lookup_flag_manager_nvc_state(flag_manager, 416, 71);
      goto compare_condition;
    case 10:
      if (*actor_id == 31 && (int)flag_manager[1619] >= 6)
        goto matched;
      return 0;
    case 11:
      if (*actor_id != 30)
        return 0;
      if (is_inventory_item_owned_by_active_ego(flag_manager, 8))
        goto matched;
      return 0;
    case 12:
      if (*actor_id != 31)
        return 0;
      if (is_global_flag_set(28))
        goto matched;
      return 0;
    case 13:
      if (*actor_id != 30
          || !lookup_flag_manager_nvc_state(flag_manager, 529, 300)
          || !lookup_flag_manager_nvc_state(flag_manager, 529, 295)
          || !lookup_flag_manager_nvc_state(flag_manager, 529, 286)
          || !lookup_flag_manager_nvc_state(flag_manager, 529, 250)
          || !lookup_flag_manager_nvc_state(flag_manager, 529, 260))
        return 0;
      if (lookup_flag_manager_nvc_state(flag_manager, 529, 269))
        goto matched;
      return 0;
    case 14:
      if (*actor_id != 27)
        return 0;
      if (lookup_flag_manager_nvc_state(flag_manager, 1277, 6) == 2)
        goto matched;
      return 0;
    case 15:
      if (*actor_id != 30)
        return 0;
      condition = lookup_flag_manager_nvc_state(flag_manager, 218, 108);
      goto compare_condition;
    case 16:
      if (*actor_id == 30 && (int)flag_manager[543] > 0)
        goto matched;
      return 0;
    default:
      return result;
  }

compare_condition:
  ready = condition == 0;
compare_ready:
  if (ready)
    return 0;
matched:
  result = 1;
advance_if_requested:
  if (advance) {
    flag_manager[1807] = (uint32_t)next_index;
    ++flag_manager[1807];
  }
  return result;
}

uint32_t *__thiscall log_flag_manager_sheep_code(uint32_t *flag_manager,
                                                  uint32_t *arguments)
{
  uint32_t logger[4];
  char *code;
  size_t code_length;

  begin_interface_debug_log(logger,
             "Z:\\Proj\\GK3\\gk3app\\Source\\FlagMgr.cpp", 1230, 7,
             arguments);
  if ((int)flag_manager[1] == -1) {
    log_interface_debug_message(logger, "<no sheep code>\n");
  } else {
    code = (char *)(uintptr_t)flag_manager[3];
    if (!code)
      code = Key;
    code_length = flag_manager[4];
    write_source_message_from_log_context(logger, code, code_length);
  }
  end_interface_debug_log(logger);
  return flag_manager;
}

uint32_t *__thiscall reset_flag_manager_state(uint32_t *flag_manager)
{
  uint8_t *bytes_begin = (uint8_t *)(uintptr_t)flag_manager[7];
  uint8_t *bytes_end = (uint8_t *)(uintptr_t)flag_manager[8];
  if (bytes_begin != bytes_end)
    memset(bytes_begin, 0, (size_t)(bytes_end - bytes_begin));

  memset(flag_manager + 10, 0, 0x18);
  memset(flag_manager + 16, 0, 0x88);
  memset(flag_manager + 50, 0, 0x22);
  memset(flag_manager + 59, 0, 0x17E8);
  memset(flag_manager + 1589, 0, 0x55);
  memset(flag_manager + 1611, 0, 0xC0);
  flag_manager[1807] = 0;
  flag_manager[1805] = 0;
  flag_manager[1806] = 0;

  uint32_t *default_values = default_inventory_status_values;
  uint32_t *inventory_status = flag_manager + 1663;
  do {
    *inventory_status++ = *default_values++;
  } while (default_values <= (uint32_t *)&last_default_inventory_status_value);
  return clear_tree_map(flag_manager + 1659);
}

uint32_t *__thiscall destroy_flag_manager_members(uint32_t *flag_manager)
{
  flag_manager[0] = (uint32_t)(uintptr_t)&flag_manager_vtable;
  destroy_tree_map(flag_manager + 1659);
  destroy_byte_vector((int *)(void *)(flag_manager + 6));
  tidy_std_string_storage((char *)(void *)flag_manager + 12, 1);
  return erase_map_entry_impl(
      flag_manager_type_descriptor,
      (uint32_t)flag_manager_registry_adjustment
          + ((uintptr_t)flag_manager != 0
                 ? (uint32_t)(uintptr_t)(flag_manager + 1)
                 : 0));
}

void *__thiscall destroy_flag_manager(void *object, char flags)
{
  destroy_flag_manager_members((uint32_t *)object);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)object);
  return object;
}

int __thiscall set_flag_bit(uint32_t *state, int index, char enabled)
{
  int bit = (int)(1u << (index % 32));
  if (enabled != 0) {
    state[index / 32 + 10] |= (uint32_t)bit;
    return bit;
  }
  bit = ~bit;
  state[index / 32 + 10] &= (uint32_t)bit;
  return bit;
}

uint8_t *__thiscall initialize_flag_manager_storage(int *object)
{
  uint8_t fill_value = 0;
  char *string_storage = (char *)(void *)object + 12;
  uint32_t *string_capacity = (uint32_t *)(void *)(string_storage + 8);

  object[1] = -1;
  if (*string_capacity < 0x400)
    grow_std_string_storage(string_storage, 1024, 0);
  return resize_byte_vector(object + 6, 0x553u, &fill_value);
}

int __thiscall construct_registered_flag_manager(int object, int unused)
{
  char default_value;

  find_or_create_registry_entry(flag_manager_type_descriptor,
                                (uint32_t)flag_manager_registry_adjustment + (uint32_t)object + 4);
  *(uint8_t *)(uintptr_t)(object + 8) = (uint8_t)default_value;
  tidy_std_string_storage((char *)(uintptr_t)(object + 12), 0);
  *(uint32_t *)(uintptr_t)(object + 28) = 0;
  *(uint8_t *)(uintptr_t)(object + 24) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 32) = 0;
  *(uint32_t *)(uintptr_t)(object + 36) = 0;
  *(uint8_t *)(uintptr_t)(object + 6636) = (uint8_t)default_value;
  *(uint8_t *)(uintptr_t)(object + 6637) = (uint8_t)default_value;
  *(uint8_t *)(uintptr_t)(object + 6644) = 0;
  initialize_flag_map((uint32_t *)(uintptr_t)(object + 6636));
  *(uint32_t *)(uintptr_t)object = (uint32_t)(uintptr_t)&flag_manager_vtable;
  initialize_flag_manager_storage((int *)(uintptr_t)object);
  return object;
}

uint32_t *__cdecl create_registered_flag_manager(void)
{
  uint32_t *memory = allocate_registered_flag_manager(7232);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_flag_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

int __thiscall construct_flag_manager(int object)
{
  char default_value;
  find_or_create_registry_entry(flag_manager_type_descriptor,
             (uint32_t)flag_manager_registry_adjustment + (uint32_t)object + 4);
  *(uint8_t *)(uintptr_t)(object + 8) = (uint8_t)default_value;
  tidy_std_string_storage((char *)(uintptr_t)(object + 12), 0);
  *(uint32_t *)(uintptr_t)(object + 28) = 0;
  *(uint8_t *)(uintptr_t)(object + 24) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 32) = 0;
  *(uint32_t *)(uintptr_t)(object + 36) = 0;
  *(uint8_t *)(uintptr_t)(object + 6636) = (uint8_t)default_value;
  *(uint8_t *)(uintptr_t)(object + 6637) = (uint8_t)default_value;
  *(uint8_t *)(uintptr_t)(object + 6644) = 0;
  initialize_flag_map((uint32_t *)(uintptr_t)(object + 6636));
  *(uint32_t *)(uintptr_t)object = (uint32_t)(uintptr_t)&flag_manager_vtable;
  initialize_flag_manager_storage((int *)(uintptr_t)object);
  reset_flag_manager_state((uint32_t *)(uintptr_t)object);
  return object;
}

uint32_t *__cdecl allocate_registered_flag_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(flag_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_flag_manager(void)
{
  uint32_t *memory = allocate_registered_flag_manager(7232);
  return memory
      ? (uint32_t *)(uintptr_t)construct_flag_manager((int)(uintptr_t)memory)
      : NULL;
}
