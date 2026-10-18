#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../common/runtime_lockit.h"

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);

/* gk3/GK3R_rest.c */
extern uint32_t unk_76D128[];
extern int dword_76D124;
extern uint32_t off_6EE718[];
extern uint32_t *__thiscall initialize_scene_data_load_times(
    uint32_t *object, char *default_value);
extern uint32_t *__thiscall construct_floor_map(uint8_t *object);
extern uint32_t *__thiscall construct_floor_contact_sound_map(uint8_t *object);
extern int system_profile_address;
extern int game_engine_instance_address;
extern int active_scene_controller_address;
extern uint32_t dword_76D168[15];
extern int dword_76D164;
extern int dword_76D0A0[15];
extern int dword_6A9EA4;
extern int dword_6C1358;
extern int dword_6A6460;
extern int first_special_stage_location_id;
extern int serialized_value_default;
extern char byte_6A6454;
extern int shared_ordered_string_map_nil_node;
extern int shared_ordered_string_map_instance_count;
extern int frame_number;
extern int game_engine_address;
extern int __thiscall sub_530B65(uint32_t *scene);
extern int __thiscall set_active_cd_volume(uint32_t *engine, int volume_id,
                                           int mode);
extern uint8_t *__thiscall sub_45DA2D(uint8_t *object);
extern uint32_t *__thiscall sub_45DA68(uint32_t *map, uint32_t *result,
                                       char *key);
extern char **__thiscall sub_45DACE(uint32_t *map, char **result, char *key);
extern int __thiscall sub_4B2FDB(int object, const char *name);
extern char __thiscall sub_4B10B6(int object, const char *name);
extern uint32_t *__thiscall sub_552739(int object);
extern uint32_t *__cdecl sub_55406D(int size);
extern uint16_t *__thiscall sub_554122(uint16_t *timer, int noun_id,
                                       int verb_id, int duration);
extern char __thiscall sub_5542E3(int timer, int noun_id, int verb_id,
                                  int duration);
extern int __thiscall sub_555AC2(int collection, uint32_t *value);
extern int __thiscall sub_555AD3(uint32_t *collection, int entry);
extern void __thiscall sub_557F62(int timer);
extern bool __cdecl __uncaught_exception(void);
extern int __thiscall sub_4078BB(uint32_t *dispatcher);
extern int *__thiscall sub_408A6D(uint32_t *dispatcher);
extern uint32_t **__thiscall sub_50303A(int *targets, int event_id);
extern int __thiscall sub_40764E(uint32_t *dispatcher, double elapsed,
                                 int noun_id, int verb_id,
                                 uint32_t **target, char active, int flags);
extern int __thiscall detach_game_layer_18(uint32_t *layer_manager);
extern int __thiscall get_engine_input_state(uint32_t *application,
                                              char input_state);
extern char *__cdecl get_action_vocabulary_string(int token_id);
extern uint32_t *__cdecl sub_551F4F(int size);
extern int __thiscall sub_551FEE(int object, const char *scene_name,
                                 int timeblock);
extern void *__thiscall sub_555C09(void *object, char release_reference);
extern void __cdecl write_source_message(const char *source_file, int line,
                               int category, int flags, char *format,
                               size_t size);
extern void *__stdcall GetForegroundWindow(void);
extern uint32_t *__thiscall update_active_soundtrack_instances(
    uint32_t *manager);
extern void *__thiscall sub_4864E5(void *context);
extern int sub_486530(void);
extern int sub_4C1003(void);
extern int sub_4CA150(void);
extern int __thiscall append_interface_recipient(int object, int *value);
extern int __thiscall release_interface_recipient_list(int *object);
extern int __thiscall sub_53AE6B(uint32_t **manager, int event_id,
                                 int event_data);
extern uint32_t *__cdecl sub_4085FD(uint32_t **reference, int event_id);
extern void __cdecl sub_4FC993(uint32_t *reference);
extern void __cdecl sub_55539C(int command, int duration);
extern int __thiscall clear_compiled_sheep_cases(uint32_t *manager);
extern int *__thiscall stop_and_clear_animator_records(uint32_t *animator);
extern int *__thiscall stop_and_clear_animator_state(uint32_t *animator);
extern char __thiscall sub_437A76(uint8_t *serializer, const char *field,
                                 int *storage, int *default_value);
extern char __thiscall sub_4B0AF1(uint8_t *serializer, const char *field,
                                 int *storage, int *default_value);
extern char __thiscall sub_4053DF(uint8_t *serializer, const char *field,
                                 int *storage, int *default_value);
extern char __cdecl sub_41F830(uint8_t *serializer, const char *field,
                              char *storage);
extern char __thiscall sub_5568C3(uint8_t *serializer, const char *field,
                                 unsigned int storage, char mode);
extern char __thiscall sub_556934(uint8_t *serializer, const char *field,
                                 int *storage, char mode);
extern char __thiscall serialize_integer_value_field(uint8_t *serializer, const char *field,
                                 int *storage, int *default_value);
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                            const char *field, char *storage,
                                            char *default_value);
extern double __thiscall sub_52A6A8(uint32_t **object);
extern int __stdcall sub_4CDFAD(float first, float second, char flags);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern void __cdecl free_tracked_memory(int address);
extern void __thiscall sub_5567A0(int *iterator);
extern uint32_t *__thiscall sub_555FE1(uint32_t *map, uint32_t *result,
                                       uint32_t *node);
extern int __thiscall sub_45F2E4(uint32_t **string_storage);
extern int __thiscall sub_556747(int *iterator, int step);
extern int *__thiscall sub_555D52(int *collection, int *insert_position,
                                  int first_begin, int first_end,
                                  int *first_cursor, int first_limit,
                                  int second_begin, int second_end,
                                  int *second_cursor, int second_limit);
extern int *__thiscall sub_555BB8(int *iterator);
extern uint32_t *__thiscall sub_555B65(uint32_t *collection,
                                      uint32_t **entry);
extern int __cdecl sub_557B2B(int location_id);
extern void __cdecl log_source_message(int source, int line, int category,
                               int flags, char *format, ...);
extern int __thiscall sub_585850(uint32_t *engine, unsigned int first,
                                 unsigned int resource_id);
extern void __thiscall sub_566440(char *engine, unsigned int first,
                                  unsigned int resource_id);
extern void __thiscall sub_555FB1(uint32_t *collection);

void __thiscall purge_oldest_stage_resources(uint32_t *manager);
uint32_t *__thiscall unregister_stage_history_entry(uint32_t *entry);
void __stdcall free_character_data_map_nodes(uint32_t *node);
int __thiscall prepare_stage_transition(int *manager);
void __thiscall release_stage_manager_owned_reference(int *reference);
void __thiscall replace_stage_manager_owned_reference(int *reference,
                                                       int object);
int __thiscall clear_stage_manager_scene_load_times(uint32_t *storage);
int __stdcall get_stage_transition_vocabulary_id(int location_id);
uint32_t *__thiscall find_stage_scene_data_object(uint32_t *manager,
                                                   uint32_t *result,
                                                   char *name);
char **__thiscall find_stage_scene_data_string(uint32_t *manager,
                                                char **result, char *name);
void __thiscall schedule_or_update_stage_timer(uint32_t *manager,
                                                int noun_id, int verb_id,
                                                int duration);
void __thiscall handle_stage_manager_notification(uint32_t *manager,
                                                   double elapsed,
                                                   unsigned int notification);
int __thiscall handle_stage_scene_entry(uint32_t *manager, double elapsed);

uint32_t *__thiscall clear_character_data_map_range(
    uint32_t *map, uint32_t *result, uint32_t *first, uint32_t *last)
{
  uint32_t *cursor = first;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)map[1];

  if (map[3] != 0 && first == (uint32_t *)(uintptr_t)*sentinel
      && last == sentinel) {
    uint32_t lock_storage = 0;
    construct_runtime_lockit(&lock_storage);
    free_character_data_map_nodes(
        (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(map[1] + 4));
    *(uint32_t *)(uintptr_t)(map[1] + 4) =
        (uint32_t)shared_ordered_string_map_nil_node;
    map[3] = 0;
    *sentinel = (uint32_t)(uintptr_t)sentinel;
    *(uint32_t *)(uintptr_t)(map[1] + 8) = (uint32_t)(uintptr_t)sentinel;
    *result = *sentinel;
    destroy_runtime_lockit(&lock_storage);
    return result;
  }

  while (cursor != last) {
    uint32_t *node = cursor;
    sub_5567A0((int *)(void *)&cursor);
    sub_555FE1(map, result, node);
  }
  *result = (uint32_t)(uintptr_t)cursor;
  return result;
}

void __thiscall destroy_character_data_map(uint32_t *map)
{
  int result;
  uint32_t *sentinel = (uint32_t *)(uintptr_t)map[1];
  clear_character_data_map_range(
      map, (uint32_t *)(void *)&result,
      (uint32_t *)(uintptr_t)*sentinel, sentinel);
  free_tracked_memory((int)(uintptr_t)sentinel);
  map[1] = 0;
  map[3] = 0;

  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);
  if (--shared_ordered_string_map_instance_count == 0) {
    free_tracked_memory(shared_ordered_string_map_nil_node);
    shared_ordered_string_map_nil_node = 0;
  }
  destroy_runtime_lockit(&lock_storage);
}

void __stdcall free_character_data_map_nodes(uint32_t *node)
{
  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);
  while (node != (uint32_t *)(uintptr_t)shared_ordered_string_map_nil_node) {
    uint32_t *next = (uint32_t *)(uintptr_t)*node;
    free_character_data_map_nodes(
        (uint32_t *)(uintptr_t)node[2]);
    sub_45F2E4((uint32_t **)(void *)(node + 3));
    free_tracked_memory((int)(uintptr_t)node);
    node = next;
  }
  destroy_runtime_lockit(&lock_storage);
}

void __thiscall initialize_character_data_map(uint32_t *map)
{
  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);

  if (shared_ordered_string_map_nil_node == 0) {
    uint32_t *nil_node = allocate_tracked_memory(36);
    nil_node[1] = 0;
    nil_node[8] = 1;
    shared_ordered_string_map_nil_node = (int)(uintptr_t)nil_node;
    nil_node[0] = 0;
    *(uint32_t *)(void *)((uint8_t *)(void *)nil_node + 8) = 0;
  }

  ++shared_ordered_string_map_instance_count;
  uint32_t *nil_node =
      (uint32_t *)(uintptr_t)shared_ordered_string_map_nil_node;
  uint32_t *root = allocate_tracked_memory(36);
  root[1] = (uint32_t)(uintptr_t)nil_node;
  root[8] = 0;
  map[1] = (uint32_t)(uintptr_t)root;
  map[3] = 0;
  root[0] = (uint32_t)(uintptr_t)root;
  *(uint32_t *)(void *)((uint8_t *)(void *)root + 8) =
      (uint32_t)(uintptr_t)root;

  destroy_runtime_lockit(&lock_storage);
}

uint32_t *__thiscall initialize_scene_data_load_times(
    uint32_t *load_times, char *default_value)
{
  load_times[0] = (load_times[0] & 0xFFFFFF00u)
      | (uint8_t)*default_value;
  for (int index = 1; index < 12; ++index)
    load_times[index] = 0;
  return load_times;
}

uint32_t *__cdecl allocate_registered_stage_history_entry(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(dword_76D168,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *__thiscall initialize_stage_history_entry(uint32_t *entry)
{
  find_or_create_registry_entry(
      dword_76D168, (uint32_t)(uintptr_t)entry + (uint32_t)dword_76D164);
  entry[0] = 0;
  entry[1] = 0;
  entry[2] = 0;
  return entry;
}

int __thiscall update_stage_manager_scene_cache(uint32_t *manager)
{
  int scene_ego = sub_530B65((uint32_t *)(uintptr_t)active_scene_controller_address);
  if (scene_ego != 0) {
    uint32_t *scene = (uint32_t *)(uintptr_t)active_scene_controller_address;
    uint32_t *scene_state = (uint32_t *)(uintptr_t)(
        *(uint32_t *)(void *)((uint8_t *)(void *)scene + 88));
    manager[8] = scene_state[6];
    return (int)scene_state[6];
  }
  return scene_ego;
}

int __stdcall set_cd_volume_for_stage_id(int stage_id)
{
  if (stage_id >= 6) {
    if (stage_id <= 11)
      return set_active_cd_volume((uint32_t *)(uintptr_t)game_engine_instance_address, 2, 0);
    if (stage_id <= 17)
      return set_active_cd_volume((uint32_t *)(uintptr_t)game_engine_instance_address, 3, 0);
  }
  return set_active_cd_volume((uint32_t *)(uintptr_t)game_engine_instance_address, 1, 0);
}

void *clear_active_scene_resource_caches(void)
{
  uint32_t *application = (uint32_t *)(uintptr_t)game_engine_instance_address;
  uint32_t *scene_resources = (uint32_t *)(uintptr_t)(
      *(uint32_t *)(void *)((uint8_t *)(void *)application + 1092) + 56);
  uint8_t *buffer_end = (uint8_t *)(uintptr_t)scene_resources[8];
  uint8_t *buffer_begin = (uint8_t *)(uintptr_t)scene_resources[7];

  if (buffer_begin != buffer_end)
    memset(buffer_begin, 0, (size_t)(buffer_end - buffer_begin));
  memset(scene_resources + 59, 0, 0x17E8u);
  memset(scene_resources + 16, 0, 0x88u);
  return memset(scene_resources + 50, 0, 0x22u);
}

static int __thiscall update_stage_resource_limit(uint32_t *manager)
{
  int limit = *(int *)(uintptr_t)(system_profile_address + 104)
      / 0x1000000 - 1;
  manager[15] = limit < 1 ? 1 : (uint32_t)limit;
  return limit;
}

int __thiscall reset_stage_manager_state(uint32_t *manager)
{
  manager[4] = 0;
  manager[5] = 0;
  manager[6] = 0;
  manager[7] = 0;
  manager[8] = 0;
  ((uint8_t *)(void *)manager)[36] = 0;
  ((uint8_t *)(void *)manager)[56] = 0;
  ((uint8_t *)(void *)manager)[57] = 0;
  return update_stage_resource_limit(manager);
}

uint32_t *__thiscall construct_character_data(uint32_t *character_data)
{
  uint8_t default_value;
  uint8_t *bytes = (uint8_t *)(void *)character_data;

  bytes[0] = default_value;
  character_data[1] = 0;
  character_data[2] = 0;
  character_data[3] = 0;
  bytes[16] = default_value;
  bytes[17] = default_value;
  bytes[24] = 0;
  initialize_character_data_map((uint32_t *)(void *)(bytes + 16));
  return character_data;
}

char __thiscall initialize_stage_resource_maps(char *manager)
{
  sub_45DA2D((uint8_t *)(void *)(manager + 112));
  sub_4B2FDB((int)(uintptr_t)(manager + 176), "Footsteps");
  sub_4B2FDB((int)(uintptr_t)(manager + 208), "Footscuffs");
  return sub_4B10B6((int)(uintptr_t)(manager + 144), "FloorMap");
}

char __thiscall serialize_stage_manager(uint32_t *manager,
                                        uint8_t *serializer, int mode)
{
  (void)mode;
  uint8_t *bytes = (uint8_t *)(void *)manager;
  uint32_t *stage_default = (uint32_t *)(void *)dword_76D0A0;

  (*(void (__thiscall **)(uint8_t *, const char *, int, uint32_t *))
      (uintptr_t)(*(uint32_t *)(void *)serializer + 68))(
          serializer, "mStage", (int)(uintptr_t)(bytes + 12), stage_default);
  sub_437A76(serializer, "mCurrentLocation", (int *)(void *)(bytes + 16),
             &dword_6A9EA4);
  sub_4B0AF1(serializer, "mCurrentTime", (int *)(void *)(bytes + 20),
             &dword_6C1358);
  sub_437A76(serializer, "mLastLocation", (int *)(void *)(bytes + 24),
             &dword_6A9EA4);
  sub_4B0AF1(serializer, "mLastTime", (int *)(void *)(bytes + 28),
             &dword_6C1358);
  sub_4053DF(serializer, "mEgo", (int *)(void *)(bytes + 32),
             &dword_6A6460);
  sub_41F830(serializer, "mInitialized", (char *)(void *)(bytes + 36));
  sub_5568C3(serializer, "mTimers", (unsigned int)(uintptr_t)(bytes + 40), 0);
  serialize_boolean_field(serializer, "mbPreventVerbCancel",
      (char *)(void *)(bytes + 56), &byte_6A6454);
  serialize_boolean_field(serializer, "mbVerbModal",
      (char *)(void *)(bytes + 57), &byte_6A6454);
  serialize_integer_value_field(serializer, "mSceneDataMaxDepth",
      (int *)(void *)(bytes + 60), &serialized_value_default);
  char result = sub_556934(serializer, "mSceneDataLoadTimes",
      (int *)(void *)(bytes + 64), 0);
  if (serializer[4] == 0) {
    initialize_stage_resource_maps((char *)(void *)manager);
    if (*(uint32_t *)(void *)(bytes + 12) != 0) {
      float elapsed = (float)sub_52A6A8(
          (uint32_t **)(uintptr_t)*(uint32_t *)(uintptr_t)(game_engine_instance_address + 1192));
      return (char)sub_4CDFAD(elapsed, 1.0f, 0);
    }
  }
  return result;
}

void __thiscall adjust_stage_history_after_transition(uint32_t *manager,
                                                       int location_id,
                                                       int frame)
{
  if (manager[27] == 0)
    return;

  int iterator[5] = {
      (int)manager[21], (int)manager[22], (int)manager[23],
      (int)manager[24], 0};
  sub_556747(iterator, -1);
  *(int *)(uintptr_t)(*(uint32_t *)(uintptr_t)iterator[2] + 8) = frame - 1;

  iterator[0] = (int)manager[17];
  iterator[1] = (int)manager[18];
  iterator[2] = (int)manager[19];
  iterator[3] = (int)manager[20];
  if (**(uint32_t **)(uintptr_t)iterator[2] != (uint32_t)location_id
      && manager[27] > manager[15])
    purge_oldest_stage_resources(manager);
}

uint32_t *__thiscall record_stage_visit(uint32_t *manager, int location_id,
                                        int frame)
{
  if (location_id >= 66 && location_id <= 72)
    manager[15] = 0;
  else if (manager[15] == 0)
    update_stage_resource_limit(manager);

  int frame_limit = (int)manager[27];
  while (frame_limit > (int)manager[15]) {
    purge_oldest_stage_resources(manager);
    --frame_limit;
  }

  int current_begin = (int)manager[17];
  int current_end = (int)manager[18];
  int *current_cursor = (int *)(uintptr_t)manager[19];
  int current_limit = (int)manager[20];
  for (;;) {
    int previous_begin = (int)manager[21];
    int previous_end = (int)manager[22];
    int *previous_cursor = (int *)(uintptr_t)manager[23];
    int previous_limit = (int)manager[24];
    if (current_cursor == previous_cursor)
      break;

    int entry_address = *current_cursor;
    if (*(int *)(uintptr_t)entry_address == location_id) {
      if (entry_address != 0) {
        erase_map_entry_impl(dword_76D168,
            (uint32_t)entry_address + (uint32_t)dword_76D164);
        free_tracked_memory(entry_address);
      }
      int merged_state[4];
      int next_position[4] = {
          current_begin, current_end, (int)(uintptr_t)current_cursor,
          current_limit};
      sub_556747(next_position, 1);
      sub_555D52((int *)(void *)(manager + 16), merged_state,
          current_begin, current_end, current_cursor, current_limit,
          next_position[0], next_position[1],
          (int *)(void *)&next_position[2], next_position[3]);
      break;
    }
      int iterator[4] = {
          current_begin, current_end, (int)(uintptr_t)current_cursor,
          current_limit};
    sub_555BB8(iterator);
    current_cursor = (int *)(uintptr_t)iterator[2];
  }

  uint32_t *entry = allocate_registered_stage_history_entry(12);
  if (entry != NULL)
    entry = initialize_stage_history_entry(entry);
  uint32_t *new_entry = entry;
  uint32_t frame_count = frame_limit != 0 ? (uint32_t)frame : 0;
  entry[1] = frame_count;
  entry[0] = (uint32_t)location_id;
  entry[2] = frame_count;
  return sub_555B65(manager + 16, &new_entry);
}

void __thiscall purge_oldest_stage_resources(uint32_t *manager)
{
  int **history = (int **)(uintptr_t)manager[19];
  uint32_t *entry = (uint32_t *)(uintptr_t)*history;
  int first_frame = (int)entry[1];
  int last_frame = (int)entry[2];
  int location_id = (int)entry[0];
  const char *location_name = (const char *)(uintptr_t)sub_557B2B(location_id);

  log_source_message((int)(uintptr_t)
      "z:\\Proj\\GK3\\gk3app\\Source\\StageMgr.cpp", 553,
      3, 0, "Purging resources Location(%s) Frames(%08d to %08d)\n",
      location_name, first_frame, last_frame);
  sub_585850((uint32_t *)(uintptr_t)game_engine_address, 0, entry[2]);
  sub_566440((char *)(uintptr_t)game_engine_address, 0, entry[2]);
  if (entry != NULL) {
    unregister_stage_history_entry(entry);
    free_tracked_memory((int)(uintptr_t)entry);
  }
  if (manager[27] != 0)
    sub_555FB1(manager + 16);
}

uint32_t *__thiscall unregister_stage_history_entry(uint32_t *entry)
{
  return erase_map_entry_impl(dword_76D168,
      (uint32_t)(uintptr_t)entry + (uint32_t)dword_76D164);
}

int __thiscall construct_registered_stage_manager(int object, int mode)
{
  char default_value = (char)((uint32_t)mode >> 24);
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;

  construct_registered_event_target((uint16_t *)(void *)bytes);
  find_or_create_registry_entry(
      unk_76D128,
      (uint32_t)dword_76D124 + (uint32_t)object + 12);
  *(uint32_t *)(void *)(bytes + 12) = 0;
  *(uint32_t *)(void *)(bytes + 44) = 0;
  bytes[40] = (uint8_t)default_value;
  *(uint32_t *)(void *)(bytes + 48) = 0;
  *(uint32_t *)(void *)(bytes + 52) = 0;
  initialize_scene_data_load_times((uint32_t *)(void *)(bytes + 64),
                                   &default_value);
  construct_character_data((uint32_t *)(void *)(bytes + 112));
  construct_floor_map(bytes + 144);
  construct_floor_contact_sound_map(bytes + 176);
  construct_floor_contact_sound_map(bytes + 208);
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)off_6EE718;
  return object;
}

int __thiscall construct_stage_manager(int object)
{
  char default_value;
  construct_registered_event_target((uint16_t *)(uintptr_t)object);
  find_or_create_registry_entry(unk_76D128,
             (uint32_t)dword_76D124 + (uint32_t)object + 12);
  *(uint32_t *)(uintptr_t)(object + 12) = 0;
  *(uint32_t *)(uintptr_t)(object + 44) = 0;
  *(uint8_t *)(uintptr_t)(object + 40) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 48) = 0;
  *(uint32_t *)(uintptr_t)(object + 52) = 0;
  initialize_scene_data_load_times((uint32_t *)(uintptr_t)(object + 64),
                                   &default_value);
  construct_character_data((uint32_t *)(uintptr_t)(object + 112));
  construct_floor_map((uint8_t *)(uintptr_t)(object + 144));
  construct_floor_contact_sound_map((uint8_t *)(uintptr_t)(object + 176));
  construct_floor_contact_sound_map((uint8_t *)(uintptr_t)(object + 208));
  *(uint32_t *)(uintptr_t)object = (uint32_t)(uintptr_t)off_6EE718;
  reset_stage_manager_state((uint32_t *)(uintptr_t)object);
  initialize_stage_resource_maps((char *)(uintptr_t)object);
  return object;
}

uint32_t *__cdecl allocate_registered_stage_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_76D128,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_stage_manager(void)
{
  uint32_t *memory = allocate_registered_stage_manager(240);
  return memory
      ? (uint32_t *)(uintptr_t)construct_stage_manager((int)(uintptr_t)memory)
      : NULL;
}

uint32_t *__cdecl create_registered_stage_manager(void)
{
  uint32_t *memory = allocate_registered_stage_manager(240);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_stage_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

int shutdown_stage_manager(uint32_t *manager)
{
  prepare_stage_transition((int *)(void *)manager);
  return reset_stage_manager_state(manager);
}

void __thiscall release_stage_manager_owned_reference(int *reference)
{
  if (*reference != 0) {
    sub_552739(*reference);
    free_tracked_memory(*reference);
  }
}

void __thiscall replace_stage_manager_owned_reference(int *reference,
                                                       int object)
{
  if (*reference != object) {
    if (*reference != 0) {
      sub_552739(*reference);
      free_tracked_memory(*reference);
    }
    *reference = object;
  }
}

int __thiscall clear_stage_manager_scene_load_times(uint32_t *storage)
{
  while (storage[11] != 0)
    sub_555FB1(storage);
  return (int)storage[11];
}

int __thiscall prepare_stage_transition(int *manager)
{
  int event_data[4] = {0};
  int value;
  uint32_t *callback_reference = NULL;

  sub_4864E5(NULL);
  if (sub_4CA150()) {
    uint32_t *application = (uint32_t *)(uintptr_t)game_engine_instance_address;
    clear_compiled_sheep_cases(
        (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application[273] + 56));
  }

  uint32_t *application = (uint32_t *)(uintptr_t)game_engine_instance_address;
  uint32_t *engine_state = (uint32_t *)(uintptr_t)application[273];
  uint32_t *scene_state = (uint32_t *)(uintptr_t)engine_state[17];
  value = (int)scene_state[7];
  append_interface_recipient((int)(uintptr_t)event_data, &value);
  value = (int)scene_state[8];
  append_interface_recipient((int)(uintptr_t)event_data, &value);
  sub_53AE6B((uint32_t **)(uintptr_t)engine_state[22], 0,
             (int)(uintptr_t)event_data);

  if (sub_4C1003())
    stop_and_clear_animator_records(
        (uint32_t *)(uintptr_t)engine_state[8]);

  sub_4085FD(&callback_reference, 3);
  sub_4FC993(callback_reference);
  replace_stage_manager_owned_reference((int *)(void *)(manager + 3), 0);

  callback_reference = NULL;
  sub_4085FD(&callback_reference, 4);
  sub_4FC993(callback_reference);
  if (sub_4C1003())
    stop_and_clear_animator_state(
        (uint32_t *)(uintptr_t)engine_state[8]);

  sub_55539C(11, 1250);
  release_interface_recipient_list(event_data);
  return sub_486530();
}

int __stdcall get_stage_transition_vocabulary_id(int location_id)
{
  const int *special_stage_ids = &first_special_stage_location_id;
  for (int remaining = 6; remaining > 0; --remaining, ++special_stage_ids) {
    if (*special_stage_ids == location_id)
      return 529;
  }
  return 507;
}

uint32_t *__thiscall find_stage_scene_data_object(uint32_t *manager,
                                                  uint32_t *result,
                                                  char *name)
{
  return sub_45DA68((uint32_t *)(void *)(manager + 28), result, name);
}

char **__thiscall find_stage_scene_data_string(uint32_t *manager,
                                               char **result, char *name)
{
  return sub_45DACE((uint32_t *)(void *)(manager + 28), result, name);
}

void __thiscall schedule_or_update_stage_timer(uint32_t *manager,
                                               int noun_id, int verb_id,
                                               int duration)
{
  uint32_t *timer_entry = (uint32_t *)(uintptr_t)manager[11];
  const uint32_t *timer_end =
      (const uint32_t *)(uintptr_t)manager[12];

  for (; timer_entry != timer_end; ++timer_entry) {
    if (sub_5542E3((int)*timer_entry, noun_id, verb_id, duration))
      return;
  }

  uint16_t *timer = sub_554122(
      (uint16_t *)(void *)sub_55406D(64), noun_id, verb_id, duration);
  uint32_t *timer_words = (uint32_t *)(void *)timer;
  timer_words[7] = manager[2];
  timer_words[8] = (uint16_t)timer[26] | 0x10000u;
  sub_557F62((int)(uintptr_t)timer);

  uint32_t *timer_collection = manager + 10;
  uint32_t timer_address = (uint32_t)(uintptr_t)timer;
  sub_555AC2((int)(uintptr_t)timer_collection, &timer_address);

  const uint32_t begin = timer_collection[1];
  const uint32_t end = timer_collection[2];
  if (begin != 0 && (end - begin) / sizeof(uint32_t) > 5) {
    log_source_message(
        (int)(uintptr_t)"z:\\Proj\\GK3\\gk3app\\Source\\StageMgr.cpp",
        897, 5,
        0, "Warning: there are lots of timers (%d)...\n",
        (end - begin) / sizeof(uint32_t));
  }
}

void __thiscall handle_stage_manager_notification(uint32_t *manager,
                                                  double elapsed,
                                                  unsigned int notification)
{
  const unsigned int notification_type = notification >> 16;
  uint32_t *application_engine_state = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);

  if (notification_type == 1) {
    uint32_t *timer_entry = (uint32_t *)(uintptr_t)manager[11];
    const uint32_t *timer_end =
        (const uint32_t *)(uintptr_t)manager[12];
    while (timer_entry != timer_end &&
           (uint16_t)((uint32_t *)(uintptr_t)*timer_entry)[13] !=
               (uint16_t)notification) {
      ++timer_entry;
    }

    if (timer_entry == timer_end) {
      log_source_message(
          (int)(uintptr_t)"z:\\Proj\\GK3\\gk3app\\Source\\StageMgr.cpp",
          948, 5,
          0, "Error: got a notify for a timer that doesn't exist! Serial = %d.\n",
          (uint16_t)notification);
      return;
    }

    uint32_t *timer = (uint32_t *)(uintptr_t)*timer_entry;
    uint32_t *event_dispatcher =
        (uint32_t *)(uintptr_t)application_engine_state[7];
    if (!sub_4078BB(event_dispatcher) || __uncaught_exception()) {
      timer[5] = 2000;
      sub_557F62((int)(uintptr_t)timer);
      return;
    }

    const int noun_id = (int)timer[14];
    const int verb_id = (int)timer[15];
    sub_555AD3(manager + 10, (int)(uintptr_t)timer_entry);
    typedef void (__thiscall *DestroyStageTimer)(uint32_t *timer,
                                                 int free_memory);
    DestroyStageTimer destroy_timer =
        (DestroyStageTimer)(uintptr_t)timer[0];
    destroy_timer(timer, 1);

    int *event_targets = sub_408A6D(event_dispatcher);
    uint32_t **target = sub_50303A(event_targets, noun_id);
    sub_40764E(event_dispatcher, elapsed, noun_id, verb_id, target, 1, 0);
  } else if (notification_type == 2) {
    detach_game_layer_18(
        (uint32_t *)(uintptr_t)application_engine_state[18]);
  }
}

int __thiscall handle_stage_scene_entry(uint32_t *manager, double elapsed)
{
  sub_4864E5(NULL);
  manager[8] = (uint32_t)get_stage_transition_vocabulary_id(
      (int)manager[5]);

  const int location_id = (int)manager[4];
  if (location_id != 47 && location_id != 0) {
    uint32_t *scene_data_map = sub_551F4F(76);
    int scene_data = scene_data_map
        ? sub_551FEE((int)(uintptr_t)scene_data_map,
                     (const char *)(uintptr_t)manager[4], (int)manager[5])
        : 0;
    if ((int)manager[3] != scene_data) {
      if (manager[3] != 0)
        sub_555C09((void *)(uintptr_t)manager[3], 1);
      manager[3] = (uint32_t)scene_data;
    }
    update_stage_manager_scene_cache(manager);
  }

  const int expected_vocabulary_id =
      get_stage_transition_vocabulary_id((int)manager[5]);
  if (expected_vocabulary_id != (int)manager[8]) {
    char *expected_vocabulary =
        get_action_vocabulary_string(expected_vocabulary_id);
    char *current_vocabulary =
        get_action_vocabulary_string((int)manager[8]);
    log_source_message(
        (int)(uintptr_t)"z:\\Proj\\GK3\\gk3app\\Source\\StageMgr.cpp",
        828, 5, 0, "Current ego (%s) is invalid (should be %s)!\n",
        current_vocabulary, expected_vocabulary);
  }

  uint32_t *application_engine_state = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  uint32_t *flag_manager =
      (uint32_t *)(uintptr_t)application_engine_state[14];
  const int timeblock = (int)manager[5];
  ++flag_manager[18 * location_id + 59 + timeblock];
  ((uint8_t *)(void *)flag_manager)[location_id + 6356] = 1;

  uint32_t *callback_reference = NULL;
  sub_4085FD(&callback_reference, 1);
  sub_4FC993(callback_reference);

  if (location_id != 47 && location_id != 0) {
    const int input_state =
        get_engine_input_state((uint32_t *)(uintptr_t)game_engine_instance_address, 1);
    void *game_window = (void *)(uintptr_t)
        *(uint32_t *)(uintptr_t)(game_engine_address + 16);
    if ((input_state & 8) != 0 && GetForegroundWindow() == game_window) {
      write_source_message(
          "z:\\Proj\\GK3\\gk3app\\Source\\StageMgr.cpp", 846, 3, 0,
          "Skipping SCENE:ENTER (you held down the shift key)...\n",
          (size_t)0xFFFFFFFFu);
    } else {
      sub_40764E(
          (uint32_t *)(uintptr_t)application_engine_state[7], elapsed,
          1037, 51, NULL, 1, 0);
    }
  }

  update_active_soundtrack_instances(
      (uint32_t *)(uintptr_t)application_engine_state[23]);
  return sub_486530();
}
