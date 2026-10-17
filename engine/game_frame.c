#include <stddef.h>
#include <stdint.h>

typedef unsigned int (__thiscall *GetGameTimeMethod)(uint32_t *engine);
typedef void (__thiscall *UpdateGameStateMethod)(uint32_t *engine, unsigned int time);
typedef void (__thiscall *UpdateTimedObjectsMethod)(uint32_t *engine, unsigned int elapsed);
typedef void (__thiscall *UpdateSoundManagerMethod)(int sound_manager);

typedef struct {
  uint32_t event_id;
  uint32_t argument;
} EngineEvent;

int frame_number = 1;

typedef struct {
  uint32_t reserved;
  uint32_t data;
  int32_t count;
  uint32_t reserved_after_count[3];
} EngineObjectCollection;

typedef struct {
  uint32_t reserved;
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} EngineEventQueue;

typedef struct {
  uint32_t reserved_slots_0_and_1[2];
  uint32_t update_timed_objects;
  uint32_t reserved_slots_3_through_6[4];
  uint32_t get_game_time;
  uint32_t reserved_slots_8_through_33[26];
  uint32_t update_game_state;
  uint32_t reserved_slots_35_through_46[12];
} GameEngineVTable;

typedef struct {
  uint32_t vtable_address;
  uint32_t reserved_before_sound_manager[52];
  uint32_t sound_manager;
  uint32_t reserved_before_cd_monitor[15];
  uint32_t cd_monitor;
  uint32_t reserved_before_objects[19];
  EngineObjectCollection objects;
  uint32_t reserved_before_events[21];
  EngineEventQueue events;
  uint32_t reserved_before_time[144];
  uint32_t previous_frame_time;
} GameFrameEngine;

_Static_assert(offsetof(GameFrameEngine, sound_manager) == 212, "sound manager offset");
_Static_assert(offsetof(GameFrameEngine, cd_monitor) == 276, "CD monitor offset");
_Static_assert(sizeof(EngineObjectCollection) == 24,
               "object collection size");
_Static_assert(offsetof(GameFrameEngine, objects) == 356, "object list offset");
_Static_assert(offsetof(GameFrameEngine, events) == 464, "event queue offset");
_Static_assert(offsetof(GameFrameEngine, previous_frame_time) == 1056,
               "previous frame time offset");
_Static_assert(offsetof(GameEngineVTable, update_timed_objects) == 8,
               "timed-object update vtable slot");
_Static_assert(offsetof(GameEngineVTable, get_game_time) == 28,
               "game-time vtable slot");
_Static_assert(offsetof(GameEngineVTable, update_game_state) == 136,
               "game-state update vtable slot");
_Static_assert(sizeof(GameEngineVTable) == 47 * sizeof(uint32_t),
               "game-engine vtable size");

enum { SOUND_MANAGER_UPDATE_METHOD_SLOT = 24 / 4 };

/* gk3/GK3R_rest.c */
extern int game_engine_address;

/* engine/game_engine.c */
extern int __thiscall restore_lost_graphics_surfaces(int engine, char force);

/* platform/cd_monitor.c */
extern char __thiscall poll_cd_monitor(int monitor, int time);

/* engine/dynamic_array.c */
extern int __thiscall vector_element_address(uint32_t *list, int index);

/* engine/active_objects.c */
extern void __thiscall refresh_active_object_children(int object);

/* engine/event_dispatch.c */
extern int __thiscall is_registered_event_target(int *event);
extern int __thiscall dispatch_registered_event(uint32_t *event);

int __thiscall process_pending_engine_events(uint32_t *engine);

int __thiscall run_game_frame(uint32_t *engine_words)
{
  GameFrameEngine *engine = (GameFrameEngine *)engine_words;
  restore_lost_graphics_surfaces(game_engine_address, 0);

  GameEngineVTable *methods = (GameEngineVTable *)(uintptr_t)
      engine->vtable_address;
  const unsigned int now = ((GetGameTimeMethod)(uintptr_t)
      methods->get_game_time)(engine_words);
  poll_cd_monitor((int)engine->cd_monitor, (int)now);
  ((UpdateGameStateMethod)(uintptr_t)
      methods->update_game_state)(engine_words, now);

  const int object_count = engine->objects.count;
  for (int index = 0; index < object_count; ++index) {
    int object = *(int *)(uintptr_t)vector_element_address(
        (uint32_t *)&engine->objects, index);
    if (object)
      refresh_active_object_children(object);
  }

  uint32_t previous_time = engine->previous_frame_time;
  if (!previous_time || previous_time > now)
    previous_time = now;
  const unsigned int elapsed = now - previous_time;
  engine->previous_frame_time = now;

  methods = (GameEngineVTable *)(uintptr_t)engine->vtable_address;
  ((UpdateTimedObjectsMethod)(uintptr_t)
      methods->update_timed_objects)(engine_words, elapsed);

  const int sound_manager = (int)engine->sound_manager;
  if (sound_manager) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)sound_manager;
    ((UpdateSoundManagerMethod)(uintptr_t)
        methods[SOUND_MANAGER_UPDATE_METHOD_SLOT])(sound_manager);
  }

  return process_pending_engine_events(engine_words);
}

int __thiscall process_pending_engine_events(uint32_t *engine_words)
{
  GameFrameEngine *engine = (GameFrameEngine *)engine_words;
  /* Each event holds a registered target ID and the argument passed to it. */
  for (int pass = 0; pass < 200; ++pass) {
    uint32_t begin = engine->events.begin;
    if (!begin)
      break;

    const uint32_t count =
        (engine->events.end - begin) / sizeof(EngineEvent);
    if (!count)
      break;
    for (uint32_t index = 0; index < count; ++index) {
      EngineEvent *event = (EngineEvent *)(uintptr_t)
          (engine->events.begin + index * sizeof(EngineEvent));
      if (is_registered_event_target((int *)event))
        dispatch_registered_event((uint32_t *)event);
    }

    /* Callbacks can append events or move the queue's allocation. */
    begin = engine->events.begin;
    EngineEvent *events = (EngineEvent *)(uintptr_t)begin;
    const uint32_t end = engine->events.end;
    const uint32_t remaining = (end - begin) / sizeof(EngineEvent) - count;
    for (uint32_t index = 0; index < remaining; ++index)
      events[index] = events[count + index];
    engine->events.end = begin + remaining * sizeof(EngineEvent);
  }

  return (int)engine->events.begin;
}
