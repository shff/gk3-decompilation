#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern uint8_t *__thiscall construct_registered_object_base(
    uint8_t *object);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);
extern void __thiscall remove_pending_engine_event(uint32_t *engine,
                                                  int *event);
extern int *__thiscall replace_event_reference_and_queue_previous(
    int *reference, int *replacement);
extern int __thiscall queue_and_clear_event_reference(int *reference);

/* engine/dynamic_array.c */
extern int __thiscall vector_element_address(uint32_t *array, int index);
extern int __thiscall destroy_pointer_vector_elements(int *array);
extern int __thiscall free_dynamic_array_storage(int *array);

/* engine/active_objects.c */
extern uint32_t *__thiscall add_active_object_child(
    int object, int *child, char retain_reference);
extern void __thiscall remove_active_object_child(int object, int child);

/* gk3/layer_manager.c */
extern int get_scene_layer(void);

/* gk3/GK3R_rest.c */
extern uint32_t animator_type_descriptor[15];
extern int animator_base_offset_adjustment;
extern uint32_t animation_record_type_descriptor[15];
extern int animation_record_base_offset_adjustment;
extern uint32_t broadcast_target_type_descriptor[15];
extern int broadcast_target_base_offset_adjustment;
extern uint32_t animator_object_vtable[];
extern uint32_t animator_vtable[];
extern uint32_t animator_animation_array_vtable[];
extern uint32_t registered_object_base_vtable[];
extern uint32_t animator_pointer_array_vtable[];
extern uint32_t animation_record_state_array_vtable[];
extern int game_engine_address;
extern uint32_t *__thiscall construct_dynamic_array(uint32_t *object,
                                                    int growth_capacity);
extern uint32_t *__thiscall construct_byte_list(uint32_t *object,
                                                uint8_t *default_value);
extern uint16_t *__thiscall initialize_event_target_subobject(
    uint16_t *object, int mode);
extern void __thiscall restore_animation_target_pose(float *target);
extern uint32_t *__thiscall advance_animation_iterator(uint32_t *iterator);
extern void __thiscall release_animation_state_collection_storage(int storage);
extern int *__thiscall erase_segmented_storage_range(
    int *storage, int *position, int begin, int end, uint32_t *current,
    int current_page_flag, int page_cursor, int directory_cursor,
    uint32_t *directory_end, int directory_capacity);
extern uint32_t *__thiscall destroy_registered_event_target(uint16_t *object);
extern char __thiscall serialize_actor_array_field(
    uint8_t *serializer, const char *field_name, int *value, char flags);
extern uint8_t *__cdecl append_string_suffix(uint8_t *result, char *first,
                                             char *suffix);
extern char __cdecl serialize_array_count_field(uint8_t *serializer,
                                                const char *field_name,
                                                int *value,
                                                int *default_value);
extern char __cdecl serialize_integer_value_field(uint8_t *serializer,
                                            const char *field_name,
                                            int *value, int *default_value);
extern void __thiscall resize_dynamic_array(uint32_t *array, int count);
extern uint32_t *__thiscall initialize_collection_serialization_context(
    uint32_t *context, int serializer, const char *field_name, int flags);
extern void __thiscall destroy_collection_serialization_context(int context);
extern char __thiscall serialize_registered_object_array(
    uint8_t *serializer, int array, int registry);
extern int __thiscall tidy_std_string_storage(char *string_storage,
                                               char mode);
extern const char Key[4];
extern int __thiscall stop_engine_animation(uint32_t *engine,
                                            uint16_t animation_id, int flags,
                                            int reserved);
extern int __thiscall stop_engine_morph_animation(uint32_t *engine,
                                                  uint16_t animation_id,
                                                  int flags);
extern int __thiscall remove_dynamic_array_element(uint32_t *array, int value);
extern void __cdecl free_tracked_memory(int address);

uint32_t *__thiscall construct_registered_animator(uint32_t *object,
                                                    int mode);
char __thiscall serialize_animator_fields(uint32_t *animator,
                                           uint8_t *serializer,
                                           int serialization_flags);
uint32_t *__thiscall destroy_animation_record_members(int *record);
uint32_t *__thiscall stop_animation_record(int *record, char clear_event);
int __thiscall clear_animation_record_event_reference(int *record);
int __thiscall clear_animation_state_collection(uint32_t *collection);
void __thiscall pop_animation_state_collection_entry(uint32_t *collection);
uint32_t *__thiscall restore_animation_record_targets(int *record);
void __thiscall remove_non_morph_animations(uint32_t *animator,
                                           int animation_id, char flags);
void __thiscall remove_morph_animations(uint32_t *animator, char flags);
int *__thiscall clear_animation_record_state_stack(char *record);
int *__thiscall clear_animator_animation_record_states(uint32_t *animator);
int *__thiscall clear_animator_state_stack(uint32_t *animator);
int *__thiscall stop_and_clear_animator_state(uint32_t *animator);
int *__thiscall stop_and_clear_animator_records(uint32_t *animator);
char __thiscall serialize_animation_record_array(
    uint8_t *serializer, const char *field_name, int array, char flags);

void __thiscall pop_animation_state_collection_entry(uint32_t *collection)
{
  int *previous_page = (int *)(uintptr_t)collection[4];
  advance_animation_iterator(collection + 1);
  if (collection[11]-- == 1) {
    release_animation_state_collection_storage((int)(uintptr_t)collection);
  } else if ((uint32_t)(uintptr_t)previous_page != collection[4]) {
    free_tracked_memory(*previous_page);
    *previous_page = 0;
  }
}

int __thiscall clear_animation_state_collection(uint32_t *collection)
{
  while (collection[11] != 0)
    pop_animation_state_collection_entry(collection);
  return 0;
}

int *__thiscall clear_animation_record_state_stack(char *record)
{
  int *storage = (int *)(void *)(record + 40);
  int position[4];
  return erase_segmented_storage_range(
      storage, position, storage[1], storage[2],
      (uint32_t *)(uintptr_t)storage[3], storage[4], storage[5], storage[6],
      (uint32_t *)(uintptr_t)storage[7],
      storage[8]);
}

int *__thiscall clear_animator_animation_record_states(uint32_t *animator)
{
  uint32_t *record_addresses = (uint32_t *)(uintptr_t)animator[7];
  const uint32_t *end = record_addresses + animator[8];
  int *result = (int *)(uintptr_t)animator[8];

  for (; record_addresses != end; ++record_addresses) {
    char *record = (char *)(uintptr_t)*record_addresses;
    result = clear_animation_record_state_stack(record);
  }
  return result;
}

int *__thiscall clear_animator_state_stack(uint32_t *animator)
{
  clear_animator_animation_record_states(animator);

  int *storage = (int *)(void *)(animator + 12);
  int position[4];
  return erase_segmented_storage_range(
      storage, position, storage[1], storage[2],
      (uint32_t *)(uintptr_t)storage[3], storage[4], storage[5], storage[6],
      (uint32_t *)(uintptr_t)storage[7],
      storage[8]);
}

int *__thiscall stop_and_clear_animator_state(uint32_t *animator)
{
  remove_non_morph_animations(animator, 0xFFFF, 0);
  remove_morph_animations(animator, 0);
  return clear_animator_state_stack(animator);
}

int *__thiscall stop_and_clear_animator_records(uint32_t *animator)
{
  remove_non_morph_animations(animator, 0xFFFF, 0);
  remove_morph_animations(animator, 0);
  return clear_animator_animation_record_states(animator);
}

uint32_t *__thiscall restore_animation_record_targets(int *record)
{
  int iterator[4] = {
      record[11], record[12], record[13], record[14]};
  const uint32_t end = (uint32_t)record[17];
  int index = 0;

  while ((uint32_t)iterator[2] != end) {
    const uint32_t target_address =
        *(uint32_t *)(uintptr_t)iterator[2];
    if (target_address != 0
        && *(uint32_t *)(uintptr_t)vector_element_address(
               (uint32_t *)(void *)(record + 22), index) == 0
        && (uint8_t)record[32] == 0) {
      const uint32_t pose_address =
          *(uint32_t *)(uintptr_t)(target_address + 100);
      restore_animation_target_pose((float *)(uintptr_t)pose_address);
    }
    advance_animation_iterator((uint32_t *)(void *)iterator);
    ++index;
  }

  return (uint32_t *)(uintptr_t)iterator[2];
}

uint32_t *allocate_registered_animator(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(animator_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

int __thiscall construct_animator(int object)
{
  uint8_t *animator = (uint8_t *)(uintptr_t)(uint32_t)object;
  uint8_t animation_state = 0;

  construct_registered_event_target((uint16_t *)(void *)animator);
  construct_registered_object_base(animator + 12);
  find_or_create_registry_entry(
      animator_type_descriptor,
      (uint32_t)object + (uint32_t)animator_base_offset_adjustment + 21);

  uint32_t *animations = (uint32_t *)(void *)(animator + 24);
  construct_dynamic_array(animations, 20);
  animations[0] = (uint32_t)(uintptr_t)animator_animation_array_vtable;
  construct_byte_list((uint32_t *)(void *)(animator + 48),
                      &animation_state);

  *(uint32_t *)(void *)animator = (uint32_t)(uintptr_t)animator_vtable;
  *(uint32_t *)(void *)(animator + 12) =
      (uint32_t)(uintptr_t)animator_object_vtable;
  *(uint32_t *)(void *)(animator + 44) = 1;
  return object;
}

uint32_t *__thiscall construct_registered_animator(uint32_t *object,
                                                    int mode)
{
  uint8_t *animator = (uint8_t *)(void *)object;
  initialize_event_target_subobject((uint16_t *)(void *)animator, mode);
  find_or_create_registry_entry(
      broadcast_target_type_descriptor,
      (uint32_t)(uintptr_t)animator
          + (uint32_t)broadcast_target_base_offset_adjustment + 16);
  *(uint32_t *)(void *)(animator + 12) =
      (uint32_t)(uintptr_t)registered_object_base_vtable;
  find_or_create_registry_entry(
      animator_type_descriptor,
      (uint32_t)(uintptr_t)animator
          + (uint32_t)animator_base_offset_adjustment + 21);
  construct_dynamic_array((uint32_t *)(void *)(animator + 24), 20);
  *(uint32_t *)(void *)(animator + 24) =
      (uint32_t)(uintptr_t)animator_animation_array_vtable;
  construct_byte_list((uint32_t *)(void *)(animator + 48),
                      (uint8_t *)(void *)&mode + 3);
  *(uint32_t *)(void *)animator = (uint32_t)(uintptr_t)animator_vtable;
  *(uint32_t *)(void *)(animator + 12) =
      (uint32_t)(uintptr_t)animator_object_vtable;
  return object;
}

int create_registered_animator(void)
{
  uint32_t *memory = allocate_registered_animator(96);
  return memory
      ? (int)(uintptr_t)construct_registered_animator(memory, 0)
      : 0;
}

char __thiscall serialize_animation_record_array_count(
    uint8_t *serializer, uint32_t *array, char *field_context)
{
  const char *context =
      *(const char **)(uintptr_t)(field_context + sizeof(uint32_t));
  if (context == NULL)
    context = Key;

  int count = (int)array[2];
  uint8_t count_name_storage[16] = {0};
  const char *count_name = (const char *)(uintptr_t)
      *((uint32_t *)(void *)append_string_suffix(
          count_name_storage, (char *)(uintptr_t)context, "-count") + 1);
  if (count_name == NULL)
    count_name = Key;

  const char result = serialize_array_count_field(
      serializer, count_name, &count, &count);
  tidy_std_string_storage((char *)(void *)count_name_storage, 1);
  resize_dynamic_array(array, count);
  array[2] = (uint32_t)count;
  return result;
}

char __thiscall serialize_animation_record_array_options(
    uint8_t *serializer, uint32_t *array, char *field_context)
{
  const char *context =
      *(const char **)(uintptr_t)(field_context + sizeof(uint32_t));
  if (context == NULL)
    context = Key;

  int auto_delete = (int)array[5];
  uint8_t option_name_storage[16] = {0};
  const char *option_name = (const char *)(uintptr_t)
      *((uint32_t *)(void *)append_string_suffix(
          option_name_storage, (char *)(uintptr_t)context, "-autoDelete") + 1);
  if (option_name == NULL)
    option_name = Key;

  const char result = serialize_integer_value_field(
      serializer, option_name, &auto_delete, &auto_delete);
  tidy_std_string_storage((char *)(void *)option_name_storage, 1);
  if (!serializer[4])
    array[5] = (uint32_t)auto_delete;
  if (!serialize_animation_record_array_count(serializer, array,
                                               field_context))
    return 0;
  return result;
}

char __thiscall serialize_animation_record_array(
    uint8_t *serializer, const char *field_name, int array_address, char flags)
{
  uint32_t field_context[6];
  initialize_collection_serialization_context(
      field_context, (int)(uintptr_t)serializer, field_name, (flags != 0) + 1);

  uint32_t *array = (uint32_t *)(uintptr_t)array_address;
  char result = serialize_animation_record_array_options(
      serializer, array, (char *)(void *)field_context);
  if (!serialize_registered_object_array(
          serializer, array_address,
          (int)(uintptr_t)animation_record_type_descriptor))
    result = 0;
  destroy_collection_serialization_context((int)(uintptr_t)field_context);
  return result;
}

char __thiscall serialize_animator_fields(uint32_t *animator,
                                           uint8_t *serializer,
                                           int serialization_flags)
{
  (void)serialization_flags;
  serialize_animation_record_array(
      serializer, "mCurAnims", (int)(uintptr_t)(animator + 6), 0);
  return serialize_actor_array_field(
      serializer, "mActors", (int *)(void *)(animator + 12), 0);
}

char __cdecl serialize_registered_animator(int object,
                                            uint8_t *serializer,
                                            int serialization_flags)
{
  return serialize_animator_fields(
      (uint32_t *)(uintptr_t)(uint32_t)object, serializer,
      serialization_flags);
}

uint32_t *__thiscall destroy_animator_members(uint32_t *animator)
{
  uint8_t *object = (uint8_t *)(void *)animator;
  uint8_t *registered_object = object + 12;

  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)animator_vtable;
  *(uint32_t *)(void *)registered_object =
      (uint32_t)(uintptr_t)animator_object_vtable;
  clear_animation_state_collection((uint32_t *)(void *)(object + 48));

  uint32_t *animations = (uint32_t *)(void *)(object + 24);
  animations[0] = (uint32_t)(uintptr_t)animator_pointer_array_vtable;
  if (*(uint32_t *)(void *)(object + 44))
    destroy_pointer_vector_elements((int *)(void *)animations);
  free_dynamic_array_storage((int *)(void *)animations);

  erase_map_entry_impl(
      animator_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)animator_base_offset_adjustment + 21);
  *(uint32_t *)(void *)registered_object =
      (uint32_t)(uintptr_t)registered_object_base_vtable;
  erase_map_entry_impl(
      broadcast_target_type_descriptor,
      (uint32_t)(uintptr_t)(registered_object + sizeof(uint32_t))
          + (uint32_t)broadcast_target_base_offset_adjustment);
  return destroy_registered_event_target((uint16_t *)(void *)object);
}

uint32_t *__thiscall destroy_animation_record_members(int *record)
{
  replace_event_reference_and_queue_previous(record + 29, NULL);
  free_dynamic_array_storage(record + 22);
  clear_animation_state_collection((uint32_t *)(void *)(record + 10));
  record[4] = (int)(uintptr_t)animation_record_state_array_vtable;
  if (record[9])
    destroy_pointer_vector_elements(record + 4);
  free_dynamic_array_storage(record + 4);
  return erase_map_entry_impl(
      animation_record_type_descriptor,
      (uint32_t)(uintptr_t)record
          + (uint32_t)animation_record_base_offset_adjustment);
}

uint32_t *__thiscall set_animation_record_stopped_state(int *record)
{
  uint32_t *result = restore_animation_record_targets(record);
  record[2] = 3;
  return result;
}

uint32_t *__thiscall stop_animation_record(int *record, char clear_event)
{
  if (clear_event)
    clear_animation_record_event_reference(record);
  else {
    record[29] = 0;
    record[30] = 0;
  }
  return set_animation_record_stopped_state(record);
}

int __thiscall clear_animation_record_event_reference(int *record)
{
  return queue_and_clear_event_reference(record + 29);
}

int __thiscall destroy_animator_animation_array(int *animations)
{
  *animations = (int)(uintptr_t)animator_pointer_array_vtable;
  if (animations[5])
    destroy_pointer_vector_elements(animations);
  return free_dynamic_array_storage(animations);
}

void __stdcall destroy_animation_record_and_free(int *record)
{
  if (record) {
    destroy_animation_record_members(record);
    free_tracked_memory((int)(uintptr_t)record);
  }
}

void __thiscall destroy_owned_animation_record(int **record_address)
{
  int *record = *record_address;
  if (record) {
    destroy_animation_record_members(record);
    free_tracked_memory((int)(uintptr_t)record);
  }
}

static int __thiscall find_animation_record_index(uint32_t *animations,
                                                   int animation_id,
                                                   char morph)
{
  if ((int)animations[2] <= 0)
    return -1;

  for (int index = 0; index < (int)animations[2]; ++index) {
    const int record_address =
        *(int *)(uintptr_t)vector_element_address(animations, index);
    if (record_address != 0
        && *(int *)(uintptr_t)(record_address + 4) == animation_id
        && *(uint8_t *)(uintptr_t)(record_address + 112) == (uint8_t)morph)
      return index;
  }
  return -1;
}

void __thiscall destroy_animator_animation_record(
    uint32_t *animator, int *record)
{
  if (record != NULL) {
    destroy_animation_record_members(record);
    free_tracked_memory((int)(uintptr_t)record);
  }
  remove_dynamic_array_element(animator + 6, (int)(uintptr_t)record);
}

static void __thiscall remove_animator_animation(
    uint32_t *animator, char morph, int animation_id, int flags,
    char record_flags)
{
  uint32_t *engine = (uint32_t *)(uintptr_t)(uint32_t)game_engine_address;
  if (morph)
    stop_engine_morph_animation(engine, (uint16_t)animation_id, 0);
  else
    stop_engine_animation(engine, (uint16_t)animation_id, flags, 0);

  const int index = find_animation_record_index(animator + 6,
                                                animation_id, morph);
  if (index < 0)
    return;

  int *record = (int *)(uintptr_t)
      *(uint32_t *)(uintptr_t)vector_element_address(animator + 6, index);
  stop_animation_record(record, record_flags);
  int event[2] = { (int)animator[2], record[0] };
  remove_pending_engine_event(engine, event);
  destroy_animator_animation_record(animator, record);
}

void __thiscall remove_non_morph_animation_by_id(
    uint32_t *animator, int animation_id, int flags, char record_flags)
{
  remove_animator_animation(animator, 0, animation_id, flags, record_flags);
}

void __thiscall remove_morph_animation_by_id(uint32_t *animator,
                                             int animation_id,
                                             char record_flags)
{
  remove_animator_animation(animator, 1, animation_id, 0, record_flags);
}

void __thiscall remove_non_morph_animations(uint32_t *animator,
                                            int animation_id, char flags)
{
  while ((int)animator[8] > 0) {
    const int record_address = *(int *)(uintptr_t)
        vector_element_address(animator + 6, 0);
    if (!*(uint8_t *)(uintptr_t)(record_address + 112))
      remove_non_morph_animation_by_id(
          animator, *(int *)(uintptr_t)(record_address + 4),
          animation_id, flags);
  }
}

void __thiscall remove_morph_animations(uint32_t *animator, char flags)
{
  while (animator[8] != 0) {
    const int record_address = *(int *)(uintptr_t)
        vector_element_address(animator + 6, 0);
    if (*(uint8_t *)(uintptr_t)(record_address + 112))
      remove_morph_animation_by_id(
          animator, *(int *)(uintptr_t)(record_address + 4), flags);
  }
}

uint32_t *construct_application_animator(void)
{
  uint32_t *memory = allocate_registered_animator(96);
  return memory
      ? (uint32_t *)(uintptr_t)construct_animator((int)(uintptr_t)memory)
      : NULL;
}

void attach_animator_to_engine(uint32_t *animator)
{
  int *animator_state = animator != NULL ? (int *)(void *)(animator + 3) : NULL;
  add_active_object_child(get_scene_layer(), animator_state, 1);
}

void shutdown_animator(uint32_t *animator)
{
  uint32_t *current_animator = (uint32_t *)(uintptr_t)get_scene_layer();
  remove_active_object_child(
      (int)(uintptr_t)current_animator,
      animator != NULL ? (int)(uintptr_t)(animator + 3) : 0);
  remove_non_morph_animations(animator, 0xFFFF, 0);
  remove_morph_animations(animator, 0);
}
