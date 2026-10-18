#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t generics_manager_type_descriptor[15]
    __asm__("dword_765CC8");
extern int generics_manager_base_offset_adjustment __asm__("dword_765CC4");
extern uint32_t generics_manager_vtable[] __asm__("off_6C30DC");
extern uint32_t generic_waiter_array_vtable[] __asm__("off_6C30E0");
extern uint32_t generic_waiter_event_target_vtable[]
    __asm__("off_6ACD94");
extern uint32_t generic_waiter_vtable[] __asm__("off_6ACD9C");
extern uint32_t registered_object_base_vtable[];
extern uint32_t generic_waiter_type_descriptor[15]
    __asm__("dword_765F08");
extern int generic_waiter_base_offset_adjustment __asm__("dword_765F04");
extern uint32_t broadcast_target_type_descriptor[15];
extern int broadcast_target_base_offset_adjustment;
extern uint8_t *__thiscall construct_registered_object_base(
    uint8_t *object);
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);
extern uint16_t *__thiscall initialize_event_target_subobject(
    uint16_t *object, int mode) __asm__("sub_406D36");
extern uint32_t *__thiscall construct_dynamic_array(uint32_t *object,
                                                    int growth_capacity);
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern int __thiscall destroy_pointer_vector_elements(int *collection);

int __thiscall construct_generic_waiter(int object)
{
  uint8_t *waiter = (uint8_t *)(uintptr_t)(uint32_t)object;
  construct_registered_object_base(waiter);
  construct_registered_event_target((uint16_t *)(void *)(waiter + 8));
  find_or_create_registry_entry(
      generic_waiter_type_descriptor,
      (uint32_t)object + (uint32_t)generic_waiter_base_offset_adjustment + 20);
  *(uint32_t *)(void *)(waiter + 24) = 0;
  *(uint32_t *)(void *)(waiter + 20) = 0;
  *(uint32_t *)(void *)(waiter + 8) =
      (uint32_t)(uintptr_t)generic_waiter_event_target_vtable;
  *(uint32_t *)(void *)waiter = (uint32_t)(uintptr_t)generic_waiter_vtable;
  return object;
}

uint16_t *__thiscall construct_registered_generic_waiter(uint16_t *object,
                                                          int mode)
{
  uint8_t *bytes = (uint8_t *)(void *)object;
  const int address = (int)(uintptr_t)object;
  find_or_create_registry_entry(
      broadcast_target_type_descriptor,
      (uint32_t)address
          + (uint32_t)broadcast_target_base_offset_adjustment + 4);
  *(uint32_t *)(void *)bytes =
      (uint32_t)(uintptr_t)registered_object_base_vtable;
  initialize_event_target_subobject(object + 4, mode);
  find_or_create_registry_entry(
      generic_waiter_type_descriptor,
      (uint32_t)address + (uint32_t)generic_waiter_base_offset_adjustment + 20);
  *(uint32_t *)(void *)(bytes + 24) = 0;
  *(uint32_t *)(void *)(bytes + 8) =
      (uint32_t)(uintptr_t)generic_waiter_event_target_vtable;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)generic_waiter_vtable;
  return object;
}

uint32_t *__thiscall initialize_fsm_collection(uint32_t *collection,
                                               char *default_value)
{
  uint8_t *bytes = (uint8_t *)(void *)collection;
  bytes[0] = (uint8_t)*default_value;
  for (int index = 1; index < 12; ++index)
    collection[index] = 0;
  return collection;
}

uint32_t *__thiscall construct_registered_generics_manager(
    uint32_t *object, int mode)
{
  char default_value = (char)((uint32_t)mode >> 24);

  find_or_create_registry_entry(
      generics_manager_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)generics_manager_base_offset_adjustment + 4);
  construct_dynamic_array(object + 1, 20);
  object[1] = (uint32_t)(uintptr_t)generic_waiter_array_vtable;
  construct_registered_generic_waiter((uint16_t *)(void *)object + 14, mode);
  initialize_fsm_collection(object + 14, (char *)(void *)&default_value);
  *((uint8_t *)(void *)object + 104) = (uint8_t)default_value;
  tidy_std_string_storage((char *)(void *)object + 104, 0);
  object[0] = (uint32_t)(uintptr_t)generics_manager_vtable;
  return object;
}

uint32_t *__thiscall construct_generics_manager(uint32_t *object)
{
  char default_value;
  find_or_create_registry_entry(
      generics_manager_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)generics_manager_base_offset_adjustment + 4);
  construct_dynamic_array(object + 1, 20);
  object[1] = (uint32_t)(uintptr_t)generic_waiter_array_vtable;
  construct_generic_waiter((int)(uintptr_t)(object + 7));
  initialize_fsm_collection(object + 14, &default_value);
  *((uint8_t *)(void *)object + 104) = (uint8_t)default_value;
  tidy_std_string_storage((char *)(void *)object + 104, 0);
  object[0] = (uint32_t)(uintptr_t)generics_manager_vtable;
  return object;
}

uint32_t *__cdecl allocate_registered_generics_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(generics_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_generics_manager(void)
{
  uint32_t *memory = allocate_registered_generics_manager(120);
  return memory ? construct_generics_manager(memory) : NULL;
}

uint32_t *__cdecl create_registered_generics_manager(void)
{
  uint32_t *memory = allocate_registered_generics_manager(120);
  return memory ? construct_registered_generics_manager(memory, 0) : NULL;
}

int shutdown_generics_manager(uint32_t *manager)
{
  return destroy_pointer_vector_elements((int *)(void *)(manager + 1));
}
