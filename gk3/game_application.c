#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *event_target);

typedef struct {
  uint32_t object_base[3];
  uint32_t event_target_base[3];
  uint8_t is_closing;
  uint8_t fast_quit;
  uint8_t main_ready;
  uint8_t reserved_flags;
  uint32_t action_manager;
  uint32_t animator;
  void *callback_manager;
  uint32_t camera;
  uint32_t camera_angle_manager;
  uint32_t cursor_manager;
  uint32_t dialogue_manager;
  uint32_t flag_manager;
  uint32_t game_state;
  uint32_t generics_manager;
  uint32_t interface_manager;
  uint32_t layer_manager;
  uint32_t mini_console;
  uint32_t report_manager;
  uint32_t score_manager;
  uint32_t sheep_engine;
  uint32_t soundtrack_manager;
  uint32_t stage_manager;
  uint32_t static_configuration;
  uint32_t debug_manager;
  uint32_t developer_control;
  uint32_t primitive_manager;
} GameApplication;

typedef struct {
  uint32_t phase;
  uint32_t callback_address;
  uint8_t once;
  uint8_t reserved[3];
} GameApplicationLifecycleCallback;

typedef struct {
  uint8_t flags;
  uint8_t reserved[3];
  uint32_t begin_address;
  uint32_t end_address;
  uint32_t capacity_address;
} GameApplicationLifecycleCallbackList;

typedef struct {
  const char *name;
  size_t offset;
  uint32_t *type_descriptor;
} GameApplicationSerializedObjectField;

typedef struct {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t data4[8];
} GameInputIdentifier;

typedef int (__thiscall *SerializeRegisteredObjectFieldMethod)(
    uint8_t *reader, const char *name, char *value, uint32_t *type_descriptor);
typedef int (__thiscall *GameApplicationMemberDestructor)(
    uint32_t *member, int free_memory);

_Static_assert(offsetof(GameApplication, is_closing) == 24,
               "game application flags offset");
_Static_assert(offsetof(GameApplication, action_manager) == 28,
               "game application manager fields offset");
_Static_assert(offsetof(GameApplication, game_state) == 60,
               "game application state offset");
_Static_assert(offsetof(GameApplication, interface_manager) == 68,
               "game application interface manager offset");
_Static_assert(offsetof(GameApplication, primitive_manager) == 112,
               "game application primitive manager offset");
_Static_assert(sizeof(GameApplication) == 116, "game application size");
_Static_assert(sizeof(GameApplicationLifecycleCallback) == 12,
               "lifecycle callback record size");
_Static_assert(sizeof(GameApplicationLifecycleCallbackList) == 16,
               "lifecycle callback list size");
_Static_assert(sizeof(GameInputIdentifier) == 16,
               "game input identifier size");

/* gk3/GK3R_rest.c */
extern int game_application_base_offset_adjustment;
extern uint32_t game_application_type_descriptor[15];
extern int game_application_lifecycle_callback_list_address;
extern uint32_t *game_application_event_target_vtable;
extern uint32_t *game_application_object_vtable;
extern uint32_t action_manager_type_descriptor[15];
extern uint32_t animator_type_descriptor[15];
extern uint32_t unk_763E30[]; /* Callback-manager type descriptor. */
extern uint32_t unk_763FD8[]; /* Camera type descriptor. */
extern uint32_t unk_7640B8[]; /* Camera-angle manager type descriptor. */
extern uint32_t unk_764D78[]; /* Cursor-manager type descriptor. */
extern uint32_t unk_7650C8[]; /* Dialogue-manager type descriptor. */
extern uint32_t unk_765708[]; /* Flag-manager type descriptor. */
extern uint32_t unk_765C18[]; /* Game-state type descriptor. */
extern uint32_t generics_manager_type_descriptor[15];
extern uint32_t unk_7664C0[]; /* Interface-manager type descriptor. */
extern uint32_t unk_7666D0[]; /* Layer-manager type descriptor. */
extern uint32_t unk_76C7E8[]; /* Report-manager type descriptor. */
extern uint32_t unk_76C8E8[]; /* Score-manager type descriptor. */
extern uint32_t unk_76CA08[]; /* Sheep-engine type descriptor. */
extern uint32_t unk_76CFD0[]; /* Soundtrack-manager type descriptor. */
extern uint32_t unk_76D128[]; /* Stage-manager type descriptor. */
extern uint32_t unk_7643E0[]; /* Static-configuration type descriptor. */
extern uint32_t unk_7644B8[]; /* Mini-console type descriptor. */
extern uint32_t debug_manager_type_descriptor[15];
extern uint32_t unk_764F48[]; /* Developer-control type descriptor. */
extern uint32_t primitive_manager_type_descriptor[15];
extern char byte_6A6454;
extern char __cdecl serialize_boolean_field(uint8_t *reader,
                                           const char *name, char *value,
                                           char *default_value);
extern void __cdecl free_tracked_memory(int address);
extern uint32_t *__thiscall destroy_game_state(uint32_t *object);
extern uint32_t *__thiscall destroy_score_manager(int *object);
extern uint32_t *__thiscall destroy_registered_object_base(
    uint32_t *object);
extern uint32_t *__thiscall destroy_registered_event_target(
    uint16_t *storage);
extern uint32_t *__thiscall erase_map_entry_impl(
    uint32_t *registry, uint32_t address);
extern int event_handler_base_offset_adjustment;
extern uint32_t event_handler_type_descriptor[15];
extern uint32_t registered_game_object_vtable[];
extern int game_engine_instance_address;
extern uint8_t *__thiscall construct_registered_game_object(
    uint8_t *object);
extern uint32_t *__thiscall stop_all_soundtrack_instances(
    uint32_t *soundtrack_manager);
extern int __thiscall increment_and_persist_setting_value(
    uint32_t **settings);
extern int (__stdcall *dynamic_array_vtable)(char);
extern int parent_control_default_object;
extern int game_engine_address;
extern int __stdcall PostMessageA(uint32_t window, uint32_t message,
                                  uint32_t wparam, int32_t lparam);
extern char __thiscall is_game_layer_active(char *layer_manager,
                                            int layer_id);
extern int __thiscall close_game_layer(char *layer_manager, int layer_id);
extern char __thiscall is_game_layer_visible(char *layer_manager,
                                             int layer_id);
extern char __thiscall is_developer_control_option_enabled(
    uint8_t *developer_control, int option);
extern int __thiscall set_game_layer_state(char *layer_manager, int layer_id,
                                           int state);
extern int *__thiscall apply_engine_display_state(
    int *engine, int state, char center_surface);
extern int __thiscall get_engine_input_state(uint32_t *engine, char state);
extern int __thiscall set_mini_console_visible(int **console, int visible);
extern int __stdcall save_display_options_to_settings(
    int mode, uint8_t width, uint8_t height, char fullscreen,
    GameInputIdentifier identity, int option_8);
extern BOOL __thiscall post_engine_restart_message(uint32_t *engine);
extern int __thiscall initialize_application_log_manager(int manager);
extern int __thiscall initialize_application_debug_manager(int manager);
extern int __thiscall append_game_application_lifecycle_callback(
    int list_address, GameApplicationLifecycleCallback *callback);
extern int __cdecl initialize_application_logging(void);
extern int __cdecl initialize_application_debug_tools(void);
extern void initialize_application_interface_manager(
    uint32_t *application_component, int context);
extern uint32_t *__thiscall add_object_to_owned_collection(
    int collection, int *object, char retain_reference);
extern uint32_t *__thiscall add_active_object_child(
    int object, int *child, char retain_reference);
extern uint32_t *construct_application_action_manager(void);
extern uint32_t *construct_application_animator(void);
extern uint32_t *construct_application_camera_manager(void);
extern uint32_t *construct_application_camera_angle_manager(void);
extern void *construct_application_callback_manager(void);
extern uint32_t *construct_application_game_state(void);
extern uint32_t *construct_application_cursor_spec_collection(void);
extern uint32_t *construct_application_generics_manager(void);
extern uint32_t *construct_application_interface_manager(void);
extern uint32_t *construct_application_layer_manager(void);
extern uint32_t *construct_application_report_manager(void);
extern uint32_t *construct_application_sheep_engine(void);
extern uint32_t *construct_application_soundtrack_manager(void);
extern uint32_t *construct_application_stage_manager(void);
extern uint32_t *construct_application_static_configuration(void);
extern uint32_t *construct_application_debug_manager(void);
extern uint32_t *construct_application_dialogue_manager(int mode);
extern uint32_t *construct_application_flag_manager(void);
extern uint32_t *construct_application_score_manager(void);
extern uint32_t *construct_application_developer_control(void);
extern uint32_t *construct_application_primitive_manager(void);
extern uint32_t *construct_application_mini_console(void);
extern void attach_animator_to_engine(uint32_t *animator);
extern void initialize_camera_manager(uint32_t *camera);
extern int initialize_developer_control(uint32_t *developer_control);
extern void shutdown_action_manager(uint32_t *manager);
extern void shutdown_animator(uint32_t *animator);
extern void shutdown_camera_manager(uint32_t *camera_manager);
extern int shutdown_generics_manager(uint32_t *manager);
extern int shutdown_report_manager(uint32_t *manager);
extern void shutdown_sheep_engine(uint32_t *sheep_engine);
extern uint32_t *shutdown_soundtrack_manager(uint32_t *manager);
extern int shutdown_stage_manager(uint32_t *manager);
extern int shutdown_developer_control(uint32_t *developer_control);
extern int shutdown_primitive_manager(uint32_t *manager);

typedef int (__cdecl *GameApplicationLifecycleCallbackMethod)(void);

void __fastcall ensure_game_application_lifecycle_callback_registry(int flags);

int __cdecl register_game_application_lifecycle_callback(
    int phase, int callback_address, char once)
{
  GameApplicationLifecycleCallback callback = {
    .phase = (uint32_t)phase,
    .callback_address = (uint32_t)callback_address,
    .once = (uint8_t)once,
    .reserved = { 0, 0, 0 }
  };

  ensure_game_application_lifecycle_callback_registry(phase);
  return append_game_application_lifecycle_callback(
      game_application_lifecycle_callback_list_address, &callback);
}

int __cdecl dispatch_game_application_lifecycle_callbacks(int phase)
{
  uint32_t list_address =
      (uint32_t)game_application_lifecycle_callback_list_address;
  int result = (int)list_address;
  if (list_address == 0)
    return result;

  GameApplicationLifecycleCallbackList *list =
      (GameApplicationLifecycleCallbackList *)(uintptr_t)list_address;
  uint32_t callback_address = list->begin_address;
  while (callback_address != list->end_address) {
    GameApplicationLifecycleCallback *callback =
        (GameApplicationLifecycleCallback *)(uintptr_t)callback_address;
    result = (int)callback->phase;
    if (callback->phase == (uint32_t)phase) {
      if (callback->once != 0)
        callback->phase = 0;
      GameApplicationLifecycleCallbackMethod method =
          (GameApplicationLifecycleCallbackMethod)(uintptr_t)
              callback->callback_address;
      result = method();
    }
    callback_address += sizeof(*callback);
  }
  return result;
}

void __fastcall ensure_game_application_lifecycle_callback_registry(int flags)
{
  if (game_application_lifecycle_callback_list_address != 0)
    return;

  GameApplicationLifecycleCallbackList *list =
      (GameApplicationLifecycleCallbackList *)allocate_tracked_memory(16);
  if (list != NULL) {
    list->flags = (uint8_t)((uint32_t)flags >> 24);
    list->begin_address = 0;
    list->end_address = 0;
    list->capacity_address = 0;
  }
  game_application_lifecycle_callback_list_address = (int)(intptr_t)list;
}

void __cdecl destroy_callback_registry(void)
{
  const uint32_t list_address =
      (uint32_t)game_application_lifecycle_callback_list_address;
  if (list_address == 0)
    return;

  GameApplicationLifecycleCallbackList *list =
      (GameApplicationLifecycleCallbackList *)(uintptr_t)list_address;
  free_tracked_memory((int)list->begin_address);
  list->begin_address = 0;
  list->end_address = 0;
  list->capacity_address = 0;
  free_tracked_memory((int)list_address);
  game_application_lifecycle_callback_list_address = 0;
}

uint32_t *__cdecl allocate_registered_game_application(int size)
{
  uint32_t *application = allocate_tracked_memory(size);
  uint32_t *registration = find_or_create_registry_entry(
      game_application_type_descriptor,
      (uint32_t)(uintptr_t)application);
  registration[2] = 1;
  return application;
}

int __thiscall construct_game_application(int object_address)
{
  GameApplication *application =
      (GameApplication *)(uintptr_t)object_address;
  uint8_t *object = (uint8_t *)(void *)application;

  construct_registered_game_object(object);
  construct_registered_event_target((uint16_t *)(void *)(object + 12));
  find_or_create_registry_entry(
      game_application_type_descriptor,
      (uint32_t)(uintptr_t)(object + 24)
          + (uint32_t)game_application_base_offset_adjustment);

  application->object_base[0] =
      (uint32_t)(uintptr_t)game_application_object_vtable;
  application->event_target_base[0] =
      (uint32_t)(uintptr_t)game_application_event_target_vtable;
  application->is_closing = 0;
  application->fast_quit = 0;
  application->main_ready = 0;
  application->static_configuration = (uint32_t)(uintptr_t)
      construct_application_static_configuration();
  application->callback_manager = construct_application_callback_manager();
  application->report_manager = (uint32_t)(uintptr_t)
      construct_application_report_manager();
  application->interface_manager = (uint32_t)(uintptr_t)
      construct_application_interface_manager();
  application->cursor_manager = (uint32_t)(uintptr_t)
      construct_application_cursor_spec_collection();
  application->layer_manager = (uint32_t)(uintptr_t)
      construct_application_layer_manager();
  application->debug_manager = (uint32_t)(uintptr_t)
      construct_application_debug_manager();
  application->game_state = (uint32_t)(uintptr_t)
      construct_application_game_state();
  application->generics_manager = (uint32_t)(uintptr_t)
      construct_application_generics_manager();
  application->sheep_engine = (uint32_t)(uintptr_t)
      construct_application_sheep_engine();
  application->soundtrack_manager = (uint32_t)(uintptr_t)
      construct_application_soundtrack_manager();
  application->stage_manager = (uint32_t)(uintptr_t)
      construct_application_stage_manager();
  application->action_manager = 0;
  application->animator = 0;
  application->camera = 0;
  application->camera_angle_manager = 0;
  application->dialogue_manager = 0;
  application->flag_manager = 0;
  application->mini_console = 0;
  application->score_manager = 0;
  application->developer_control = 0;
  application->primitive_manager = 0;
  dispatch_game_application_lifecycle_callbacks(1);
  return object_address;
}

/* The original entry receives the application in ECX and context in EDI. */
int initialize_game_application(int object_address, int context)
{
  GameApplication *application =
      (GameApplication *)(uintptr_t)object_address;
  uint8_t *engine = (uint8_t *)(uintptr_t)game_engine_instance_address;
  uint32_t engine_application = *(uint32_t *)(void *)(engine + 1092);
  uint32_t interface_manager =
      *(uint32_t *)(uintptr_t)(engine_application + 68);

  initialize_application_interface_manager(
      (uint32_t *)(uintptr_t)interface_manager, context);
  initialize_application_logging();
  initialize_application_debug_tools();
  add_object_to_owned_collection(
      (int)(interface_manager + 28), (int *)(void *)application, 1);
  add_active_object_child(
      (int)(interface_manager + 32),
      (int *)(uintptr_t)application->soundtrack_manager, 1);
  return dispatch_game_application_lifecycle_callbacks(2);
}

void __thiscall initialize_deferred_game_application_components(
    GameApplication *application)
{
  if (application->main_ready != 0)
    return;

  application->main_ready = 1;
  application->action_manager = (uint32_t)(uintptr_t)
      construct_application_action_manager();
  application->animator = (uint32_t)(uintptr_t)
      construct_application_animator();
  application->camera = (uint32_t)(uintptr_t)
      construct_application_camera_manager();
  application->camera_angle_manager = (uint32_t)(uintptr_t)
      construct_application_camera_angle_manager();
  const uint8_t dialogue_mode =
      *((uint8_t *)(uintptr_t)game_engine_instance_address + 1096);
  application->dialogue_manager = (uint32_t)(uintptr_t)
      construct_application_dialogue_manager(dialogue_mode);
  application->flag_manager = (uint32_t)(uintptr_t)
      construct_application_flag_manager();
  application->score_manager = (uint32_t)(uintptr_t)
      construct_application_score_manager();
  application->primitive_manager = (uint32_t)(uintptr_t)
      construct_application_primitive_manager();
  application->developer_control = (uint32_t)(uintptr_t)
      construct_application_developer_control();

  attach_animator_to_engine(
      (uint32_t *)(uintptr_t)application->animator);
  initialize_camera_manager((uint32_t *)(uintptr_t)application->camera);
  initialize_developer_control(
      (uint32_t *)(uintptr_t)application->developer_control);
  stop_all_soundtrack_instances(
      (uint32_t *)(uintptr_t)application->soundtrack_manager);
  increment_and_persist_setting_value(
      *(uint32_t ***)(uintptr_t)(game_engine_instance_address + 1192));
  dispatch_game_application_lifecycle_callbacks(3);
}

int __thiscall request_game_application_close(
    GameApplication *application, char mark_closing, char fast_quit)
{
  if (mark_closing != 0)
    application->is_closing = 1;
  if (fast_quit != 0) {
    application->is_closing = 1;
    application->fast_quit = 1;
  }

  const uint32_t window =
      *(uint32_t *)(uintptr_t)(game_engine_address + 16);
  return PostMessageA(window, 0x10u, 0, 0);
}

int __thiscall handle_engine_close_request(GameApplication *application)
{
  char *layer_manager =
      (char *)(uintptr_t)application->layer_manager;
  uint8_t *debug_manager =
      (uint8_t *)(uintptr_t)application->debug_manager;

  if (is_game_layer_active(layer_manager, 12)) {
    close_game_layer(layer_manager, 12);
    return 1;
  }
  if (!is_game_layer_visible(layer_manager, 15))
    return 0;

  if (is_developer_control_option_enabled(debug_manager, 15)) {
    application->is_closing = 1;
    application->fast_quit = 1;
  }
  if (application->is_closing == 0) {
    if (!is_game_layer_visible(layer_manager, 3))
      set_game_layer_state(layer_manager, 3, 0);
    return 1;
  }
  if (application->fast_quit == 0) {
    application->is_closing = 0;
    return 1;
  }

  application->is_closing = 1;
  apply_engine_display_state(
      (int *)(uintptr_t)game_engine_instance_address, 0, 1);
  return 0;
}

int __thiscall handle_engine_command_message(
    GameApplication *application, int command)
{
  if (command != 40001)
    return 0;
  request_game_application_close(application, 0, 0);
  return 1;
}

int __thiscall handle_game_application_key_message(
    GameApplication *application, int message, int unused_argument)
{
  uint32_t *engine_context =
      (uint32_t *)(uintptr_t)game_engine_instance_address;
  uint32_t *interface_manager =
      (uint32_t *)(uintptr_t)application->interface_manager;
  uint32_t interface_settings = interface_manager[27];
  const int console_toggle_message =
      *(int *)(uintptr_t)(interface_settings + 244);
  (void)unused_argument;
  if (message == console_toggle_message
      && (get_engine_input_state(engine_context, 0) & 0x38) == 0x18) {
    uint32_t mini_console_address = application->mini_console;
    int visible = 1;
    if (mini_console_address != 0) {
      const uint8_t *mini_console =
          (const uint8_t *)(uintptr_t)mini_console_address;
      if (mini_console[24] != 0)
        visible = 0;
    } else {
      uint32_t *mini_console = construct_application_mini_console();
      application->mini_console = (uint32_t)(uintptr_t)mini_console;
      mini_console_address = application->mini_console;
    }

    set_mini_console_visible((int **)(uintptr_t)mini_console_address,
                             visible);
    return 1;
  }

  if (message == 13
      && (get_engine_input_state(engine_context, 0) & 0x38) == 0x20) {
    uint8_t configuration[36];
    memcpy(configuration,
           (const void *)(uintptr_t)(game_engine_address + 112),
           sizeof(configuration));
    configuration[12] = (uint8_t)(configuration[12] == 0);

    GameInputIdentifier identity;
    uint32_t first;
    int32_t sixth;
    memcpy(&first, configuration, sizeof(first));
    memcpy(&identity, configuration + 16, sizeof(identity));
    memcpy(&sixth, configuration + 32, sizeof(sixth));
    save_display_options_to_settings(
        (int)first, (uint8_t)configuration[4], configuration[8],
        (int8_t)configuration[12], identity, sixth);
    post_engine_restart_message(engine_context);
    return 1;
  }

  return 0;
}

int __thiscall shutdown_game_application(GameApplication *application)
{
  if (application->animator != 0)
    shutdown_animator((uint32_t *)(uintptr_t)application->animator);
  if (application->camera != 0)
    shutdown_camera_manager((uint32_t *)(uintptr_t)application->camera);
  if (application->stage_manager != 0)
    shutdown_stage_manager(
        (uint32_t *)(uintptr_t)application->stage_manager);
  if (application->soundtrack_manager != 0)
    shutdown_soundtrack_manager(
        (uint32_t *)(uintptr_t)application->soundtrack_manager);
  if (application->sheep_engine != 0)
    shutdown_sheep_engine(
        (uint32_t *)(uintptr_t)application->sheep_engine);
  if (application->generics_manager != 0)
    shutdown_generics_manager(
        (uint32_t *)(uintptr_t)application->generics_manager);
  if (application->action_manager != 0)
    shutdown_action_manager(
        (uint32_t *)(uintptr_t)application->action_manager);
  if (application->developer_control != 0)
    shutdown_developer_control(
        (uint32_t *)(uintptr_t)application->developer_control);
  if (application->primitive_manager != 0)
    shutdown_primitive_manager(
        (uint32_t *)(uintptr_t)application->primitive_manager);
  if (application->report_manager != 0)
    shutdown_report_manager(
        (uint32_t *)(uintptr_t)application->report_manager);
  return dispatch_game_application_lifecycle_callbacks(4);
}

int __thiscall serialize_game_application_fields(
    GameApplication *application, uint8_t *reader, int serialization_flags)
{
  static const GameApplicationSerializedObjectField object_fields[] = {
    { "mActionMgr", offsetof(GameApplication, action_manager), action_manager_type_descriptor },
    { "mAnimator", offsetof(GameApplication, animator), animator_type_descriptor },
    { "mCallbackMgr", offsetof(GameApplication, callback_manager), unk_763E30 },
    { "mCamera", offsetof(GameApplication, camera), unk_763FD8 },
    { "mCameraAngleMgr", offsetof(GameApplication, camera_angle_manager), unk_7640B8 },
    { "mCursorMgr", offsetof(GameApplication, cursor_manager), unk_764D78 },
    { "mDialogueMgr", offsetof(GameApplication, dialogue_manager), unk_7650C8 },
    { "mFlagMgr", offsetof(GameApplication, flag_manager), unk_765708 },
    { "mGameState", offsetof(GameApplication, game_state), unk_765C18 },
    { "mGenerics", offsetof(GameApplication, generics_manager), generics_manager_type_descriptor },
    { "mInterfaceMgr", offsetof(GameApplication, interface_manager), unk_7664C0 },
    { "mLayerMgr", offsetof(GameApplication, layer_manager), unk_7666D0 },
    { "mReportMgr", offsetof(GameApplication, report_manager), unk_76C7E8 },
    { "mScoreMgr", offsetof(GameApplication, score_manager), unk_76C8E8 },
    { "mSheepEngine", offsetof(GameApplication, sheep_engine), unk_76CA08 },
    { "mSoundTrackMgr", offsetof(GameApplication, soundtrack_manager), unk_76CFD0 },
    { "mStageMgr", offsetof(GameApplication, stage_manager), unk_76D128 },
    { "mStaticConfig", offsetof(GameApplication, static_configuration), unk_7643E0 },
    { "mMiniConsole", offsetof(GameApplication, mini_console), unk_7644B8 },
    { "mDebugMgr", offsetof(GameApplication, debug_manager), debug_manager_type_descriptor },
    { "mDevControl", offsetof(GameApplication, developer_control), unk_764F48 },
    { "mPrimitiveMgr", offsetof(GameApplication, primitive_manager), primitive_manager_type_descriptor }
  };
  uint32_t *reader_methods = *(uint32_t **)(void *)reader;
  SerializeRegisteredObjectFieldMethod serialize_object_field =
      (SerializeRegisteredObjectFieldMethod)(uintptr_t)reader_methods[17];
  int result;

  (void)serialization_flags;
  serialize_boolean_field(reader, "mIsClosing",
                          (char *)&application->is_closing, &byte_6A6454);
  serialize_boolean_field(reader, "mFastQuit",
                          (char *)&application->fast_quit, &byte_6A6454);
  serialize_boolean_field(reader, "mMainReady",
                          (char *)&application->main_ready, &byte_6A6454);

  for (size_t index = 0;
       index < sizeof(object_fields) / sizeof(object_fields[0]); ++index) {
    const GameApplicationSerializedObjectField *field = &object_fields[index];
    result = serialize_object_field(
        reader, field->name,
        (char *)(void *)application + field->offset,
        field->type_descriptor);
  }

  if (reader[4] == 0) {
    dispatch_game_application_lifecycle_callbacks(1);
    result = dispatch_game_application_lifecycle_callbacks(2);
    if (application->main_ready != 0)
      return dispatch_game_application_lifecycle_callbacks(3);
  }
  return result;
}

int __cdecl serialize_game_application_callback(
    char *object, uint8_t *reader, int serialization_flags)
{
  return serialize_game_application_fields(
      (GameApplication *)(void *)object, reader, serialization_flags);
}

uint32_t *__fastcall destroy_game_application(int object_address)
{
  static const size_t destruction_order[] = {
    offsetof(GameApplication, score_manager),
    offsetof(GameApplication, soundtrack_manager),
    offsetof(GameApplication, flag_manager),
    offsetof(GameApplication, dialogue_manager),
    offsetof(GameApplication, camera_angle_manager),
    offsetof(GameApplication, camera),
    offsetof(GameApplication, animator),
    offsetof(GameApplication, action_manager),
    offsetof(GameApplication, stage_manager),
    offsetof(GameApplication, sheep_engine),
    offsetof(GameApplication, generics_manager),
    offsetof(GameApplication, game_state),
    offsetof(GameApplication, developer_control),
    offsetof(GameApplication, primitive_manager),
    offsetof(GameApplication, debug_manager),
    offsetof(GameApplication, mini_console),
    offsetof(GameApplication, layer_manager),
    offsetof(GameApplication, cursor_manager),
    offsetof(GameApplication, interface_manager),
    offsetof(GameApplication, report_manager),
    offsetof(GameApplication, callback_manager),
    offsetof(GameApplication, static_configuration)
  };
  GameApplication *application =
      (GameApplication *)(uintptr_t)object_address;
  uint8_t *application_bytes = (uint8_t *)(void *)application;

  application->object_base[0] =
      (uint32_t)(uintptr_t)game_application_object_vtable;
  application->event_target_base[0] =
      (uint32_t)(uintptr_t)game_application_event_target_vtable;
  dispatch_game_application_lifecycle_callbacks(5);

  for (size_t index = 0;
       index < sizeof(destruction_order) / sizeof(destruction_order[0]);
       ++index) {
    uint32_t *member_slot = (uint32_t *)(void *)
        (application_bytes + destruction_order[index]);
    uint32_t *member = (uint32_t *)(uintptr_t)*member_slot;

    if (member != NULL) {
      if (destruction_order[index]
          == offsetof(GameApplication, score_manager)) {
        destroy_score_manager((int *)(void *)member);
        free_tracked_memory((int)(uintptr_t)member);
      } else if (destruction_order[index]
                 == offsetof(GameApplication, game_state)) {
        destroy_game_state(member);
        free_tracked_memory((int)(uintptr_t)member);
      } else {
        const GameApplicationMemberDestructor destroy_member =
            (GameApplicationMemberDestructor)(uintptr_t)*member;
        destroy_member(member, 1);
      }
    }
    *member_slot = 0;
  }

  erase_map_entry_impl(
      game_application_type_descriptor,
      (uint32_t)(uintptr_t)application + 24
          + (uint32_t)game_application_base_offset_adjustment);
  destroy_registered_event_target(
      (uint16_t *)(void *)application->event_target_base);
  application->object_base[0] =
      (uint32_t)(uintptr_t)registered_game_object_vtable;
  erase_map_entry_impl(
      event_handler_type_descriptor,
      (uint32_t)(uintptr_t)(application_bytes + 9)
          + (uint32_t)event_handler_base_offset_adjustment);
  return destroy_registered_object_base((uint32_t *)(void *)application);
}
