#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_7643E0[];
extern int __thiscall construct_game_configuration(int object);

uint32_t *__cdecl allocate_registered_game_configuration(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_7643E0,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_static_configuration(void)
{
  uint32_t *memory = allocate_registered_game_configuration(260);
  return memory
      ? (uint32_t *)(uintptr_t)construct_game_configuration(
            (int)(uintptr_t)memory)
      : NULL;
}
