#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_764D78[];
extern int cursor_spec_collection_base_offset_adjustment;
extern uint32_t cursor_spec_type_descriptor[16];
extern int empty_cursor_spec_name_address;
extern const char Key[4];
extern uint32_t cursor_spec_collection_vtable;
extern uint32_t cursor_spec_array_vtable;
extern uint32_t *__thiscall construct_dynamic_array(uint32_t *array,
                                                    int growth_capacity);
extern uint32_t *__thiscall initialize_collection_serialization_context(
    uint32_t *context, int serializer, const char *field_name, int flags);
extern char __thiscall serialize_registered_object_array(
    uint8_t *serializer, int array, int registry);
extern void __thiscall destroy_collection_serialization_context(int context);
extern char __thiscall serialize_cursor_spec_entry_fields(
    uint8_t *serializer, int array, char *context);
extern uint8_t *__cdecl append_string_suffix(uint8_t *result, char *first,
                                             char *suffix);
extern char __cdecl serialize_integer_value_field(uint8_t *serializer,
                                           const char *field_name,
                                           int *value, int *default_value);
extern char __cdecl serialize_array_count_field(uint8_t *serializer,
                                                const char *field_name,
                                                int *value,
                                                int *default_value);
extern void __thiscall resize_dynamic_array(uint32_t *array, int count);
extern int __thiscall tidy_std_string_storage(char *string_storage,
                                              char mode);
extern int __thiscall initialize_cursor_spec(int object, char *name);
extern int __cdecl compare_cursor_spec_names(const char *first, char *second,
                                            size_t count);
extern int __thiscall append_dynamic_array_element(uint32_t *array, int value);
extern int __thiscall destroy_pointer_vector_elements(int *array);
extern int __thiscall free_dynamic_array_storage(int *array);
extern void __cdecl free_tracked_memory(int address);

uint32_t *__cdecl allocate_registered_cursor_spec_collection(int size);
uint32_t *__cdecl allocate_registered_cursor_spec(int size);
void initialize_cursor_spec_collection(uint32_t *object);
char __thiscall serialize_cursor_spec_entry_count(uint8_t *serializer,
                                                   int array,
                                                   char *context);

char __thiscall serialize_cursor_spec_entry_fields(
    uint8_t *serializer, int array, char *context)
{
  int auto_delete = *(int *)(uintptr_t)(array + 20);
  uint8_t option_name_storage[16] = {0};
  const char *option_name = (const char *)(uintptr_t)
      *((uint32_t *)(void *)append_string_suffix(option_name_storage, context,
                                                 "-autoDelete") + 1);
  if (!option_name)
    option_name = Key;

  char result = serialize_integer_value_field(serializer, option_name,
                                        &auto_delete, &auto_delete);
  tidy_std_string_storage((char *)(void *)option_name_storage, 1);
  if (!serializer[4])
    *(int *)(uintptr_t)(array + 20) = auto_delete;
  if (!serialize_cursor_spec_entry_count(serializer, array, context))
    return 0;
  return result;
}

char __thiscall serialize_cursor_spec_entry_count(uint8_t *serializer,
                                                   int array,
                                                   char *context)
{
  int count = *(int *)(uintptr_t)(array + 8);
  uint8_t option_name_storage[16] = {0};
  const char *option_name = (const char *)(uintptr_t)
      *((uint32_t *)(void *)append_string_suffix(option_name_storage, context,
                                                 "-count") + 1);
  if (!option_name)
    option_name = Key;

  char result = serialize_array_count_field(serializer, option_name,
                                            &count, &count);
  tidy_std_string_storage((char *)(void *)option_name_storage, 1);
  resize_dynamic_array((uint32_t *)(uintptr_t)array, count);
  *(int *)(uintptr_t)(array + 8) = count;
  return result;
}

char __thiscall serialize_cursor_spec_collection_value(
    uint8_t *serializer, const char *field_name, int array, char required)
{
  uint32_t context[6];
  initialize_collection_serialization_context(
      context, (int)(uintptr_t)serializer, field_name, (required != 0) + 1);
  char result = serialize_cursor_spec_entry_fields(
      serializer, array, (char *)(void *)context);
  if (!serialize_registered_object_array(
          serializer, array, (int)(uintptr_t)cursor_spec_type_descriptor))
    result = 0;
  destroy_collection_serialization_context((int)(uintptr_t)context);
  return result;
}

uint32_t *construct_cursor_spec_collection(uint32_t *object)
{
  find_or_create_registry_entry(
      unk_764D78,
      (uint32_t)(uintptr_t)object
          + (uint32_t)cursor_spec_collection_base_offset_adjustment + 4);
  construct_dynamic_array(object + 1, 20);
  object[1] = (uint32_t)(uintptr_t)&cursor_spec_array_vtable;
  object[0] = (uint32_t)(uintptr_t)&cursor_spec_collection_vtable;
  initialize_cursor_spec_collection(object);
  return object;
}

uint32_t *__thiscall construct_registered_cursor_spec_collection(
    uint32_t *object, int mode)
{
  (void)mode;
  return construct_cursor_spec_collection(object);
}

uint32_t *create_registered_cursor_spec_collection(void)
{
  uint32_t *memory = allocate_registered_cursor_spec_collection(28);
  return memory ? construct_registered_cursor_spec_collection(memory, 0)
                : NULL;
}

char __thiscall serialize_cursor_spec_collection_fields(
    uint32_t *object, uint8_t *serializer, int serialization_flags)
{
  (void)serialization_flags;
  return serialize_cursor_spec_collection_value(
      serializer, "mCursorSpecs", (int)(uintptr_t)(object + 1), 0);
}

char __cdecl serialize_registered_cursor_spec_collection(
    int object, uint8_t *serializer, int serialization_flags)
{
  return serialize_cursor_spec_collection_fields(
      (uint32_t *)(uintptr_t)(uint32_t)object, serializer,
      serialization_flags);
}

void initialize_cursor_spec_collection(uint32_t *object)
{
  object[6] = 1;
}

uint32_t *__thiscall destroy_cursor_spec_collection_members(
    uint32_t *object)
{
  object[0] = (uint32_t)(uintptr_t)&cursor_spec_collection_vtable;
  uint32_t *array = object + 1;
  array[0] = (uint32_t)(uintptr_t)&cursor_spec_array_vtable;
  if (object[6])
    destroy_pointer_vector_elements((int *)(void *)array);
  free_dynamic_array_storage((int *)(void *)array);
  return erase_map_entry_impl(
      unk_764D78,
      (uint32_t)cursor_spec_collection_base_offset_adjustment
          + (uint32_t)(uintptr_t)array);
}

uint32_t *__thiscall delete_cursor_spec_collection(uint32_t *object,
                                                    char free_memory)
{
  destroy_cursor_spec_collection_members(object);
  if ((free_memory & 1) != 0)
    free_tracked_memory((int)(uintptr_t)object);
  return object;
}

int __thiscall find_or_create_cursor_spec(uint32_t *collection,
                                          char *name, int retain_reference)
{
  if (!name || !*name)
    name = (char *)(uintptr_t)empty_cursor_spec_name_address;

  uint32_t *specifications = collection + 1;
  int *entries = (int *)(uintptr_t)specifications[1];
  int *end = entries + specifications[2];
  int spec_address = 0;

  for (int *entry = entries; entry != end; ++entry) {
    const char *entry_name = *(const char **)(uintptr_t)(*entry + 4);
    if (!entry_name)
      entry_name = Key;
    if (compare_cursor_spec_names(entry_name, name, (size_t)-1)) {
      spec_address = *entry;
      break;
    }
  }

  if (!spec_address) {
    uint32_t *memory = allocate_registered_cursor_spec(32);
    spec_address = memory
        ? initialize_cursor_spec((int)(uintptr_t)memory, name) : 0;
    append_dynamic_array_element(specifications, spec_address);
  }

  if (retain_reference) {
    uint32_t *reference = *(uint32_t **)(uintptr_t)(spec_address + 16);
    void (__thiscall *retain)(uint32_t *object) =
        (void (__thiscall *)(uint32_t *))(uintptr_t)reference[1];
    retain(reference);
  }
  return spec_address;
}

uint32_t *__cdecl allocate_registered_cursor_spec(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(cursor_spec_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

int __thiscall destroy_cursor_spec_array(int *array)
{
  array[0] = (int)(uintptr_t)&cursor_spec_array_vtable;
  if (array[5])
    destroy_pointer_vector_elements(array);
  return free_dynamic_array_storage(array);
}

uint32_t *__cdecl allocate_registered_cursor_spec_collection(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_764D78,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_cursor_spec_collection(void)
{
  uint32_t *memory = allocate_registered_cursor_spec_collection(28);
  return memory ? construct_cursor_spec_collection(memory) : NULL;
}
