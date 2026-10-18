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
extern uint32_t mini_console_type_descriptor[];
extern int mini_console_base_offset_adjustment;
extern uint32_t mini_console_vtable;
extern int mini_console_coordinate_default_a;
extern int mini_console_coordinate_default_b;
extern int mini_console_integer_default;
extern uint32_t mini_console_display_type_descriptor[15];
extern uint32_t mini_console_command_type_descriptor[15];
extern int mini_console_background_type_descriptor[15];
extern int game_engine_instance_address;
extern int __thiscall construct_console_control_base(int object);
extern uint32_t *__thiscall destroy_mini_console_control_base(
    uint32_t *object);
extern int __thiscall construct_control_container_base(char *object, int mode);
extern void __thiscall detach_control_from_service(
    int service, uint8_t *object);
extern int __thiscall attach_control_to_service(
    int service, int manager, char active);
extern void __thiscall initialize_mini_console_version_display(
    uint32_t *display);
extern int __thiscall initialize_mini_console(int console);
extern char __thiscall serialize_integer_field_with_supplied_default(
    uint8_t *serializer, const char *field_name, int *value,
    int *default_value);
extern void __cdecl free_tracked_memory(int address);

uint32_t *__cdecl allocate_registered_mini_console(int size);

uint32_t *__thiscall construct_mini_console(uint32_t *console)
{
  construct_console_control_base((int)(uintptr_t)console);
  find_or_create_registry_entry(
      mini_console_type_descriptor,
      (uint32_t)(uintptr_t)console
          + (uint32_t)mini_console_base_offset_adjustment + 197);
  console[0] = (uint32_t)(uintptr_t)&mini_console_vtable;
  console[50] = (uint32_t)mini_console_coordinate_default_a;
  console[52] = 0;
  console[53] = 0;
  console[54] = 0;
  console[51] = (uint32_t)mini_console_coordinate_default_b;
  initialize_mini_console((int)(uintptr_t)console);
  return console;
}

uint32_t *__thiscall construct_registered_mini_console(uint32_t *console,
                                                        int mode)
{
  construct_control_container_base((char *)(void *)console, mode);
  find_or_create_registry_entry(
      mini_console_type_descriptor,
      (uint32_t)(uintptr_t)console
          + (uint32_t)mini_console_base_offset_adjustment + 197);
  console[0] = (uint32_t)(uintptr_t)&mini_console_vtable;
  return console;
}

uint32_t *create_registered_mini_console(void)
{
  uint32_t *memory = allocate_registered_mini_console(220);
  return memory ? construct_registered_mini_console(memory, 0) : NULL;
}

char __thiscall serialize_mini_console_fields(uint32_t *console,
                                              uint8_t *serializer,
                                              int serialization_flags)
{
  (void)serialization_flags;
  serialize_integer_field_with_supplied_default(serializer, "mOffset",
                          (int *)(void *)(console + 50),
                          &mini_console_integer_default);
  uint32_t *methods = *(uint32_t **)(void *)serializer;
  ((void (__thiscall *)(uint8_t *, const char *, int *, uint32_t *))
      (uintptr_t)methods[68 / 4])(
      serializer, "mDisplay", (int *)(void *)(console + 52),
      mini_console_display_type_descriptor);
  ((void (__thiscall *)(uint8_t *, const char *, int *, uint32_t *))
      (uintptr_t)methods[68 / 4])(
      serializer, "mCommand", (int *)(void *)(console + 53),
      mini_console_command_type_descriptor);
  return (char)((int (__thiscall *)(uint8_t *, const char *, int *, int *))
      (uintptr_t)methods[68 / 4])(
      serializer, "mBackground", (int *)(void *)(console + 54),
      mini_console_background_type_descriptor);
}

char __cdecl serialize_registered_mini_console(int object,
                                                uint8_t *serializer,
                                                int serialization_flags)
{
  return serialize_mini_console_fields(
      (uint32_t *)(uintptr_t)(uint32_t)object, serializer,
      serialization_flags);
}

uint32_t *__thiscall destroy_mini_console_members(uint32_t *console)
{
  console[0] = (uint32_t)(uintptr_t)&mini_console_vtable;
  for (int index = 52; index <= 54; ++index) {
    uint32_t *child = (uint32_t *)(uintptr_t)console[index];
    if (child) {
      uint32_t *methods = *(uint32_t **)(void *)child;
      void (__thiscall *destroy)(uint32_t *object, int free_memory) =
          (void (__thiscall *)(uint32_t *, int))(uintptr_t)methods[0];
      destroy(child, 1);
    }
  }
  erase_map_entry_impl(
      mini_console_type_descriptor,
      (uint32_t)mini_console_base_offset_adjustment
          + (uint32_t)(uintptr_t)console + 197);
  return destroy_mini_console_control_base(console);
}

uint32_t *__thiscall delete_mini_console(uint32_t *console,
                                         char free_memory)
{
  destroy_mini_console_members(console);
  if ((free_memory & 1) != 0)
    free_tracked_memory((int)(uintptr_t)console);
  return console;
}

int __thiscall set_mini_console_visible(uint32_t *console, int visible)
{
  uint32_t *application =
      (uint32_t *)(uintptr_t)(uint32_t)game_engine_instance_address;
  uint32_t *log_service = *(uint32_t **)(uintptr_t)(application[273] + 68);
  uint32_t *methods = *(uint32_t **)(void *)console;
  int result;

  if ((uint8_t)visible) {
    attach_control_to_service(
        (int)log_service[7], (int)(uintptr_t)console, 1);
    initialize_mini_console_version_display(
        (uint32_t *)(uintptr_t)console[52]);
  }
  result = ((int (__thiscall *)(uint32_t *, int))(uintptr_t)methods[44])(
      console, visible);
  if (!(uint8_t)visible) {
    detach_control_from_service(
        (int)log_service[7], (uint8_t *)(void *)console);
    return ((int (__thiscall *)(uint32_t *))(uintptr_t)methods[2])(console);
  }
  return result;
}

uint32_t *__cdecl allocate_registered_mini_console(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(mini_console_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_mini_console(void)
{
  uint32_t *memory = allocate_registered_mini_console(220);
  return memory ? construct_mini_console(memory) : NULL;
}
