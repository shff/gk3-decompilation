#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *map,
                                                 uint32_t address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_7664C0[];
extern int interface_manager_base_offset_adjustment
    __asm__("dword_7664BC");
extern int cursor_default_coordinate_x __asm__("dword_76D3F8");
extern int cursor_default_coordinate_y __asm__("dword_76D3FC");
extern int interface_layer_type_descriptor __asm__("dword_764788");
extern int cursor_screen_position_address __asm__("dword_764728");
extern int game_engine_instance_address __asm__("dword_765A2C");
extern int game_engine_address;
extern uint32_t __stdcall GetForegroundWindow(void);
extern uint32_t *__cdecl create_window_capture_event(
    uint32_t **event_storage, int event_id) __asm__("sub_4CE074");
extern uint32_t __stdcall SetCapture(uint32_t window);
extern int __stdcall ReleaseCapture(void);
extern uint8_t loc_640794;
extern uint32_t interface_manager_vtable[] __asm__("off_6C8240");
extern int __thiscall destroy_interface_layer_collection(int list)
    __asm__("sub_4E8DAB");
extern int __cdecl destroy_interface_cursor(uint32_t *member)
    __asm__("sub_4E9587");
extern int __cdecl destroy_interface_console(uint32_t *member)
    __asm__("sub_4E959D");
extern int __cdecl destroy_interface_owned_layer(uint32_t *member)
    __asm__("sub_4E95B3");
extern int __cdecl destroy_interface_ui_translator(uint32_t *member)
    __asm__("sub_4E95C9");
extern void *__thiscall begin_interface_debug_log(
    int *context, int file, int line, int category, uint32_t *arguments)
    __asm__("sub_52D127");
extern void __thiscall end_interface_debug_log(int *context)
    __asm__("sub_52D18D");
extern void __cdecl log_interface_debug_message(int context, char *format, ...)
    __asm__("sub_409150");
extern int __thiscall interface_layer_index_between(uint32_t *first,
                                                    uint32_t *last)
    __asm__("sub_4E97B0");
extern int __thiscall get_engine_input_state(uint32_t *engine, char unused);
extern const char Key[4];
extern uint32_t *__thiscall initialize_layer_pointer_array(
    uint32_t *object, char *default_value) __asm__("sub_4E9019");
extern uint32_t *__cdecl allocate_registered_interface_layer(int size)
    __asm__("sub_4E7B5E");
extern uint32_t *__thiscall construct_registered_interface_layer(
    uint32_t *object, uint32_t *type_descriptor) __asm__("sub_4ED193");
extern char *__thiscall assign_std_string_storage(char *storage,
                                                  const char *value,
                                                  size_t length);
extern uint32_t *__cdecl create_layer_child_added_event(
    uint32_t *member, int layer_id, int layer_address) __asm__("sub_4E686D");
extern uint32_t *__cdecl create_layer_child_removed_event(
    uint32_t *member, int layer_id, int layer_address) __asm__("sub_4E6964");
extern void __thiscall destroy_interface_temporary_object(uint32_t *object)
    __asm__("sub_48567E");
extern uint32_t *__cdecl allocate_registered_interface_layer_collection(
    int size) __asm__("sub_4E5FCB");
extern uint32_t *__thiscall construct_private_bottom_layer(uint32_t *object)
    __asm__("sub_4E606B");
extern uint32_t *__thiscall initialize_layer_collection_reference(int *result)
    __asm__("sub_4E8BF7");
extern uint32_t *__thiscall add_layer_collection_reference(
    uint32_t *member, uint32_t *value) __asm__("sub_4E8DC5");
extern uint32_t *__cdecl allocate_registered_interface_console(int size)
    __asm__("sub_4E7B81");
extern int __thiscall create_interface_input_object(
    uint32_t *manager, char *first, int second) __asm__("sub_485923");
extern uint32_t *__cdecl allocate_registered_cursor(int size)
    __asm__("sub_4842AB");
extern uint32_t __thiscall construct_cursor(uint32_t object)
    __asm__("sub_48436A");
extern void __thiscall set_cursor_spec(uint32_t object, int context)
    __asm__("sub_484E36");
extern char *get_mouse_cursor_worker_manager(void);
extern int __cdecl set_engine_cursor_screen_position(uint32_t *position)
    __asm__("sub_5A71A0");
extern int __thiscall construct_interface_console(int object)
    __asm__("sub_55903E");
extern uint32_t *__cdecl allocate_registered_ui_translator(int size)
    __asm__("sub_4E6D07");
extern char **__thiscall construct_ui_translator(char **object)
    __asm__("sub_4E6DBC");
extern void __thiscall release_layer_collection_reference(
    uint32_t **objects) __asm__("sub_4E653D");
extern int __thiscall adjust_interface_layer_iterator(int *iterator,
                                                      int direction)
    __asm__("sub_484175");
extern uint32_t *__thiscall advance_interface_layer_iterator(
    uint32_t *iterator) __asm__("sub_4E8CC5");
extern uint32_t *__thiscall retain_interface_event_reference(
    uint32_t *reference, uint32_t **event) __asm__("sub_4E8D98");
extern int __thiscall append_interface_recipient(int list, uint32_t *value)
    __asm__("sub_4E8D14");
extern int __thiscall release_interface_recipient_list(int *list)
    __asm__("sub_4E8FBF");
extern uint32_t *__thiscall erase_interface_layer_range(
    int *list, uint32_t *result, int first_start, int first_index,
    uint32_t *first_current, int first_end, int last_start, int last_index,
    uint32_t *last_current, int last_end) __asm__("sub_4E8E50");
extern uint32_t *__thiscall retreat_interface_layer_iterator(
    uint32_t *iterator) __asm__("sub_4E8F94");
extern int __cdecl release_interface_event_and_get_payload(uint32_t *reference)
    __asm__("sub_4A2943");
extern void __thiscall reset_engine_input_state(int engine);
extern char __thiscall has_game_layer_object(uint32_t *layer_manager,
                                             int layer_id);
extern char *__thiscall get_game_layer_slot(char *layer_manager, int layer_id,
                                            char create);
extern void __thiscall clear_pointer_activity_state(int object);
extern uint32_t *__cdecl get_engine_cursor_screen_position(uint32_t *result)
    __asm__("sub_5A7160");
extern int __thiscall sub_4BA1D4(int engine, int first, char second,
                                 char third);
extern int __thiscall sub_45485C(int *rectangle, int *bounds);
extern int __thiscall get_mouse_cursor_activity_state(uint32_t *context);
extern int __thiscall find_or_create_cursor_spec(uint32_t *collection,
                                                char *name,
                                                int retain_reference);
extern int __thiscall apply_cursor_activity_properties(
    char *manager, uint32_t *cursor_spec);
extern int __thiscall reset_interface_cursor_properties(
    uint32_t *cursor_properties);
int __thiscall set_input_context_event_state(int manager,
                                            int event_id, int value);
int __thiscall dispatch_pointer_event(
    int *manager, int *coordinates,
    int (__thiscall *callback)(int, int *), int extra);
int __thiscall dispatch_pointer_event_with_state(
    uint32_t *manager, int first, int second,
    int (__thiscall *callback)(int, int, int), int offset);
int __thiscall dispatch_pointer_drag_event(
    uint32_t *manager, int first, int second, int third,
    int (__thiscall *callback)(int, int, int, int), int offset);
int __thiscall dispatch_pointer_motion_event(
    uint32_t *manager, int first, int second, int third,
    int (__thiscall *callback)(int, int, int, int), int offset);
int __thiscall dispatch_input_event(
    uint32_t *manager, int event_id, int event_value,
    int (__thiscall *callback)(int, int, int), int offset);
int __thiscall dispatch_interface_key_release(uint32_t *manager,
                                              int event_id,
                                              int event_value);
uint32_t *__thiscall activate_interface_manager(uint32_t *manager,
                                                uint32_t *activation_target);
int __thiscall deactivate_interface_manager(uint32_t *manager,
                                            uint32_t *bounds_target,
                                            uint32_t *deactivation_target);
extern int __thiscall sub_44D91D(void *object);
extern int __thiscall sub_44D922(void *object);
extern int __thiscall sub_44D92C(void *object);
extern int __thiscall sub_44D936(void *object);
extern int __thiscall sub_44D93B(void *object);
extern int __thiscall sub_4CA356(void *state);
extern int __thiscall sub_4CCA17(void *context);
extern int __thiscall dispatch_pointer_position_to_interface_target(
    void *object) __asm__("sub_44D945");

typedef struct {
  uint32_t start;
  uint32_t index;
  uint32_t current;
  uint32_t end;
} InterfaceLayerIterator;

typedef struct {
  uint32_t flags;
  uint32_t *begin;
  uint32_t *end;
  uint32_t *capacity;
} InterfaceEventRecipientList;

void __thiscall clear_interface_keyboard_capture_target(uint32_t *manager);
void *__thiscall clear_interface_mouse_capture_target(uint32_t *manager);
int __thiscall has_application_interface_event_target(void);
void __thiscall select_interface_cursor_for_position(uint32_t *manager,
                                                     uint32_t *cursor_data,
                                                     char force);
uint32_t *__thiscall update_interface_cursor_activity(
    uint32_t *manager, uint32_t *cursor_data);
int __thiscall reset_interface_cursor(uint8_t *cursor_context);
void __thiscall refresh_interface_pointer_cursor(uint32_t *manager,
                                                 char force);
uint32_t *__thiscall refresh_interface_cursor_state(uint32_t *manager);

uint32_t *__thiscall destroy_interface_manager_members(uint32_t *manager)
{
  manager[0] = (uint32_t)(uintptr_t)interface_manager_vtable;
  destroy_interface_cursor(manager + 2);
  destroy_interface_console(manager + 5);
  destroy_interface_owned_layer(manager + 7);
  destroy_interface_owned_layer(manager + 8);
  destroy_interface_owned_layer(manager + 9);
  destroy_interface_ui_translator(manager + 27);
  while (manager[21])
    destroy_interface_layer_collection((int)(uintptr_t)(manager + 10));
  return erase_map_entry_impl(
      unk_7664C0,
      (uint32_t)(uintptr_t)(manager + 1)
          + (uint32_t)interface_manager_base_offset_adjustment);
}

uint32_t *__thiscall release_interface_manager(uint32_t *manager,
                                               char free_object)
{
  destroy_interface_manager_members(manager);
  if (free_object & 1)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}

void __thiscall log_interface_layer_stack(uint32_t *manager,
                                          uint32_t *arguments)
{
  int context[4];
  uint32_t begin[4] = {
      manager[15], manager[16], manager[17], manager[18]};
  uint32_t cursor[4] = {begin[0], begin[1], begin[2], begin[3]};
  uint32_t last_segment = manager[13];

  begin_interface_debug_log(context, (int)"Z:\\Proj\\GK3\\gk3app\\Source\\InterfaceMgr.cpp",
             916, 7, arguments);
  if (cursor[2] != last_segment) {
    do {
      uint32_t previous[4] = {cursor[0], cursor[1], cursor[2], cursor[3]};
      uint32_t current_item[4] = {
          cursor[0], cursor[1], cursor[2], cursor[3]};
      uint32_t *layer;
      const char *save_policy;
      const char *key;
      uint32_t *bounds;
      int index;

      adjust_interface_layer_iterator((int *)previous, -1);
      layer = (uint32_t *)(uintptr_t)previous[2];
      save_policy = (layer[2] && *(uint32_t *)(uintptr_t)(layer[2] + 4))
                        ? "'save'"
                        : "'do not save'";
      adjust_interface_layer_iterator((int *)current_item, -1);
      layer = (uint32_t *)(uintptr_t)current_item[2];
      bounds = layer + 7;
      key = *(const char **)(uintptr_t)(current_item[2] + 308);
      if (!key)
        key = Key;
      index = interface_layer_index_between(begin, cursor);
      log_interface_debug_message((int)(uintptr_t)context,
                 "Layer %02d (%s): ambient=%s, rect={%d,%d,%d,%d}\n",
                 index, key, save_policy, bounds[0], bounds[1], bounds[2],
                 bounds[3]);
      retreat_interface_layer_iterator(cursor);
    } while (cursor[2] != last_segment);
  }
  end_interface_debug_log(context);
}

void __thiscall log_interface_input_state(uint32_t *manager,
                                          uint32_t *arguments)
{
  int context[4];
  int input_state;

  begin_interface_debug_log(context, (int)"Z:\\Proj\\GK3\\gk3app\\Source\\InterfaceMgr.cpp",
             939, 7, arguments);
  log_interface_debug_message((int)(uintptr_t)context, "mouse capture is %s\n",
             manager[24] ? "on" : "off");
  log_interface_debug_message((int)(uintptr_t)context, "keyboard capture is %s\n",
             manager[25] ? "on" : "off");
  log_interface_debug_message((int)(uintptr_t)context, "current modifiers:\n");
  input_state = get_engine_input_state(
      (uint32_t *)(uintptr_t)game_engine_instance_address, 0);
  if (input_state & 1)
    log_interface_debug_message((int)(uintptr_t)context, "left mouse button\n");
  if (input_state & 2)
    log_interface_debug_message((int)(uintptr_t)context, "middle mouse button\n");
  if (input_state & 4)
    log_interface_debug_message((int)(uintptr_t)context, "right mouse button\n");
  if (input_state & 8)
    log_interface_debug_message((int)(uintptr_t)context, "shift key\n");
  if (input_state & 0x10)
    log_interface_debug_message((int)(uintptr_t)context, "control key\n");
  if (input_state & 0x20)
    log_interface_debug_message((int)(uintptr_t)context, "alt key\n");
  if (!input_state)
    log_interface_debug_message((int)(uintptr_t)context, "none\n");
  end_interface_debug_log(context);
}

void __thiscall dispatch_interface_event(uint32_t *manager,
                                         uint32_t *event_address)
{
  uint32_t *event = (uint32_t *)(uintptr_t)event_address;
  uint32_t event_data = event[1];
  uint32_t event_code = *(uint32_t *)(uintptr_t)(event_data + 4);
  int is_high_priority_event = event_code > 1124;
  uint32_t *application = (uint32_t *)(uintptr_t)game_engine_instance_address;
  uint32_t *application_components =
      (uint32_t *)(uintptr_t)application[273];

  if (*(uint32_t *)(uintptr_t)(event_data + 8) == 6) {
    uint32_t *retained_event = NULL;
    uint32_t **event_reference = &event;

    retain_interface_event_reference(
        (uint32_t *)(void *)&retained_event, event_reference);
    if (*(uint32_t *)(uintptr_t)(
            release_interface_event_and_get_payload(retained_event) + 12) == 3) {
      clear_interface_mouse_capture_target(manager);
      clear_interface_keyboard_capture_target(manager);
      reset_engine_input_state(game_engine_instance_address);
    }
  }

  if ((event_code == 1024 || event_code == 1025)
      && *((uint8_t *)(void *)manager + 92)) {
    destroy_interface_temporary_object(event);
    return;
  }

  ((void (__thiscall *)(uint32_t *, uint32_t **))
      (uintptr_t)*(uint32_t *)(uintptr_t)
          (*(uint32_t *)(uintptr_t)manager[5] + 12))(
      (uint32_t *)(uintptr_t)manager[5], &event);
  ((void (__thiscall *)(uint32_t *, uint32_t **))
      (uintptr_t)*(uint32_t *)(uintptr_t)
          (*(uint32_t *)(uintptr_t)manager[7] + 12))(
      (uint32_t *)(uintptr_t)manager[7], &event);

  uint32_t *pointer_context = (uint32_t *)(uintptr_t)manager[8];
  uint32_t pointer_context_event_code =
      *(uint32_t *)(uintptr_t)(event[1] + 4);
  if (*((uint8_t *)(void *)pointer_context + 4)
      || pointer_context_event_code == 1024 || is_high_priority_event) {
    ((void (__thiscall *)(uint32_t *, uint32_t **))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)pointer_context[0] + 12))(
        pointer_context, &event);

    if (is_high_priority_event) {
      InterfaceEventRecipientList recipients = {0};
      InterfaceLayerIterator cursor = {
          manager[11], manager[12], manager[13], manager[14]};
      uint32_t *layer_manager =
          (uint32_t *)(uintptr_t)application_components[18];

      recipients.flags = ((uint32_t)(uintptr_t)event >> 8) & 0xff;
      while (cursor.current != manager[17]) {
        uint32_t layer_address =
            *(uint32_t *)(uintptr_t)cursor.current;
        uint32_t *recipient = recipients.begin;

        while (recipient != recipients.end
               && *recipient != layer_address)
          ++recipient;
        if (recipient == recipients.end)
          append_interface_recipient((int)(uintptr_t)&recipients,
                                     &layer_address);
        advance_interface_layer_iterator((uint32_t *)(void *)&cursor);
      }

      for (int layer_id = 0; layer_id != 21; ++layer_id) {
        if (has_game_layer_object(layer_manager, layer_id)) {
          char *layer_slot = get_game_layer_slot(
              (char *)(void *)layer_manager, layer_id, 1);
          uint32_t layer_address = *(uint32_t *)(void *)layer_slot;
          uint32_t *recipient = recipients.begin;

          while (recipient != recipients.end
                 && *recipient != layer_address)
            ++recipient;
          if (recipient == recipients.end)
            append_interface_recipient((int)(uintptr_t)&recipients,
                                       &layer_address);
        }
      }

      for (uint32_t *recipient = recipients.begin;
           recipient != recipients.end; ++recipient) {
        uint32_t *layer = (uint32_t *)(uintptr_t)*recipient;
        ((void (__thiscall *)(uint32_t *, uint32_t **))
            (uintptr_t)*(uint32_t *)(uintptr_t)
                (*(uint32_t *)(uintptr_t)layer[0] + 12))(
            layer, &event);
      }

      if (has_application_interface_event_target()) {
        uint32_t *application_event_target =
            (uint32_t *)(uintptr_t)application_components[27];
        ((void (__thiscall *)(uint32_t *, uint32_t **))
            (uintptr_t)*(uint32_t *)(uintptr_t)
                (*(uint32_t *)(uintptr_t)application_event_target[0] + 12))(
            application_event_target, &event);
      }
      release_interface_recipient_list((int *)(void *)&recipients);
    } else {
      InterfaceLayerIterator top_layer = {
          manager[15], manager[16], manager[17], manager[18]};
      uint32_t *layer;

      adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
      layer = (uint32_t *)(uintptr_t)
          *(uint32_t *)(uintptr_t)top_layer.current;
      ((void (__thiscall *)(uint32_t *, uint32_t **))
          (uintptr_t)*(uint32_t *)(uintptr_t)
              (*(uint32_t *)(uintptr_t)layer[0] + 12))(
          layer, &event);
    }
  } else {
    InterfaceLayerIterator top_layer = {
        manager[15], manager[16], manager[17], manager[18]};
    uint32_t *layer;

    adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
    layer = (uint32_t *)(uintptr_t)
        *(uint32_t *)(uintptr_t)top_layer.current;
    ((void (__thiscall *)(uint32_t *, uint32_t **))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)layer[0] + 12))(
        layer, &event);
  }
  destroy_interface_temporary_object(event);
}

int __thiscall has_application_interface_event_target(void)
{
  if (!game_engine_instance_address)
    return 0;
  uint32_t *application = (uint32_t *)(uintptr_t)game_engine_instance_address;
  uint32_t *components = (uint32_t *)(uintptr_t)application[273];
  if (!components)
    return 0;
  return components[27] != 0;
}

int __thiscall has_active_interface_target(uint32_t *manager)
{
  typedef int (__thiscall *IsActiveMethod)(uint32_t *target);
  uint32_t *target = (uint32_t *)(uintptr_t)manager[7];
  int is_active = ((IsActiveMethod)(uintptr_t)
      *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 96))(target);

  if (is_active)
    return is_active;

  target = (uint32_t *)(uintptr_t)manager[8];
  if (*((uint8_t *)(void *)target + 4)) {
    is_active = ((IsActiveMethod)(uintptr_t)
        *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 96))(
        target);
    if (is_active)
      return is_active;
  }

  target = (uint32_t *)(uintptr_t)manager[27];
  is_active = ((IsActiveMethod)(uintptr_t)
      *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 96))(target);
  if (is_active)
    return is_active;

  InterfaceLayerIterator top_layer = {
      manager[15], manager[16], manager[17], manager[18]};
  adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
  target = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)top_layer.current;
  return ((IsActiveMethod)(uintptr_t)
      *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 96))(target);
}

int __thiscall update_interface_manager_targets(uint32_t *manager,
                                                int update_value,
                                                int update_context)
{
  typedef int (__thiscall *UpdateMethod)(uint32_t *target, int, int);
  InterfaceLayerIterator top_layer;
  uint32_t *target;

  if (*((uint8_t *)(void *)manager + 12)) {
    *((uint8_t *)(void *)manager + 12) = 0;
    refresh_interface_pointer_cursor(manager, 0);
  }
  if (*((uint8_t *)(void *)manager + 24)) {
    *((uint8_t *)(void *)manager + 24) = 0;
    refresh_interface_cursor_state(manager);
  }
  if (manager[21] > 1) {
    InterfaceLayerIterator previous_layer = {
        manager[15], manager[16], manager[17], manager[18]};
    adjust_interface_layer_iterator((int *)(void *)&previous_layer, -1);
    adjust_interface_layer_iterator((int *)(void *)&previous_layer, -1);
    target = (uint32_t *)(uintptr_t)
        *(uint32_t *)(uintptr_t)previous_layer.current;
    ((UpdateMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
        (*(uint32_t *)(uintptr_t)target[0] + 240))(target, update_value,
                                                   update_context);
  }

  top_layer.start = manager[15];
  top_layer.index = manager[16];
  top_layer.current = manager[17];
  top_layer.end = manager[18];
  adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
  target = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)top_layer.current;
  ((UpdateMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
      (*(uint32_t *)(uintptr_t)target[0] + 160))(target, update_value,
                                                 update_context);

  target = (uint32_t *)(uintptr_t)manager[8];
  if (*((uint8_t *)(void *)target + 4))
    ((UpdateMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
        (*(uint32_t *)(uintptr_t)target[0] + 160))(target, update_value,
                                                   update_context);
  target = (uint32_t *)(uintptr_t)manager[7];
  ((UpdateMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
      (*(uint32_t *)(uintptr_t)target[0] + 160))(target, update_value,
                                                 update_context);
  target = (uint32_t *)(uintptr_t)manager[5];
  return ((UpdateMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
      (*(uint32_t *)(uintptr_t)target[0] + 160))(target, update_value,
                                                 update_context);
}

void __thiscall clear_interface_pointer_activity(uint32_t *manager)
{
  clear_pointer_activity_state((int)manager[2]);
}

void __thiscall refresh_interface_pointer_cursor(uint32_t *manager,
                                                 char force)
{
  uint32_t cursor_data_storage[2];
  uint32_t *cursor_data;

  get_mouse_cursor_worker_manager();
  cursor_data = get_engine_cursor_screen_position(cursor_data_storage);
  select_interface_cursor_for_position(
      manager, cursor_data, force);
}

uint32_t *__thiscall refresh_interface_cursor_state(uint32_t *manager)
{
  uint32_t cursor_data_storage[2];
  uint32_t *cursor_data;

  get_mouse_cursor_worker_manager();
  cursor_data = get_engine_cursor_screen_position(cursor_data_storage);
  return update_interface_cursor_activity(manager, cursor_data);
}

uint32_t *__thiscall activate_interface_manager(
    uint32_t *manager, uint32_t *activation_target)
{
  uint32_t cursor_data_storage[2];
  uint32_t *cursor_data;
  uint32_t *input_context;

  *((uint8_t *)(void *)manager + 92) = 0;
  clear_interface_pointer_activity(manager);
  if (activation_target) {
    uint32_t *vtable = (uint32_t *)(uintptr_t)activation_target[0];
    ((void (__thiscall *)(uint32_t *))(uintptr_t)vtable[1])(
        activation_target);
  }

  input_context = (uint32_t *)(uintptr_t)manager[5];
  ((void (__thiscall *)(uint32_t *))(uintptr_t)
      ((uint32_t *)(uintptr_t)input_context[0])[1])(input_context);
  get_mouse_cursor_worker_manager();
  cursor_data = get_engine_cursor_screen_position(cursor_data_storage);
  select_interface_cursor_for_position(manager, cursor_data, 1);
  cursor_data = update_interface_cursor_activity(manager, cursor_data);

  if (*((uint8_t *)(void *)manager + 104)) {
    uint32_t *engine = (uint32_t *)(uintptr_t)game_engine_address;
    uint32_t *vtable = (uint32_t *)(uintptr_t)engine[0];
    return (uint32_t *)(uintptr_t)
        ((int (__thiscall *)(uint32_t *))(uintptr_t)vtable[13])(engine);
  }
  return cursor_data;
}

int __thiscall deactivate_interface_manager(
    uint32_t *manager, uint32_t *bounds_target,
    uint32_t *deactivation_target)
{
  uint32_t *input_context;
  int result = (int)(uintptr_t)bounds_target;

  *((uint8_t *)(void *)manager + 92) = 1;
  clear_interface_mouse_capture_target(manager);
  clear_interface_keyboard_capture_target(manager);

  input_context = (uint32_t *)(uintptr_t)manager[5];
  ((void (__thiscall *)(uint32_t *))(uintptr_t)
      ((uint32_t *)(uintptr_t)input_context[0])[2])(input_context);
  clear_interface_pointer_activity(manager);

  {
    uint32_t *vtable = (uint32_t *)(uintptr_t)deactivation_target[0];
    ((void (__thiscall *)(uint32_t *))(uintptr_t)vtable[2])(
        deactivation_target);
  }

  if (bounds_target) {
    uint32_t bounds[4] = {
        bounds_target[7], bounds_target[8],
        bounds_target[9], bounds_target[10]};
    result = sub_45485C((int *)(void *)bounds,
                        (int *)(void *)&interface_layer_type_descriptor);
    if (result) {
      sub_4BA1D4(game_engine_instance_address, 0, 0, 0);
      uint32_t *vtable = (uint32_t *)(uintptr_t)deactivation_target[0];
      return ((int (__thiscall *)(uint32_t *, uint32_t, uint32_t *))
          (uintptr_t)vtable[59])(
              deactivation_target, *(uint32_t *)(uintptr_t)
                  (game_engine_address + 24), bounds);
    }
  }
  return result;
}

void __thiscall select_interface_cursor_for_position(uint32_t *manager,
                                                     uint32_t *cursor_data,
                                                     char force)
{
  typedef int (__thiscall *FindCursorMethod)(uint32_t *, uint32_t *);
  uint32_t *target;
  int cursor_spec = 0;

  if (force || manager[24] == 0) {
    target = (uint32_t *)(uintptr_t)manager[7];
    cursor_spec = ((FindCursorMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
        (*(uint32_t *)(uintptr_t)target[0] + 184))(target, cursor_data);
    if (!cursor_spec) {
      target = (uint32_t *)(uintptr_t)manager[8];
      if (*((uint8_t *)(void *)target + 4))
        cursor_spec = ((FindCursorMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)target[0] + 184))(target, cursor_data);
      if (!cursor_spec) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        target = (uint32_t *)(uintptr_t)
            *(uint32_t *)(uintptr_t)top_layer.current;
        cursor_spec = ((FindCursorMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)target[0] + 184))(target, cursor_data);
        if (!cursor_spec) {
          uint32_t *application =
              (uint32_t *)(uintptr_t)game_engine_instance_address;
          uint32_t *application_components =
              (uint32_t *)(uintptr_t)application[273];
          uint32_t *cursor_collection =
              (uint32_t *)(uintptr_t)application_components[12];
          cursor_spec = find_or_create_cursor_spec(cursor_collection, NULL, 1);
        }
      }
    }
  } else {
    target = (uint32_t *)(uintptr_t)manager[24];
    cursor_spec = ((FindCursorMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
        (*(uint32_t *)(uintptr_t)target[0] + 184))(target, cursor_data);
    if (!cursor_spec)
      cursor_spec = (int)manager[1];
  }

  if (manager[1] != (uint32_t)cursor_spec) {
    manager[1] = (uint32_t)cursor_spec;
    set_cursor_spec(manager[2], cursor_spec);
  }
}

uint32_t *__thiscall update_interface_cursor_activity(uint32_t *manager,
                                                      uint32_t *cursor_data)
{
  typedef uint32_t *(__thiscall *GetCursorActivityMethod)(uint32_t *,
                                                          uint32_t *);
  uint32_t *cursor_properties = NULL;
  uint32_t *target;
  uint32_t *cursor_context = (uint32_t *)(uintptr_t)manager[5];
  uint32_t *activity_context = (uint32_t *)(uintptr_t)
      get_mouse_cursor_worker_manager();
  int activity_count = get_mouse_cursor_activity_state(activity_context);

  if (activity_count > 0) {
    target = (uint32_t *)(uintptr_t)manager[7];
    cursor_properties = ((GetCursorActivityMethod)(uintptr_t)
        *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 188))(
        target, cursor_data);
    if (!cursor_properties) {
      target = (uint32_t *)(uintptr_t)manager[8];
      if (*((uint8_t *)(void *)target + 4))
        cursor_properties = ((GetCursorActivityMethod)(uintptr_t)
            *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 188))(
            target, cursor_data);
      if (!cursor_properties) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        target = (uint32_t *)(uintptr_t)
            *(uint32_t *)(uintptr_t)top_layer.current;
        cursor_properties = ((GetCursorActivityMethod)(uintptr_t)
            *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)target[0] + 188))(
            target, cursor_data);
      }
    }
  }

  if (manager[4] != (uint32_t)(uintptr_t)cursor_properties
      || cursor_properties == NULL) {
    manager[4] = (uint32_t)(uintptr_t)cursor_properties;
    if (cursor_properties)
      return (uint32_t *)(uintptr_t)apply_cursor_activity_properties(
          (char *)(void *)cursor_context, cursor_properties);
    return (uint32_t *)(uintptr_t)
        reset_interface_cursor((uint8_t *)(void *)cursor_context);
  }
  return cursor_properties ? cursor_properties
                           : (uint32_t *)(uintptr_t)activity_count;
}

int __thiscall reset_interface_cursor(uint8_t *cursor_context)
{
  cursor_context[448] = 0;
  int result = reset_interface_cursor_properties(
      (uint32_t *)(void *)(cursor_context + 396));
  if (cursor_context[24]) {
    uint32_t *object = (uint32_t *)(void *)cursor_context;
    result = ((int (__thiscall *)(uint32_t *))(uintptr_t)
        *(uint32_t *)(uintptr_t)(object[0] + 180))(object);
  }
  return result;
}

int __thiscall notify_interface_control_state_changed(uint32_t *manager,
                                                      int control)
{
  *((uint8_t *)(void *)manager + 12) = 1;
  if ((uint32_t)control != manager[5]) {
    manager[4] = 0;
    *((uint8_t *)(void *)manager + 24) = 1;
  }
  return control;
}

int __thiscall update_input_context_pointer_position(uint32_t *manager,
                                                     int *position)
{
  typedef void (__thiscall *PointerPositionMethod)(uint32_t *, int *);
  uint32_t *pointer_context = (uint32_t *)(uintptr_t)manager[5];
  uint32_t pointer_context_vtable = pointer_context[0];

  select_interface_cursor_for_position(
      manager, (uint32_t *)(void *)position, 0);
  update_interface_cursor_activity(manager, (uint32_t *)(void *)position);
  ((PointerPositionMethod)(uintptr_t)*(uint32_t *)(uintptr_t)
      (pointer_context_vtable + 80))(pointer_context, position);
  return dispatch_pointer_event(
      (int *)(void *)manager, position,
      (int (__thiscall *)(int, int *))
          dispatch_pointer_position_to_interface_target, 0);
}

int __thiscall notify_input_context_pointer_activity(void *manager,
                                                     int unused_first,
                                                     int unused_second)
{
  return set_input_context_event_state((int)(uintptr_t)manager, 27, 0);
}

int __thiscall dispatch_pointer_event(
    int *manager, int *coordinates,
    int (__thiscall *callback)(int, int *), int offset)
{
  int result;

  if (manager[28] != coordinates[0] || manager[29] != coordinates[1]) {
    manager[28] = coordinates[0];
    manager[29] = coordinates[1];
    clear_interface_pointer_activity((uint32_t *)(void *)manager);
  }

  if (manager[24]) {
    result = callback(manager[24] + offset, coordinates);
    if (result)
      return result;
  }

  result = callback(manager[7] + offset, coordinates);
  if (!result) {
    int pointer_context = manager[8];
    if (!*((uint8_t *)(uintptr_t)pointer_context + 4)
        || (result = callback(pointer_context + offset, coordinates)) == 0) {
      InterfaceLayerIterator top_layer = {
          (uint32_t)manager[15], (uint32_t)manager[16],
          (uint32_t)manager[17], (uint32_t)manager[18]};
      adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
      return callback(offset + *(int *)(uintptr_t)top_layer.current,
                      coordinates);
    }
  }
  return result;
}

int __thiscall dispatch_pointer_event_with_state(
    uint32_t *manager, int first, int second,
    int (__thiscall *callback)(int, int, int), int offset)
{
  int result;
  int captured_target = (int)manager[24];

  if (!captured_target
      || (result = callback(captured_target + offset, first, second)) == 0) {
    result = callback((int)manager[7] + offset, first, second);
    if (!result) {
      int pointer_context = (int)manager[8];
      if (!*((uint8_t *)(uintptr_t)pointer_context + 4)
          || (result = callback(pointer_context + offset, first, second)) == 0) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        return callback(offset + *(int *)(uintptr_t)top_layer.current,
                        first, second);
      }
    }
  }
  return result;
}

int __thiscall dispatch_pointer_drag_event(
    uint32_t *manager, int first, int second, int third,
    int (__thiscall *callback)(int, int, int, int), int offset)
{
  int result;
  int captured_target = (int)manager[24];

  if (!captured_target
      || (result = callback(captured_target + offset, first, second, third))
             == 0) {
    result = callback((int)manager[7] + offset, first, second, third);
    if (!result) {
      int pointer_context = (int)manager[8];
      if (!*((uint8_t *)(uintptr_t)pointer_context + 4)
          || (result = callback(pointer_context + offset, first, second,
                                third)) == 0) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        return callback(offset + *(int *)(uintptr_t)top_layer.current,
                        first, second, third);
      }
    }
  }
  return result;
}

int __thiscall dispatch_pointer_motion_event(
    uint32_t *manager, int first, int second, int third,
    int (__thiscall *callback)(int, int, int, int), int offset)
{
  int result;
  int captured_target = (int)manager[24];

  if (!captured_target
      || (result = callback(captured_target + offset, first, second, third))
             == 0) {
    result = callback((int)manager[7] + offset, first, second, third);
    if (!result) {
      int pointer_context = (int)manager[8];
      if (!*((uint8_t *)(uintptr_t)pointer_context + 4)
          || (result = callback(pointer_context + offset, first, second,
                                third)) == 0) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        return callback(offset + *(int *)(uintptr_t)top_layer.current,
                        first, second, third);
      }
    }
  }
  return result;
}

int __thiscall dispatch_input_event(
    uint32_t *manager, int event_id, int event_value,
    int (__thiscall *callback)(int, int, int), int offset)
{
  int result;

  clear_interface_pointer_activity(manager);
  if (manager[25]) {
    result = callback((int)manager[25] + offset, event_id, event_value);
    if (result)
      return result;
  }

  result = callback((int)manager[7] + offset, event_id, event_value);
  if (!result) {
    int pointer_context = (int)manager[8];
    if (!*((uint8_t *)(uintptr_t)pointer_context + 4)
        || (result = callback(pointer_context + offset, event_id,
                              event_value)) == 0) {
      result = callback((int)manager[27] + offset, event_id, event_value);
      if (!result) {
        InterfaceLayerIterator top_layer = {
            manager[15], manager[16], manager[17], manager[18]};
        adjust_interface_layer_iterator((int *)(void *)&top_layer, -1);
        return callback(offset + *(int *)(uintptr_t)top_layer.current,
                        event_id, event_value);
      }
    }
  }
  return result;
}

int __thiscall set_input_context_event_state(int manager, int event_id,
                                             int event_value)
{
  if (event_id == 122) {
    uint32_t *engine = (uint32_t *)(uintptr_t)game_engine_instance_address;
    int active_key_state = (get_engine_input_state(engine, 0) >> 3) & 1;
    return sub_4CA356((void *)(uintptr_t)active_key_state);
  }
  if (event_id == 120) {
    uint32_t *application =
        (uint32_t *)(uintptr_t)game_engine_instance_address;
    uint32_t *components = (uint32_t *)(uintptr_t)application[273];
    return sub_4CCA17((void *)(uintptr_t)components[16]);
  }

  reset_interface_cursor(
      (uint8_t *)(uintptr_t)((uint32_t *)(uintptr_t)manager)[5]);
  return dispatch_input_event(
      (uint32_t *)(uintptr_t)manager, event_id, event_value,
      (int (__thiscall *)(int, int, int))sub_44D91D, 0);
}

int __thiscall dispatch_pointer_button_1_press(uint32_t *manager,
                                               int *coordinates)
{
  reset_interface_cursor((uint8_t *)(uintptr_t)manager[5]);
  return dispatch_pointer_event(
      (int *)(void *)manager, coordinates,
      (int (__thiscall *)(int, int *))sub_44D922, 0);
}

int __thiscall dispatch_pointer_button_2_press(uint32_t *manager,
                                               int *coordinates)
{
  reset_interface_cursor((uint8_t *)(uintptr_t)manager[5]);
  return dispatch_pointer_event(
      (int *)(void *)manager, coordinates,
      (int (__thiscall *)(int, int *))sub_44D92C, 0);
}

int __thiscall dispatch_pointer_button_3_press(uint32_t *manager,
                                               int *coordinates)
{
  reset_interface_cursor((uint8_t *)(uintptr_t)manager[5]);
  return dispatch_pointer_event(
      (int *)(void *)manager, coordinates,
      (int (__thiscall *)(int, int *))sub_44D93B, 0);
}

int __thiscall dispatch_interface_key_release(uint32_t *manager,
                                              int event_id,
                                              int event_value)
{
  return dispatch_input_event(
      manager, event_id, event_value,
      (int (__thiscall *)(int, int, int))sub_44D936, 0);
}

int __thiscall contains_interface_layer(uint32_t *manager, int layer_address)
{
  uint32_t last_segment = manager[13];
  InterfaceLayerIterator cursor = {
      manager[15], manager[16], manager[17], manager[18]};
  InterfaceLayerIterator candidate;

  if (cursor.current != last_segment) {
    do {
      candidate = cursor;
      adjust_interface_layer_iterator((int *)(void *)&candidate.start, -1);
      if (*(uint32_t *)(uintptr_t)candidate.current
          == (uint32_t)layer_address)
        break;
      retreat_interface_layer_iterator((uint32_t *)&cursor);
    } while (cursor.current != last_segment);
  }
  return cursor.current != last_segment;
}

uint32_t *__thiscall remove_interface_layer(uint32_t *manager,
                                            int layer_address)
{
  uint32_t *list = manager + 10;
  uint32_t last_segment = manager[17];
  InterfaceLayerIterator cursor = {
      manager[11], manager[12], manager[13], manager[14]};
  uint32_t result_storage[4];

  while (cursor.current != last_segment) {
    if (*(uint32_t *)(uintptr_t)cursor.current
        == (uint32_t)layer_address) {
      InterfaceLayerIterator next = cursor;

      adjust_interface_layer_iterator((int *)(void *)&next.start, 1);
      return erase_interface_layer_range(
          (int *)(void *)list, result_storage, (int)cursor.start,
          (int)cursor.index, (uint32_t *)(uintptr_t)cursor.current,
          (int)cursor.end, (int)next.start, (int)next.index,
          (uint32_t *)(uintptr_t)next.current, (int)next.end);
    }
    advance_interface_layer_iterator((uint32_t *)&cursor);
  }
  return (uint32_t *)(uintptr_t)cursor.current;
}

void __thiscall clear_interface_keyboard_capture_target(
    uint32_t *manager);

void __thiscall set_interface_keyboard_capture_target(uint32_t *manager,
                                                     uint32_t *target)
{
  uint32_t *previous_target = (uint32_t *)(uintptr_t)manager[25];
  manager[25] = (uint32_t)(uintptr_t)target;
  if (previous_target != NULL) {
    uint32_t *event_storage = NULL;
    uint32_t *event = create_window_capture_event(&event_storage, 1027);
    ((void (__thiscall *)(uint32_t *, uint32_t *))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)previous_target[0] + 12))(
        previous_target, event);
    destroy_interface_temporary_object(event_storage);
  }
}

void __thiscall clear_interface_keyboard_capture_target(uint32_t *manager)
{
  uint32_t *target = (uint32_t *)(uintptr_t)manager[25];
  manager[25] = 0;
  if (target != NULL) {
    uint32_t *event_storage = NULL;
    uint32_t *event = create_window_capture_event(&event_storage, 1027);
    ((void (__thiscall *)(uint32_t *, uint32_t *))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)target[0] + 12))(
        target, event);
    destroy_interface_temporary_object(event_storage);
  }
}

void __thiscall clear_interface_keyboard_capture_target_if_matches(
    uint32_t *manager, int target_address)
{
  if (manager[25] == (uint32_t)target_address)
    clear_interface_keyboard_capture_target(manager);
}

void __thiscall set_interface_mouse_capture_target(uint32_t *manager,
                                                   uint32_t *target)
{
  uint32_t *previous_target = (uint32_t *)(uintptr_t)manager[24];
  manager[24] = (uint32_t)(uintptr_t)target;
  if (previous_target != NULL) {
    uint32_t *event_storage = NULL;
    uint32_t *event = create_window_capture_event(&event_storage, 1026);
    ((void (__thiscall *)(uint32_t *, uint32_t *))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)previous_target[0] + 12))(
        previous_target, event);
    destroy_interface_temporary_object(event_storage);
  } else {
    SetCapture(*(uint32_t *)(uintptr_t)(game_engine_address + 16));
  }
}

void *__thiscall clear_interface_mouse_capture_target(uint32_t *manager)
{
  uint32_t *target = (uint32_t *)(uintptr_t)manager[24];
  manager[24] = 0;
  if (target != NULL) {
    uint32_t *event_storage = NULL;
    uint32_t *event = create_window_capture_event(&event_storage, 1026);
    ((void (__thiscall *)(uint32_t *, uint32_t *))
        (uintptr_t)*(uint32_t *)(uintptr_t)
            (*(uint32_t *)(uintptr_t)target[0] + 12))(
        target, event);
    destroy_interface_temporary_object(event_storage);
    return (void *)(uintptr_t)ReleaseCapture();
  }
  return &loc_640794;
}

void *__thiscall clear_interface_mouse_capture_target_if_matches(
    uint32_t *manager, void *target_address)
{
  void *current_target = (void *)(uintptr_t)manager[24];
  if (current_target == target_address)
    return clear_interface_mouse_capture_target(manager);
  return current_target;
}

uint32_t *__thiscall construct_registered_interface_manager(
    uint32_t *object, int unused)
{
  char default_value;
  find_or_create_registry_entry(
      unk_7664C0,
      (uint32_t)(uintptr_t)object
          + (uint32_t)interface_manager_base_offset_adjustment + 4);
  initialize_layer_pointer_array(object + 10, &default_value);
  object[0] = (uint32_t)(uintptr_t)interface_manager_vtable;
  return object;
}

uint32_t *__thiscall construct_interface_manager(uint32_t *object)
{
  char default_value;
  find_or_create_registry_entry(unk_7664C0,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)interface_manager_base_offset_adjustment + 4);
  initialize_layer_pointer_array(object + 10, &default_value);
  object[0] = (uint32_t)(uintptr_t)interface_manager_vtable;
  object[1] = 0;
  object[2] = 0;
  *((uint8_t *)(void *)object + 12) = 1;
  object[4] = 0;
  object[5] = 0;
  *((uint8_t *)(void *)object + 24) = 1;
  object[7] = 0;
  object[8] = 0;
  object[9] = 0;
  object[22] = 0;
  *((uint8_t *)(void *)object + 92) = 0;
  object[24] = 0;
  object[25] = 0;
  *((uint8_t *)(void *)object + 104) = 1;
  object[27] = 0;
  object[28] = (uint32_t)cursor_default_coordinate_x;
  object[29] = (uint32_t)cursor_default_coordinate_y;
  return object;
}

void initialize_application_interface_manager(
    uint32_t *application_component, int context)
{
  uint32_t *global_layer_memory = allocate_registered_interface_layer(320);
  uint32_t *global_layer = global_layer_memory
      ? construct_registered_interface_layer(
            global_layer_memory,
            (uint32_t *)&interface_layer_type_descriptor)
      : NULL;
  application_component[7] = (uint32_t)(uintptr_t)global_layer;
  uint32_t *layer_name = global_layer + 76;
  assign_std_string_storage((char *)(void *)layer_name, "GlobalLayer",
                            strlen("GlobalLayer"));
  uint32_t *layer_vtable = (uint32_t *)(uintptr_t)global_layer[0];
  typedef void (__thiscall *InitializeLayerMethod)(uint32_t *, int);
  typedef void (__thiscall *SetLayerEnabledMethod)(uint32_t *, int);
  typedef uint32_t *(__thiscall *AttachLayerObjectMethod)(uint32_t *,
                                                          uint32_t *);
  ((InitializeLayerMethod)(uintptr_t)layer_vtable[1])(global_layer, context);
  ((SetLayerEnabledMethod)(uintptr_t)layer_vtable[44])(global_layer, 1);
  uint32_t *layer_child = create_layer_child_added_event(
      (uint32_t *)(void *)&layer_name, 0, (int)(uintptr_t)global_layer);
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(global_layer,
                                                        layer_child);
  destroy_interface_temporary_object(layer_name);
  layer_child = create_layer_child_removed_event(
      (uint32_t *)(void *)&layer_name, 0, (int)(uintptr_t)global_layer);
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(global_layer,
                                                        layer_child);
  destroy_interface_temporary_object(layer_name);

  uint32_t *pausing_layer_memory = allocate_registered_interface_layer(320);
  uint32_t *pausing_layer = pausing_layer_memory
      ? construct_registered_interface_layer(
            pausing_layer_memory,
            (uint32_t *)&interface_layer_type_descriptor)
      : NULL;
  application_component[8] = (uint32_t)(uintptr_t)pausing_layer;
  layer_name = pausing_layer + 76;
  assign_std_string_storage((char *)(void *)layer_name,
                            "PausingGlobalLayer",
                            strlen("PausingGlobalLayer"));
  layer_vtable = (uint32_t *)(uintptr_t)pausing_layer[0];
  ((void (__thiscall *)(uint32_t *))(uintptr_t)layer_vtable[1])(
      pausing_layer);
  ((SetLayerEnabledMethod)(uintptr_t)layer_vtable[44])(pausing_layer, 1);
  layer_child = create_layer_child_added_event(
      (uint32_t *)(void *)&layer_name, 0, (int)(uintptr_t)pausing_layer);
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(pausing_layer,
                                                        layer_child);
  destroy_interface_temporary_object(layer_name);
  layer_child = create_layer_child_removed_event(
      (uint32_t *)(void *)&layer_name, 0, (int)(uintptr_t)pausing_layer);
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(pausing_layer,
                                                        layer_child);
  destroy_interface_temporary_object(layer_name);

  uint32_t *layer_collection_memory =
      allocate_registered_interface_layer_collection(324);
  uint32_t *layer_collection = layer_collection_memory
      ? construct_private_bottom_layer(layer_collection_memory)
      : NULL;
  application_component[9] = (uint32_t)(uintptr_t)layer_collection;
  uint32_t *collection_member[2] = {0, 0};
  int collection_result;
  initialize_layer_collection_reference(&collection_result);
  collection_member[0] = layer_collection;
  add_layer_collection_reference(application_component + 10,
                                (uint32_t *)(void *)collection_member);
  layer_child = create_layer_child_added_event(
      (uint32_t *)(void *)&layer_name, 0, (int)(uintptr_t)layer_collection);
  layer_vtable = (uint32_t *)(uintptr_t)layer_collection[0];
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(layer_collection,
                                                        layer_child);
  destroy_interface_temporary_object(layer_name);
  layer_child = create_layer_child_removed_event(
      (uint32_t *)(void *)&layer_collection_memory, 0,
      (int)(uintptr_t)layer_collection);
  ((AttachLayerObjectMethod)(uintptr_t)layer_vtable[3])(layer_collection,
                                                        layer_child);
  destroy_interface_temporary_object(layer_collection_memory);
  application_component[1] = (uint32_t)create_interface_input_object(
      *(uint32_t **)(uintptr_t)(*(uint32_t *)(uintptr_t)
                                    (game_engine_instance_address + 1092)
                               + 48),
      NULL, 1);
  uint32_t *input_object_memory = allocate_registered_cursor(444);
  uint32_t input_object = input_object_memory
      ? construct_cursor((uint32_t)(uintptr_t)input_object_memory)
      : 0;
  int application_input = (int)application_component[1];
  application_component[2] = input_object;
  set_cursor_spec(input_object, application_input);

  uint32_t game_window =
      *(uint32_t *)(uintptr_t)(game_engine_address + 16);
  if (GetForegroundWindow() == game_window) {
    get_mouse_cursor_worker_manager();
    set_engine_cursor_screen_position(
        (uint32_t *)(uintptr_t)cursor_screen_position_address);
  }

  uint32_t *mini_console_memory = allocate_registered_interface_console(456);
  application_component[5] = mini_console_memory
      ? (uint32_t)construct_interface_console(
            (int)(uintptr_t)mini_console_memory)
      : 0;
  uint32_t *application_component_memory =
      allocate_registered_ui_translator(328);
  char **application_subcomponent = application_component_memory
      ? construct_ui_translator((char **)application_component_memory)
      : NULL;
  application_component[27] = (uint32_t)(uintptr_t)application_subcomponent;
  release_layer_collection_reference(collection_member);
}

uint32_t *__cdecl allocate_registered_interface_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(unk_7664C0,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_interface_manager(void)
{
  uint32_t *memory = allocate_registered_interface_manager(120);
  return memory ? construct_interface_manager(memory) : NULL;
}

uint32_t *__cdecl create_registered_interface_manager(void)
{
  uint32_t *memory = allocate_registered_interface_manager(120);
  return memory
      ? construct_registered_interface_manager(memory, 0)
      : NULL;
}
