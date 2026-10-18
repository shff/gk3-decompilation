#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);

/* gk3/GK3R_rest.c */
extern uint32_t primitive_manager_type_descriptor[15];
extern int primitive_manager_base_offset_adjustment;
extern int parent_control_default_object;
extern uint32_t primitive_manager_event_target_vtable[];
extern uint32_t primitive_manager_vtable[];
extern int __thiscall construct_parent_control(int object,
                                              uint32_t *engine_object);
extern uint32_t *__stdcall allocate_parent_control_list_node(
    uint32_t *previous, uint32_t *next);
extern uint32_t *__thiscall construct_control_settings(uint32_t *object);
extern int __thiscall construct_control_container_base(char *object, int mode);
extern int destroy_primitive_manager(uint32_t object);

int __thiscall construct_registered_primitive_manager(int object, int mode)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t mode_byte = (uint8_t)((uint32_t)mode >> 24);

  construct_control_container_base((char *)(void *)bytes, mode);
  construct_registered_event_target((uint16_t *)(void *)(bytes + 196));
  find_or_create_registry_entry(
      primitive_manager_type_descriptor,
      (uint32_t)(uintptr_t)(bytes + 208
          + primitive_manager_base_offset_adjustment));
  bytes[208] = mode_byte;
  *((uint32_t *)(void *)bytes + 53) =
      (uint32_t)(uintptr_t)allocate_parent_control_list_node(NULL, NULL);
  *((uint32_t *)(void *)bytes + 54) = 0;
  construct_control_settings((uint32_t *)(void *)bytes + 62);
  *((uint32_t *)(void *)bytes) = (uint32_t)(uintptr_t)primitive_manager_vtable;
  *((uint32_t *)(void *)bytes + 49) =
      (uint32_t)(uintptr_t)primitive_manager_event_target_vtable;
  return object;
}

uint16_t *__thiscall construct_primitive_manager(uint16_t *object)
{
  char default_value;
  construct_parent_control((int)(uintptr_t)object,
                           (uint32_t *)(uintptr_t)parent_control_default_object);
  construct_registered_event_target(object + 98);
  find_or_create_registry_entry(primitive_manager_type_descriptor,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)primitive_manager_base_offset_adjustment + 208);
  *((uint8_t *)(void *)object + 208) = (uint8_t)default_value;
  *((uint32_t *)(void *)object + 53) =
      (uint32_t)(uintptr_t)allocate_parent_control_list_node(NULL, NULL);
  *((uint32_t *)(void *)object + 54) = 0;
  construct_control_settings((uint32_t *)(void *)object + 62);
  *((uint32_t *)(void *)object) = (uint32_t)(uintptr_t)primitive_manager_vtable;
  *((uint32_t *)(void *)object + 49) =
      (uint32_t)(uintptr_t)primitive_manager_event_target_vtable;
  *((uint32_t *)(void *)object + 55) = 0;
  *((uint32_t *)(void *)object + 56) = 0;
  *((uint32_t *)(void *)object + 60) = 0;
  *((uint32_t *)(void *)object + 61) = 0;
  *((uint32_t *)(void *)object + 63) = (uint32_t)(uintptr_t)object;
  return object;
}

uint32_t *__cdecl allocate_registered_primitive_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(primitive_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_primitive_manager(void)
{
  uint16_t *memory = (uint16_t *)allocate_registered_primitive_manager(268);
  return memory ? (uint32_t *)(void *)construct_primitive_manager(memory)
                : NULL;
}

uint32_t *__cdecl create_registered_primitive_manager(void)
{
  uint16_t *memory = (uint16_t *)allocate_registered_primitive_manager(268);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_primitive_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

int shutdown_primitive_manager(uint32_t *manager)
{
  return destroy_primitive_manager((uint32_t)(uintptr_t)manager);
}
