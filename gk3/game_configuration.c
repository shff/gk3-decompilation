#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t static_configuration_type_descriptor[];
extern uint8_t *__thiscall construct_registered_config_file(
    uint8_t *object, const char *filename, const char *identity);
extern uint32_t *__thiscall construct_byte_list(uint32_t *object,
                                                uint8_t *default_value);
extern int static_configuration_base_offset_adjustment;
extern uint32_t static_configuration_vtable[];
extern char __thiscall load_configuration_file_section(uint32_t *object,
                                                       int load);
extern uint32_t *__thiscall load_local_game_configuration(
    uint32_t *configuration);

uint32_t *__cdecl allocate_registered_game_configuration(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(static_configuration_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

int __thiscall construct_game_configuration(int object)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t first_default_value;
  uint8_t second_default_value;

  /* The export builds this fixed filename as "game" + ".cfg". */
  construct_registered_config_file(bytes, "game.cfg", "game");
  find_or_create_registry_entry(
      static_configuration_type_descriptor,
      (uint32_t)(uintptr_t)bytes
          + (uint32_t)static_configuration_base_offset_adjustment + 61);
  construct_byte_list((uint32_t *)(void *)(bytes + 64),
                      &first_default_value);
  construct_byte_list((uint32_t *)(void *)(bytes + 112),
                      &second_default_value);
  construct_byte_list((uint32_t *)(void *)(bytes + 160),
                      &first_default_value);
  construct_byte_list((uint32_t *)(void *)(bytes + 208),
                      &second_default_value);
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)static_configuration_vtable;
  *(uint16_t *)(void *)(bytes + 256) = 1;
  load_configuration_file_section((uint32_t *)(void *)bytes, 1);
  load_local_game_configuration((uint32_t *)(void *)bytes);
  return object;
}

uint32_t *construct_application_static_configuration(void)
{
  uint32_t *memory = allocate_registered_game_configuration(260);
  return memory
      ? (uint32_t *)(uintptr_t)construct_game_configuration(
            (int)(uintptr_t)memory)
      : NULL;
}
