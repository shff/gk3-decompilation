#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t soundtrack_manager_type_descriptor[];
extern int soundtrack_manager_base_offset_adjustment;
extern uint32_t soundtrack_manager_vtable[];
extern uint32_t soundtrack_instance_vtable;
extern uint32_t soundtrack_instance_event_target_vtable;
extern uint32_t soundtrack_snapshot_vtable;
extern uint32_t broadcast_target_type_descriptor[];
extern int broadcast_target_base_offset_adjustment;
extern uint32_t registered_object_base_vtable[];
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t key);
extern const char Key[];
extern uint32_t soundtrack_instance_type_descriptor[15];
extern int soundtrack_instance_base_offset_adjustment;
extern uint32_t soundtrack_snapshot_type_descriptor[15];
extern int soundtrack_snapshot_base_offset_adjustment;
extern char soundtrack_snapshot_registry_shutdown_flag;
extern int registered_type_descriptor_count;
extern int game_engine_instance_address;
extern uint8_t *__thiscall construct_registered_object_base(uint8_t *object);
extern uint32_t *__stdcall allocate_soundtrack_list_node(uint32_t *previous,
                                                         uint32_t *next);
extern uint32_t *__cdecl allocate_registered_gconfig_file(int size);
extern uint8_t *__cdecl allocate_registered_soundtrack_snapshot(int size);
extern uint8_t *__cdecl deserialize_soundtrack_sound_entry(int entry);
extern int *__cdecl deserialize_soundtrack_wait_entry(uint32_t *entry);
extern int __thiscall construct_soundtrack_presentation_entry(int object);
extern int __thiscall find_map_value_impl(uint32_t *map, uint32_t key);
extern void __thiscall destroy_soundtrack_list_storage(uint32_t *list);
extern uint32_t *__thiscall erase_soundtrack_list_range(uint32_t *list, uint32_t *context,
                                      uint32_t *first, uint32_t *sentinel);
extern uint32_t *__thiscall append_soundtrack_manager_list_node(uint32_t *list, uint32_t *result,
                                       int list_end, uint32_t **value);
uint32_t *__thiscall reset_soundtrack_playback(int object);
extern int __stdcall find_soundtrack_list_entry_by_identifier(int16_t identifier, int list_address);
extern void __thiscall remove_soundtrack_instance_from_manager(uint32_t *collection, uint32_t **value);
extern int __thiscall append_soundtrack_snapshot_entry(int list_address, uint32_t *value);
extern char *__thiscall construct_named_gconfig_file(char *string, const char *value);
extern char __thiscall save_gconfig_file(const char *string, int mode);
extern uint32_t *__thiscall destroy_gconfig_file(uint32_t *string);
extern char __thiscall load_gconfig_file(uint32_t *string, int mode);
extern int *__thiscall replace_soundtrack_event_reference_and_queue_previous(int *reference, int mode);
extern int __thiscall tidy_std_string_storage(char *storage, char mode);
extern char *__thiscall assign_std_string_storage(char *storage,
                                                  const char *value,
                                                  size_t length);
extern int __thiscall add_soundtrack_snapshot_name(int string, uint8_t *value);
extern uint32_t *__thiscall find_or_create_registry_entry(uint32_t *registry,
                                       uint32_t address);
extern int *__thiscall register_runtime_type_descriptor(uint32_t *registry, int name,
                                  uint32_t *version, int object_size,
                                  int growth, int factory, int serializer,
                                  int first_flag, int second_flag,
                                  int *cookie);
extern void __thiscall destroy_runtime_type_descriptor(uint32_t *registry);
extern uint32_t *__stdcall allocate_soundtrack_list_node_with_links(uint32_t *previous, uint32_t *next);
extern int __thiscall initialize_registered_soundtrack_instance_active_object(int object, int mode);
extern int __thiscall initialize_soundtrack_instance_active_object(int object, int first, int second,
                                 int third, int flags, int context);
extern uint32_t *__thiscall destroy_soundtrack_instance_active_object(int object);
extern void __thiscall destroy_soundtrack_instance_node_list(uint32_t *collection);
extern int __thiscall clear_soundtrack_snapshot_member_array(int *collection);
extern char __cdecl destroy_soundtrack_instance_list_objects(uint32_t *first, uint32_t *sentinel,
                               char mode);
extern int __thiscall destroy_string_vector(int *vector);
extern char __thiscall serialize_soundtrack_snapshot_names(uint8_t *serializer, const char *field,
                                  unsigned int value, int flags);
extern char __thiscall serialize_soundtrack_snapshot_members(uint8_t *serializer, const char *field,
                                  unsigned int value, char flags);
extern int *__thiscall replace_event_reference_and_queue_previous(
    int *reference, int *replacement);
extern int __cdecl soundtrack_list_contains_instance(int list_address, uint32_t **value);
extern uint32_t *__thiscall get_first_config_entry(uint32_t *state, uint32_t **cursor);
extern uint32_t *__thiscall set_config_entry_iterator(uint32_t *cursor, uint32_t **state);
extern char *__thiscall get_config_entry_name(uint32_t *cursor);
extern int __thiscall get_next_config_entry(char *cursor, uint32_t **state);
extern int __thiscall select_or_create_gconfig_section(int state, char *section);
extern int __thiscall get_config_string_value(uint32_t *state, char *name, int fallback);
extern int __thiscall get_config_integer_value(uint32_t *state, char *name, int fallback);
extern int __thiscall get_config_boolean_value(uint32_t *state, char *name, int fallback);
extern int __thiscall parse_soundtrack_type_name(char *value, int *result);
extern uint32_t *__thiscall append_soundtrack_instance_list_node(uint32_t *list, uint32_t *result,
                                       int sentinel, int *value);
extern uint32_t *__thiscall append_soundtrack_presentation_sound(int list, int *result, int *value);
extern int __thiscall get_soundtrack_instance_load_result(uint32_t *instance);
extern int __thiscall get_elapsed_game_time(int object);
extern int __cdecl log_source_message(int source, int line, int severity,
                              int flags, const char *format, ...);
extern int __thiscall create_gconfig_section_entry(uint32_t *serializer, const char *name);
extern void __thiscall write_config_string_entry(uint32_t *serializer, char *name,
                                 const char *value);
extern void __thiscall write_config_integer_entry(uint32_t *serializer, char *name,
                                 int value);
extern const char *__cdecl soundtrack_type_name(int soundtrack_type);

void __thiscall set_soundtrack_instance_active(uint32_t *manager,
                                               int instance_address,
                                               char active);
int *__thiscall find_or_create_soundtrack_instance(uint32_t *manager,
                                                   int *wide_name);
int __thiscall register_soundtrack_instance_if_missing(uint32_t *manager,
                                                       int *wide_name);

int __thiscall soundtrack_member_count(uint32_t *members)
{
  const uint32_t begin = members[4];
  const uint32_t end = members[5];
  return begin != 0 ? (int)((end - begin) / sizeof(uint32_t)) : 0;
}

int __thiscall find_soundtrack_node_index(uint32_t *instance)
{
  uint32_t **sentinel = (uint32_t **)(uintptr_t)instance[28];
  uint32_t *node = *sentinel;
  uint32_t *target = (uint32_t *)(uintptr_t)instance[23];
  int index = 0;

  if (node == (uint32_t *)sentinel)
    return -1;
  while (node != target) {
    node = (uint32_t *)(uintptr_t)*node;
    ++index;
    if (node == (uint32_t *)sentinel)
      return -1;
  }
  return index;
}

uint32_t *__cdecl allocate_registered_soundtrack_instance(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(soundtrack_instance_type_descriptor, (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *__thiscall construct_soundtrack_instance(uint8_t *object,
                                                   char *name)
{
  uint8_t name_high_byte =
      (uint8_t)((uint32_t)(uintptr_t)name >> 24);
  uint32_t engine_address =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t context_object =
      *(uint32_t *)(uintptr_t)(engine_address + 68);
  int active_object_context =
      *(int *)(uintptr_t)(context_object + 32);
  uint32_t *instance = (uint32_t *)(void *)object;

  initialize_soundtrack_instance_active_object((int)(uintptr_t)object, 0, 0, 0, 1,
             active_object_context);
  find_or_create_registry_entry(soundtrack_instance_type_descriptor,
             (uint32_t)(uintptr_t)object + soundtrack_instance_base_offset_adjustment + 64);
  object[64] = name_high_byte;
  tidy_std_string_storage((char *)object + 64, 0);
  instance[24] = 0;
  instance[25] = 0;
  object[104] = 1;
  instance[28] = (uint32_t)(uintptr_t)allocate_soundtrack_list_node_with_links(NULL, NULL);
  instance[29] = 0;
  object[108] = name_high_byte;
  instance[0] = (uint32_t)(uintptr_t)&soundtrack_instance_vtable;
  instance[3] = (uint32_t)(uintptr_t)&soundtrack_instance_event_target_vtable;
  assign_std_string_storage((char *)object + 64, name, strlen(name));
  instance[20] = 4;
  object[84] = 0;
  instance[22] = 0;
  instance[23] = 0;
  object[104] = 0;
  return instance;
}

uint32_t *__thiscall construct_registered_soundtrack_instance(
    uint32_t *object, int mode)
{
  uint8_t *bytes = (uint8_t *)(void *)object;
  const uint8_t default_value = (uint8_t)((uint32_t)mode >> 24);

  initialize_registered_soundtrack_instance_active_object((int)(uintptr_t)object, mode);
  find_or_create_registry_entry(soundtrack_instance_type_descriptor,
             (uint32_t)(uintptr_t)bytes + soundtrack_instance_base_offset_adjustment + 64);
  bytes[64] = default_value;
  tidy_std_string_storage((char *)bytes + 64, 0);
  object[24] = 0;
  object[25] = 0;
  bytes[104] = 1;
  bytes[108] = default_value;
  object[28] = (uint32_t)(uintptr_t)allocate_soundtrack_list_node_with_links(NULL, NULL);
  object[29] = 0;
  object[0] = (uint32_t)(uintptr_t)&soundtrack_instance_vtable;
  object[3] = (uint32_t)(uintptr_t)&soundtrack_instance_event_target_vtable;
  object[20] = 4;
  bytes[84] = 0;
  object[22] = 0;
  object[23] = 0;
  bytes[104] = 0;
  return object;
}

uint32_t *__cdecl create_registered_soundtrack_instance(void)
{
  uint32_t *memory = allocate_registered_soundtrack_instance(120);
  return memory != NULL
             ? construct_registered_soundtrack_instance(memory, 0)
             : NULL;
}

uint32_t *__thiscall destroy_soundtrack_instance_members(
    uint32_t *instance)
{
  *instance = (uint32_t)(uintptr_t)&soundtrack_instance_vtable;
  instance[3] = (uint32_t)(uintptr_t)&soundtrack_instance_event_target_vtable;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)instance[28];
  destroy_soundtrack_instance_list_objects((uint32_t *)(uintptr_t)*sentinel, sentinel,
             (char)(uintptr_t)instance);
  destroy_soundtrack_instance_node_list(instance + 27);
  replace_soundtrack_event_reference_and_queue_previous((int *)(void *)(instance + 24), 0);
  tidy_std_string_storage((char *)(void *)instance + 64, 1);
  erase_map_entry_impl(
      soundtrack_instance_type_descriptor,
      (uint32_t)soundtrack_instance_base_offset_adjustment +
          (instance != NULL ? (uint32_t)(uintptr_t)(instance + 16) : 0));
  return destroy_soundtrack_instance_active_object((int)(uintptr_t)instance);
}

int __thiscall release_registered_soundtrack_instance(
    uint32_t *registered_instance, char mode)
{
  uint32_t *instance = registered_instance - 3;
  destroy_soundtrack_instance_members(instance);
  if ((mode & 1) != 0)
    free_tracked_memory((int)(uintptr_t)instance);
  return (int)(uintptr_t)instance;
}

int __thiscall find_soundtrack_member_index(uint32_t *members, int member)
{
  uint32_t *current = (uint32_t *)(uintptr_t)members[4];
  uint32_t *end = (uint32_t *)(uintptr_t)members[5];
  int index = 0;
  while (current != end && (int)*current != member) {
    ++index;
    ++current;
  }
  return index;
}

int __thiscall soundtrack_member_at_restore_index(uint32_t *members,
                                                  int index)
{
  uint32_t *begin = (uint32_t *)(uintptr_t)members[4];
  uint32_t *end = (uint32_t *)(uintptr_t)members[5];
  if (index < 0 || begin == NULL ||
      (uint32_t)index >= (uint32_t)(end - begin))
    return 0;
  if (index > 1)
    begin += index - 1;
  return (int)*begin;
}

uint32_t *__thiscall soundtrack_node_at_index(uint32_t *instance, int index)
{
  if (index < 0 || (uint32_t)index >= instance[29])
    return NULL;

  uint32_t *sentinel = (uint32_t *)(uintptr_t)instance[28];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  while (node != sentinel && index-- > 0)
    node = (uint32_t *)(uintptr_t)*node;
  return node;
}

uint32_t *__thiscall append_soundtrack_sound_entry(uint32_t *instance,
                                                   int entry_address)
{
  uint8_t *sound = deserialize_soundtrack_sound_entry(entry_address);
  if (sound != NULL) {
    int entry = (int)(uintptr_t)sound;
    int result;
    return append_soundtrack_instance_list_node(instance + 27, (uint32_t *)(void *)&result,
                      (int)instance[28], &entry);
  }
  return (uint32_t *)(void *)sound;
}

uint32_t *__thiscall append_soundtrack_presentation_entry(
    uint32_t *instance, int entry_address)
{
  uint8_t *sound = deserialize_soundtrack_sound_entry(entry_address);
  uint32_t *presentation;
  int result;

  if (sound == NULL)
    return NULL;

  if (instance[29] == 0) {
    presentation = NULL;
  } else {
    uint32_t *sentinel = (uint32_t *)(uintptr_t)instance[28];
    uint32_t *first_node = (uint32_t *)(uintptr_t)sentinel[1];
    presentation = (uint32_t *)(uintptr_t)first_node[2];
    if (presentation != NULL && presentation[1] == 3)
      goto append_sound;
  }

  presentation = (uint32_t *)allocate_tracked_memory(28);
  if (presentation != NULL)
    construct_soundtrack_presentation_entry((int)(uintptr_t)presentation);
  int presentation_address = (int)(uintptr_t)presentation;
  append_soundtrack_instance_list_node(instance + 27, (uint32_t *)(void *)&result,
             (int)instance[28], &presentation_address);

append_sound:
  {
    int sound_address = (int)(uintptr_t)sound;
    return append_soundtrack_presentation_sound((int)(uintptr_t)(presentation + 3), &result,
                      &sound_address);
  }
}

int *__thiscall append_soundtrack_wait_entry(uint32_t *instance,
                                             int *entry)
{
  int *wait = deserialize_soundtrack_wait_entry((uint32_t *)entry);
  if (wait != NULL) {
    int wait_address = (int)(uintptr_t)wait;
    int result;
    return (int *)append_soundtrack_instance_list_node(instance + 27, (uint32_t *)(void *)&result,
                             (int)instance[28], &wait_address);
  }
  return wait;
}

uint32_t *__thiscall restore_soundtrack_serialized_state(
    uint32_t *instance, int state_address)
{
  uint32_t *state = (uint32_t *)(uintptr_t)state_address;
  const char *default_type = soundtrack_type_name((int)instance[20]);
  char *soundtrack_type = (char *)(uintptr_t)(uint32_t)get_config_string_value(
      state, "SoundType", (int)(uintptr_t)default_type);
  if (!parse_soundtrack_type_name(soundtrack_type, (int *)(void *)(instance + 20))) {
    log_source_message(
        (int)(uintptr_t)"z:\\Proj\\GK3\\gk3app\\Source\\SoundMgr.cpp",
        648, 5, 0, "SoundTrack(%s) contains Illegal SoundType(%s)\n",
        (const char *)(uintptr_t)(state_address + 4), soundtrack_type);
    instance[20] = 4;
  }

  select_or_create_gconfig_section(state_address, "Restore");
  if (get_config_integer_value(state, "Version", 0) > 0) {
    int playback_state = get_config_integer_value(state, "State", (int)instance[13]);
    int remaining_ms = get_config_integer_value(state, "MS", 0);
    if (remaining_ms <= 0) {
      if (playback_state >= 0)
        --playback_state;
    } else {
      typedef void (__thiscall *SetRemainingTime)(uint32_t *, int);
      uint32_t vtable = *(uint32_t *)(void *)instance;
      SetRemainingTime set_remaining_time =
          (SetRemainingTime)(uintptr_t)(vtable + 24);
      set_remaining_time(instance, remaining_ms);
    }
    instance[13] = (uint32_t)playback_state;
    ((uint8_t *)(void *)instance)[84] =
        (uint8_t)get_config_boolean_value(state, "Stopping",
                           ((uint8_t *)(void *)instance)[84]);

    int current_node_index = get_config_integer_value(state, "CurrentNode", -1);
    int current_sound_index = get_config_integer_value(state, "CurrentSound", -1);
    uint32_t current_node_address = 0;
    uint32_t *current_node =
        soundtrack_node_at_index(instance, current_node_index);
    instance[23] = (uint32_t)(uintptr_t)current_node;
    if (current_node != NULL) {
      uint32_t *sound_node = (uint32_t *)(uintptr_t)current_node[2];
      int sound_type = (int)sound_node[1];
      uint32_t *current_sound = NULL;
      if (sound_type == 3) {
        current_sound = (uint32_t *)(uintptr_t)
            soundtrack_member_at_restore_index(sound_node,
                                                current_sound_index);
      } else if (sound_type == 1) {
        current_sound = sound_node;
      }
      instance[22] = (uint32_t)(uintptr_t)current_sound;
      if (current_sound != NULL) {
        current_sound[3] = (uint32_t)get_config_integer_value(
            state, "CurrentSoundHandle", 0);
      }
    }
  }
  return instance;
}

int __thiscall insert_soundtrack_snapshot_entry(void *snapshot,
                                                 uint32_t serialized_entry)
{
  char *name = (char *)(uintptr_t)(serialized_entry + 4);
  char name_storage[16] = {0};

  name_storage[0] = (char)((uintptr_t)name_storage >> 24);
  tidy_std_string_storage(name_storage, 0);
  assign_std_string_storage(name_storage, name, strlen(name));
  add_soundtrack_snapshot_name((int)(uintptr_t)((uint8_t *)snapshot + 4),
             (uint8_t *)name_storage);
  tidy_std_string_storage(name_storage, 1);
  return append_soundtrack_snapshot_entry((int)(uintptr_t)snapshot + 20, &serialized_entry);
}

uint8_t *__thiscall construct_soundtrack_snapshot(uint8_t *object)
{
  find_or_create_registry_entry(soundtrack_snapshot_type_descriptor,
             (uint32_t)(uintptr_t)object + (uint32_t)soundtrack_snapshot_base_offset_adjustment + 4);
  object[4] = 0;
  *(uint32_t *)(void *)(object + 8) = 0;
  *(uint32_t *)(void *)(object + 12) = 0;
  *(uint32_t *)(void *)(object + 16) = 0;
  object[20] = 0;
  *(uint32_t *)(void *)(object + 24) = 0;
  *(uint32_t *)(void *)(object + 28) = 0;
  *(uint32_t *)(void *)(object + 32) = 0;
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)&soundtrack_snapshot_vtable;
  return object;
}

uint8_t *__thiscall construct_registered_soundtrack_snapshot(
    uint8_t *object, int mode)
{
  const uint8_t default_value = (uint8_t)((uint32_t)mode >> 24);
  find_or_create_registry_entry(soundtrack_snapshot_type_descriptor,
             (uint32_t)(uintptr_t)object + (uint32_t)soundtrack_snapshot_base_offset_adjustment + 4);
  object[4] = default_value;
  *(uint32_t *)(void *)(object + 8) = 0;
  *(uint32_t *)(void *)(object + 12) = 0;
  *(uint32_t *)(void *)(object + 16) = 0;
  object[20] = default_value;
  *(uint32_t *)(void *)(object + 24) = 0;
  *(uint32_t *)(void *)(object + 28) = 0;
  *(uint32_t *)(void *)(object + 32) = 0;
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)&soundtrack_snapshot_vtable;
  return object;
}

uint8_t *__cdecl create_registered_soundtrack_snapshot(void)
{
  uint8_t *memory = (uint8_t *)allocate_registered_soundtrack_snapshot(36);
  return memory != NULL
             ? construct_registered_soundtrack_snapshot(memory, 0)
             : NULL;
}

uint32_t *__thiscall destroy_soundtrack_snapshot_members(
    uint32_t *snapshot)
{
  *snapshot = (uint32_t)(uintptr_t)&soundtrack_snapshot_vtable;
  uint32_t *entry_begin = (uint32_t *)(uintptr_t)snapshot[6];
  uint32_t *entry_end = (uint32_t *)(uintptr_t)snapshot[7];
  for (uint32_t *entry = entry_begin; entry != entry_end; ++entry) {
    uint32_t *object = (uint32_t *)(uintptr_t)*entry;
    if (object != NULL) {
      uint32_t *vtable = (uint32_t *)(uintptr_t)object[0];
      typedef void (__thiscall *DestroySnapshotEntry)(uint32_t *, int);
      ((DestroySnapshotEntry)(uintptr_t)vtable[0])(object, 1);
    }
  }
  clear_soundtrack_snapshot_member_array((int *)(void *)(snapshot + 5));
  destroy_string_vector((int *)(void *)(snapshot + 1));
  return erase_map_entry_impl(
      soundtrack_snapshot_type_descriptor,
      (uint32_t)soundtrack_snapshot_base_offset_adjustment +
          (snapshot != NULL ? (uint32_t)(uintptr_t)(snapshot + 1) : 0));
}

int __thiscall release_soundtrack_snapshot(uint32_t *snapshot, char mode)
{
  destroy_soundtrack_snapshot_members(snapshot);
  if ((mode & 1) != 0)
    free_tracked_memory((int)(uintptr_t)snapshot);
  return (int)(uintptr_t)snapshot;
}

char __thiscall serialize_soundtrack_snapshot(uint32_t *snapshot,
                                              uint8_t *serializer,
                                              int flags)
{
  (void)flags;
  serialize_soundtrack_snapshot_names(serializer, "pausedSndTracksNames",
             (unsigned int)(uintptr_t)(snapshot + 1), 3);
  char result = serialize_soundtrack_snapshot_members(serializer, "pausedSndTracks",
                           (unsigned int)(uintptr_t)(snapshot + 5), 1);
  if (!serializer[4]) {
    uint32_t *serialized_entry =
        (uint32_t *)(uintptr_t)snapshot[6];
    uint32_t *serialized_end =
        (uint32_t *)(uintptr_t)snapshot[7];
    uint8_t *names = (uint8_t *)(uintptr_t)snapshot[2];

    for (uint32_t index = 0; serialized_entry != serialized_end;
         ++serialized_entry, ++index) {
      const char *name = *(const char **)(void *)(names + index * 16 + 4);
      if (name == NULL)
        name = Key;
      char *destination =
          (char *)(uintptr_t)(*(uint32_t *)(uintptr_t)serialized_entry + 4);
      strcpy(destination, name);
    }
  }
  return result;
}

char __cdecl serialize_registered_soundtrack_snapshot(
    uint32_t *snapshot, uint8_t *serializer, int flags)
{
  return serialize_soundtrack_snapshot(snapshot, serializer, flags);
}

int *__thiscall register_soundtrack_snapshot_type(void)
{
  return register_runtime_type_descriptor(
      soundtrack_snapshot_type_descriptor, (int)(uintptr_t)"SoundTrackPauseCookie",
      (uint32_t *)(uintptr_t)3, 36, 500,
      (int)(uintptr_t)create_registered_soundtrack_snapshot,
      (int)(uintptr_t)serialize_registered_soundtrack_snapshot, 0, 0, 0);
}

static void __cdecl shutdown_soundtrack_snapshot_registry(void)
{
  if ((soundtrack_snapshot_registry_shutdown_flag & 1) == 0) {
    soundtrack_snapshot_registry_shutdown_flag |= 1;
    destroy_runtime_type_descriptor(soundtrack_snapshot_type_descriptor);
    --registered_type_descriptor_count;
  }
}

int __cdecl initialize_soundtrack_snapshot_type(void)
{
  register_soundtrack_snapshot_type();
  return atexit(shutdown_soundtrack_snapshot_registry);
}

void initialize_soundtrack_snapshot_registry_offset(void)
{
  soundtrack_snapshot_base_offset_adjustment = -4;
}

int __thiscall load_soundtrack_instance_from_state(
    uint32_t *instance, uint32_t *serialized_state)
{
  uint32_t *cursor = serialized_state;
  const char *first_entry = (const char *)get_first_config_entry(serialized_state, &cursor);
  int entry_address = (int)(uintptr_t)serialized_state;

  if (first_entry != NULL) {
    do {
      set_config_entry_iterator((uint32_t *)(uintptr_t)entry_address, &cursor);
      const char *kind = get_config_entry_name((uint32_t *)(uintptr_t)entry_address);
      if (strcasecmp(kind, "SOUND") == 0) {
        append_soundtrack_sound_entry(instance, entry_address);
      } else if (strcasecmp(kind, "PRS") == 0) {
        append_soundtrack_presentation_entry(instance, entry_address);
      } else if (strcasecmp(kind, "WAIT") == 0) {
        append_soundtrack_wait_entry(instance,
                                     (int *)(uintptr_t)entry_address);
      } else if (*kind != '\0' && strcasecmp(kind, "SoundTrack") != 0 &&
                 strcasecmp(kind, "Restore") != 0) {
        log_source_message(
            (int)(uintptr_t)"z:\\Proj\\GK3\\gk3app\\Source\\SoundMgr.cpp",
            559, 5, 0, "SndTrack::Load(%s): unknown sound type '%s'\n",
            (const char *)(uintptr_t)(entry_address + 4), kind);
      }
    } while (get_next_config_entry((char *)(uintptr_t)entry_address, &cursor));
  }

  restore_soundtrack_serialized_state(instance, entry_address);
  return get_soundtrack_instance_load_result(instance);
}

uint32_t *__thiscall serialize_soundtrack_instance(
    uint32_t *instance, uint32_t *serializer)
{
  create_gconfig_section_entry(serializer, "SoundTrack");
  write_config_string_entry(serializer, "SoundType", soundtrack_type_name(instance[20]));
  create_gconfig_section_entry(serializer, "Restore");
  write_config_integer_entry(serializer, "Version", 1);

  const uint32_t duration = instance[11];
  if (duration != 0) {
    const uint32_t elapsed = (uint32_t)get_elapsed_game_time((int)(uintptr_t)(instance + 10));
    const int remaining = elapsed < duration ? (int)(duration - elapsed) : 1;
    write_config_integer_entry(serializer, "MS", remaining);
  }

  write_config_integer_entry(serializer, "State", (int)instance[13]);
  if (((uint8_t *)instance)[84] != 0)
    write_config_integer_entry(serializer, "Stopping", ((uint8_t *)instance)[84]);

  uint32_t *current_node = (uint32_t *)(uintptr_t)instance[23];
  if (current_node != NULL) {
    const int node_index = find_soundtrack_node_index(instance);
    if (node_index >= 0)
      write_config_integer_entry(serializer, "CurrentNode", node_index);

    uint32_t *current_sound = (uint32_t *)(uintptr_t)instance[22];
    if (current_sound != NULL) {
      uint32_t *sound_node = (uint32_t *)(uintptr_t)current_node[2];
      const int sound_type = (int)sound_node[1];
      if (sound_type == 1) {
        write_config_integer_entry(serializer, "CurrentSound", 0);
      } else if (sound_type == 3) {
        write_config_integer_entry(serializer, "CurrentSound",
                   find_soundtrack_member_index(
                       sound_node, (int)(uintptr_t)current_sound));
      } else {
        goto serialize_owned_entries;
      }
      write_config_integer_entry(serializer, "CurrentSoundHandle",
                 (int)current_sound[3]);
    }
  }

serialize_owned_entries:
  ;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)instance[28];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  uint32_t *result = sentinel;
  while (node != sentinel) {
    uint32_t *owned_object = (uint32_t *)(uintptr_t)node[2];
    uint32_t *methods = (uint32_t *)(uintptr_t)owned_object[0];
    uint32_t *(__thiscall *serialize)(uint32_t *, uint32_t *) =
        (uint32_t *(__thiscall *)(uint32_t *, uint32_t *))
            (uintptr_t)(methods[1]);
    result = serialize(owned_object, serializer);
    node = (uint32_t *)(uintptr_t)*node;
  }
  return result;
}

uint32_t *__thiscall find_soundtrack_by_id(uint32_t *manager,
                                           int16_t identifier)
{
  return (uint32_t *)(uintptr_t)find_soundtrack_list_entry_by_identifier(
      identifier, (int)(uintptr_t)(manager + 3));
}

uint32_t *__thiscall find_soundtrack_by_name(uint32_t *manager,
                                             int16_t name_key)
{
  return (uint32_t *)(uintptr_t)find_soundtrack_list_entry_by_identifier(
      name_key, (int)(uintptr_t)(manager + 6));
}

void __thiscall set_soundtrack_active_by_name(uint32_t *manager,
                                              int *wide_name, char active)
{
  uint32_t *instance = find_soundtrack_by_id(
      manager, (int16_t)(uintptr_t)wide_name);
  if (instance == NULL)
    instance = (uint32_t *)find_or_create_soundtrack_instance(manager,
                                                               wide_name);
  set_soundtrack_instance_active(manager, (int)(uintptr_t)instance, active);
}

int *__thiscall configure_soundtrack_playback(uint32_t *manager,
                                              int16_t identifier,
                                              int first, int second,
                                              int active)
{
  uint32_t *instance = find_soundtrack_by_id(manager, identifier);
  if (instance != NULL) {
    typedef void (__thiscall *ConfigureSoundtrackMethod)(
        uint32_t *instance, int first, int second, int active);
    uint32_t vtable = *(uint32_t *)(void *)instance;
    ConfigureSoundtrackMethod configure =
        (ConfigureSoundtrackMethod)(uintptr_t)(vtable + 52);
    configure(instance, first, second, 1);
  }
  int cleared_reference[2] = {0, 0};
  return replace_event_reference_and_queue_previous(cleared_reference, NULL);
}

int __thiscall query_soundtrack_instance_state(uint32_t *manager,
                                               int16_t identifier)
{
  uint32_t *instance = find_soundtrack_by_id(manager, identifier);
  if (instance == NULL)
    return 0;

  typedef int (__thiscall *QuerySoundtrackMethod)(uint32_t *instance,
                                                  int argument);
  uint32_t vtable = *(uint32_t *)(void *)instance;
  QuerySoundtrackMethod query =
      (QuerySoundtrackMethod)(uintptr_t)(vtable + 56);
  return query(instance, 0);
}

int __thiscall query_soundtrack_instance_value(uint32_t *manager,
                                               int16_t identifier)
{
  uint32_t *instance = find_soundtrack_by_id(manager, identifier);
  if (instance == NULL)
    return 0;

  typedef int (__thiscall *GetSoundtrackMethod)(uint32_t *instance);
  uint32_t vtable = *(uint32_t *)(void *)instance;
  GetSoundtrackMethod get_value =
      (GetSoundtrackMethod)(uintptr_t)(vtable + 20);
  return get_value(instance);
}

void __thiscall remove_and_destroy_soundtrack_instance(
    uint32_t *manager, uint32_t *instance)
{
  remove_soundtrack_instance_from_manager(manager + 3, &instance);
  if (instance != NULL) {
    uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
    typedef void (__thiscall *DestroySoundtrackInstance)(uint32_t *, int);
    DestroySoundtrackInstance destroy_instance =
        (DestroySoundtrackInstance)(uintptr_t)vtable[0];
    destroy_instance(instance, 1);
  }
}

uint32_t *__thiscall update_active_soundtrack_instances(uint32_t *manager)
{
  uint32_t *sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  uint32_t *result = sentinel;

  while (node != sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
    typedef uint32_t *__thiscall (*UpdateSoundtrackMethod)(uint32_t *instance);
    UpdateSoundtrackMethod update =
        (UpdateSoundtrackMethod)(uintptr_t)vtable[2];
    result = (uint32_t *)(uintptr_t)update(instance);
    node = (uint32_t *)(uintptr_t)*node;
  }
  return result;
}

uint32_t *__thiscall serialize_soundtrack_instances(uint32_t *manager)
{
  uint32_t *sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  uint32_t *result = sentinel;

  while (node != sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    const char *name = (const char *)(uintptr_t)instance[17];
    uint32_t serialized_state[75];
    if (name == NULL)
      name = Key;
    construct_named_gconfig_file((char *)serialized_state, name);
    serialize_soundtrack_instance(instance, serialized_state);
    save_gconfig_file((const char *)serialized_state, 0);
    result = destroy_gconfig_file(serialized_state);
    node = (uint32_t *)(uintptr_t)*node;
  }
  return result;
}

void __thiscall capture_and_remove_soundtrack_instances(
    uint32_t *manager, void *snapshot, int flag_mask, int mode)
{
  struct TemporarySoundtrackList {
    uint32_t state;
    uint32_t *sentinel;
    uint32_t count;
  } temporary = {
      (uint8_t)((uint32_t)flag_mask >> 24),
      allocate_soundtrack_list_node(NULL, NULL),
      0,
  };
  uint32_t *manager_sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *node = (uint32_t *)(uintptr_t)*manager_sentinel;

  while (node != manager_sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    if (*(uint8_t *)((char *)(void *)instance + 84) == 0 &&
        (instance[20] & (uint32_t)flag_mask) != 0) {
      const char *name = (const char *)(uintptr_t)instance[17];
      uint32_t *serialized_state;
      char *serialized_name;
      uint32_t *temporary_node;

      if (name == NULL)
        name = Key;
      serialized_state = allocate_registered_gconfig_file(300);
      if (serialized_state != NULL)
        serialized_name = construct_named_gconfig_file((char *)serialized_state, name);
      else
        serialized_name = NULL;

      serialize_soundtrack_instance(instance,
                                    (uint32_t *)(void *)serialized_name);
      insert_soundtrack_snapshot_entry(snapshot,
                                       (uint32_t)(uintptr_t)serialized_name);
      {
        uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
        typedef void (__thiscall *SetSoundtrackMode)(uint32_t *, int);
        SetSoundtrackMode set_mode =
            (SetSoundtrackMode)(uintptr_t)vtable[14];
        set_mode(instance, mode);
      }
      append_soundtrack_manager_list_node((uint32_t *)(void *)&temporary,
                 (uint32_t *)(void *)&temporary_node,
                 (int)(uintptr_t)temporary.sentinel, &instance);
    }
    node = (uint32_t *)(uintptr_t)*node;
  }

  node = (uint32_t *)(uintptr_t)*temporary.sentinel;
  while (node != temporary.sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    remove_and_destroy_soundtrack_instance(manager, instance);
    node = (uint32_t *)(uintptr_t)*node;
  }
  destroy_soundtrack_list_storage((uint32_t *)(void *)&temporary);
}

void __thiscall restore_soundtrack_instances(uint32_t *manager,
                                              int snapshot_address)
{
  uint32_t *snapshot = (uint32_t *)(uintptr_t)snapshot_address;
  uint32_t *entry;
  uint32_t *end;

  for (entry = (uint32_t *)(uintptr_t)snapshot[6],
       end = (uint32_t *)(uintptr_t)snapshot[7];
       entry != end; ++entry) {
    uint32_t *serialized_state = (uint32_t *)(uintptr_t)*entry;
    uint8_t *instance_memory =
        (uint8_t *)allocate_registered_soundtrack_instance(120);
    int *instance = instance_memory != NULL
                        ? (int *)construct_soundtrack_instance(
                              instance_memory,
                              (char *)serialized_state + 4)
                        : NULL;
    uint32_t *registry_entry = (uint32_t *)(uintptr_t)find_map_value_impl(
        soundtrack_instance_type_descriptor, (uint32_t)(uintptr_t)instance);
    registry_entry[2] = 4;
    load_soundtrack_instance_from_state((uint32_t *)(void *)instance,
                                        serialized_state);
    set_soundtrack_instance_active(manager, (int)(uintptr_t)instance, 1);
  }
}

int *__stdcall create_soundtrack_instance_from_name(char *name)
{
  int *instance = NULL;
  uint32_t serialized_state[76];
  construct_named_gconfig_file((char *)serialized_state, name);
  if (load_gconfig_file(serialized_state, 0)) {
    uint8_t *instance_memory =
        (uint8_t *)allocate_registered_soundtrack_instance(120);
    if (instance_memory != NULL)
      instance = (int *)construct_soundtrack_instance(instance_memory, name);
    uint32_t *registry_entry = (uint32_t *)(uintptr_t)find_map_value_impl(
        soundtrack_instance_type_descriptor, (uint32_t)(uintptr_t)instance);
    registry_entry[2] = 4;
    load_soundtrack_instance_from_state((uint32_t *)(void *)instance,
                                        serialized_state);
  }
  destroy_gconfig_file(serialized_state);
  return instance;
}

void __thiscall set_soundtrack_instance_active(uint32_t *manager,
                                               int instance_address,
                                               char active)
{
  uint32_t *instance = (uint32_t *)(uintptr_t)instance_address;
  if (instance == NULL)
    return;

  uint32_t *list = manager + 3;
  uint32_t *list_result = list;
  if (soundtrack_list_contains_instance((int)(uintptr_t)list, &instance))
    append_soundtrack_manager_list_node(list, (uint32_t *)(void *)&list_result,
               (int)list[1], &instance);
  if (active != 0) {
    uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
    typedef void (__thiscall *ActivateSoundtrackInstance)(uint32_t *,
                                                          uint32_t *);
    ActivateSoundtrackInstance activate =
        (ActivateSoundtrackInstance)(uintptr_t)vtable[2];
    activate(instance, manager);
  }
}

uint8_t *__thiscall construct_registered_soundtrack_manager(uint8_t *object,
                                                             int unused)
{
  char default_value;

  find_or_create_registry_entry(
      broadcast_target_type_descriptor,
      (uint32_t)(uintptr_t)&((char *)(void *)object)[
          broadcast_target_base_offset_adjustment + 4]);
  *(uint32_t *)(void *)object =
      (uint32_t)(uintptr_t)registered_object_base_vtable;
  find_or_create_registry_entry(
      soundtrack_manager_type_descriptor,
      (uint32_t)(uintptr_t)&((char *)(void *)object)[soundtrack_manager_base_offset_adjustment + 9]);
  object[12] = (uint8_t)default_value;
  *((uint32_t *)(void *)object + 4) =
      (uint32_t)(uintptr_t)allocate_soundtrack_list_node(NULL, NULL);
  *((uint32_t *)(void *)object + 5) = 0;
  object[24] = (uint8_t)default_value;
  *((uint32_t *)(void *)object + 7) =
      (uint32_t)(uintptr_t)allocate_soundtrack_list_node(NULL, NULL);
  *((uint32_t *)(void *)object + 8) = 0;
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)soundtrack_manager_vtable;
  *((uint32_t *)(void *)object + 9) = 0;
  return object;
}

int __thiscall construct_soundtrack_manager(int object)
{
  char default_value;
  construct_registered_object_base((uint8_t *)(uintptr_t)object);
  find_or_create_registry_entry(soundtrack_manager_type_descriptor,
             (uint32_t)soundtrack_manager_base_offset_adjustment + (uint32_t)object + 9);
  *(uint8_t *)(uintptr_t)(object + 12) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 16) =
      (uint32_t)(uintptr_t)allocate_soundtrack_list_node(NULL, NULL);
  *(uint32_t *)(uintptr_t)(object + 20) = 0;
  *(uint8_t *)(uintptr_t)(object + 24) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 28) =
      (uint32_t)(uintptr_t)allocate_soundtrack_list_node(NULL, NULL);
  *(uint32_t *)(uintptr_t)(object + 32) = 0;
  *(uint32_t *)(uintptr_t)object = (uint32_t)(uintptr_t)soundtrack_manager_vtable;
  *(uint32_t *)(uintptr_t)(object + 36) = 0;
  return object;
}

int *__thiscall dispatch_soundtrack_command_to_matching_instances(
    uint32_t *manager, int flag_mask, int first, int second, int unused)
{
  uint32_t *sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  int result_reference[2] = {first, second};

  (void)unused;
  while (node != sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    if (*(uint8_t *)((char *)(void *)instance + 84) == 0 &&
        (instance[20] & (uint32_t)flag_mask) != 0) {
      uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
      typedef void (__thiscall *DispatchSoundtrackCommand)(
          uint32_t *, int, int, int);
      DispatchSoundtrackCommand dispatch =
          (DispatchSoundtrackCommand)(uintptr_t)vtable[13];

      first = result_reference[0];
      second = result_reference[1];
      result_reference[0] = 0;
      result_reference[1] = 0;
      dispatch(instance, first, second, 1);
    }
    node = (uint32_t *)(uintptr_t)*node;
  }
  return replace_soundtrack_event_reference_and_queue_previous(result_reference, 0);
}

void __thiscall handle_soundtrack_resource_message(uint32_t *manager,
                                                   int message)
{
  if (message == 1125) {
    uint8_t *snapshot = allocate_registered_soundtrack_snapshot(36);
    manager[9] = (uint32_t)(uintptr_t)(snapshot != NULL
                                          ? construct_soundtrack_snapshot(snapshot)
                                          : NULL);
    capture_and_remove_soundtrack_instances(
        manager, (void *)(uintptr_t)manager[9], 31, 0);
  } else if ((message == 1126 || message == 1128) && manager[9] != 0) {
    uint32_t *snapshot = (uint32_t *)(uintptr_t)manager[9];
    uint32_t *vtable;
    restore_soundtrack_instances(manager, (int)(uintptr_t)snapshot);
    vtable = (uint32_t *)(uintptr_t)snapshot[0];
    typedef void (__thiscall *DestroySnapshot)(uint32_t *, int);
    ((DestroySnapshot)(uintptr_t)vtable[0])(snapshot, 1);
    manager[9] = 0;
  }
}

uint32_t *__thiscall destroy_soundtrack_manager_members(uint32_t *manager)
{
  *manager = (uint32_t)(uintptr_t)soundtrack_manager_vtable;
  reset_soundtrack_playback((int)(uintptr_t)manager);
  destroy_soundtrack_list_storage(manager + 6);
  destroy_soundtrack_list_storage(manager + 3);
  erase_map_entry_impl(
      soundtrack_manager_type_descriptor,
      (uint32_t)soundtrack_manager_base_offset_adjustment + (manager != NULL
                                    ? (uint32_t)(uintptr_t)manager + 9
                                    : 0));
  *manager = (uint32_t)(uintptr_t)registered_object_base_vtable;
  return erase_map_entry_impl(
      broadcast_target_type_descriptor,
      (uint32_t)broadcast_target_base_offset_adjustment + (manager != NULL
                                    ? (uint32_t)(uintptr_t)(manager + 1)
                                    : 0));
}

uint32_t *__thiscall release_soundtrack_manager(uint32_t *manager,
                                                char mode)
{
  destroy_soundtrack_manager_members(manager);
  if ((mode & 1) != 0)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}

typedef int (__thiscall *SetSoundtrackInstanceActiveMethod)(
    uint32_t *instance, int first, int second, char active);

uint32_t *__cdecl allocate_registered_soundtrack_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(soundtrack_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_soundtrack_manager(void)
{
  uint32_t *memory = allocate_registered_soundtrack_manager(40);
  return memory
      ? (uint32_t *)(uintptr_t)construct_soundtrack_manager(
            (int)(uintptr_t)memory)
      : NULL;
}

uint32_t *__cdecl create_registered_soundtrack_manager(void)
{
  uint8_t *memory = (uint8_t *)allocate_registered_soundtrack_manager(40);
  return memory
      ? (uint32_t *)(void *)construct_registered_soundtrack_manager(memory, 0)
      : NULL;
}

uint32_t *shutdown_soundtrack_manager(uint32_t *manager)
{
  return reset_soundtrack_playback((int)(uintptr_t)manager);
}

uint32_t *__thiscall stop_all_soundtrack_instances(uint32_t *manager)
{
  uint32_t *sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *node = (uint32_t *)(uintptr_t)*sentinel;
  uint32_t *result = sentinel;

  while (node != sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)node[2];
    uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
    SetSoundtrackInstanceActiveMethod set_active =
        (SetSoundtrackInstanceActiveMethod)(uintptr_t)vtable[52 / 4];
    result = (uint32_t *)(uintptr_t)set_active(instance, 0, 0, 1);
    node = (uint32_t *)(uintptr_t)*node;
  }

  return result;
}

static char __cdecl destroy_soundtrack_instances_in_list(
    uint32_t *first, uint32_t *sentinel, char result)
{
  while (first != sentinel) {
    uint32_t *instance = (uint32_t *)(uintptr_t)first[2];
    if (instance != NULL) {
      uint32_t *vtable = (uint32_t *)(uintptr_t)instance[0];
      typedef void (__thiscall *DestroySoundtrackInstance)(uint32_t *, int);
      DestroySoundtrackInstance destroy_instance =
          (DestroySoundtrackInstance)(uintptr_t)vtable[0];
      destroy_instance(instance, 1);
    }
    first = (uint32_t *)(uintptr_t)first[0];
  }
  return result;
}

static uint32_t *__thiscall clear_soundtrack_instance_list(int list_address)
{
  uint32_t *list = (uint32_t *)(uintptr_t)list_address;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)list[1];
  uint32_t context = (uint32_t)list_address;
  uint32_t *first = (uint32_t *)(uintptr_t)*sentinel;
  return erase_soundtrack_list_range(list, &context, first, sentinel);
}

uint32_t *__thiscall reset_soundtrack_playback(int object)
{
  uint32_t *manager = (uint32_t *)(uintptr_t)(uint32_t)object;
  uint32_t *instance_sentinel = (uint32_t *)(uintptr_t)manager[4];
  uint32_t *first_instance =
      (uint32_t *)(uintptr_t)*instance_sentinel;

  stop_all_soundtrack_instances(manager);
  destroy_soundtrack_instances_in_list(first_instance, instance_sentinel, 0);
  uint32_t *result = clear_soundtrack_instance_list(object + 12);

  uint32_t *owned_instance = (uint32_t *)(uintptr_t)manager[9];
  if (owned_instance != NULL) {
    uint32_t *vtable = (uint32_t *)(uintptr_t)owned_instance[0];
    typedef void (__thiscall *DestroySoundtrackInstance)(uint32_t *, int);
    DestroySoundtrackInstance destroy_instance =
        (DestroySoundtrackInstance)(uintptr_t)vtable[0];
    destroy_instance(owned_instance, 1);
    manager[9] = 0;
  }
  return result;
}
