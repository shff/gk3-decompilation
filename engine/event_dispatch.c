#include <stdint.h>
#include <stddef.h>

typedef struct {
  uint32_t method_table;
  uint16_t target_id;
  uint16_t reserved_06;
  uint32_t registration_handle;
} RegisteredEventTarget;

typedef struct {
  uint32_t unknown_00[2];
  uint32_t target_slots;
} RegisteredEventRegistry;

typedef struct {
  uint32_t unused_method;
  uint32_t dispatch_method;
} RegisteredEventTargetMethods;

typedef struct {
  uint32_t registration_handle;
  uint32_t argument;
} QueuedEngineEvent;

typedef struct {
  uint32_t reserved;
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} EngineEventQueue;

typedef int (__thiscall *EventTargetDispatchMethod)(
    RegisteredEventTarget *target, int argument);

_Static_assert(offsetof(RegisteredEventTarget, target_id) == 4,
               "event target ID offset");
_Static_assert(offsetof(RegisteredEventTarget, registration_handle) == 8,
               "event target registration handle offset");
_Static_assert(sizeof(RegisteredEventTarget) == 12,
               "registered event target size");
_Static_assert(sizeof(QueuedEngineEvent) == 8,
               "queued engine event size");
_Static_assert(offsetof(EngineEventQueue, begin) == 4,
               "engine event queue begin offset");
_Static_assert(offsetof(EngineEventQueue, end) == 8,
               "engine event queue end offset");
_Static_assert(sizeof(EngineEventQueue) == 16,
               "engine event queue size");

/* gk3/GK3R_rest.c */
extern uint32_t registered_event_registry[18];
extern uint16_t word_751900; /* Next registered event-target ID. */
extern int dword_77369C; /* GNotifyTarget base offset adjustment. */
extern uint32_t dword_7736A8[16]; /* GNotifyTarget type descriptor. */
extern uint32_t off_6A6958[]; /* GNotifyTarget vtable. */
extern int *__thiscall sub_5747D0(int *registry, int *entry, int target);
extern int game_engine_address; /* Current game engine object. */

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, unsigned int address);

uint16_t *__thiscall construct_registered_event_target(
    uint16_t *event_target)
{
  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(void *)event_target;
  int registration_arguments[2];

  target->target_id = word_751900++;
  if (!word_751900)
    word_751900 = 1;

  registration_arguments[1] = (int)(uintptr_t)target;
  find_or_create_registry_entry(
      dword_7736A8,
      (unsigned int)(uintptr_t)target + dword_77369C + 6);
  target->registration_handle = 0;
  target->method_table = (uint32_t)(uintptr_t)off_6A6958;
  target->registration_handle = (uint32_t)*sub_5747D0(
      (int *)(void *)registered_event_registry, registration_arguments,
      (int)(uintptr_t)target);
  return event_target;
}

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

static RegisteredEventTarget *find_registered_event_target(int registration_handle)
{
  const RegisteredEventRegistry *registry =
      (const RegisteredEventRegistry *)(const void *)registered_event_registry;
  const uint16_t slot = (uint16_t)registration_handle;
  const uint32_t *target_slots =
      (const uint32_t *)(uintptr_t)registry->target_slots;
  const uint32_t target_address = target_slots[slot];
  if (!target_address)
    return NULL;

  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(uintptr_t)target_address;
  return target->registration_handle == (uint32_t)registration_handle
      ? target : NULL;
}

static int __thiscall dispatch_event_to_registered_target(
    uint16_t target_slot, int argument)
{
  const RegisteredEventRegistry *registry =
      (const RegisteredEventRegistry *)(const void *)registered_event_registry;
  const uint32_t *target_slots =
      (const uint32_t *)(uintptr_t)registry->target_slots;
  const uint32_t target_address = target_slots[target_slot];
  if (!target_address)
    return target_slot;

  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(uintptr_t)target_address;
  const RegisteredEventTargetMethods *methods =
      (const RegisteredEventTargetMethods *)(uintptr_t)target->method_table;
  const EventTargetDispatchMethod dispatch =
      (EventTargetDispatchMethod)(uintptr_t)methods->dispatch_method;
  return dispatch(target, argument);
}

int __thiscall is_registered_event_target(int *event)
{
  return event && *event && find_registered_event_target(*event) != NULL;
}

int __thiscall dispatch_registered_event(uint32_t *event)
{
  return dispatch_event_to_registered_target(
      (uint16_t)event[0], (int)event[1]);
}

int __stdcall dispatch_event_if_registered(int *event)
{
  int registered = is_registered_event_target(event);
  if (registered && *event)
    return dispatch_registered_event((uint32_t *)event);
  return registered;
}

void __thiscall remove_pending_engine_event(uint32_t *engine_words,
                                            int *event_words)
{
  if (!is_registered_event_target(event_words))
    return;

  enum { ENGINE_EVENT_QUEUE_OFFSET = 464 };
  EngineEventQueue *queue = (EngineEventQueue *)
      ((uint8_t *)engine_words + ENGINE_EVENT_QUEUE_OFFSET);
  if (!queue->begin || queue->begin == queue->end)
    return;

  QueuedEngineEvent *queued =
      (QueuedEngineEvent *)(uintptr_t)queue->begin;
  const QueuedEngineEvent *end =
      (const QueuedEngineEvent *)(uintptr_t)queue->end;
  for (; queued != end; ++queued) {
    if (queued->registration_handle == (uint32_t)event_words[0]
        && queued->argument == (uint32_t)event_words[1]) {
      queued->registration_handle = 0;
      queued->argument = 0;
    }
  }
}

int __thiscall queue_engine_event(uint32_t *engine_words, int *event_words)
{
  if (!is_registered_event_target(event_words))
    return 0;

  enum { ENGINE_EVENT_QUEUE_OFFSET = 464 };
  EngineEventQueue *queue = (EngineEventQueue *)
      ((uint8_t *)engine_words + ENGINE_EVENT_QUEUE_OFFSET);
  if (queue->capacity - queue->end >= sizeof(QueuedEngineEvent)) {
    QueuedEngineEvent *end =
        (QueuedEngineEvent *)(uintptr_t)queue->end;
    end->registration_handle = (uint32_t)event_words[0];
    end->argument = (uint32_t)event_words[1];
    queue->end += sizeof(*end);
    return (int)queue->end;
  }

  const uint32_t old_begin = queue->begin;
  const int old_count = old_begin
      ? (int)(queue->end - old_begin) / (int)sizeof(QueuedEngineEvent)
      : 0;
  const int growth = old_count > 1 ? old_count : 1;
  const int new_capacity = old_count + growth;
  QueuedEngineEvent *new_events = (QueuedEngineEvent *)
      allocate_tracked_memory((int)(sizeof(*new_events) * new_capacity));
  const QueuedEngineEvent *old_events =
      (const QueuedEngineEvent *)(uintptr_t)old_begin;
  for (int index = 0; index < old_count; ++index)
    new_events[index] = old_events[index];
  new_events[old_count].registration_handle = (uint32_t)event_words[0];
  new_events[old_count].argument = (uint32_t)event_words[1];

  queue->begin = (uint32_t)(uintptr_t)new_events;
  queue->end = (uint32_t)(uintptr_t)(new_events + old_count + 1);
  queue->capacity = (uint32_t)(uintptr_t)(new_events + new_capacity);
  free_tracked_memory((int)old_begin);
  return (int)queue->end;
}

int *__thiscall replace_event_reference_and_queue_previous(
    int *reference, int *replacement)
{
  if (is_registered_event_target(reference))
    queue_engine_event((uint32_t *)(uintptr_t)game_engine_address, reference);

  if (!replacement) {
    reference[0] = 0;
    reference[1] = 0;
    return NULL;
  }

  reference[0] = replacement[0];
  reference[1] = replacement[1];
  return (int *)(uintptr_t)(uint32_t)replacement[1];
}

int __thiscall queue_and_clear_event_reference(int *reference)
{
  int result = is_registered_event_target(reference);
  if (result)
    result = queue_engine_event(
        (uint32_t *)(uintptr_t)game_engine_address, reference);

  reference[0] = 0;
  reference[1] = 0;
  return result;
}
