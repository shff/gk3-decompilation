#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t camera_type_descriptor[];
extern int game_engine_instance_address;
extern int parent_control_default_object;
extern int default_stacked_hook_control;
extern int camera_manager_base_offset_adjustment;
extern uint32_t user_scene_controller_type_descriptor[15];
extern uint32_t camera_manager_vtable[];
extern uint32_t camera_pointer_vector_vtable[];
extern uint32_t dynamic_array_vtable[];
extern int game_engine_address;
extern uint32_t *__thiscall construct_stacked_hook_control(
    uint32_t *camera, uint32_t *camera_defaults);
extern uint32_t *__thiscall construct_byte_list(uint32_t *object,
                                                char *default_value);
extern uint32_t *__thiscall construct_dynamic_array(uint32_t *object,
                                                    int growth_capacity);
extern uint32_t *__thiscall construct_pointer_vector(uint32_t *object,
                                                     int capacity);
extern uint32_t *__thiscall construct_camera_angle(uint32_t *object);
extern uint32_t *__thiscall construct_camera_controller_popper_list(
    uint32_t *object, char *default_value);
extern char __thiscall read_smooth_camera_transition_setting(
    uint32_t **settings);
extern int *__thiscall set_registry_object_flags(
    uint32_t *registry, uint32_t address, int flags);
extern int __thiscall construct_user_scene_controller(int object);
extern uint8_t *__thiscall push_camera_controller(int *camera,
                                                  uint8_t *controller,
                                                  char active);
extern int __thiscall set_control_active(uint8_t *control, char active);
extern char __thiscall read_camera_smooth_motion_setting(
    uint32_t **settings);
extern char *__thiscall synchronize_camera_state_from_game_view(
    uint32_t *camera);
extern void __thiscall set_camera_viewport_rectangle(
    uint32_t *camera, uint32_t *rectangle, char update_engine_viewport);
extern int __thiscall get_top_camera_controller(uint32_t *collection);
extern void __thiscall pop_camera_stack_through(uint32_t *collection,
                                                int controller);
extern void __thiscall pop_top_camera_controller(uint32_t *camera);
extern int active_scene_controller_address;
extern int __thiscall adjust_camera_stack_iterator(int *iterator, int step);
extern void __thiscall release_segmented_storage(int stack_address);
extern uint32_t *__thiscall advance_segmented_storage_iterator(
    uint32_t *iterator);
extern uint32_t *__thiscall allocate_camera_hook_stack_page(
    uint32_t *hook_stack);
extern void __thiscall release_camera_hook_stack_page_if_empty(
    uint32_t *hook_stack);
extern int *__thiscall remove_camera_controller_popper_for_controller(
    int *camera, int controller);
extern int __thiscall camera_rectangles_differ(uint32_t *rectangle,
                                               uint32_t *other);
extern unsigned int __thiscall ensure_segmented_storage_capacity(
    uint32_t *stack, int required_slots);
extern uint32_t *__thiscall decrement_segmented_storage_iterator(
    uint32_t *iterator);
extern uint8_t *__thiscall append_byte_storage_value(uint32_t *collection,
                                                     uint8_t *value);
extern void __thiscall pop_byte_storage_value(uint32_t *collection);
extern unsigned int __thiscall adjust_segmented_byte_iterator(
    uint32_t *iterator, int step);
extern int __thiscall free_pointer_vector_storage(int *collection);
extern int __thiscall destroy_pointer_vector_elements(int *collection);
extern uint32_t *__thiscall erase_segmented_byte_storage_range(
    int *collection, uint32_t *temporary, int first, int second,
    uint8_t *third, int fourth, int fifth, int sixth, uint8_t *seventh,
    int eighth);
extern uint32_t *__thiscall append_camera_controller_popper(
    uint32_t *list, int *value);
extern int *__thiscall erase_camera_controller_popper_range(
    int *list, int *temporary, int first_begin, int first_end,
    uint32_t *first_position, int first_capacity, int second_begin,
    int second_end, uint32_t *second_position, int second_capacity);
extern uint32_t *__thiscall advance_camera_controller_popper_iterator(
    uint32_t *iterator);
extern int __thiscall adjust_camera_controller_popper_iterator(
    int *iterator, int step);
extern int __thiscall vector_element_address(uint32_t *collection, int index);
extern int __thiscall append_dynamic_array_element(uint32_t *collection,
                                                 int value);
extern void __thiscall erase_integer_array_value(uint32_t *collection,
                                                 int index);
extern int __thiscall find_integer_array_value(uint32_t *collection,
                                               int value);
extern uint32_t *__thiscall create_camera_target_reference(
    uint32_t *engine, uint16_t target_id, int mode);
extern void __thiscall release_camera_target_reference(int **reference);
extern int __thiscall destroy_camera_target_reference(int *object);
extern void __cdecl free_tracked_memory(int address);
extern double __thiscall get_camera_angle_field_of_view(float *value);
extern char *__thiscall copy_camera_angle_state(char *destination,
                                                int source);
extern float __thiscall get_engine_camera_pitch(uint32_t *engine);
extern double __thiscall get_engine_camera_yaw(uint32_t *engine);
extern uint32_t *__thiscall get_engine_camera_position(uint32_t *engine);
extern float __thiscall get_engine_camera_field_of_view(uint32_t *engine);
extern int *__thiscall get_engine_viewport_rectangle(
    int *engine, int *rectangle, float *width, float *height, float *scale);
extern void __thiscall set_engine_viewport_rectangle(
    uint32_t *engine, uint32_t *rectangle, float width, float height,
    float scale, int update);

int __thiscall construct_camera_manager(int object)
{
  uint8_t *camera = (uint8_t *)(uintptr_t)object;
  char default_value;

  construct_stacked_hook_control((uint32_t *)(void *)camera,
                                 (uint32_t *)(uintptr_t)default_stacked_hook_control);
  find_or_create_registry_entry(camera_type_descriptor,
             (uint32_t)camera_manager_base_offset_adjustment
                 + (uint32_t)object + 129);
  construct_byte_list((uint32_t *)(void *)(camera + 132), &default_value);
  camera[180] = 1;
  camera[181] = 1;
  construct_dynamic_array((uint32_t *)(void *)(camera + 184), 20);
  *(uint32_t *)(void *)(camera + 184) =
      (uint32_t)(uintptr_t)dynamic_array_vtable;
  construct_pointer_vector((uint32_t *)(void *)(camera + 208), 20);
  *(uint32_t *)(void *)(camera + 208) =
      (uint32_t)(uintptr_t)camera_pointer_vector_vtable;
  construct_byte_list((uint32_t *)(void *)(camera + 232), &default_value);
  construct_camera_angle((uint32_t *)(void *)(camera + 280));
  construct_camera_angle((uint32_t *)(void *)(camera + 336));
  construct_camera_angle((uint32_t *)(void *)(camera + 392));
  construct_camera_angle((uint32_t *)(void *)(camera + 448));
  *(uint32_t *)(void *)(camera + 536) = 0;
  construct_camera_angle((uint32_t *)(void *)(camera + 544));
  construct_camera_controller_popper_list(
      (uint32_t *)(void *)(camera + 604), &default_value);
  *(uint32_t *)(void *)camera = (uint32_t)(uintptr_t)camera_manager_vtable;
  *(uint32_t *)(void *)(camera + 204) = 1;
  *(uint32_t *)(void *)(camera + 504) = 0;
  uint32_t **settings =
      *(uint32_t ***)(uintptr_t)(game_engine_instance_address + 1192);
  camera[532] = (uint8_t)read_smooth_camera_transition_setting(settings);
  camera[533] = 0;
  camera[534] = 0;
  *(uint32_t *)(void *)(camera + 540) = 0;
  uint32_t *camera_state = allocate_tracked_memory(260);
  set_registry_object_flags(user_scene_controller_type_descriptor,
                            (uint32_t)(uintptr_t)camera_state, 1);
  uint8_t *state = camera_state
      ? (uint8_t *)(uintptr_t)construct_user_scene_controller(
            (int)(uintptr_t)camera_state)
      : NULL;
  push_camera_controller((int *)(void *)camera, state, 1);
  *(uint32_t *)(void *)(camera + 600) = 0;
  set_control_active(camera, 1);
  return object;
}

uint32_t *allocate_registered_camera(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(camera_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_camera_manager(void)
{
  uint32_t *memory = allocate_registered_camera(652);
  return memory
      ? (uint32_t *)(uintptr_t)construct_camera_manager((int)(uintptr_t)memory)
      : NULL;
}

void initialize_camera_manager(uint32_t *camera)
{
  uint32_t **settings =
      *(uint32_t ***)(uintptr_t)(game_engine_instance_address + 1192);

  *((uint8_t *)(void *)camera + 180) =
      read_camera_smooth_motion_setting(settings);
  synchronize_camera_state_from_game_view(camera);
  set_camera_viewport_rectangle(
      camera, (uint32_t *)(void *)&parent_control_default_object, 1);
}

void shutdown_camera_manager(uint32_t *camera_manager)
{
  while (camera_manager[44] != 0) {
    const int camera = get_top_camera_controller(camera_manager);
    pop_camera_stack_through(camera_manager, camera);
  }
}

uint32_t *__thiscall construct_camera_controller_popper_list(
    uint32_t *list, char *default_value)
{
  uint32_t *result = list;
  *(uint8_t *)(void *)list = (uint8_t)*default_value;
  list[1] = 0;
  list[2] = 0;
  list[3] = 0;
  list[4] = 0;
  list[5] = 0;
  list[6] = 0;
  list[7] = 0;
  list[8] = 0;
  list[9] = 0;
  list[10] = 0;
  list[11] = 0;
  return result;
}

int __thiscall get_top_camera_controller(uint32_t *camera)
{
  int iterator[4];

  iterator[0] = camera[25];
  iterator[1] = camera[26];
  iterator[2] = camera[27];
  iterator[3] = camera[28];
  adjust_camera_stack_iterator(iterator, -1);
  return *(int *)(uintptr_t)iterator[2];
}

void __thiscall set_camera_controller_hook(uint32_t *camera,
                                            uint8_t *controller,
                                            char update_hook)
{
  uint32_t *current_hook = camera + 18;
  if (*current_hook != (uint32_t)(uintptr_t)controller) {
    if (update_hook) {
      uint32_t *controller_vtable =
          *(uint32_t **)(void *)controller;
      void (__thiscall *notify)(uint8_t *);
      notify = (void (__thiscall *)(uint8_t *))
          (uintptr_t)controller_vtable[camera[1] ? 1 : 2];
      notify(controller);
    }

    *current_hook = (uint32_t)(uintptr_t)controller;
    if (camera[6] && controller[24]) {
      uint32_t *controller_vtable = *(uint32_t **)(void *)controller;
      void (__thiscall *activate)(uint8_t *);
      activate = (void (__thiscall *)(uint8_t *))
          (uintptr_t)controller_vtable[38];
      activate(controller);

      const uint32_t input_controller_address =
          *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
      const uint32_t input_controller =
          *(uint32_t *)(uintptr_t)(input_controller_address + 68);
      *(uint8_t *)(uintptr_t)(input_controller + 12) = 1;
      *(uint8_t *)(uintptr_t)(input_controller + 24) = 1;
      *(uint32_t *)(uintptr_t)(input_controller + 16) = 0;
    }
  }
}

int __thiscall clear_camera_controller_hook(uint32_t *camera)
{
  uint8_t *controller =
      (uint8_t *)(uintptr_t)*(uint32_t *)(void *)(camera + 18);
  int result = 0;
  if (controller && camera[6] && controller[24]) {
    uint32_t *controller_vtable = *(uint32_t **)(void *)controller;
    void (__thiscall *activate)(uint8_t *);
    activate = (void (__thiscall *)(uint8_t *))
        (uintptr_t)controller_vtable[38];
    activate(controller);

    const uint32_t input_controller_address =
        *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
    result = *(int *)(uintptr_t)(input_controller_address + 68);
    *(uint32_t *)(uintptr_t)(result + 16) = 0;
    *(uint8_t *)(uintptr_t)(result + 12) = 1;
    *(uint8_t *)(uintptr_t)(result + 24) = 1;
  }

  *(uint32_t *)(void *)(camera + 18) = 0;
  return result;
}

int __thiscall notify_camera_controller_activation(uint32_t *camera)
{
  int result = 0;
  if (camera[1]) {
    int iterator[4] = {
        (int)camera[25], (int)camera[26],
        (int)camera[27], (int)camera[28]};
    adjust_camera_stack_iterator(iterator, -1);
    const uint32_t controller = *(uint32_t *)(uintptr_t)iterator[2];
    uint32_t *controller_vtable =
        *(uint32_t **)(uintptr_t)controller;
    int (__thiscall *notify)(uint32_t *);
    notify = (int (__thiscall *)(uint32_t *))
        (uintptr_t)controller_vtable[1];
    result = notify((uint32_t *)(uintptr_t)controller);
  }
  return result;
}

int __thiscall notify_camera_controller_deactivation(uint32_t *camera)
{
  int iterator[4] = {
      (int)camera[25], (int)camera[26],
      (int)camera[27], (int)camera[28]};
  adjust_camera_stack_iterator(iterator, -1);
  const uint32_t controller = *(uint32_t *)(uintptr_t)iterator[2];
  uint32_t *controller_vtable = *(uint32_t **)(uintptr_t)controller;
  int (__thiscall *notify)(uint32_t *);
  notify = (int (__thiscall *)(uint32_t *))
      (uintptr_t)controller_vtable[2];
  return notify((uint32_t *)(uintptr_t)controller);
}

uint32_t *__thiscall push_camera_hook_stack_entry(uint32_t *hook_stack,
                                                   uint32_t *entry_address)
{
  if (!hook_stack[11] || hook_stack[7] == hook_stack[6])
    allocate_camera_hook_stack_page(hook_stack);

  advance_segmented_storage_iterator(hook_stack + 5);
  int iterator[4] = {
      (int)hook_stack[5], (int)hook_stack[6],
      (int)hook_stack[7], (int)hook_stack[8]};
  adjust_camera_stack_iterator(iterator, -1);
  uint32_t *entry = (uint32_t *)(uintptr_t)iterator[2];
  if (entry)
    *entry = *entry_address;
  ++hook_stack[11];
  return entry;
}

void __thiscall pop_camera_hook_stack_entry(uint32_t *hook_stack)
{
  if (hook_stack[11]) {
    int iterator[4] = {
        (int)hook_stack[5], (int)hook_stack[6],
        (int)hook_stack[7], (int)hook_stack[8]};
    adjust_camera_stack_iterator(iterator, -1);
    release_camera_hook_stack_page_if_empty(hook_stack);
  }
}

uint32_t *__thiscall allocate_camera_hook_stack_page(uint32_t *hook_stack)
{
  uint32_t *page = allocate_tracked_memory(4096);
  uint32_t *result;
  uint32_t *stack_iterator;
  uint32_t *directory_entry;
  uint32_t *directory_begin;
  uint32_t *directory_end;
  uint32_t *directory_capacity;
  uint32_t *stack_fields = hook_stack + 5;

  if (hook_stack[11]) {
    const uint32_t stack_page = hook_stack[8];
    if (stack_page >= hook_stack[9] + 4 * hook_stack[10] - 8) {
      const int required_slots =
          (int)((stack_page - hook_stack[4]) / sizeof(uint32_t)) + 1;
      directory_begin = (uint32_t *)(uintptr_t)
          ensure_segmented_storage_capacity(hook_stack, required_slots);
      directory_entry = &directory_begin[required_slots];
      *directory_entry = (uint32_t)(uintptr_t)page;
      directory_entry[1] = 0;
      hook_stack[1] = directory_begin[0];
      hook_stack[2] = hook_stack[1] + 4096;
      hook_stack[4] = (uint32_t)(uintptr_t)directory_begin;
      result = page;
      stack_iterator = directory_entry;
      directory_begin = page;
      directory_end = page + 4096 / sizeof(uint32_t);
      directory_capacity = page;
    } else {
      uint32_t *next_stack_page = (uint32_t *)(uintptr_t)(stack_page + 4);
      hook_stack[8] = (uint32_t)(uintptr_t)next_stack_page;
      *next_stack_page = (uint32_t)(uintptr_t)page;
      next_stack_page[1] = 0;
      result = next_stack_page;
      stack_iterator = result;
      directory_begin = (uint32_t *)(uintptr_t)*result;
      directory_end = directory_begin + 4096 / sizeof(uint32_t);
      directory_capacity = page;
    }
  } else {
    uint32_t *directory = allocate_tracked_memory(32);
    hook_stack[9] = (uint32_t)(uintptr_t)directory;
    hook_stack[10] = 8;
    directory[3] = 0;
    directory[4] = (uint32_t)(uintptr_t)page;
    directory[5] = 0;
    stack_iterator = &directory[4];
    directory_begin = (uint32_t *)(uintptr_t)*stack_iterator;
    directory_end = directory_begin + 4096 / sizeof(uint32_t);
    directory_capacity = page + 512;
    hook_stack[1] = (uint32_t)(uintptr_t)directory_begin;
    hook_stack[2] = (uint32_t)(uintptr_t)directory_end;
    hook_stack[3] = (uint32_t)(uintptr_t)directory_capacity;
    hook_stack[4] = (uint32_t)(uintptr_t)stack_iterator;
    result = directory_end;
  }

  stack_fields[0] = (uint32_t)(uintptr_t)directory_begin;
  stack_fields[1] = (uint32_t)(uintptr_t)directory_end;
  stack_fields[2] = (uint32_t)(uintptr_t)directory_capacity;
  stack_fields[3] = (uint32_t)(uintptr_t)stack_iterator;
  return result;
}

void __thiscall release_camera_hook_stack_page_if_empty(
    uint32_t *hook_stack)
{
  int *previous_page = (int *)(uintptr_t)hook_stack[8];
  decrement_segmented_storage_iterator(hook_stack + 5);
  if (hook_stack[11]-- == 1) {
    release_segmented_storage((int)(uintptr_t)hook_stack);
  } else if ((uint32_t)(uintptr_t)previous_page != hook_stack[8]) {
    free_tracked_memory(*previous_page);
    *previous_page = 0;
  }
}

int __thiscall install_camera_controller_hook(uint32_t *camera,
                                               uint8_t *controller)
{
  if (camera[31] != 0) {
    notify_camera_controller_deactivation(camera);
  }

  set_camera_controller_hook(camera, controller, 1);
  uint32_t controller_address = (uint32_t)(uintptr_t)controller;
  push_camera_hook_stack_entry(camera + 20, &controller_address);
  return notify_camera_controller_activation(camera);
}

int __thiscall restore_camera_controller_hook(uint32_t *camera)
{
  notify_camera_controller_deactivation(camera);
  pop_camera_hook_stack_entry(camera + 20);
  if (camera[31] == 0) {
    return clear_camera_controller_hook(camera);
  }

  uint32_t iterator[4] = {
      camera[25], camera[26], camera[27], camera[28]};
  adjust_camera_stack_iterator((int *)iterator, -1);
  uint8_t *previous_controller =
      (uint8_t *)(uintptr_t)*(uint32_t *)(uintptr_t)iterator[2];
  set_camera_controller_hook(camera, previous_controller, 1);
  return notify_camera_controller_activation(camera);
}

uint8_t *__thiscall push_camera_controller(int *camera,
                                           uint8_t *controller,
                                           char active)
{
  if (camera[44] != 0) {
    for (;;) {
      const int top = get_top_camera_controller((uint32_t *)(void *)camera);
      if (!(*(uint8_t (__thiscall **)(int))(uintptr_t)
                (*(uint32_t *)(uintptr_t)top + 220))(top)) {
        break;
      }

      const int previous_top =
          get_top_camera_controller((uint32_t *)(void *)camera);
      (*(void (__thiscall **)(int))(uintptr_t)
           (*(uint32_t *)(uintptr_t)previous_top + 228))(previous_top);
      remove_camera_controller_popper_for_controller(camera, previous_top);
      pop_top_camera_controller((uint32_t *)(void *)camera);
    }
  }

  uint32_t rectangle[4] = {camera[7], camera[8], camera[9], camera[10]};
  (*(void (__thiscall **)(uint8_t *, uint32_t *))(uintptr_t)
       (*(uint32_t *)(uintptr_t)controller + 216))(controller, rectangle);
  (*(void (__thiscall **)(uint8_t *, int))(uintptr_t)
       (*(uint32_t *)(uintptr_t)controller + 176))(controller, 1);
  install_camera_controller_hook((uint32_t *)(void *)camera, controller);
  return append_byte_storage_value((uint32_t *)(void *)camera + 33,
                                   (uint8_t *)&active);
}

void __thiscall pop_camera_stack_through(uint32_t *camera, int controller)
{
  while (get_top_camera_controller(camera) != controller) {
    pop_top_camera_controller(camera);
  }
  pop_top_camera_controller(camera);
}

void __thiscall reset_camera_controller_stack(uint32_t *camera)
{
  while (camera[44] > 1) {
    pop_top_camera_controller(camera);
  }
  camera[150] = 0;
}

uint32_t *__thiscall add_camera_controller_popper(uint32_t *camera,
                                                  int controller)
{
  return append_camera_controller_popper(camera + 151, &controller);
}

int *__thiscall remove_camera_controller_popper_for_controller(
    int *camera, int controller)
{
  int temporary[4];
  int current[4] = {camera[152], camera[153], camera[154], camera[155]};
  int first_end[4] = {camera[156], camera[157], camera[158], camera[159]};

  while (current[2] != first_end[2]) {
    if (*(int *)(uintptr_t)(*(int *)(uintptr_t)current[2] + 8) == controller) {
      *(int *)(uintptr_t)(*(int *)(uintptr_t)current[2] + 8) = 0;
      int second_begin[4] = {current[0], current[1], current[2], current[3]};
      int second_end[4] = {current[0], current[1], current[2], current[3]};
      adjust_camera_controller_popper_iterator(second_end, 1);
      return erase_camera_controller_popper_range(camera + 151, temporary,
                        current[0], current[1],
                        (uint32_t *)(uintptr_t)current[2], current[3],
                        second_end[0], second_end[1],
                        (uint32_t *)(uintptr_t)second_end[2],
                        second_end[3]);
    }
    advance_camera_controller_popper_iterator((uint32_t *)(void *)current);
  }
  return (int *)(uintptr_t)current[2];
}

int *__thiscall remove_camera_controller_popper(uint32_t *camera,
                                                 int controller)
{
  int temporary[4];
  int current[4] = {camera[152], camera[153], camera[154], camera[155]};
  int first_end[4] = {camera[156], camera[157], camera[158], camera[159]};

  while (current[2] != first_end[2]) {
    if (*(int *)(uintptr_t)current[2] == controller) {
      int second_begin[4] = {current[0], current[1], current[2], current[3]};
      int second_end[4] = {current[0], current[1], current[2], current[3]};
      adjust_camera_controller_popper_iterator(second_end, 1);
      return erase_camera_controller_popper_range(
                        (int *)(void *)(camera + 151), temporary,
                        current[0], current[1],
                        (uint32_t *)(uintptr_t)current[2], current[3],
                        second_end[0], second_end[1],
                        (uint32_t *)(uintptr_t)second_end[2],
                        second_end[3]);
    }
    advance_camera_controller_popper_iterator((uint32_t *)(void *)current);
  }
  return (int *)(uintptr_t)current[2];
}

int __thiscall is_camera_target_registered(uint32_t *camera,
                                           int target_id,
                                           char local_only)
{
  int index;

  if (!local_only) {
    uint32_t *shared_targets = (uint32_t *)(uintptr_t)(
        *(uint32_t *)(uintptr_t)(active_scene_controller_address + 84) + 424);
    index = find_integer_array_value(shared_targets, target_id);
    if (index != -1) {
      return 1;
    }
  }

  index = find_integer_array_value(camera + 52, target_id);
  return index != -1;
}

void __thiscall register_camera_target(uint32_t *camera, int target_id,
                                       char temporary)
{
  int *reference[4] = {NULL, NULL, NULL, NULL};

  if (is_camera_target_registered(camera, target_id, 0)) {
    return;
  }

  append_dynamic_array_element(camera + 52, target_id);
  append_byte_storage_value(camera + 58, (uint8_t *)&temporary);
  reference[0] = (int *)create_camera_target_reference(
      (uint32_t *)(uintptr_t)game_engine_address, (uint16_t)target_id, 0);
  reference[0][12] = temporary == 0;
  append_dynamic_array_element(camera + 46, (int)(uintptr_t)reference[0]);
  reference[0] = NULL;
  reference[3] = (int *)-1;
  release_camera_target_reference(reference);
}

void __thiscall unregister_camera_target(uint32_t *camera, int target_id)
{
  if (!is_camera_target_registered(camera, target_id, 1)) {
    return;
  }

  const int index = find_integer_array_value(camera + 52, target_id);
  erase_integer_array_value(camera + 52, index);

  uint32_t flag_iterator[4] = {
      camera[59], camera[60], camera[61], camera[62]};
  adjust_segmented_byte_iterator(flag_iterator, index);
  uint32_t flag_end[4] = {
      flag_iterator[0], flag_iterator[1], flag_iterator[2], flag_iterator[3]};
  adjust_segmented_byte_iterator(flag_end, 1);
  erase_segmented_byte_storage_range(
             (int *)(void *)(camera + 58), (uint32_t[4]){0},
             (int)flag_iterator[0], (int)flag_iterator[1],
             (uint8_t *)(uintptr_t)flag_iterator[2],
             (int)flag_iterator[3], (int)flag_end[0], (int)flag_end[1],
             (uint8_t *)(uintptr_t)flag_end[2], (int)flag_end[3]);

  uint32_t *reference_slot = (uint32_t *)(uintptr_t)
      vector_element_address(camera + 46, index);
  int *reference = (int *)(uintptr_t)*reference_slot;
  if (reference != NULL) {
    destroy_camera_target_reference(reference);
    free_tracked_memory((int)(uintptr_t)reference);
  }
  erase_integer_array_value(camera + 46, index);
}

int __thiscall release_camera_manager_collections(uint32_t *camera)
{
  uint32_t temporary[4];

  if ((int)camera[54] <= 0) {
    return 0;
  }

  free_pointer_vector_storage((int *)(void *)(camera + 52));
  erase_segmented_byte_storage_range((int *)(void *)(camera + 58), temporary,
             (int)camera[59], (int)camera[60],
             (uint8_t *)(uintptr_t)camera[61], (int)camera[62],
             (int)camera[63], (int)camera[64],
             (uint8_t *)(uintptr_t)camera[65], (int)camera[66]);
  return destroy_pointer_vector_elements((int *)(void *)(camera + 46));
}

void __thiscall pop_top_camera_controller(uint32_t *camera)
{
  uint32_t iterator[2];
  uint8_t *active;
  void (__thiscall ***controller)(uint32_t, int);

  controller = (void (__thiscall ***)(uint32_t, int))
      (uintptr_t)get_top_camera_controller(camera);
  restore_camera_controller_hook(camera);
  iterator[0] = camera[38];
  iterator[1] = camera[39];
  active = (uint8_t *)(uintptr_t)camera[40];
  adjust_segmented_byte_iterator(iterator, -1);
  if (*active != 0 && controller != NULL) {
    (**controller)((uint32_t)(uintptr_t)controller, 1);
  }
  pop_byte_storage_value(camera + 33);
}

char *__thiscall synchronize_camera_state_from_game_view(uint32_t *camera)
{
  uint32_t *engine = (uint32_t *)(uintptr_t)game_engine_address;
  float viewport_scale;
  const float pitch = get_engine_camera_pitch(engine);
  const double yaw = get_engine_camera_yaw(engine);
  uint32_t *position;

  *(float *)(void *)((uint8_t *)(void *)camera + 360) = (float)yaw;
  *(float *)(void *)((uint8_t *)(void *)camera + 364) = pitch;
  position = get_engine_camera_position(engine);
  *(uint32_t *)(void *)((uint8_t *)(void *)camera + 368) = position[0];
  *(uint32_t *)(void *)((uint8_t *)(void *)camera + 372) = position[1];
  *(uint32_t *)(void *)((uint8_t *)(void *)camera + 376) = position[2];
  *(float *)(void *)((uint8_t *)(void *)camera + 380) =
      get_engine_camera_field_of_view(engine);
  get_engine_viewport_rectangle(
      (int *)engine, (int *)(void *)((uint8_t *)(void *)camera + 516),
      (float *)(void *)((uint8_t *)(void *)camera + 508),
      (float *)(void *)((uint8_t *)(void *)camera + 512), &viewport_scale);
  *(float *)(void *)((uint8_t *)(void *)camera + 384) = viewport_scale;
  (*(void (__thiscall **)(uint32_t *))(uintptr_t)
       (*(uint32_t *)(uintptr_t)(camera + 84) + 24))(camera + 84);
  return copy_camera_angle_state((char *)(void *)(camera + 70),
                                 (int)(uintptr_t)(camera + 84));
}

void __thiscall set_camera_viewport_rectangle(uint32_t *camera,
                                              uint32_t *rectangle,
                                              char update_engine_viewport)
{
  uint32_t *current_rectangle = camera + 129;

  if (camera_rectangles_differ(current_rectangle, rectangle)
      || update_engine_viewport) {
    current_rectangle[0] = rectangle[0];
    current_rectangle[1] = rectangle[1];
    current_rectangle[2] = rectangle[2];
    current_rectangle[3] = rectangle[3];

    (*(void (__thiscall **)(uint32_t *, uint32_t *))(uintptr_t)
         (*(uint32_t *)(uintptr_t)camera[0] + 168))(camera, current_rectangle);

    const float scale =
        (float)get_camera_angle_field_of_view((float *)(void *)(camera + 76));
    set_engine_viewport_rectangle(
        (uint32_t *)(uintptr_t)game_engine_address, current_rectangle,
        *(float *)(void *)(camera + 127), *(float *)(void *)(camera + 128),
        scale, 1);

    if (active_scene_controller_address != 0) {
      synchronize_camera_state_from_game_view(camera);
    }
  }
}
