#include <stddef.h>
#include <stdint.h>
#include <strings.h>

#include "../common/runtime_lockit.h"

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_7650C8[];
extern int dialogue_manager_base_offset_adjustment __asm__("dword_7650C4");
extern uint32_t broadcast_target_type_descriptor[];
extern int broadcast_target_base_offset_adjustment;
extern int game_engine_instance_address __asm__("dword_765A2C");
extern uint32_t dialogue_manager_vtable[] __asm__("off_6BE19C");
extern uint32_t registered_object_base_vtable[];
extern uint8_t byte_6BE250[4];
extern char byte_6A6454;
extern int played_dialogue_index_sentinel_address __asm__("dword_765190");
extern int played_dialogue_index_reference_count __asm__("dword_765194");
extern uint8_t *__thiscall construct_registered_object_base(uint8_t *object);
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern void __cdecl free_tracked_memory(int address);
extern void __thiscall remove_active_object_child(int object, int child);
extern char __cdecl serialize_dialogue_string_field(
    int serializer, int field, void *storage) __asm__("sub_4012C2");
extern char __cdecl serialize_dialogue_language_field(
    uint8_t *serializer, const char *field, uint8_t *storage,
    uint8_t *default_value) __asm__("sub_493527");
extern char __thiscall serialize_dialogue_camera_map_field(
    uint8_t *serializer, const char *field, unsigned int storage, int mode)
    __asm__("sub_47D0CB");
extern char __thiscall serialize_dialogue_listener_map_field(
    uint8_t *serializer, const char *field, unsigned int storage, int mode)
    __asm__("sub_47D14F");
extern int __thiscall serialize_dialogue_key_field(
    int storage, uint8_t *serializer, int field) __asm__("sub_48FEBA");
extern char __thiscall serialize_played_dialogue_index_field(
    uint8_t *serializer, const char *field, uint32_t *storage,
    uint32_t *default_value) __asm__("sub_492E42");
extern char __thiscall serialize_dialogue_sequence_vector(
    uint8_t *serializer, const char *field, int *storage, char mode)
    __asm__("sub_493225");
extern char __thiscall serialize_dialogue_line_vector(
    uint8_t *serializer, const char *field, int *storage, char mode)
    __asm__("sub_4932AC");
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                            const char *field, char *storage,
                                            char *default_value);
extern char __cdecl erase_dialogue_sequence_vector_range(
    int first_begin, int first_end, uint32_t *first_capacity, int second_begin,
    int second_end, int second_capacity, uint32_t *parent, int count,
    char owner) __asm__("sub_493B76");
extern char __cdecl erase_dialogue_line_vector_range(
    int first_begin, int first_end, uint32_t *first_capacity, int second_begin,
    int second_end, int second_capacity, uint32_t *parent, int count,
    char owner) __asm__("sub_493B9C");
extern void __thiscall remove_dialogue_line_vector_entry(uint32_t *collection)
    __asm__("sub_4925F2");
extern void __thiscall remove_dialogue_sequence_vector_entry(
    uint32_t *collection) __asm__("sub_492572");
extern uint32_t *__thiscall erase_played_dialogue_index_range(
    uint32_t *index, uint32_t *result, uint32_t *first, uint32_t *last);
extern uint32_t *__thiscall find_played_dialogue_index_node(
    uint32_t *index, int key) __asm__("sub_4927F6");
extern char __cdecl compare_played_dialogue_keys(int first, int second)
    __asm__("sub_48FF77");
extern uint32_t *__thiscall construct_played_dialogue_key(
    uint32_t *key, int first, int second, int third, char flags)
    __asm__("sub_48FE9A");
extern void __thiscall clear_dialogue_listener_map(uint32_t *collection)
    __asm__("sub_47EE16");
extern void __thiscall clear_dialogue_camera_map(uint32_t *collection)
    __asm__("sub_47C71B");
extern uint32_t *__thiscall construct_dialogue_camera_map(
    uint32_t *object, char *default_value);
extern uint32_t *__thiscall construct_dialogue_listener_map(
    uint32_t *object, char *default_value);
/* 0x48FE8A: Concurrency TaskStack constructor. */
extern void __thiscall construct_concurrency_task_stack(void *object);
extern uint32_t *__thiscall add_active_object_child_with_policy_callback(
    uint8_t *parent, int *child, char retain_reference);
extern const char Key[];
extern uint32_t *__thiscall advance_dialogue_sequence_iterator(
    uint32_t *iterator) __asm__("sub_491C3B");
extern int __thiscall adjust_dialogue_sequence_iterator(int *iterator,
                                                       int amount)
    __asm__("sub_49298A");
extern int *__thiscall erase_dialogue_sequence_iterator_range(
    int *collection, int *result, int first_begin, int first_end,
    uint32_t *first_position, int first_capacity, int second_begin,
    int second_end, uint32_t *second_position, int second_capacity)
    __asm__("sub_491DBB");
extern uint32_t *__thiscall advance_dialogue_line_iterator(
    uint32_t *iterator) __asm__("sub_492092");
extern int __thiscall adjust_dialogue_line_iterator(int *iterator, int amount)
    __asm__("sub_492A43");
extern int *__thiscall erase_dialogue_line_iterator_range(
    int *collection, int *result, int first_begin, int first_end,
    uint32_t *first_position, int first_capacity, int second_begin,
    int second_end, uint32_t *second_position, int second_capacity)
    __asm__("sub_491F49");

void __thiscall destroy_played_dialogue_line_list(uint32_t *list)
{
  int result;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)list[1];
  erase_played_dialogue_index_range(list, (uint32_t *)(void *)&result,
                                    (uint32_t *)(uintptr_t)*sentinel,
                                    sentinel);
  free_tracked_memory((int)(uintptr_t)sentinel);
  list[1] = 0;
  list[3] = 0;

  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);
  if (--played_dialogue_index_reference_count == 0) {
    free_tracked_memory(played_dialogue_index_sentinel_address);
    played_dialogue_index_sentinel_address = 0;
  }
  destroy_runtime_lockit(&lock_storage);
}

uint32_t *__thiscall clear_played_dialogue_index(uint32_t *index)
{
  int result = (int)(uintptr_t)index;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)index[1];
  return erase_played_dialogue_index_range(
      index, (uint32_t *)(void *)&result,
      (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)index[1], sentinel);
}

uint32_t *__thiscall clear_dialogue_play_history(uint32_t *manager)
{
  return clear_played_dialogue_index(
      (uint32_t *)(void *)((uint8_t *)(void *)manager + 160));
}

int *__thiscall find_played_dialogue_index_entry(uint32_t *index,
                                                 int *result, int key)
{
  uint32_t *entry = find_played_dialogue_index_node(index, key);
  if (entry == (uint32_t *)(uintptr_t)index[1]
      || compare_played_dialogue_keys(key, (int)(uintptr_t)(entry + 3))) {
    *result = (int)index[1];
  } else {
    *result = (int)(uintptr_t)entry;
  }
  return result;
}

char __thiscall has_played_dialogue_key(uint32_t *manager, int first,
                                        int second, int third, char flags)
{
  uint32_t key[4];
  int found_entry;
  construct_played_dialogue_key(key, first, second, third, flags);
  return *find_played_dialogue_index_entry(manager + 40, &found_entry,
                                            (int)(uintptr_t)key)
      != (int)manager[41];
}

uint32_t *__thiscall construct_dialogue_sequence_vector(
    uint32_t *vector, char *default_value)
{
  *(uint8_t *)(void *)vector = (uint8_t)*default_value;
  for (size_t field = 1; field != 12; ++field)
    vector[field] = 0;
  return vector;
}

uint32_t *__thiscall construct_dialogue_line_vector(
    uint32_t *vector, char *default_value)
{
  *(uint8_t *)(void *)vector = (uint8_t)*default_value;
  for (size_t field = 1; field != 12; ++field)
    vector[field] = 0;
  return vector;
}

int *__thiscall remove_dialogue_sequence_by_id(int *manager,
                                               int sequence_id)
{
  int current[4] = {manager[45], manager[46], manager[47], manager[48]};
  int end[4];

  for (;;) {
    end[0] = manager[49];
    end[1] = manager[50];
    end[2] = manager[51];
    end[3] = manager[52];
    int *entry = (int *)(uintptr_t)current[2];
    if (current[2] == end[2] || *entry == sequence_id)
      break;
    advance_dialogue_sequence_iterator((uint32_t *)(void *)current);
  }

  end[0] = manager[49];
  end[1] = manager[50];
  end[2] = manager[51];
  end[3] = manager[52];
  if (current[2] == end[2])
    return (int *)(uintptr_t)current[2];

  int sequence = *(int *)(uintptr_t)current[2];
  if (sequence != 0) {
    uint32_t *vtable = *(uint32_t **)(uintptr_t)sequence;
    void (__thiscall *destroy)(int, int) =
        (void (__thiscall *)(int, int))(uintptr_t)vtable[0];
    destroy(sequence, 1);
  }

  int first_begin = current[0];
  int first_end = current[1];
  uint32_t *first_position = (uint32_t *)(uintptr_t)current[2];
  int first_capacity = current[3];
  int second[4] = {current[0], current[1], current[2], current[3]};
  adjust_dialogue_sequence_iterator(second, 1);
  int result[4];
  return erase_dialogue_sequence_iterator_range(
      manager + 44, result, first_begin, first_end, first_position,
      first_capacity, second[0], second[1],
      (uint32_t *)(uintptr_t)second[2], second[3]);
}

int *__thiscall remove_dialogue_line_by_id(int *manager, int line_id)
{
  int current[4] = {manager[57], manager[58], manager[59], manager[60]};
  int end[4];

  for (;;) {
    end[0] = manager[61];
    end[1] = manager[62];
    end[2] = manager[63];
    end[3] = manager[64];
    int *entry = (int *)(uintptr_t)current[2];
    if (current[2] == end[2] || *entry == line_id)
      break;
    advance_dialogue_line_iterator((uint32_t *)(void *)current);
  }

  end[0] = manager[61];
  end[1] = manager[62];
  end[2] = manager[63];
  end[3] = manager[64];
  if (current[2] == end[2])
    return (int *)(uintptr_t)current[2];

  int line = *(int *)(uintptr_t)current[2];
  if (line != 0) {
    uint32_t *vtable = *(uint32_t **)(uintptr_t)line;
    void (__thiscall *destroy)(int, int) =
        (void (__thiscall *)(int, int))(uintptr_t)vtable[0];
    destroy(line, 1);
  }

  int first_begin = current[0];
  int first_end = current[1];
  uint32_t *first_position = (uint32_t *)(uintptr_t)current[2];
  int first_capacity = current[3];
  int second[4] = {current[0], current[1], current[2], current[3]};
  adjust_dialogue_line_iterator(second, 1);
  int result[4];
  return erase_dialogue_line_iterator_range(
      manager + 56, result, first_begin, first_end, first_position,
      first_capacity, second[0], second[1],
      (uint32_t *)(uintptr_t)second[2], second[3]);
}

int *__thiscall clear_dialogue_lines(int *manager)
{
  int current[4] = {manager[57], manager[58], manager[59], manager[60]};
  int end[4] = {manager[61], manager[62], manager[63], manager[64]};

  while (current[2] != end[2]) {
    int line = *(int *)(uintptr_t)current[2];
    if (line != 0) {
      uint32_t *vtable = *(uint32_t **)(uintptr_t)line;
      void (__thiscall *destroy)(int, int) =
          (void (__thiscall *)(int, int))(uintptr_t)vtable[0];
      destroy(line, 1);
    }
    advance_dialogue_line_iterator((uint32_t *)(void *)current);
  }

  return erase_dialogue_line_iterator_range(
      manager + 56, end, manager[57], manager[58],
      (uint32_t *)(uintptr_t)manager[59], manager[60], manager[61],
      manager[62], (uint32_t *)(uintptr_t)manager[63], manager[64]);
}

int __thiscall find_dialogue_line_by_name(uint32_t *manager,
                                          const char *name)
{
  int current[4] = {(int)manager[57], (int)manager[58],
                    (int)manager[59], (int)manager[60]};
  const int end = (int)manager[63];

  while (current[2] != end) {
    const int line = *(int *)(uintptr_t)current[2];
    const char *line_name = line != 0
        ? *(const char **)(uintptr_t)(line + 16)
        : NULL;
    if (line_name == NULL)
      line_name = Key;
    if (strcasecmp(name, line_name) == 0)
      return line;
    advance_dialogue_line_iterator((uint32_t *)(void *)current);
  }
  return 0;
}

void __thiscall initialize_played_dialogue_lines(uint32_t *list)
{
  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);

  if (played_dialogue_index_sentinel_address == 0) {
    uint32_t *sentinel = allocate_tracked_memory(56);
    sentinel[1] = 0;
    sentinel[13] = 1;
    played_dialogue_index_sentinel_address = (int)(uintptr_t)sentinel;
    sentinel[0] = 0;
    *(uint32_t *)(uintptr_t)(played_dialogue_index_sentinel_address + 8) = 0;
  }

  ++played_dialogue_index_reference_count;
  uint32_t *sentinel =
      (uint32_t *)(uintptr_t)played_dialogue_index_sentinel_address;
  uint32_t *node = allocate_tracked_memory(56);
  node[1] = (uint32_t)(uintptr_t)sentinel;
  node[13] = 0;
  list[1] = (uint32_t)(uintptr_t)node;
  list[3] = 0;
  node[0] = (uint32_t)(uintptr_t)node;
  *(uint32_t *)(void *)((uint8_t *)(void *)node + 8) =
      (uint32_t)(uintptr_t)node;

  destroy_runtime_lockit(&lock_storage);
}

char __thiscall serialize_dialogue_manager(uint32_t *manager,
                                           uint8_t *serializer, int mode)
{
  (void)mode;
  serialize_dialogue_string_field((int)(uintptr_t)serializer,
             (int)(uintptr_t)"mLine",
             (uint8_t *)(void *)manager + 12);
  serialize_dialogue_language_field(serializer, "mLanguage",
             (uint8_t *)(void *)manager + 28, byte_6BE250);
  serialize_dialogue_string_field((int)(uintptr_t)serializer,
             (int)(uintptr_t)"mCurrentConversation",
             (uint8_t *)(void *)manager + 32);
  serialize_dialogue_camera_map_field(serializer, "mDialogueCams",
             (unsigned int)(uintptr_t)manager + 48, 1);
  serialize_dialogue_listener_map_field(serializer, "mListeners",
             (unsigned int)(uintptr_t)manager + 96, 1);
  serialize_dialogue_key_field((int)(uintptr_t)manager + 144, serializer,
             (int)(uintptr_t)"mDlgKey");
  serialize_played_dialogue_index_field(serializer, "mLinesPlayed", manager + 40,
             (uint32_t *)1);
  serialize_dialogue_sequence_vector(serializer, "mSeqs", (int *)(void *)
             ((uint8_t *)(void *)manager + 176), 0);
  serialize_dialogue_line_vector(serializer, "mLines", (int *)(void *)
             ((uint8_t *)(void *)manager + 224), 0);
  return serialize_boolean_field(serializer, "mSequencePlaying",
      (char *)(void *)((uint8_t *)(void *)manager + 272), &byte_6A6454);
}

uint32_t *__thiscall destroy_dialogue_manager_members(uint32_t *manager)
{
  char owner = (char)(uintptr_t)manager;
  uint32_t application = (uint32_t)(uintptr_t)
      *(int *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t active_object_service =
      *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)(application + 68) + 28);

  *manager = (uint32_t)(uintptr_t)dialogue_manager_vtable;
  remove_active_object_child((int)active_object_service,
                             (int)(uintptr_t)manager);
  erase_dialogue_sequence_vector_range(
             manager[45], manager[46], (uint32_t *)(uintptr_t)manager[47],
             manager[48], manager[49], manager[50],
             (uint32_t *)(uintptr_t)manager[51], manager[52], owner);
  erase_dialogue_line_vector_range(
             manager[57], manager[58], (uint32_t *)(uintptr_t)manager[59],
             manager[60], manager[61], manager[62],
             (uint32_t *)(uintptr_t)manager[63], manager[64], owner);
  while (manager[67] != 0)
    remove_dialogue_line_vector_entry(manager + 56);
  while (manager[55] != 0)
    remove_dialogue_sequence_vector_entry(manager + 44);
  destroy_played_dialogue_line_list(manager + 40);
  while (manager[35] != 0)
    clear_dialogue_listener_map(manager + 24);
  while (manager[23] != 0)
    clear_dialogue_camera_map(manager + 12);
  tidy_std_string_storage((char *)(void *)((uint8_t *)(void *)manager + 12), 1);
  tidy_std_string_storage((char *)(void *)((uint8_t *)(void *)manager + 32), 1);
  erase_map_entry_impl(
      unk_7650C8, (uint32_t)dialogue_manager_base_offset_adjustment
          + (manager != NULL ? (uint32_t)(uintptr_t)manager + 9 : 0));
  *manager = (uint32_t)(uintptr_t)registered_object_base_vtable;
  return erase_map_entry_impl(
      broadcast_target_type_descriptor,
      (uint32_t)broadcast_target_base_offset_adjustment
          + (manager != NULL ? (uint32_t)(uintptr_t)(manager + 1) : 0));
}

uint32_t *__thiscall destroy_dialogue_manager(uint32_t *manager, char flags)
{
  destroy_dialogue_manager_members(manager);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}

char *__thiscall construct_registered_dialogue_manager(char *object,
                                                        int mode)
{
  char default_value_a;
  char default_value_b;
  uint8_t *bytes = (uint8_t *)(void *)object;

  (void)mode;
  find_or_create_registry_entry(
      broadcast_target_type_descriptor,
      (uint32_t)(uintptr_t)&object[broadcast_target_base_offset_adjustment + 4]);
  *(uint32_t *)(void *)bytes =
      (uint32_t)(uintptr_t)registered_object_base_vtable;
  find_or_create_registry_entry(
      unk_7650C8,
      (uint32_t)(uintptr_t)&object[
          dialogue_manager_base_offset_adjustment + 9]);
  bytes[12] = (uint8_t)default_value_b;
  tidy_std_string_storage((char *)(void *)(bytes + 12), 0);
  bytes[32] = (uint8_t)default_value_b;
  tidy_std_string_storage((char *)(void *)(bytes + 32), 0);
  construct_dialogue_camera_map((uint32_t *)(void *)(bytes + 48),
                                &default_value_b);
  construct_dialogue_listener_map((uint32_t *)(void *)(bytes + 96),
                                  &default_value_a);
  construct_concurrency_task_stack(bytes + 144);
  bytes[160] = (uint8_t)default_value_a;
  bytes[168] = 0;
  bytes[161] = (uint8_t)default_value_a;
  initialize_played_dialogue_lines((uint32_t *)(void *)(bytes + 160));
  construct_dialogue_sequence_vector((uint32_t *)(void *)(bytes + 176),
                                     &default_value_a);
  construct_dialogue_line_vector((uint32_t *)(void *)(bytes + 224),
                                &default_value_b);
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)dialogue_manager_vtable;
  return object;
}

int __thiscall construct_dialogue_manager(int object, int mode)
{
  char default_value_a;
  char default_value_b;
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t mode_byte = (uint8_t)((uint32_t)mode >> 24);

  construct_registered_object_base(bytes);
  find_or_create_registry_entry(unk_7650C8,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)dialogue_manager_base_offset_adjustment + 9);
  bytes[12] = mode_byte;
  tidy_std_string_storage((char *)(void *)(bytes + 12), 0);
  bytes[32] = mode_byte;
  tidy_std_string_storage((char *)(void *)(bytes + 32), 0);
  construct_dialogue_camera_map((uint32_t *)(void *)(bytes + 48),
                                &default_value_b);
  construct_dialogue_listener_map((uint32_t *)(void *)(bytes + 96),
                                  &default_value_a);
  construct_concurrency_task_stack(bytes + 144);
  bytes[160] = mode_byte;
  bytes[161] = mode_byte;
  bytes[168] = 0;
  initialize_played_dialogue_lines((uint32_t *)(void *)(bytes + 160));
  construct_dialogue_sequence_vector((uint32_t *)(void *)(bytes + 176),
                                     &default_value_a);
  construct_dialogue_line_vector((uint32_t *)(void *)(bytes + 224),
                                &default_value_b);
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)dialogue_manager_vtable;
  bytes[28] = (uint8_t)mode;
  int application = *(int *)(uintptr_t)(game_engine_instance_address + 1092);
  uint8_t *dialogue_service = *(uint8_t **)(uintptr_t)(
      *(uint32_t *)(uintptr_t)(application + 68) + 28);
  add_active_object_child_with_policy_callback(
      dialogue_service, (int *)(void *)bytes, 1);
  bytes[272] = 0;
  return object;
}

uint32_t *__cdecl allocate_registered_dialogue_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_7650C8,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_dialogue_manager(int mode)
{
  uint32_t *memory = allocate_registered_dialogue_manager(276);
  return memory
      ? (uint32_t *)(uintptr_t)construct_dialogue_manager(
            (int)(uintptr_t)memory, mode)
      : NULL;
}

uint32_t *__cdecl create_registered_dialogue_manager(void)
{
  uint32_t *memory = allocate_registered_dialogue_manager(276);
  return memory
      ? (uint32_t *)(void *)construct_registered_dialogue_manager(
            (char *)(void *)memory, 0)
      : NULL;
}
