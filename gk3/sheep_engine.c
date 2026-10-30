#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/containers.c */
extern int __thiscall vector_element_address(uint32_t *collection, int index);
extern int __thiscall free_dynamic_array_storage(int *array);

/* engine/active_objects.c */
extern void __thiscall set_active_object_parent(int *child,
                                                 int parent_address);

/* engine/event_dispatch.c */
extern int __thiscall queue_engine_event(uint32_t *engine, int *event);

/* gk3/GK3R_rest.c */
extern uint32_t sheep_engine_runtime_type_descriptor[];
extern uint8_t *__thiscall construct_sheep_engine(uint8_t *object);
extern int game_engine_address;

void shutdown_sheep_machine(int machine_address);

static int queue_sheep_machine_completion_event(uint32_t *machine)
{
  int *event = (int *)(void *)(machine + 24);
  const int result = queue_engine_event(
      (uint32_t *)(uintptr_t)game_engine_address, event);
  event[0] = 0;
  event[1] = 0;
  return result;
}

void __thiscall release_sheep_machine(int *machine)
{
  queue_sheep_machine_completion_event((uint32_t *)(void *)machine);

  uint32_t *machine_words = (uint32_t *)(void *)machine;
  uint32_t *machine_data = (uint32_t *)(uintptr_t)machine_words[5];
  --machine_data[3];
  machine_words[5] = 0;
  set_active_object_parent((int *)machine_words, 0);
}

static void clear_sheep_machine_callback_state(uint32_t *state)
{
  state[0] = 0;
  state[2] = 0;
  state[4] = 0;
  state[1] = 0;
  state[3] = 0;
  state[6] = 0;
}

static int count_sheep_machine_registry_entries(uint32_t *machine)
{
  const uintptr_t begin = machine[19];
  const uintptr_t end = machine[20];
  return begin == 0 ? 0 : (int)((end - begin) / (2 * sizeof(uint32_t)));
}

uint16_t *__thiscall find_sheep_machine_registry_entry(uint32_t *registry,
                                                        int handle)
{
  const uintptr_t begin = registry[21];
  const uintptr_t end = registry[22];
  const uint16_t index = (uint16_t)handle;
  const uint16_t generation = (uint16_t)((uint32_t)handle >> 16);

  if (begin == 0 || index >= (end - begin) / 12)
    return NULL;

  uint16_t *entry = (uint16_t *)(begin + (uintptr_t)index * 12);
  return entry[0] == generation ? entry : NULL;
}

int __thiscall destroy_sheep_machine_string_queue(int collection_address)
{
  return free_dynamic_array_storage((int *)(uintptr_t)collection_address);
}

uint32_t *__cdecl allocate_registered_sheep_engine(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(sheep_engine_runtime_type_descriptor,
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

void shutdown_sheep_machine(int machine_address)
{
  uint8_t *machine = (uint8_t *)(uintptr_t)machine_address;
  uint32_t *machine_words = (uint32_t *)(void *)machine;
  uint32_t *handle_entries = (uint32_t *)(uintptr_t)machine_words[19];
  const int entry_count = count_sheep_machine_registry_entries(machine_words);

  clear_sheep_machine_callback_state((uint32_t *)(void *)(machine + 24));
  machine_words[17] = UINT32_MAX;

  for (int index = 0; index < entry_count; ++index) {
    const int handle = (int)handle_entries[index * 2 + 1];
    uint16_t *entry = find_sheep_machine_registry_entry(
        (uint32_t *)(uintptr_t)machine_words[3], handle);
    if (entry != NULL && *((uint8_t *)entry + 2) != 0)
      ((uint32_t *)(void *)entry)[1] = 0;
  }

  destroy_sheep_machine_string_queue(machine_address + 72);
  machine[90] = 0;
  machine[89] = 0;
  machine_words[23] = 0;
  release_sheep_machine((int *)machine_words);
}
