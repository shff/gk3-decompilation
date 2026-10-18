#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../common/runtime_lockit.h"

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_7640B8[];
extern uint32_t dword_7640F8[15];
extern int dword_7640B4;
extern int dword_7640F4;
extern int dword_7647B0;
extern int dword_7647B4;
extern int dword_7647B8;
extern void *Buf2;
extern int active_scene_controller_address;
extern int dword_76417C;
extern int dword_764180;
extern void *__thiscall (*off_6AE0C8)(void *object, char flags);
extern uint32_t off_6A72AC[];
extern int game_engine_instance_address;
extern const char Key[4];
extern int __thiscall tidy_std_string_storage(char *string_storage,
                                             char mode);
extern char *__thiscall assign_std_string_storage(char *storage,
                                                  const char *value,
                                                  size_t length);
extern int *__thiscall sub_4589E1(uint32_t *tree, int *result, int key);
extern int *__thiscall sub_458A25(uint32_t *tree, int *result, int key);
extern uint32_t *__thiscall sub_458576(uint32_t *tree, char *key);
extern uint32_t *__thiscall sub_458657(uint32_t *tree, uint32_t *result,
                                       uint32_t *node);
extern uint32_t *__thiscall sub_4589CD(int tree);
extern uint32_t *__thiscall sub_458925(uint32_t *tree, uint32_t *result,
                                       uint32_t *first, uint32_t *last);
extern uint32_t *__cdecl sub_457CA5(int size);
extern uint32_t *__thiscall find_or_create_registry_entry(uint32_t *registry,
                                      uint32_t address);
extern void *__thiscall sub_447754(void *object);
extern uint32_t *__thiscall sub_40ECE2(uint32_t *object);
extern int __thiscall sub_40EE23(float *first, float *second);
extern float *__thiscall sub_40D73E(float *matrix, float *vector);
extern void __thiscall sub_575F20(float *matrix, float angle);
extern void __thiscall sub_575F80(float *matrix, float angle);
extern void __thiscall sub_578B90(float *matrix, float *first,
                                  float *second, int flags, int count);
extern uint32_t *__thiscall begin_interface_debug_log(uint32_t *logger, int source,
                                      int line, int category, void *context);
extern int __thiscall log_interface_debug_message(uint32_t *logger, const char *format, ...);
extern void __thiscall end_interface_debug_log(int *logger);
extern char *__cdecl sub_475282(int camera_type);
extern char *__thiscall copy_camera_angle_state(char *destination, int source);
extern char __thiscall sub_459038(uint8_t *serializer, int field,
                                 uint32_t *value, int mode);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                 uint32_t address);
extern char __thiscall sub_454F29(int camera, uint32_t *position);
extern void *__thiscall sub_41838F(uint32_t *bounds, uint8_t *rectangle);
extern void __thiscall sub_458A69(int *iterator);
extern void __thiscall sub_45945F(int *iterator, int index);
extern void __thiscall sub_45367B(int camera, int angle, int *target,
                                  char transition, int flags, char mode);
extern void __thiscall sub_453A7E(int camera, int angle, char cut, char mode);
extern int __cdecl log_source_message(int source_file, int line, int severity,
                              int flags, const char *format, ...);
extern void __cdecl free_tracked_memory(int address);

uint32_t *__thiscall construct_camera_angle(uint32_t *angle)
{
  sub_447754(angle + 6);
  sub_40ECE2(angle);
  find_or_create_registry_entry(dword_7640F8,
             (uint32_t)(uintptr_t)angle + (uint32_t)dword_7640F4 + 56);
  angle[0] = (uint32_t)(uintptr_t)off_6A72AC;
  return angle;
}

void __thiscall calculate_camera_angle_view_position(float *angle,
                                                       float *position)
{
  float transform[12];

  if (sub_40EE23((float *)&dword_7647B0, angle + 2)) {
    position[0] = *(float *)&dword_7647B0;
    position[1] = *(float *)&dword_7647B4;
    position[2] = *(float *)&dword_7647B8;
    return;
  }

  memcpy(transform, Buf2, sizeof(transform));
  transform[11] -= angle[5];
  sub_575F20(transform, angle[1]);
  sub_575F80(transform, angle[0]);
  sub_40D73E(transform, angle + 2);
  position[0] = 0.0f;
  position[1] = 0.0f;
  position[2] = 0.0f;
  sub_578B90(transform, position, position, 1, 12);
}

double __thiscall get_camera_angle_field_of_view(float *angle)
{
  if (angle[6] == 0.0f) {
    uint32_t viewport = *(uint32_t *)(uintptr_t)(active_scene_controller_address + 84);
    return *(float *)(uintptr_t)(viewport + 36);
  }
  return angle[6];
}

void __thiscall set_camera_angle_target_position(float *angle,
                                                  float *position)
{
  float transform[12];

  if (sub_40EE23((float *)&dword_7647B0, position)) {
    angle[2] = *(float *)&dword_7647B0;
    angle[3] = *(float *)&dword_7647B4;
    angle[4] = *(float *)&dword_7647B8;
    return;
  }

  memcpy(transform, Buf2, sizeof(transform));
  sub_575F20(transform, angle[1]);
  sub_575F80(transform, angle[0]);
  sub_40D73E(transform, position);
  angle[2] = 0.0f;
  angle[3] = 0.0f;
  angle[4] = angle[5];
  sub_578B90(transform, angle + 2, angle + 2, 1, 12);
}

char __thiscall camera_angles_equal(float *first, float *second)
{
  const double epsilon = 0.0000009999999974752427;

  if (fabs(first[0] - second[0]) >= epsilon ||
      fabs(first[1] - second[1]) >= epsilon ||
      fabs(first[5] - second[5]) >= epsilon ||
      fabs(get_camera_angle_field_of_view(first) -
           get_camera_angle_field_of_view(second)) >= epsilon) {
    return 0;
  }
  return (char)sub_40EE23(first + 2, second + 2);
}

void __thiscall log_camera_angle_details(float *angle, uint32_t *context)
{
  int logger[4];
  uint32_t *entry = begin_interface_debug_log(
      (uint32_t *)logger,
      (int)"Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
      118, 7, context);
  const double field_of_view = get_camera_angle_field_of_view(angle);
  char *type = sub_475282(*(int *)(void *)(angle + 7));

  log_interface_debug_message(entry,
             "angles: horizontal = %f, vertical = %f\n"
             "target: x = %f, y = %f, z = %f\n"
             "distance = %f\n"
             "field of view = %f\n"
             "type = %s\n"
             "SIF: angle={%.2f, %.2f}, pos={%.2f, %.2f, %.2f}\n",
             angle[0] * 57.295776, angle[1] * 57.295776,
             angle[2], angle[3], angle[4], angle[5],
             field_of_view * 57.295776,
             type, angle[0] * 57.295776, angle[1] * 57.295776,
             angle[2], angle[3], angle[4]);
  end_interface_debug_log((int *)logger);
}

void __thiscall log_camera_angle_summary(float *angle, uint32_t *context)
{
  int logger[4];
  uint32_t *entry = begin_interface_debug_log(
      (uint32_t *)logger,
      (int)"Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
      143, 7, context);
  const double field_of_view =
      get_camera_angle_field_of_view(angle) * 57.295776;

  log_interface_debug_message(entry,
             "h=%.2f, v=%.2f, pos=(%.2f,%.2f,%.2f), fov=%.2f",
             angle[0] * 57.295776, angle[1] * 57.295776,
             angle[2], angle[3], angle[4], field_of_view);
  if (context == NULL) {
    log_interface_debug_message(entry, "\n");
  }
  end_interface_debug_log((int *)logger);
}

char *__thiscall format_camera_angle_description(float *angle,
                                                  char *string_storage)
{
  char buffer[100];

  snprintf(buffer, sizeof(buffer),
           "angle={%.2f, %.2f}, pos={%.2f, %.2f, %.2f}",
           angle[0] * 57.295776, angle[1] * 57.295776,
           angle[2], angle[3], angle[4]);
  if (angle[6] != 0.0f) {
    const size_t length = strlen(buffer);
    snprintf(buffer + length, sizeof(buffer) - length, ", fov=%.1f",
             angle[6] * 57.295776);
  }

  string_storage[0] = (char)((uintptr_t)string_storage >> 24);
  tidy_std_string_storage(string_storage, 0);
  assign_std_string_storage(string_storage, buffer, strlen(buffer));
  return string_storage;
}

int __thiscall find_camera_angle_by_name(uint32_t *manager, char *name)
{
  char key_storage[16] = {0};
  int node;

  key_storage[0] = (char)((uintptr_t)name >> 24);
  tidy_std_string_storage(key_storage, 0);
  assign_std_string_storage(key_storage, name, strlen(name));
  sub_4589E1(manager + 1, &node, (int)(uintptr_t)key_storage);
  tidy_std_string_storage(key_storage, 1);

  if ((uint32_t)node == manager[2])
    return 0;
  return *(int *)(uintptr_t)(node + 28);
}

int __thiscall lookup_camera_angle_by_name(uint32_t *manager, char *name)
{
  char key_storage[16] = {0};
  int node;

  key_storage[0] = (char)((uintptr_t)name >> 24);
  tidy_std_string_storage(key_storage, 0);
  assign_std_string_storage(key_storage, name, strlen(name));
  sub_458A25(manager + 1, &node, (int)(uintptr_t)key_storage);
  tidy_std_string_storage(key_storage, 1);

  if ((uint32_t)node == manager[2])
    return 0;
  return *(int *)(uintptr_t)(node + 28);
}

char __thiscall serialize_camera_angle_manager(uint32_t *manager,
                                              uint8_t *serializer, int mode)
{
  (void)mode;
  return sub_459038(serializer, (int)(uintptr_t)"mAngles", manager + 1,
                    1);
}

char __cdecl serialize_registered_camera_angle_manager(
    uint32_t *manager, uint8_t *serializer, int mode)
{
  return serialize_camera_angle_manager(manager, serializer, mode);
}

void __thiscall glide_to_camera_angle(uint32_t *manager, char *name,
                                      int *target, char transition,
                                      int flags, char mode)
{
  int angle = find_camera_angle_by_name(manager, name);
  if (angle != 0) {
    int camera_manager = *(int *)(uintptr_t)(
        *(int *)(uintptr_t)(game_engine_instance_address + 1092) + 40);
    sub_45367B(camera_manager, angle, target, transition, flags, mode);
  } else {
    log_source_message(
        (int)(uintptr_t)
            "Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
        232, 6, 0,
        "CameraAngleMgr::GlideTo(): camera angle '%s' does not exist", name);
  }
}

void __thiscall cut_to_camera_angle(uint32_t *manager, char *name,
                                    char cut, char mode)
{
  int angle = find_camera_angle_by_name(manager, name);
  if (angle != 0) {
    int camera_manager = *(int *)(uintptr_t)(
        *(int *)(uintptr_t)(game_engine_instance_address + 1092) + 40);
    sub_453A7E(camera_manager, angle, cut, mode);
  } else {
    log_source_message(
        (int)(uintptr_t)
            "Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
        250, 6, 0,
        "CameraAngleMgr::CutTo(): camera angle '%s' does not exist", name);
  }
}

int __thiscall count_camera_angles_outside_bounds(uint32_t *manager,
                                                  uint32_t *bounds,
                                                  int angle_type,
                                                  char include_contained)
{
  int *nil_node = (int *)(uintptr_t)manager[2];
  int outside_count = 0;
  int node = *nil_node;
  int iterator = *nil_node;

  for (; (int *)iterator != nil_node; node = iterator) {
    char inside;
    uint32_t angle_position[3];
    uint32_t camera_position[3];

    if (angle_type == -1
        || *(int *)(uintptr_t)(*(int *)(uintptr_t)(node + 28) + 52)
               == angle_type) {
      calculate_camera_angle_view_position((float *)(uintptr_t)(
                     *(int *)(uintptr_t)(node + 28) + 24),
                 (float *)(void *)camera_position);
      angle_position[0] = camera_position[0];
      angle_position[1] = camera_position[1];
      angle_position[2] = camera_position[2];
      inside = sub_454F29(
          *(int *)(uintptr_t)(*(int *)(uintptr_t)(game_engine_instance_address + 1092) + 40),
          angle_position);

      if ((!inside && !include_contained)
          || (sub_41838F(bounds, (uint8_t *)(uintptr_t)(iterator + 12)),
              ++outside_count, !inside)) {
        const char *name = *(const char **)(uintptr_t)(iterator + 16);
        if (name == NULL)
          name = Key;
        log_source_message(
            (int)(uintptr_t)
                "Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
            329, 5, 0, "Warning: Camera ('%s') outside bounds!\n", name);
      }
    }
    sub_458A69(&iterator);
  }
  return outside_count;
}

int __thiscall camera_angle_count(uint32_t *manager)
{
  return (int)manager[4];
}

uint32_t **__thiscall camera_angle_entry_at_index(uint32_t **manager,
                                                 int index)
{
  uint32_t **iterator = (uint32_t **)*manager[2];
  sub_45945F((int *)&iterator, index);
  return iterator + 3;
}

int __thiscall set_camera_angle_from_spec(uint32_t *manager, char *name,
                                          int angle_spec)
{
  uint32_t *angle = sub_457CA5(56);
  angle = angle ? construct_camera_angle(angle) : NULL;
  copy_camera_angle_state((char *)(void *)angle, angle_spec);

  char lookup_key[16] = {0};
  lookup_key[0] = (char)((uintptr_t)angle_spec >> 24);
  tidy_std_string_storage(lookup_key, 0);
  assign_std_string_storage(lookup_key, name, strlen(name));

  int node;
  sub_4589E1(manager + 1, &node, (int)(uintptr_t)lookup_key);
  tidy_std_string_storage(lookup_key, 1);
  if ((uint32_t)node == manager[2]) {
    char insert_key[16] = {0};
    insert_key[0] = (char)((uintptr_t)name >> 24);
    tidy_std_string_storage(insert_key, 0);
    assign_std_string_storage(insert_key, name, strlen(name));
    uint32_t *value_address = (uint32_t *)(void *)
        sub_458576(manager + 1, insert_key);
    *value_address = (uint32_t)(uintptr_t)angle;
    tidy_std_string_storage(insert_key, 1);
  } else {
    uint32_t *old_angle = (uint32_t *)(uintptr_t)
        *(uint32_t *)(uintptr_t)(node + 28);
    if (old_angle != NULL) {
      typedef void (__thiscall *CameraAngleDestructor)(uint32_t *, int);
      CameraAngleDestructor destroy = (CameraAngleDestructor)(uintptr_t)
          *(uint32_t *)(void *)old_angle;
      destroy(old_angle, 1);
    }
    *(uint32_t *)(uintptr_t)(node + 28) = (uint32_t)(uintptr_t)angle;
  }
  return 0;
}

int __thiscall insert_camera_angle_from_spec(uint32_t *manager, char *name,
                                             int angle_spec)
{
  if (find_camera_angle_by_name(manager, name) != 0) {
    log_source_message(
        (int)(uintptr_t)
            "Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
        260, 5, 0, "Attempt to insert duplicate camera angle %s.", name);
  }
  return set_camera_angle_from_spec(manager, name, angle_spec);
}

uint32_t *__thiscall remove_camera_angle(uint32_t *manager, char *name)
{
  char key_storage[16] = {0};
  int node;

  key_storage[0] = (char)((uintptr_t)name >> 24);
  tidy_std_string_storage(key_storage, 0);
  assign_std_string_storage(key_storage, name, strlen(name));
  sub_4589E1(manager + 1, &node, (int)(uintptr_t)key_storage);
  tidy_std_string_storage(key_storage, 1);

  uint32_t *entry = (uint32_t *)(uintptr_t)node;
  uint32_t *angle = (uint32_t *)(uintptr_t)entry[7];
  if (angle != NULL) {
    typedef void (__thiscall *CameraAngleDestructor)(uint32_t *, int);
    CameraAngleDestructor destroy = (CameraAngleDestructor)(uintptr_t)
        *(uint32_t *)(void *)angle;
    destroy(angle, 1);
  }
  uint32_t result = 0;
  return sub_458657(manager + 1, &result, entry);
}

uint32_t *__thiscall clear_camera_angles(uint32_t *manager)
{
  int nil_node = (int)manager[2];
  int node = *(int *)(uintptr_t)nil_node;

  while (node != nil_node) {
    uint32_t *entry = (uint32_t *)(uintptr_t)node;
    uint32_t *angle = (uint32_t *)(uintptr_t)entry[7];
    if (angle != NULL) {
      typedef void (__thiscall *CameraAngleDestructor)(uint32_t *, int);
      CameraAngleDestructor destroy = (CameraAngleDestructor)(uintptr_t)
          *(uint32_t *)(void *)angle;
      destroy(angle, 1);
    }
    sub_458A69(&node);
  }
  return sub_4589CD((int)(uintptr_t)(manager + 1));
}

void __thiscall log_camera_angles(uint32_t *manager, uint32_t *context)
{
  uint32_t logger[4];
  begin_interface_debug_log(logger,
             (int)(uintptr_t)
                 "Z:\\Proj\\GK3\\gk3app\\Source\\CameraAngleMgr.cpp",
             376, 7, context);

  int nil_node = (int)manager[2];
  int node = *(int *)(uintptr_t)nil_node;
  while (node != nil_node) {
    uint32_t *entry = (uint32_t *)(uintptr_t)node;
    const char *name = *(const char **)(void *)(entry + 4);
    if (name == NULL)
      name = Key;
    log_interface_debug_message(logger, "%s = ", name);
    log_camera_angle_summary((float *)(uintptr_t)(entry[7] + 24), logger);
    log_interface_debug_message(logger, "\n");
    sub_458A69(&node);
  }
  end_interface_debug_log((int *)(void *)logger);
}

uint32_t *__thiscall destroy_camera_angle_map(uint32_t *map)
{
  uint32_t ignored_result[4];
  uint32_t *header = (uint32_t *)(uintptr_t)map[1];
  sub_458925(map, ignored_result, (uint32_t *)(uintptr_t)*header, header);
  free_tracked_memory((int)map[1]);
  map[1] = 0;
  map[3] = 0;

  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);
  if (--dword_764180 == 0) {
    free_tracked_memory(dword_76417C);
    dword_76417C = 0;
  }
  destroy_runtime_lockit(&lock_storage);
  return map;
}

uint32_t *__thiscall destroy_camera_angle_manager_members(uint32_t *manager)
{
  manager[0] = (uint32_t)(uintptr_t)&off_6AE0C8;
  clear_camera_angles(manager);
  destroy_camera_angle_map(manager + 1);
  return erase_map_entry_impl(
      unk_7640B8,
      (uint32_t)dword_7640B4
          + ((uintptr_t)manager != 0
                 ? (uint32_t)(uintptr_t)(manager + 1)
                 : 0));
}

void *__thiscall destroy_camera_angle_manager(void *object, char flags)
{
  destroy_camera_angle_manager_members((uint32_t *)object);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)object);
  return object;
}

void __thiscall initialize_camera_angle_map(uint32_t *map)
{
  uint32_t lock_storage = 0;
  construct_runtime_lockit(&lock_storage);

  if (dword_76417C == 0) {
    uint32_t *nil_node = allocate_tracked_memory(36);
    nil_node[1] = 0;
    nil_node[8] = 1;
    dword_76417C = (int)(uintptr_t)nil_node;
    nil_node[0] = 0;
    nil_node[2] = 0;
  }

  ++dword_764180;
  uint32_t *node = allocate_tracked_memory(36);
  node[1] = (uint32_t)dword_76417C;
  node[8] = 0;
  map[1] = (uint32_t)(uintptr_t)node;
  map[3] = 0;
  node[0] = (uint32_t)(uintptr_t)node;
  node[2] = (uint32_t)(uintptr_t)node;

  destroy_runtime_lockit(&lock_storage);
}

char *__thiscall construct_camera_angle_manager(char *object)
{
  char default_value;
  find_or_create_registry_entry(unk_7640B8,
             (uint32_t)(uintptr_t)&object[dword_7640B4 + 4]);
  object[12] = 0;
  object[4] = default_value;
  object[5] = default_value;
  initialize_camera_angle_map((uint32_t *)(void *)object + 1);
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)&off_6AE0C8;
  return object;
}

char *__thiscall construct_registered_camera_angle_manager(char *object,
                                                            int unused)
{
  char default_value;
  find_or_create_registry_entry(unk_7640B8,
             (uint32_t)(uintptr_t)&object[dword_7640B4 + 4]);
  object[12] = 0;
  object[4] = default_value;
  object[5] = default_value;
  initialize_camera_angle_map((uint32_t *)(void *)object + 1);
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)&off_6AE0C8;
  return object;
}

uint32_t *allocate_registered_camera_angle_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_7640B8,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_camera_angle_manager(void)
{
  char *memory = (char *)allocate_registered_camera_angle_manager(20);
  return memory ? (uint32_t *)(void *)construct_camera_angle_manager(memory)
                : NULL;
}

uint32_t *create_registered_camera_angle_manager(void)
{
  char *memory = (char *)allocate_registered_camera_angle_manager(20);
  return memory
      ? (uint32_t *)(void *)construct_registered_camera_angle_manager(memory,
                                                                       0)
      : NULL;
}
