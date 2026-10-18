#include <stdint.h>
#include <stddef.h>

typedef struct {
  uint32_t method_table;
  uint16_t target_id;
  uint16_t reserved_06;
  uint32_t registration_handle;
} RegisteredEventTarget;

typedef struct {
  uint32_t segment_begin;
  uint32_t segment_end;
  uint32_t current;
  uint32_t map_position;
} SegmentedArrayCursor;

/* Four-word array storage embedded at offsets 4 through 16. */
typedef struct {
  uint32_t reserved;
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} EventTargetSlotArray;

/* Chunked deque of reusable target-slot indices. */
typedef struct {
  uint32_t reserved;
  SegmentedArrayCursor first;
  SegmentedArrayCursor last;
  uint32_t block_map;
  uint32_t block_map_capacity;
  uint32_t count;
} ReusableEventTargetSlots;

typedef struct {
  uint32_t unknown_00;
  EventTargetSlotArray target_slots;
  ReusableEventTargetSlots reusable_slots;
  uint32_t unknown_44;
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
_Static_assert(offsetof(RegisteredEventRegistry, target_slots.begin) == 8,
               "event target slot array offset");
_Static_assert(offsetof(RegisteredEventRegistry, reusable_slots.first) == 24,
               "event target free slot deque offset");
_Static_assert(offsetof(RegisteredEventRegistry, reusable_slots.count) == 64,
               "event target free slot count offset");
_Static_assert(sizeof(RegisteredEventRegistry) == 72,
               "registered event registry size");
_Static_assert(offsetof(EngineEventQueue, begin) == 4,
               "engine event queue begin offset");
_Static_assert(offsetof(EngineEventQueue, end) == 8,
               "engine event queue end offset");
_Static_assert(sizeof(EngineEventQueue) == 16,
               "engine event queue size");

/* gk3/GK3R_rest.c */
extern uint32_t registered_event_registry[18];
extern uint16_t next_registered_event_target_id; /* Next registered event-target ID. */
extern int registered_event_target_base_offset_adjustment;
extern uint32_t registered_event_target_type_descriptor[16];
extern uint32_t registered_event_target_vtable[];
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern int game_engine_address; /* Current game engine object. */

int *__thiscall register_event_target(RegisteredEventRegistry *registry,
                                     int *registration_handle,
                                     int target_address);
int __thiscall unregister_registered_event_target(
    RegisteredEventRegistry *registry, int target_address);

/* engine/dynamic_array.c */
extern uint32_t __thiscall insert_segmented_deque_block_map_entry(
    uint32_t *deque, int index);

/* gk3/GK3R_rest.c */
extern int __thiscall advance_segmented_array_cursor(
    SegmentedArrayCursor *cursor, int offset);
extern void __thiscall destroy_segmented_array(int deque_address);
extern uint32_t *__thiscall insert_repeated_array_values(
    uint32_t *array, uint32_t *position, int count, uint32_t *value);
extern uint32_t *__thiscall set_segmented_array_cursor(
    uint32_t *cursor, int current, uint32_t *map_position);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, unsigned int address);

uint16_t *__thiscall construct_registered_event_target(
    uint16_t *event_target)
{
  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(void *)event_target;
  int registration_arguments[2];

  target->target_id = next_registered_event_target_id++;
  if (!next_registered_event_target_id)
    next_registered_event_target_id = 1;

  registration_arguments[1] = (int)(uintptr_t)target;
  find_or_create_registry_entry(
      registered_event_target_type_descriptor,
      (unsigned int)(uintptr_t)target
          + registered_event_target_base_offset_adjustment + 6);
  target->registration_handle = 0;
  target->method_table = (uint32_t)(uintptr_t)registered_event_target_vtable;
  target->registration_handle = (uint32_t)*register_event_target(
      (RegisteredEventRegistry *)(void *)registered_event_registry,
      registration_arguments,
      (int)(uintptr_t)target);
  return event_target;
}

uint32_t *__thiscall destroy_registered_event_target(uint16_t *storage)
{
  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(void *)storage;
  if (!target)
    return NULL;

  target->method_table = (uint32_t)(uintptr_t)registered_event_target_vtable;
  unregister_registered_event_target(
      (RegisteredEventRegistry *)(void *)registered_event_registry,
      (int)(uintptr_t)target);
  uint32_t registration_address = (uint32_t)(uintptr_t)target
      + (uint32_t)registered_event_target_base_offset_adjustment + 6;
  uint32_t *result = erase_map_entry_impl(
                                           registered_event_target_type_descriptor,
                                           registration_address);
  target->target_id = 0;
  target->reserved_06 = 0;
  return result;
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
      (const uint32_t *)(uintptr_t)registry->target_slots.begin;
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
      (const uint32_t *)(uintptr_t)registry->target_slots.begin;
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

int *__thiscall register_event_target(RegisteredEventRegistry *registry,
                                     int *registration_handle,
                                     int target_address)
{
  EventTargetSlotArray *target_slots = &registry->target_slots;
  ReusableEventTargetSlots *free_slots = &registry->reusable_slots;
  const uint32_t target = (uint32_t)target_address;
  uint32_t slot_index;

  if (free_slots->count == 0) {
    slot_index = target_slots->begin
        ? (target_slots->end - target_slots->begin) / sizeof(uint32_t)
        : 0;
    insert_repeated_array_values(
        (uint32_t *)(void *)target_slots,
        (uint32_t *)(uintptr_t)target_slots->end, 1,
        (uint32_t *)(void *)&target);
  } else {
    /* Reuse the most recently released slot and pop it from the deque. */
    SegmentedArrayCursor free_slot_cursor = free_slots->last;
    advance_segmented_array_cursor(&free_slot_cursor, -1);
    slot_index = *(uint32_t *)(uintptr_t)free_slot_cursor.current;
    ((uint32_t *)(uintptr_t)target_slots->begin)[slot_index] = target;

    uint32_t *old_block_map_position =
        (uint32_t *)(uintptr_t)free_slots->last.map_position;
    uint32_t previous_slot_address = free_slots->last.current;
    if (previous_slot_address == free_slots->last.segment_begin) {
      uint32_t *previous_block_map_position = old_block_map_position - 1;
      if (*previous_block_map_position) {
        free_slots->last.map_position =
            (uint32_t)(uintptr_t)previous_block_map_position;
        free_slots->last.segment_begin = *previous_block_map_position;
        free_slots->last.segment_end =
            *previous_block_map_position + 4096;
        previous_slot_address = free_slots->last.segment_end;
      }
    }
    free_slots->last.current = previous_slot_address - sizeof(uint32_t);

    if (--free_slots->count != 0) {
      if (old_block_map_position
          != (uint32_t *)(uintptr_t)free_slots->last.map_position) {
        free_tracked_memory((int)*old_block_map_position);
        *old_block_map_position = 0;
      }
    } else {
      destroy_segmented_array((int)(uintptr_t)free_slots);
    }
  }

  const uint16_t target_id =
      *(const uint16_t *)(uintptr_t)(target + offsetof(RegisteredEventTarget,
                                                       target_id));
  const uint32_t encoded_target = (target & UINT16_MAX)
      | ((uint32_t)target_id << 16);
  /* The handle combines the target identity with its registry slot. */
  *registration_handle = (int)(encoded_target
      ^ (uint16_t)(slot_index ^ target));
  return registration_handle;
}

int __thiscall unregister_registered_event_target(
    RegisteredEventRegistry *registry, int target_address)
{
  EventTargetSlotArray *target_slots = &registry->target_slots;
  ReusableEventTargetSlots *free_slots = &registry->reusable_slots;
  RegisteredEventTarget *target =
      (RegisteredEventTarget *)(uintptr_t)target_address;
  const uint32_t slot_index = (uint16_t)target->registration_handle;
  ((uint32_t *)(uintptr_t)target_slots->begin)[slot_index] = 0;

  if (free_slots->count == 0
      || free_slots->last.current == free_slots->last.segment_end) {
    /* Add another 1024-entry block when the deque reaches its end. */
    uint32_t *new_block = allocate_tracked_memory(4096);
    const uint32_t new_block_address = (uint32_t)(uintptr_t)new_block;

    if (free_slots->count != 0) {
      uint32_t *last_map_position =
          (uint32_t *)(uintptr_t)free_slots->last.map_position;
      uint32_t *map_begin =
          (uint32_t *)(uintptr_t)free_slots->block_map;
      uint32_t *map_end = map_begin + free_slots->block_map_capacity;

      if ((uintptr_t)last_map_position >= (uintptr_t)(map_end - 2)) {
        uint32_t *first_map_position =
            (uint32_t *)(uintptr_t)free_slots->first.map_position;
        const int insert_at =
            (int)(last_map_position - first_map_position) + 1;
        const uint32_t new_map_address =
            insert_segmented_deque_block_map_entry(
                (uint32_t *)(void *)free_slots, insert_at);
        uint32_t *new_map_position =
            (uint32_t *)(uintptr_t)new_map_address;
        uint32_t *new_block_map_entry = new_map_position + insert_at;
        new_block_map_entry[0] = new_block_address;
        new_block_map_entry[1] = 0;

        set_segmented_array_cursor(
            (uint32_t *)(void *)&free_slots->first,
            (int)free_slots->first.current, new_map_position);
        set_segmented_array_cursor(
            (uint32_t *)(void *)&free_slots->last,
            (int)new_block_address, new_block_map_entry);
      } else {
        uint32_t *new_block_map_entry = last_map_position + 1;
        free_slots->last.map_position =
            (uint32_t)(uintptr_t)new_block_map_entry;
        new_block_map_entry[0] = new_block_address;
        new_block_map_entry[1] = 0;
        set_segmented_array_cursor(
            (uint32_t *)(void *)&free_slots->last,
            (int)new_block_address, new_block_map_entry);
      }
    } else {
      uint32_t *block_map = allocate_tracked_memory(32);
      free_slots->block_map = (uint32_t)(uintptr_t)block_map;
      free_slots->block_map_capacity = 8;
      block_map[3] = 0;
      block_map[4] = new_block_address;
      block_map[5] = 0;
      uint32_t *first_entry = &block_map[4];
      const uint32_t middle_of_block = new_block_address + 2048;

      set_segmented_array_cursor(
          (uint32_t *)(void *)&free_slots->first,
          (int)middle_of_block, first_entry);
      set_segmented_array_cursor(
          (uint32_t *)(void *)&free_slots->last,
          (int)middle_of_block, first_entry);
    }
  }

  uint32_t *write_position =
      (uint32_t *)(uintptr_t)free_slots->last.current;
  if (free_slots->last.current != free_slots->last.segment_end) {
    ++write_position;
    free_slots->last.current = (uint32_t)(uintptr_t)write_position;
    if (free_slots->last.current == free_slots->last.segment_end) {
      uint32_t *next_map_position =
          (uint32_t *)(uintptr_t)free_slots->last.map_position + 1;
      if (*next_map_position) {
        free_slots->last.map_position =
            (uint32_t)(uintptr_t)next_map_position;
        free_slots->last.segment_begin = *next_map_position;
        free_slots->last.current = *next_map_position;
        free_slots->last.segment_end = *next_map_position + 4096;
        write_position = (uint32_t *)(uintptr_t)free_slots->last.current;
      }
    }
  }
  if (write_position)
    *write_position = slot_index;

  return (int)++free_slots->count;
}
