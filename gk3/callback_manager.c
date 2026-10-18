#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t *vtable;
  uint16_t target_id;
  uint16_t reserved_06;
  uint32_t registration_handle;
} CallbackManager;

_Static_assert(offsetof(CallbackManager, target_id) == 4,
               "callback manager target ID offset");
_Static_assert(offsetof(CallbackManager, registration_handle) == 8,
               "callback manager registration handle offset");
_Static_assert(sizeof(CallbackManager) == 12,
               "callback manager object size");

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);
extern uint32_t *__thiscall destroy_registered_event_target(uint16_t *object);
extern int __thiscall queue_engine_event(uint32_t *engine, int *event);

/* gk3/GK3R_rest.c */
extern uint32_t unk_763E30[];
extern int callback_manager_base_offset_adjustment;
extern uint32_t callback_manager_vtable[];
extern int game_engine_address;

static CallbackManager *__thiscall construct_registered_callback_manager(
    CallbackManager *object, int unused)
{
  construct_registered_event_target((uint16_t *)(void *)object);
  find_or_create_registry_entry(unk_763E30,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)callback_manager_base_offset_adjustment + 12);
  object->vtable = callback_manager_vtable;
  return object;
}

static CallbackManager *__thiscall construct_callback_manager(
    CallbackManager *object)
{
  construct_registered_event_target((uint16_t *)(void *)object);
  find_or_create_registry_entry(unk_763E30,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)callback_manager_base_offset_adjustment + 12);
  object->vtable = callback_manager_vtable;
  return object;
}

static CallbackManager *allocate_registered_callback_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_763E30,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return (CallbackManager *)(void *)memory;
}

void *construct_application_callback_manager(void)
{
  CallbackManager *memory = allocate_registered_callback_manager(12);
  return memory ? construct_callback_manager(memory) : NULL;
}

void *__cdecl create_registered_callback_manager(void)
{
  CallbackManager *memory = allocate_registered_callback_manager(12);
  return memory
      ? construct_registered_callback_manager(memory, 0)
      : NULL;
}

uint32_t *__thiscall destroy_callback_manager_members(
    CallbackManager *manager)
{
  uint32_t *v2;
  uint32_t *v3;
  void (__thiscall ***v4)(uint32_t, int);

  manager->vtable = callback_manager_vtable;
  v2 = *(uint32_t **)(uintptr_t)((uint32_t)game_engine_address + 468);
  v3 = *(uint32_t **)(uintptr_t)((uint32_t)game_engine_address + 472);
  while (v2 != v3) {
    if (*v2 == manager->registration_handle) {
      v4 = (void (__thiscall ***)(uint32_t, int))(uintptr_t)v2[1];
      if (v4)
        (**v4)((uint32_t)(uintptr_t)v4, 1);
      *v2 = 0;
      v2[1] = 0;
    }
    v2 += 2;
  }
  erase_map_entry_impl(unk_763E30,
      (uint32_t)callback_manager_base_offset_adjustment
      + (manager != NULL ? (uint32_t)(uintptr_t)manager + 12 : 0));
  return destroy_registered_event_target((uint16_t *)(void *)manager);
}

int __thiscall dispatch_callback_or_queue_event(CallbackManager *manager,
                                               int callback_address)
{
  int result;
  int v4[2];

  if ((*(uint8_t (__thiscall **)(int))
          (*(uint32_t *)(uintptr_t)callback_address + 8))(
          callback_address)) {
    result = (*(int (__thiscall **)(int))
        (*(uint32_t *)(uintptr_t)callback_address + 4))(
        callback_address);
    if (callback_address)
      return (**(int (__thiscall ***)(int, int))(uintptr_t)callback_address)(
          callback_address, 1);
  } else {
    v4[0] = (int)manager->registration_handle;
    v4[1] = callback_address;
    return queue_engine_event((uint32_t *)(uintptr_t)game_engine_address, v4);
  }
  return result;
}

void *__thiscall release_callback_manager(CallbackManager *manager,
                                         char flags)
{
  destroy_callback_manager_members(manager);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}
