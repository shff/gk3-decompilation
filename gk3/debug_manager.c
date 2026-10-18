#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "../common/runtime_lockit.h"

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);

/* gk3/GK3R_rest.c */
extern uint32_t debug_manager_type_descriptor[15]
    __asm__("dword_764EF0");
extern int debug_manager_base_offset_adjustment __asm__("dword_764EEC");
extern int key_binding_tree_nil_node_address __asm__("dword_764F34");
extern int key_binding_tree_reference_count __asm__("dword_764F38");
extern uint32_t debug_console_type_descriptor[15]
    __asm__("dword_764578");
extern uint32_t sprite_control_type_descriptor[15]
    __asm__("dword_7648F0");
extern char byte_6A6454;
extern uint32_t debug_manager_event_target_vtable[]
    __asm__("off_6BD29C");
extern uint32_t debug_manager_vtable[] __asm__("off_6BD2A4");
extern uint32_t debug_console_vtable[] __asm__("off_6BA4A0");
extern int game_engine_instance_address __asm__("dword_765A2C");
extern int game_engine_address;
extern int screen_width_address __asm__("dword_7715CC");
extern int debug_console_base_offset_adjustment __asm__("dword_764574");
extern int __thiscall construct_control(int object);
extern float *__thiscall construct_sprite_control(float *object);
extern void __thiscall construct_key_binding_collection(uint32_t *object);
extern uint32_t *__thiscall attach_control_to_service(int service, int object,
                                                     char active)
    __asm__("sub_506755");
extern int *__thiscall find_or_create_engine_string_resource(
    uint32_t *engine, int *result, const char *name, int first, int second)
    __asm__("sub_56B0F0");
extern float *__thiscall initialize_default_option_values(float *object);
extern int *__thiscall find_or_create_engine_resource_handle(
    uint32_t *engine, int *result, const char *name, int option);
extern int __thiscall construct_debug_console_control_base(int object)
    __asm__("sub_447B7E");
extern int __thiscall initialize_debug_console(int console)
    __asm__("sub_47003F");
extern int __thiscall set_debug_console_visible(uint8_t *console, int visible,
                                                int reason)
    __asm__("sub_47041F");
extern int __thiscall hide_debug_console(uint8_t *console, int reason)
    __asm__("sub_470479");
extern int __thiscall write_debug_console_text(int *console, const char *text)
    __asm__("sub_4704B2");
extern int __thiscall get_engine_input_state(uint32_t *engine, char state);
extern char __thiscall get_keyboard_text_input_mode(uint32_t *input)
    __asm__("sub_53AFB6");
extern int __thiscall set_keyboard_text_input_mode(uint32_t *input,
                                                  char enabled)
    __asm__("sub_53AFA6");
extern char __thiscall request_keyboard_text_input(
    int *input, const char *title, int value, int *result, int flags)
    __asm__("sub_53B057");
extern void __thiscall detach_control_from_service(int service,
                                                  uint8_t *control)
    __asm__("sub_5069B3");
extern void __thiscall add_manager_to_event_dispatcher(
    uint32_t *dispatcher, uint32_t *manager) __asm__("sub_4E7CBE");
extern void __thiscall remove_manager_from_event_dispatcher(
    uint32_t *dispatcher, int manager) __asm__("sub_4E7D59");
extern uint32_t *__thiscall find_debug_key_binding_node(
    uint32_t *collection, uint32_t *result, uint32_t *key)
    __asm__("sub_487E65");
extern void __cdecl log_debug_source_message(
    const char *source, int line, int category, int flags, char *message,
    size_t size) __asm__("sub_557404");
extern uint32_t loc_6399FA[];
extern const char Key[4];

char __thiscall set_debug_manager_console_open(uint32_t *manager, char open,
                                               int reason);
uint32_t *__cdecl allocate_registered_debug_console(int size);
uint32_t *__thiscall construct_debug_console(uint32_t *console);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                 uint32_t address);
extern uint32_t *__thiscall destroy_registered_event_target(
    uint16_t *object);
extern uint32_t *__thiscall destroy_registered_sprite_control(
    uint32_t *control) __asm__("sub_44785C");
extern uint32_t *__thiscall destroy_registered_control(uint32_t *control)
    __asm__("sub_476ACF");
extern uint32_t *__thiscall destroy_key_binding_tree_nodes(
    uint32_t *collection, uint32_t *result, uint32_t *first,
    uint32_t *last) __asm__("sub_487DBD");

/* gk3/registered_controls.c */
extern uint32_t *__thiscall construct_registered_control(
    uint32_t *object, int mode);
extern int __thiscall construct_registered_sprite_control(int object,
                                                           int mode);
extern char __thiscall is_developer_control_option_enabled(
    uint8_t *developer_control, int option);
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                            const char *field_name,
                                            char *value,
                                            char *default_value);
extern char __thiscall serialize_key_binding_collection(
    uint8_t *serializer, const char *field_name, uint32_t *collection,
    int mode) __asm__("sub_488417");
extern int __cdecl serialize_debug_option_flags(
    uint8_t *serializer, int first, int count, const char *field_name,
    const char *key_field_name, const char *value_field_name,
    int (__cdecl *get_value)(int), void (__cdecl *set_value)(int, int))
    __asm__("sub_4887E1");

int __cdecl debug_option_storage_index(int option)
{
  return option + 1;
}

int __thiscall set_debug_option_enabled(uint8_t *object, int option,
                                       char enabled)
{
  const int storage_index = debug_option_storage_index(option);
  object[storage_index + 156] = (uint8_t)enabled;
  return storage_index;
}

int __thiscall disable_debug_option(uint8_t *object, int option)
{
  return set_debug_option_enabled(object, option, 0);
}

int __thiscall update_debug_manager_layout(int *manager)
{
  int rectangle[2];
  int *layout_control = manager + 16;
  rectangle[0] = *(int *)(uintptr_t)dword_7715CC
      - (manager[25] - manager[23]) - 20;
  rectangle[1] = 20;

  uint32_t *vtable = (uint32_t *)(uintptr_t)*layout_control;
  typedef int (__thiscall *SetControlPosition)(int *control, int *position);
  SetControlPosition set_position =
      (SetControlPosition)(uintptr_t)vtable[164 / sizeof(uint32_t)];
  return set_position(layout_control, rectangle);
}

static int __cdecl read_serialized_debug_option(int option)
{
  const uint32_t application =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint8_t *debug_manager = (uint8_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(application + 104);
  return is_developer_control_option_enabled(debug_manager, option);
}

static void __cdecl write_serialized_debug_option(int option, int enabled)
{
  const uint32_t application =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint8_t *debug_manager = (uint8_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(application + 104);
  set_debug_option_enabled(debug_manager, option, (char)enabled);
}

int __thiscall serialize_debug_manager(uint32_t *manager,
                                      uint8_t *serializer, int mode)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  const uint32_t *methods = *(const uint32_t **)serializer;
  typedef void (__thiscall *SerializeObjectReferenceMethod)(
      uint8_t *, const char *, int, uint32_t *);
  typedef void (__thiscall *WriteDiagnosticMessageMethod)(
      uint8_t *, const char *, ...);
  const SerializeObjectReferenceMethod serialize_object_reference =
      (SerializeObjectReferenceMethod)(uintptr_t)
          methods[68 / sizeof(uint32_t)];
  const WriteDiagnosticMessageMethod write_diagnostic_message =
      (WriteDiagnosticMessageMethod)(uintptr_t)
          methods[56 / sizeof(uint32_t)];
  (void)mode;

  serialize_object_reference(serializer, "mConsole",
                             (int)(uintptr_t)(bytes + 56), dword_764578);
  serialize_boolean_field(serializer, "mCreatingConsole",
                          (char *)(void *)(bytes + 60), &byte_6A6454);
  write_diagnostic_message(serializer, "member: type=%s, owner type=%s",
                           (const char *)(uintptr_t)dword_7648F0[0],
                           (const char *)(uintptr_t)dword_764EF0[0]);
  serialize_boolean_field(serializer, "mKeyWaiting",
                          (char *)(void *)(bytes + 136), &byte_6A6454);
  serialize_boolean_field(serializer, "mKeyUsed",
                          (char *)(void *)(bytes + 137), &byte_6A6454);
  sub_488417(serializer, "mKeyBindings",
             (uint32_t *)(void *)(bytes + 140), 3);
  if (!serializer[4])
    memset(bytes + 156, 0, 0x22);
  return sub_4887E1(serializer, 0, 32, "mFlags", "flag", "set",
                    read_serialized_debug_option,
                    write_serialized_debug_option);
}

int __cdecl serialize_registered_debug_manager(int object,
                                               uint8_t *serializer,
                                               int mode)
{
  return serialize_debug_manager((uint32_t *)(uintptr_t)object, serializer,
                                 mode);
}

int __thiscall construct_registered_debug_manager(int object, int mode)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t mode_byte = (uint8_t)((uint32_t)mode >> 24);

  construct_registered_control((uint32_t *)(void *)bytes, mode);
  construct_registered_event_target((uint16_t *)(void *)(bytes + 44));
  find_or_create_registry_entry(
      dword_764EF0,
      (uint32_t)(uintptr_t)(bytes + dword_764EEC + 56));
  construct_registered_sprite_control((int)(uintptr_t)(bytes + 64), mode);
  bytes[148] = 0;
  bytes[140] = mode_byte;
  bytes[141] = mode_byte;
  construct_key_binding_collection((uint32_t *)(void *)(bytes + 140));
  *(uint32_t *)(void *)(bytes + 44) = (uint32_t)(uintptr_t)off_6BD29C;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)off_6BD2A4;
  return object;
}

char *__thiscall construct_debug_manager(char *object)
{
  char default_value;
  construct_control((int)(uintptr_t)object);
  construct_registered_event_target((uint16_t *)(void *)object + 22);
  find_or_create_registry_entry(dword_764EF0,
             (uint32_t)(uintptr_t)&object[dword_764EEC + 56]);
  construct_sprite_control((float *)(void *)object + 16);
  object[140] = default_value;
  object[141] = default_value;
  object[148] = 0;
  construct_key_binding_collection((uint32_t *)(void *)object + 35);
  *(uint32_t *)(void *)object = (uint32_t)(uintptr_t)off_6BD2A4;
  *((uint32_t *)(void *)object + 11) = (uint32_t)(uintptr_t)off_6BD29C;
  memset(object + 156, 0, 0x22);
  *((uint32_t *)(void *)object + 14) = 0;
  object[60] = 0;
  return object;
}

int __thiscall initialize_application_debug_manager(int object)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)object;
  uint32_t option_values[5];
  int lookup_result;
  uint32_t application_engine =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint32_t debug_service = *(uint32_t *)(uintptr_t)(application_engine + 68);
  int debug_settings = *(int *)(uintptr_t)(debug_service + 28);

  sub_506755(debug_settings, object, 1);
  uint32_t *debug_layer =
      (uint32_t *)(uintptr_t)*(uint32_t *)(void *)(manager + 64);
  uint32_t debug_context[2] = {0, 0};
  int *loaded_value = sub_56B0F0(
      (uint32_t *)(uintptr_t)game_engine_address, &lookup_result,
      "cain", 0, 0);
  typedef void (__thiscall *InitializeDebugLayerMethod)(
      uint32_t *layer, uint32_t *context, int value);
  InitializeDebugLayerMethod initialize_layer =
      (InitializeDebugLayerMethod)(uintptr_t)(debug_layer[0] + 196);
  initialize_layer(debug_layer, debug_context, *loaded_value);
  update_debug_manager_layout((int *)(void *)manager);
  initialize_default_option_values((float *)(void *)option_values);
  option_values[0] = 1;
  option_values[3] = (uint32_t)*find_or_create_engine_resource_handle(
      (uint32_t *)(uintptr_t)game_engine_address, &lookup_result,
      "cain_alpha", 0);
  memcpy(manager + 112, option_values, 0x14);
  manager[132] = 1;
  manager[136] = 0;
  manager[137] = 0;
  typedef void (__thiscall *RefreshDebugManagerMethod)(uint32_t *manager);
  RefreshDebugManagerMethod refresh_manager =
      (RefreshDebugManagerMethod)(uintptr_t)(
          *(uint32_t *)(void *)manager + 4);
  refresh_manager((uint32_t *)(void *)manager);
  return set_debug_option_enabled(manager, 2, 1);
}

uint32_t *__cdecl allocate_registered_debug_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(dword_764EF0,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_debug_manager(void)
{
  char *memory = (char *)allocate_registered_debug_manager(192);
  return memory ? (uint32_t *)(void *)construct_debug_manager(memory) : NULL;
}

uint32_t *__cdecl create_registered_debug_manager(void)
{
  uint32_t *memory = allocate_registered_debug_manager(192);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_debug_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

char __thiscall is_debug_manager_console_open(uint32_t *manager)
{
  uint32_t *console = (uint32_t *)(uintptr_t)manager[14];
  return console ? *(uint8_t *)(void *)(console + 6) : 0;
}

uint32_t *__thiscall create_debug_manager_console(uint8_t *manager)
{
  uint32_t *result = loc_6399FA;

  if (!*(uint32_t *)(void *)(manager + 56)) {
    if (manager[60]) {
      sub_557404("Z:\\Proj\\GK3\\gk3app\\Source\\DebugMgr.cpp",
                 463, 0, 0,
                 "Recursive errors while creating console\n", 0xFFFFFFFFu);
      return result;
    }

    manager[60] = 1;
    uint32_t *console = allocate_registered_debug_console(228);
    result = console ? construct_debug_console(console) : NULL;
    *(uint32_t *)(void *)(manager + 56) = (uint32_t)(uintptr_t)result;
    manager[60] = 0;
  }
  return result;
}

uint32_t *__cdecl allocate_registered_debug_console(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(dword_764578,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *__thiscall construct_debug_console(uint32_t *console)
{
  sub_447B7E((int)(uintptr_t)console);
  find_or_create_registry_entry(
      dword_764578,
      (uint32_t)(uintptr_t)console + (uint32_t)dword_764574 + 197);
  console[55] = 0;
  console[0] = (uint32_t)(uintptr_t)off_6BA4A0;
  console[53] = 0;
  console[54] = 0;
  console[56] = 0;
  sub_47003F((int)(uintptr_t)console);
  return console;
}

int __thiscall get_debug_manager_console(uint32_t *manager)
{
  create_debug_manager_console((uint8_t *)(void *)manager);
  return (int)manager[14];
}

int __thiscall open_debug_manager_console(uint32_t *manager)
{
  set_debug_manager_console_open(manager, 1, 0);
  return (int)manager[14];
}

char __thiscall set_debug_manager_console_open(uint32_t *manager,
                                               char open, int reason)
{
  uint8_t *manager_bytes = (uint8_t *)(void *)manager;
  char was_open = is_debug_manager_console_open((uint32_t *)(void *)manager);

  if (was_open != open) {
    if (open) {
      uint8_t *console = (uint8_t *)(uintptr_t)get_debug_manager_console(
          (uint32_t *)(void *)manager);
      return (char)sub_47041F(console, 1, reason);
    }
    return (char)sub_470479(
        (uint8_t *)(uintptr_t)*(uint32_t *)(void *)(manager_bytes + 56), reason);
  }
  return was_open;
}

char __thiscall toggle_debug_manager_console_open(uint32_t *manager,
                                                  int reason)
{
  return set_debug_manager_console_open(
      manager, (char)!is_debug_manager_console_open(manager), reason);
}

void __thiscall write_debug_manager_console_text(int manager_address,
                                                 const char *text)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)manager_address;

  if (*(uint32_t *)(void *)(manager + 56) || !manager[60]) {
    if (*text) {
      int console = get_debug_manager_console((uint32_t *)(void *)manager);
      sub_4704B2((int *)(uintptr_t)console, text);
    }
    if (is_developer_control_option_enabled(manager, 3) &&
        !is_debug_manager_console_open((uint32_t *)(void *)manager))
      set_debug_manager_console_open((uint32_t *)(void *)manager, 1, 0);
  }
}

void __thiscall set_debug_manager_key_capture(uint32_t *manager,
                                              char capturing)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  uint32_t application =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint32_t *services =
      (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application + 68);
  uint32_t *control = (uint32_t *)(void *)(bytes + 64);

  bytes[137] = 0;
  bytes[136] = (uint8_t)capturing;
  if (capturing != bytes[88]) {
    if (capturing) {
      sub_506755((int)services[7], (int)(uintptr_t)control, 1);
      typedef void (__thiscall *SetControlVisibleMethod)(uint32_t *control,
                                                          int visible);
      SetControlVisibleMethod set_visible =
          (SetControlVisibleMethod)(uintptr_t)
              (*(uint32_t *)(void *)control + 176);
      set_visible(control, 1);
      sub_4E7CBE(services, manager);
    } else {
      typedef void (__thiscall *HideControlMethod)(uint32_t *control);
      HideControlMethod hide_control =
          (HideControlMethod)(uintptr_t)
              (*(uint32_t *)(void *)control + 180);
      hide_control(control);
      sub_5069B3((int)services[7], (uint8_t *)(void *)control);
      sub_4E7D59(services, (int)(uintptr_t)manager);
    }
  }
}

void __thiscall clear_debug_manager_input_state(uint8_t *manager)
{
  manager[4] = 0;
  set_debug_manager_key_capture((uint32_t *)(void *)manager, 0);
}

void __thiscall handle_debug_manager_input_message(uint32_t *manager,
                                                   int message)
{
  if (message == 1128)
    set_debug_manager_key_capture(manager, 0);
}

char __thiscall is_debug_manager_control_visible(uint8_t *manager)
{
  return manager[88] != 0;
}

char __thiscall is_debug_manager_waiting_for_key_binding(uint8_t *manager)
{
  return manager[136] != 0;
}

int __thiscall handle_debug_manager_key_down(int manager_address,
                                             unsigned int key,
                                             int event_flags)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)manager_address;
  int *key_binding;

  if (manager[136]) {
    if (key == 27) {
      set_debug_manager_key_capture((uint32_t *)(void *)manager, 0);
      manager[137] = 1;
      return 1;
    }

    uint32_t application =
        *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
    uint32_t *services =
        (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application + 68);
    uint32_t *keyboard =
        (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application + 88);
    uint32_t *key_node;
    int position;

    if (key != *(uint32_t *)(uintptr_t)(services[27] + 244)) {
      if (key < 0x100) {
        key_node = sub_487E65((uint32_t *)(void *)(manager + 140),
                              (uint32_t *)(void *)&position, &key);
        key_binding = (int *)(uintptr_t)*key_node;
        if ((uint32_t)(uintptr_t)key_binding !=
            *(uint32_t *)(void *)(manager + 144) && key_binding[6]) {
          char previous_mode = sub_53AFB6(keyboard);
          sub_53AFA6(keyboard, 0);
          const char *name = (const char *)(uintptr_t)key_binding[5];
          if (!name)
            name = Key;
          sub_53B057((int *)keyboard, "Debug Binding", (int)(uintptr_t)name,
                     NULL, 0);
          sub_53AFA6(keyboard, previous_mode);
        }
      }
      manager[137] = 1;
      return 1;
    }
    return 0;
  }

  uint32_t application =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint32_t *services =
      (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application + 68);
  if (key == *(uint32_t *)(uintptr_t)(services[27] + 244) &&
      (event_flags & 0x40000000) == 0 &&
      (get_engine_input_state((uint32_t *)(uintptr_t)dword_765A2C, 0) &
       0x38) == 0) {
    set_debug_manager_key_capture((uint32_t *)(void *)manager, 1);
    return 1;
  }
  return 0;
}

int __thiscall handle_debug_manager_key_up(uint32_t *manager, int key,
                                           int event_flags)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  uint32_t application =
      *(uint32_t *)(uintptr_t)(dword_765A2C + 1092);
  uint32_t *services =
      (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application + 68);

  if (bytes[136] && key == *(uint32_t *)(uintptr_t)(services[27] + 244)) {
    if (!bytes[137])
      toggle_debug_manager_console_open(manager, 0);
    set_debug_manager_key_capture(manager, 0);
    return 1;
  }
  (void)event_flags;
  return 0;
}

void __thiscall construct_key_binding_collection(uint32_t *collection)
{
  uint32_t lock_storage[1];
  uint32_t *nil_node;
  uint32_t *root_node;

  construct_runtime_lockit(lock_storage);
  if (!dword_764F34) {
    nil_node = allocate_tracked_memory(36);
    nil_node[1] = 0;
    nil_node[8] = 1;
    dword_764F34 = (int)(uintptr_t)nil_node;
    nil_node[0] = 0;
    nil_node[2] = 0;
  }

  ++dword_764F38;
  nil_node = (uint32_t *)(uintptr_t)dword_764F34;
  root_node = allocate_tracked_memory(36);
  root_node[1] = (uint32_t)(uintptr_t)nil_node;
  root_node[8] = 0;
  collection[1] = (uint32_t)(uintptr_t)root_node;
  collection[3] = 0;
  root_node[0] = (uint32_t)(uintptr_t)root_node;
  root_node[2] = (uint32_t)(uintptr_t)root_node;
  destroy_runtime_lockit(lock_storage);
}

void __thiscall destroy_key_binding_collection(uint32_t *collection)
{
  uint32_t lock_storage[1];
  uint32_t discarded_root;
  uint32_t *root = (uint32_t *)(uintptr_t)collection[1];

  sub_487DBD(collection, &discarded_root,
             (uint32_t *)(uintptr_t)root[0], root);
  free_tracked_memory((int)collection[1]);
  collection[1] = 0;
  collection[3] = 0;

  construct_runtime_lockit(lock_storage);
  if (!--dword_764F38) {
    free_tracked_memory(dword_764F34);
    dword_764F34 = 0;
  }
  destroy_runtime_lockit(lock_storage);
}

uint32_t *__thiscall destroy_debug_manager_members(uint32_t *manager)
{
  uint16_t *event_target = (uint16_t *)(void *)(manager + 11);
  uint32_t *console = (uint32_t *)(uintptr_t)manager[14];

  manager[0] = (uint32_t)(uintptr_t)off_6BD2A4;
  manager[11] = (uint32_t)(uintptr_t)off_6BD29C;
  if (console) {
    typedef void (__thiscall *DeleteObjectMethod)(uint32_t *object,
                                                   int free_storage);
    DeleteObjectMethod delete_console =
        (DeleteObjectMethod)(uintptr_t)console[0];
    delete_console(console, 1);
  }
  destroy_key_binding_collection(manager + 35);
  sub_44785C(manager + 16);
  erase_map_entry_impl(dword_764EF0,
                       (uint32_t)dword_764EEC +
                           (uint32_t)(uintptr_t)(manager + 14));
  destroy_registered_event_target(event_target);
  return sub_476ACF(manager);
}

int __thiscall delete_debug_manager(uint32_t *adjusted_this, char flags)
{
  uint32_t *manager = adjusted_this - 11;
  destroy_debug_manager_members(manager);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)manager);
  return (int)(uintptr_t)manager;
}
