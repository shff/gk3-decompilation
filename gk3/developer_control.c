#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t developer_control_type_descriptor[];
extern int __thiscall construct_developer_control(int object);
extern int __thiscall populate_developer_control_menu(int developer_control);
extern int __thiscall attach_developer_control_to_interface(
    uint8_t *developer_control);
extern int __thiscall developer_control_shutdown_noop(uint32_t object);

uint32_t *__cdecl allocate_registered_developer_control(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(developer_control_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_developer_control(void)
{
  uint32_t *memory = allocate_registered_developer_control(436);
  return memory
      ? (uint32_t *)(uintptr_t)construct_developer_control(
            (int)(uintptr_t)memory)
      : NULL;
}

int initialize_developer_control(uint32_t *developer_control)
{
  uint8_t *object = (uint8_t *)(void *)developer_control;
  uint32_t *vtable = *(uint32_t **)(void *)object;
  typedef int (__thiscall *EnableDeveloperControlMethod)(uint8_t *, int);

  populate_developer_control_menu((int)(uintptr_t)object);
  attach_developer_control_to_interface(object);
  EnableDeveloperControlMethod enable =
      (EnableDeveloperControlMethod)(uintptr_t)vtable[176 / sizeof(uint32_t)];
  return enable(object, 1);
}

int shutdown_developer_control(uint32_t *developer_control)
{
  return developer_control_shutdown_noop((uint32_t)(uintptr_t)developer_control);
}

char __thiscall is_developer_control_option_enabled(
    uint8_t *developer_control, int option)
{
  return developer_control[option + 157];
}
