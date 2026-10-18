#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/containers.c */
extern int __thiscall vector_element_address(uint32_t *collection, int index);

/* gk3/GK3R_rest.c */
extern uint32_t sheep_engine_type_descriptor[];
extern uint8_t *__thiscall construct_sheep_engine(uint8_t *object);
extern void __thiscall shutdown_sheep_machine(int object);

uint32_t *__cdecl allocate_registered_sheep_engine(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(sheep_engine_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_sheep_engine(void)
{
  uint8_t *memory = (uint8_t *)allocate_registered_sheep_engine(24);
  return memory ? (uint32_t *)(void *)construct_sheep_engine(memory) : NULL;
}

void shutdown_sheep_engine(uint32_t *sheep_engine)
{
  uint32_t *resource_collection = (uint32_t *)(uintptr_t)sheep_engine[1];
  const int resource_count = (int)resource_collection[26];
  uint32_t *resource_entries = resource_collection + 24;

  for (int index = 0; index < resource_count; ++index) {
    uint32_t resource_address = (uint32_t)vector_element_address(
        resource_entries, index);
    uint32_t resource = *(uint32_t *)(uintptr_t)resource_address;
    if (*(uint32_t *)(uintptr_t)(resource + 92) != 0)
      shutdown_sheep_machine((int)resource);
  }
}
