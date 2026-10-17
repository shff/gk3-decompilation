#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef uint32_t _DWORD;

typedef struct {
  uint32_t registry;
  uint32_t index;
  uint32_t category;
} ObjectRegistration;

int __thiscall shutdown_mouse_cursor_worker_manager(int manager_address);
HANDLE __thiscall stop_mouse_cursor_worker_thread(HANDLE *manager);
void __thiscall set_mouse_cursor_activity_state(
    struct _RTL_CRITICAL_SECTION *manager,
    struct _RTL_CRITICAL_SECTION_DEBUG *value);
PRTL_CRITICAL_SECTION_DEBUG __thiscall get_mouse_cursor_activity_state(
    struct _RTL_CRITICAL_SECTION *manager);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/game_engine.c */
uint32_t game_engine_type_descriptor[15];
int game_engine_base_offset_adjustment;
typedef void (__thiscall *GameEngineMethod)(void);

extern void __thiscall sub_4B5852(void);
extern void __thiscall sub_4B7D36(void);
extern int __thiscall sub_5712A0(uint32_t *engine, int elapsed);
extern void __thiscall sub_571230(void);
extern void __thiscall sub_4B5A66(void);
extern void __thiscall sub_570E70(void);
extern void __thiscall sub_570F10(void);
extern int __thiscall get_game_time(uint32_t *engine);
extern void __thiscall sub_4B5C42(void);
extern void __thiscall sub_4B73A4(void);
extern void __thiscall sub_4B7ADF(void);
extern void __thiscall sub_4B8637(void);
extern void __thiscall sub_4B7A2E(void);
extern void __thiscall sub_4B7ADA(void);
extern void __thiscall sub_4B7269(void);
extern void __thiscall sub_4B7681(void);
extern void __thiscall sub_4B84E6(void);
extern void __thiscall sub_4B858A(void);
extern void __thiscall sub_4B7D8E(void);
extern void __thiscall sub_4B8244(void);
extern void __thiscall sub_4B7E37(void);
extern void __thiscall sub_4B832B(void);
extern void __thiscall sub_4B7F6F(void);
extern void __thiscall sub_4B7A30(void);
extern void __thiscall sub_4B79BF(void);
extern void __thiscall sub_4B7141(void);
extern void __thiscall sub_4B7ED3(void);
extern void __thiscall sub_4B8404(void);
extern void __thiscall sub_4B7A98(void);
extern void __thiscall sub_4B78B0(void);
extern void __thiscall sub_4B87F0(void);
extern void __thiscall sub_4B86B2(void);
extern void __thiscall sub_4B873F(void);
extern void __thiscall sub_4B7A2F(void);
extern void __thiscall sub_4B5842(void);
extern void __thiscall sub_4B7BBC(void);
extern void __thiscall sub_570FD0(void);
extern void __thiscall sub_566640(void);
extern void __thiscall sub_4B7BC8(void);
extern void __thiscall sub_4B6303(void);
extern void __thiscall sub_4B636C(void);
extern void __thiscall sub_4B5926(void);
extern void __thiscall sub_570330(void);
extern void __thiscall sub_570490(void);
extern void __thiscall sub_570580(void);
extern void __thiscall sub_4B7D82(void);
extern void __thiscall sub_4B5D4D(void);

/* Unknown methods retain address-derived names until their bodies are identified. */
static const GameEngineMethod game_engine_vtable[] = {
  (GameEngineMethod)sub_4B5852,
  (GameEngineMethod)sub_4B7D36,
  (GameEngineMethod)sub_5712A0, /* update_timed_objects */
  (GameEngineMethod)sub_571230,
  (GameEngineMethod)sub_4B5A66,
  (GameEngineMethod)sub_570E70,
  (GameEngineMethod)sub_570F10,
  (GameEngineMethod)get_game_time,
  (GameEngineMethod)sub_4B5C42,
  (GameEngineMethod)sub_4B73A4,
  (GameEngineMethod)sub_4B7ADF,
  (GameEngineMethod)sub_4B8637,
  (GameEngineMethod)sub_4B7A2E,
  (GameEngineMethod)sub_4B7ADA,
  (GameEngineMethod)sub_4B7269,
  (GameEngineMethod)sub_4B7681,
  (GameEngineMethod)sub_4B84E6,
  (GameEngineMethod)sub_4B858A,
  (GameEngineMethod)sub_4B7D8E,
  (GameEngineMethod)sub_4B8244,
  (GameEngineMethod)sub_4B7E37,
  (GameEngineMethod)sub_4B832B,
  (GameEngineMethod)sub_4B7F6F,
  (GameEngineMethod)sub_4B7A30,
  (GameEngineMethod)sub_4B79BF,
  (GameEngineMethod)sub_4B7141,
  (GameEngineMethod)sub_4B7ED3,
  (GameEngineMethod)sub_4B8404,
  (GameEngineMethod)sub_4B7A98,
  (GameEngineMethod)sub_4B78B0,
  (GameEngineMethod)sub_4B87F0,
  (GameEngineMethod)sub_4B86B2,
  (GameEngineMethod)sub_4B873F,
  (GameEngineMethod)sub_4B7A2F,
  (GameEngineMethod)sub_4B5842, /* update_game_state */
  (GameEngineMethod)sub_4B7BBC,
  (GameEngineMethod)sub_570FD0,
  (GameEngineMethod)sub_566640,
  (GameEngineMethod)sub_4B7BC8,
  (GameEngineMethod)sub_4B6303,
  (GameEngineMethod)sub_4B636C,
  (GameEngineMethod)sub_4B5926,
  (GameEngineMethod)sub_570330,
  (GameEngineMethod)sub_570490,
  (GameEngineMethod)sub_570580,
  (GameEngineMethod)sub_4B7D82,
  (GameEngineMethod)sub_4B5D4D
};

_Static_assert(sizeof(game_engine_vtable) / sizeof(game_engine_vtable[0]) == 47,
               "game-engine vtable slot count");
_Static_assert(sizeof(GameEngineMethod) == sizeof(uint32_t),
               "game-engine vtable requires 32-bit function pointers");
extern uint32_t g_engine_type_descriptor[15]; /* dword_771608: "GEngine". */
extern uint32_t g_engine_vtable[]; /* off_6F18F4. */
extern uint32_t engine_object_collection_vtable[]; /* off_6F19B0. */
extern uint32_t *__thiscall initialize_display_options(uint32_t *options);
extern int16_t *__thiscall capture_display_mode_state(int16_t *state,
                                                      uint16_t width,
                                                      uint16_t height);
/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *event_target);
/* gk3/GK3R_rest.c: 0x403039, MSVC std::string::_Tidy(char). */
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern DWORD __stdcall timeGetTime(void);

/* gk3/GK3R_rest.c: shared rectangle values used to seed window geometry. */
extern int dword_7739C8;
extern int dword_7739CC;
extern int dword_7739D0;
extern int dword_7739D4;
/* platform/window_geometry.c */
extern int zero_point_x;
extern int zero_point_y;

/* engine/dynamic_array.c */
extern void *__thiscall initialize_16_byte_vector(void *vector);
extern int __thiscall destroy_object_vector(int *collection);
extern int __thiscall free_vector_storage(int *collection);
extern int __thiscall set_vector_element(uint32_t *collection, int index,
                                        int value);
extern int __thiscall vector_element_address(uint32_t *collection, int index);
extern int __thiscall insert_repeated_array_value(int *cookie, uint32_t *entries, int add,
                                  uint32_t *entry_id);
extern int __thiscall free_dynamic_array_storage(int *array);
extern int __thiscall vector_element_value(uint32_t *collection, int index);
extern void __stdcall destroy_trivial_array_elements(uint32_t begin,
                                                      uint32_t end);

/* engine/registry.c */
extern ObjectRegistration *__thiscall find_or_create_registry_entry(
    uint32_t *registry, unsigned int address);
extern int initialize_event_registry(void);
extern void *unregister_event_registry(void);

/* platform/cd_monitor.c */
extern char *__thiscall construct_cd_monitor(char *memory);

/* engine/sound_manager.c */
extern int __thiscall construct_sound_manager(int address);
extern int __thiscall resume_sound_by_id(int *manager, int item);
extern void __thiscall pause_sounds_matching(
    char **items, uint8_t (__cdecl *predicate)(uint32_t), int context);
extern int __thiscall remove_sounds_matching(
    int *items, uint8_t (__cdecl *predicate)(uint32_t), int context,
    char flag);

/* gk3/graphics_resources.c */
extern int __thiscall release_graphics_resources(uint32_t *engine);
/* gk3/graphics_resources.c */
extern int __thiscall initialize_graphics_resources(uint32_t *engine);

/* gk3/graphics_resources.c */
extern void __thiscall apply_gamma_ramp(float *controller, float gamma,
                                        float force);

/* platform/message_loop.c */
extern char __cdecl pump_game_messages(HWND window, WPARAM *exit_code);

/* engine/engine_clock.c */
extern int __thiscall pause_engine_clock(uint32_t *engine);
extern int __thiscall resume_engine_clock(uint32_t *engine);
extern uint32_t __thiscall set_previous_frame_time(uint32_t *engine,
                                                   uint32_t time);

/* engine/engine_logging.c */
extern int report_engine_message(int engine_address, const char *format, ...);

/* engine/game_engine.c */
extern int __thiscall get_engine_object_by_id(uint32_t *engine,
                                               uint16_t resource_id);
extern int __thiscall release_engine_object_by_id(uint32_t *engine,
                                                   uint16_t resource_id);

/* engine/game_frame.c */
extern int frame_number;
/* engine/engine_logging.c */
extern int log_engine_message(int engine_address, const char *format, ...);

/* engine/game_engine.c */
extern void __thiscall pause_game_engine_with_gdi_surface(void *engine);
extern char *get_mouse_cursor_worker_manager(void);
extern char __cdecl collect_pause_cookie_sound(int first, int *second);
extern int __thiscall invoke_graphics_resource_method_by_id(uint32_t *engine, uint16_t object_id);

/* gk3/GK3R_rest.c */
extern int accelerator_resource_id;
extern int game_engine_address;
extern char mouse_cursor_worker_manager_storage[];
extern char mouse_cursor_worker_manager_initialization_flags;
extern char painter_registration_initialized;
extern uint32_t painter_type_descriptor[15];
extern int active_painter_address;
extern char *__thiscall construct_mouse_cursor_worker_manager(char *memory);
extern void __cdecl unknown_libname_237(void);
extern uint8_t __thiscall is_sound_paused_by_id(int *manager, int sound_id);
extern void __thiscall sub_587E80(int resource_address, int value);
extern int sub_6A3260(void);
extern int file_manager_address; /* Shared FileManager object pointer. */
extern uint32_t sound_manager_registry[15];
extern HACCEL hAccTable;
extern int fullscreen_flag_address;
extern int direct_draw_address;
extern int direct_draw4_address;
extern int primary_surface_address;
extern int screen_surface_address;
extern int secondary_screen_surface_address;
extern int z_buffer_surface_address;
extern int direct3d_interface_address;
extern int dword_771644; /* Default GEngine render flags. */
/* gk3/GK3R_rest.c: remaining DirectDraw/Direct3D state pointers. */
extern int dword_773664;
extern int dword_773668;
extern int dword_77366C;
extern int dword_773674;
extern int dword_773678;

/* gk3/GK3R_rest.c: global resource-cache storage */
extern int dword_777274; /* 16-bit cache buffer begin. */
extern int dword_777278; /* 16-bit cache buffer end. */
extern int dword_77727C; /* 16-bit cache buffer capacity. */
extern char byte_777CC8; /* Header for the fourth global resource buffer. */
extern int dword_777CCC;
extern int dword_777CD0;
extern int dword_777CD4;
extern int dword_777CDC;
extern int dword_777CE0;
extern int dword_777CE4;
extern int dword_777CEC;
extern int dword_777CF0;
extern int dword_777CF4;
extern int dword_777CFC;
extern int dword_777D00;
extern int dword_777D04;

typedef void (__thiscall *EngineSetupMethod)(uint32_t *engine);
typedef void (__thiscall *EnginePauseMethod)(int engine);
typedef void (__thiscall *EngineResumeMethod)(int engine);
typedef void (__thiscall *EngineDestructorMethod)(uint32_t *engine,
                                                  int free_memory);
typedef void (__thiscall *EngineLifecycleMethod)(uint32_t *engine);
typedef void (__thiscall *ResourceShutdownMethod)(uint32_t *resource);
typedef void (__thiscall *ResourceDestructorMethod)(uint32_t *resource,
                                                    int free_memory);
typedef int (__thiscall *ResourceCommandMethod)(uint32_t *resource,
                                                 int command, int value);
typedef int (__thiscall *ResourceReleaseMethod)(int resource);
typedef void (__stdcall *FlipToGdiSurfaceMethod)(int direct_draw);

/* engine/game_engine.c */
extern int __thiscall release_game_engine_resources(uint32_t *engine);

/* platform/window_proc.c */
extern int __thiscall destroy_message_hook_list(int *message_hooks);

/* common/memory.c */
extern void __cdecl free_tracked_memory(int address);

typedef struct {
  uint8_t instance_byte;
  uint8_t reserved[3];
  uint32_t list_head;
  uint32_t count;
} MessageHooks;

typedef struct {
  uint32_t next;
  uint32_t previous;
  uint32_t reserved[3];
} MessageHookListHead;

typedef struct {
  uint32_t methods;
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
  int32_t x;
  int32_t y;
} EnginePoint;

typedef struct {
  RECT outer_window_bounds;
  RECT viewport_bounds;
  POINT client_area_origin;
  POINT coordinate_origin;
} EngineWindowGeometry;

typedef struct {
  float x;
  float y;
  float z;
} EngineVector3;

typedef struct {
  uint32_t methods;
  uint32_t reserved[3];
  float current_gamma;
} GammaRampController;

typedef struct {
  uint32_t words[4];
} EngineStringStorage;

typedef struct {
  uint32_t methods;
  uint32_t reserved_before_instance[2];
  uint32_t instance;
  uint32_t window;
  uint32_t command_line;
  uint32_t shutdown_object_ids[4];
  EngineWindowGeometry window_geometry;
  uint32_t handling_fatal_error;
  uint32_t reserved_before_paused[2];
  uint32_t paused;
  uint8_t reserved_before_renderer_mode_flag[5];
  uint8_t uses_non_software_renderer;
  uint8_t reserved_before_initialized[94];
  uint32_t initialized;
  uint32_t reserved_before_sound_manager;
  uint32_t sound_manager;
  uint32_t reserved_before_cd_monitor[15];
  uint32_t cd_monitor;
  uint32_t gamma_ramp_controller;
  EngineObjectCollection object_collections[7];
  uint32_t pause_cookie;
  uint32_t camera;
  int32_t frame_rate;
  EngineEventQueue events;
  EnginePoint viewport_origin;
  EngineVector3 light_position;
  EngineVector3 shadow_light_position;
  uint32_t shadow_type;
  uint32_t shadow_texture;
  uint32_t reserved_before_render_flags[2];
  uint32_t render_flags;
  char error_log_path[260];
  char log_path[260];
  uint8_t used_default_resource;
  uint8_t reserved_before_clock_fields[3];
  uint32_t previous_frame_time;
  uint32_t time_offset;
  uint32_t time_freeze_time;
  uint8_t reserved_before_gamma_ramp_refresh[9];
  uint8_t gamma_ramp_refresh_enabled;
  uint8_t reserved_after_gamma_ramp_refresh[2];
  uint32_t message_hooks;
  uint32_t startup_flags;
  uint32_t reserved_before_application[1];
  uint32_t application;
  char language_code[2];
  SYSTEMTIME startup_time;
  uint8_t ignore_scene_changed;
  uint8_t reserved_before_startup_strings;
  EngineStringStorage startup_sheep;
  EngineStringStorage startup_arguments;
  uint32_t reserved_before_base_system_time[3];
  uint32_t base_system_time;
  uint32_t time_multiplier_words[2];
  uint32_t reserved_before_startup_state[3];
  uint32_t startup_state[10];
  uint8_t region_state_storage[96];
  uint8_t reserved_before_mouse_smoothing[53];
  uint8_t mouse_smoothing_enabled;
  uint8_t mouse_smoothing_allowed;
  uint8_t reserved_after_mouse_smoothing[17];
} GameEngine;

_Static_assert(sizeof(MessageHooks) == 12, "message hooks size");
_Static_assert(sizeof(MessageHookListHead) == 20, "message hook list head size");
_Static_assert(sizeof(ObjectRegistration) == 12, "object registration size");
_Static_assert(sizeof(EngineStringStorage) == 16, "engine string storage size");
_Static_assert(sizeof(EngineObjectCollection) == 24,
               "object collection size");
_Static_assert(offsetof(EngineObjectCollection, data) == 4,
               "object collection data offset");
_Static_assert(offsetof(EngineObjectCollection, count) == 8,
               "object collection count offset");
_Static_assert(offsetof(GammaRampController, current_gamma) == 16,
               "current gamma field offset");
_Static_assert(sizeof(EngineWindowGeometry) == 48, "window geometry size");
_Static_assert(sizeof(SYSTEMTIME) == 16, "system time size");
_Static_assert(sizeof(GameEngine) == 1392, "game engine size");
_Static_assert(offsetof(GameEngine, instance) == 12, "instance offset");
_Static_assert(offsetof(GameEngine, window) == 16, "window offset");
_Static_assert(offsetof(GameEngine, command_line) == 20, "command line offset");
_Static_assert(offsetof(GameEngine, shutdown_object_ids) == 24,
               "shutdown object IDs offset");
_Static_assert(offsetof(GameEngine, window_geometry) == 40,
               "window geometry offset");
_Static_assert(offsetof(GameEngine, handling_fatal_error) == 88, "fatal error offset");
_Static_assert(offsetof(GameEngine, paused) == 100, "paused offset");
_Static_assert(offsetof(GameEngine, uses_non_software_renderer) == 109,
               "renderer mode flag offset");
_Static_assert(offsetof(GameEngine, initialized) == 204, "initialized offset");
_Static_assert(offsetof(GameEngine, sound_manager) == 212, "sound manager offset");
_Static_assert(offsetof(GameEngine, cd_monitor) == 276, "CD monitor offset");
_Static_assert(offsetof(GameEngine, gamma_ramp_controller) == 280,
               "gamma ramp controller offset");
_Static_assert(offsetof(GameEngine, object_collections) == 284,
               "object collection array offset");
_Static_assert(offsetof(GameEngine, pause_cookie) == 452, "pause cookie offset");
_Static_assert(offsetof(GameEngine, events) == 464, "event queue offset");
_Static_assert(offsetof(GameEngine, render_flags) == 528, "render flags offset");
_Static_assert(offsetof(GameEngine, used_default_resource) == 1052,
               "default resource flag offset");
_Static_assert(offsetof(GameEngine, previous_frame_time) == 1056,
               "previous frame time offset");
_Static_assert(offsetof(GameEngine, gamma_ramp_refresh_enabled) == 1077,
               "gamma ramp refresh flag offset");
_Static_assert(offsetof(GameEngine, message_hooks) == 1080, "message hooks offset");
_Static_assert(offsetof(GameEngine, startup_flags) == 1084, "startup flags offset");
_Static_assert(offsetof(GameEngine, application) == 1092, "application offset");
_Static_assert(offsetof(GameEngine, startup_time) == 1098, "startup time offset");
_Static_assert(offsetof(GameEngine, startup_sheep) == 1116, "startup sheep offset");
_Static_assert(offsetof(GameEngine, base_system_time) == 1160,
               "base system time offset");
_Static_assert(offsetof(GameEngine, mouse_smoothing_enabled) == 1373,
               "mouse smoothing offset");

enum {
  ENGINE_SPRITE_COLLECTION = 0,
  ENGINE_TEXTURE_COLLECTION = 1,
  ENGINE_BITMAP_COLLECTION = 2,
  ENGINE_MODEL_COLLECTION = 3,
  ENGINE_ANIMATION_COLLECTION = 4,
  ENGINE_UNCLASSIFIED_COLLECTION = 5,
  ENGINE_SCENE_COLLECTION = 6,
  ENGINE_SETUP_METHOD_SLOT = 100 / 4,
  ENGINE_FINAL_SETUP_METHOD_SLOT = 56 / 4,
  ENGINE_PAUSE_METHOD_SLOT = 92 / 4,
  ENGINE_RESUME_METHOD_SLOT = 112 / 4,
  ENGINE_POST_RESUME_METHOD_SLOT = 52 / 4,
  ENGINE_PRE_SHUTDOWN_METHOD_SLOT = 116 / 4,
  ENGINE_SHUTDOWN_METHOD_SLOT = 96 / 4,
  SOUND_MANAGER_SHUTDOWN_METHOD_SLOT = 28 / 4,
  SOUND_MANAGER_DESTRUCTOR_METHOD_SLOT = 16 / 4,
  DIRECT_DRAW_FLIP_TO_GDI_SLOT = 40 / 4
};

uint32_t *__cdecl allocate_registered_game_engine(int size);
char *__thiscall construct_game_engine(char *engine, int command_line);
int __thiscall initialize_game_engine_fields(int engine_address)
{
  GameEngine *engine =
      (GameEngine *)(uintptr_t)(uint32_t)engine_address;
  uint8_t *engine_bytes = (uint8_t *)(void *)engine;

  /* The export reads v5 from uninitialized stack storage; omit those writes. */
  construct_registered_event_target((uint16_t *)(void *)engine);
  find_or_create_registry_entry(
      g_engine_type_descriptor, (uint32_t)(uintptr_t)engine);
  memset(engine->shutdown_object_ids, 0, sizeof(engine->shutdown_object_ids));

  initialize_display_options((uint32_t *)(void *)(engine_bytes + 112));

  *(uint32_t *)(void *)(engine_bytes + 160) = 0;
  *(uint32_t *)(void *)(engine_bytes + 164) = 0;
  *(uint32_t *)(void *)(engine_bytes + 168) = 0;
  engine_bytes[172] = 0;
  *(uint32_t *)(void *)(engine_bytes + 176) = UINT32_MAX;
  *(uint32_t *)(void *)(engine_bytes + 184) = 0;
  *(uint32_t *)(void *)(engine_bytes + 188) = 0;
  *(uint32_t *)(void *)(engine_bytes + 192) = 0;
  engine_bytes[196] = 0;
  *(uint32_t *)(void *)(engine_bytes + 200) = UINT32_MAX;

  capture_display_mode_state(
      (int16_t *)(void *)(engine_bytes + 216), 0x0F00u, 0x0C00u);
  tidy_std_string_storage((char *)(void *)(engine_bytes + 220), 0);
  *(uint32_t *)(void *)(engine_bytes + 244) = 0;
  *(uint32_t *)(void *)(engine_bytes + 248) = 0;
  *(uint32_t *)(void *)(engine_bytes + 252) = 0;
  *(uint32_t *)(void *)(engine_bytes + 260) = 0;
  *(uint32_t *)(void *)(engine_bytes + 264) = 0;
  *(uint32_t *)(void *)(engine_bytes + 268) = 0;

  for (int index = 0; index <= ENGINE_SCENE_COLLECTION; ++index) {
    EngineObjectCollection *collection = &engine->object_collections[index];
    collection->methods =
        (uint32_t)(uintptr_t)engine_object_collection_vtable;
    collection->data = 0;
    collection->count = 0;
    collection->reserved_after_count[0] = 0;
    collection->reserved_after_count[1] = 20;
    collection->reserved_after_count[2] = 0;
  }

  engine->events.begin = 0;
  engine->events.end = 0;
  engine->events.capacity = 0;
  engine->shadow_texture = 0;
  engine->methods = (uint32_t)(uintptr_t)g_engine_vtable;

  engine->instance = 0;
  engine->window = 0;
  engine->command_line = 0;
  engine->window_geometry.outer_window_bounds = (RECT){
      dword_7739C8, dword_7739CC, dword_7739D0, dword_7739D4};
  engine->window_geometry.viewport_bounds = (RECT){
      dword_7739C8, dword_7739CC, dword_7739D0, dword_7739D4};
  engine->window_geometry.client_area_origin =
      (POINT){zero_point_x, zero_point_y};
  engine->window_geometry.coordinate_origin =
      (POINT){zero_point_x, zero_point_y};
  engine->handling_fatal_error = 0;
  engine->reserved_before_paused[0] = 0;
  engine->reserved_before_paused[1] = 0;
  engine->paused = 0;
  memset(engine_bytes + 104, 0, 4);
  *(uint32_t *)(void *)(engine_bytes + 148) = 0;
  *(uint32_t *)(void *)(engine_bytes + 152) = 0;
  engine->initialized = 0;
  *(uint32_t *)(void *)(engine_bytes + 208) = timeGetTime();
  engine->sound_manager = 0;
  engine->reserved_before_cd_monitor[14] = 0;
  engine->cd_monitor = 0;
  engine->gamma_ramp_controller = 0;

  engine->pause_cookie = 0;
  engine->camera = 0;
  engine->frame_rate = 67;
  engine->viewport_origin = (EnginePoint){zero_point_x, zero_point_y};
  engine->light_position = (EngineVector3){10.0f, 10.0f, 10.0f};
  engine->shadow_type = 0;
  engine->shadow_light_position = (EngineVector3){10.0f, 10.0f, 10.0f};
  engine->shadow_texture = 0;
  engine->reserved_before_render_flags[0] = 0;
  engine->reserved_before_render_flags[1] = 0;
  engine->render_flags = (uint32_t)dword_771644;
  engine->used_default_resource = 0;
  engine->previous_frame_time = 0;
  engine->time_offset = 43200000;
  engine->time_freeze_time = 0;
  engine->message_hooks = 0;
  engine->gamma_ramp_refresh_enabled = 0;

  direct_draw_address = 0;
  direct_draw4_address = 0;
  primary_surface_address = 0;
  screen_surface_address = 0;
  secondary_screen_surface_address = 0;
  z_buffer_surface_address = 0;
  dword_773664 = 0;
  dword_773668 = 0;
  dword_77366C = 0;
  direct3d_interface_address = 0;
  dword_773674 = 0;
  dword_773678 = 0;

  strcpy(engine->error_log_path, "c:\\error.txt");
  strcpy(engine->log_path, "c:\\log.txt");
  return engine_address;
}

char *__cdecl create_game_engine(int command_line)
{
  char *engine = (char *)allocate_registered_game_engine(sizeof(GameEngine));
  return engine ? construct_game_engine(engine, command_line) : NULL;
}

uint32_t *__cdecl allocate_registered_game_engine(int size)
{
  uint32_t *engine = allocate_tracked_memory(size);
  ObjectRegistration *registration = find_or_create_registry_entry(
      game_engine_type_descriptor, (uint32_t)(uintptr_t)engine);
  registration->category = 3;
  return engine;
}

char *__thiscall construct_game_engine(char *engine, int command_line)
{
  (void)command_line;
  initialize_game_engine_fields((int)(intptr_t)engine);
  find_or_create_registry_entry(
      game_engine_type_descriptor,
      (uint32_t)(uintptr_t)(engine + game_engine_base_offset_adjustment + 1084));

  initialize_16_byte_vector(engine + 1116);
  initialize_16_byte_vector(engine + 1132);
  for (int index = 0; index < 3; ++index) {
    initialize_16_byte_vector(engine + 1224 + index * 16);
    initialize_16_byte_vector(engine + 1272 + index * 16);
  }

  *(uint32_t *)engine = (uint32_t)(uintptr_t)game_engine_vtable;
  return engine;
}

int __thiscall reset_and_clear_engine_collection(int *engine_words, int value)
{
  GameEngine *engine = (GameEngine *)engine_words;
  EngineObjectCollection *collection =
      &engine->object_collections[ENGINE_UNCLASSIFIED_COLLECTION];
  for (int index = 0; index < collection->count; ++index) {
    const int object = *(int *)(uintptr_t)vector_element_address(
        (uint32_t *)(void *)collection, index);
    if (object)
      sub_587E80(object, value);
  }
  return destroy_object_vector((int *)(void *)collection);
}

int __thiscall broadcast_resource_command(uint32_t *engine_words,
                                          int command, int value)
{
  GameEngine *engine = (GameEngine *)engine_words;
  EngineObjectCollection *collection =
      &engine->object_collections[ENGINE_ANIMATION_COLLECTION];
  int result = collection->count;

  for (int index = 0; index < collection->count; ++index) {
    const int object = *(int *)(uintptr_t)vector_element_address(
        (uint32_t *)(void *)collection, index);
    if (!object || (*(uint8_t *)(uintptr_t)(object + 48) & 0x20) != 0)
      continue;

    uint32_t *methods = *(uint32_t **)(uintptr_t)object;
    const ResourceCommandMethod send_command =
        (ResourceCommandMethod)(uintptr_t)methods[52 / sizeof(uint32_t)];
    result = send_command((uint32_t *)(uintptr_t)object, command, value);
  }
  return result;
}

void release_engine_global_resources(void)
{
  destroy_trivial_array_elements((uint32_t)dword_777CFC,
                                 (uint32_t)dword_777D00);
  free_tracked_memory(dword_777CFC);
  dword_777CFC = 0;
  dword_777D00 = 0;
  dword_777D04 = 0;

  destroy_trivial_array_elements((uint32_t)dword_777CEC,
                                 (uint32_t)dword_777CF0);
  free_tracked_memory(dword_777CEC);
  dword_777CEC = 0;
  dword_777CF0 = 0;
  dword_777CF4 = 0;

  destroy_trivial_array_elements((uint32_t)dword_777CDC,
                                 (uint32_t)dword_777CE0);
  free_tracked_memory(dword_777CDC);
  dword_777CDC = 0;
  dword_777CE0 = 0;
  dword_777CE4 = 0;

  destroy_trivial_array_elements((uint32_t)dword_777CCC,
                                 (uint32_t)dword_777CD0);
  free_dynamic_array_storage((int *)(void *)&byte_777CC8);
}

void clear_global_engine_caches(void)
{
  sub_6A3260();
  dword_777278 = dword_777274;
  free_tracked_memory(dword_777274);
  dword_777274 = 0;
  dword_777278 = 0;
  dword_77727C = 0;
}

int __thiscall release_game_engine_resources(uint32_t *engine_words)
{
  GameEngine *engine = (GameEngine *)engine_words;
  int this = (int)(intptr_t)engine_words;
  int v2 = 0;
  EngineObjectCollection *animation_collection =
      &engine->object_collections[ENGINE_ANIMATION_COLLECTION];
  void (__thiscall ***v3)(_DWORD, int) =
      (void (__thiscall ***)(_DWORD, int))(uintptr_t)engine->pause_cookie;
  if (v3)
    (**v3)(v3, 1);
  engine->pause_cookie = 0;
  free_tracked_memory((int)engine->gamma_ramp_controller);
  engine->gamma_ramp_controller = 0;
  char *cursor_manager = get_mouse_cursor_worker_manager();
  shutdown_mouse_cursor_worker_manager((int)cursor_manager);
  if (engine->shutdown_object_ids[2]) {
    release_engine_object_by_id(engine_words,
                                (uint16_t)engine->shutdown_object_ids[2]);
  }
  if (engine->shutdown_object_ids[0]) {
    release_engine_object_by_id(engine_words,
                                (uint16_t)engine->shutdown_object_ids[0]);
  }
  if (engine->shutdown_object_ids[1]) {
    release_engine_object_by_id(engine_words,
                                (uint16_t)engine->shutdown_object_ids[1]);
  }
  if (engine->shutdown_object_ids[3]) {
    release_engine_object_by_id(engine_words,
                                (uint16_t)engine->shutdown_object_ids[3]);
  }
  reset_and_clear_engine_collection((int *)this, 0);
  broadcast_resource_command(engine_words, 0xFFFF, 0);
  engine->handling_fatal_error = 1;
  void (__thiscall ***v9)(_DWORD, int) =
      (void (__thiscall ***)(_DWORD, int))(uintptr_t)engine->camera;
  if (v9)
    (**v9)(v9, 1);
  engine->camera = 0;
  if (*(_BYTE *)(this + 110))
    release_engine_global_resources();
  else
    clear_global_engine_caches();
  free_tracked_memory(*(_DWORD *)(this + 148));
  *(_DWORD *)(this + 148) = 0;
  destroy_object_vector((int *)(void *)&engine->object_collections[
      ENGINE_UNCLASSIFIED_COLLECTION]);
  if (animation_collection->count > 0) {
    do {
      while (*(_DWORD *)vector_element_address(
          (uint32_t *)(void *)animation_collection, v2)) {
        int object = *(_DWORD *)vector_element_address(
            (uint32_t *)(void *)animation_collection, v2);
        if (*(int *)(object + 40) <= 0)
          break;
        uint32_t *methods = *(uint32_t **)(uintptr_t)object;
        ((ResourceShutdownMethod)(uintptr_t)methods[16 / 4])(
            (uint32_t *)(uintptr_t)object);
      }
      ++v2;
    } while (v2 < animation_collection->count);
  }
  int elapsed_start = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  int animation_count = animation_collection->count;
  destroy_object_vector((int *)(void *)animation_collection);
  unsigned int elapsed = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  char output[100];
  sprintf(output, "%8d MS deleting %d anims\n",
          elapsed - elapsed_start, animation_count);
  OutputDebugStringA(output);

  EngineObjectCollection *model_collection =
      &engine->object_collections[ENGINE_MODEL_COLLECTION];
  int model_count = model_collection->count;
  destroy_object_vector((int *)(void *)model_collection);
  int now = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d models\n", now - elapsed, model_count);
  elapsed = now;
  OutputDebugStringA(output);

  EngineObjectCollection *scene_collection =
      &engine->object_collections[ENGINE_SCENE_COLLECTION];
  int scene_count = scene_collection->count;
  destroy_object_vector((int *)(void *)scene_collection);
  now = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d scenes\n", now - elapsed, scene_count);
  elapsed = now;
  OutputDebugStringA(output);

  EngineObjectCollection *sprite_collection =
      &engine->object_collections[ENGINE_SPRITE_COLLECTION];
  int sprite_count = sprite_collection->count;
  destroy_object_vector((int *)(void *)sprite_collection);
  now = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d sprites\n", now - elapsed, sprite_count);
  elapsed = now;
  OutputDebugStringA(output);

  EngineObjectCollection *bitmap_collection =
      &engine->object_collections[ENGINE_BITMAP_COLLECTION];
  int bitmap_count = bitmap_collection->count;
  destroy_object_vector((int *)(void *)bitmap_collection);
  now = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d bitmap8\n", now - elapsed, bitmap_count);
  elapsed = now;
  OutputDebugStringA(output);

  EngineObjectCollection *texture_collection =
      &engine->object_collections[ENGINE_TEXTURE_COLLECTION];
  int texture_count = texture_collection->count;
  int deleted_single_textures = 0;
  for (uint32_t index = 0; index < (uint32_t)texture_count; ++index) {
    int object = *(_DWORD *)vector_element_address(
        (uint32_t *)(void *)texture_collection, (int)index);
    if (object && *(int *)(object + 60) <= 1) {
      ++deleted_single_textures;
      uint32_t *methods = *(uint32_t **)(uintptr_t)object;
      ((ResourceDestructorMethod)(uintptr_t)methods[0])(
          (uint32_t *)(uintptr_t)object, 1);
      set_vector_element((uint32_t *)(void *)texture_collection,
                         (int)index, 0);
    }
  }
  int texture_start = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d textures\n",
          texture_start - elapsed, deleted_single_textures);
  OutputDebugStringA(output);

  int deleted_shared_textures = 0;
  int shared_texture_references = 0;
  for (uint32_t index = 0; index < (uint32_t)texture_collection->count;
       ++index) {
    int object = *(_DWORD *)vector_element_address(
        (uint32_t *)(void *)texture_collection, (int)index);
    if (!object || *(int *)(object + 60) <= 1)
      continue;

    ++deleted_shared_textures;
    if (*(_WORD *)(object + 6) == 0) {
      uint32_t *methods = *(uint32_t **)(uintptr_t)object;
      ((ResourceShutdownMethod)(uintptr_t)methods[4 / 4])(
          (uint32_t *)(uintptr_t)object);
    }
    shared_texture_references += *(int *)(object + 60);
    *(_DWORD *)(object + 44) = frame_number;
    uint32_t *methods = *(uint32_t **)(uintptr_t)object;
    ((ResourceDestructorMethod)(uintptr_t)methods[0])(
        (uint32_t *)(uintptr_t)object, 1);
    set_vector_element((uint32_t *)(void *)texture_collection,
                       (int)index, 0);
  }
  now = (*(int (__thiscall **)(int))
      (*(uint32_t *)(uintptr_t)game_engine_address + 24))(game_engine_address);
  sprintf(output, "%8d MS deleting %d/%d multi textures\n",
          now - texture_start, deleted_shared_textures,
          shared_texture_references);
  OutputDebugStringA(output);
  free_vector_storage((int *)(void *)texture_collection);
  return release_graphics_resources(engine_words);
}

static void shutdown_game_engine(uint32_t *engine_words)
{
  GameEngine *engine = (GameEngine *)engine_words;
  pause_game_engine_with_gdi_surface(engine_words);

  uint32_t *engine_methods = (uint32_t *)(uintptr_t)engine->methods;
  ((EngineLifecycleMethod)(uintptr_t)engine_methods[ENGINE_PRE_SHUTDOWN_METHOD_SLOT])(
      engine_words);
  release_game_engine_resources(engine_words);

  uint32_t sound_manager_address = engine->sound_manager;
  if (sound_manager_address) {
    uint32_t *sound_manager =
        (uint32_t *)(uintptr_t)sound_manager_address;
    uint32_t *sound_manager_methods =
        (uint32_t *)(uintptr_t)sound_manager[0];
    ((ResourceShutdownMethod)(uintptr_t)
        sound_manager_methods[SOUND_MANAGER_SHUTDOWN_METHOD_SLOT])(
            sound_manager);

    sound_manager_address = engine->sound_manager;
    if (sound_manager_address) {
      sound_manager = (uint32_t *)(uintptr_t)sound_manager_address;
      sound_manager_methods = (uint32_t *)(uintptr_t)sound_manager[0];
      ((ResourceDestructorMethod)(uintptr_t)
          sound_manager_methods[SOUND_MANAGER_DESTRUCTOR_METHOD_SLOT])(
              sound_manager, 1);
    }
    engine->sound_manager = 0;
  }

  engine_methods = (uint32_t *)(uintptr_t)engine->methods;
  ((EngineLifecycleMethod)(uintptr_t)engine_methods[ENGINE_SHUTDOWN_METHOD_SLOT])(
      engine_words);

  uint32_t cd_monitor_address = engine->cd_monitor;
  if (cd_monitor_address) {
    uint32_t *cd_monitor = (uint32_t *)(uintptr_t)cd_monitor_address;
    uint32_t *cd_monitor_methods = (uint32_t *)(uintptr_t)cd_monitor[0];
    ((ResourceDestructorMethod)(uintptr_t)cd_monitor_methods[0])(
        cd_monitor, 1);
  }
  engine->cd_monitor = 0;

  uint32_t message_hooks_address = engine->message_hooks;
  if (message_hooks_address) {
    destroy_message_hook_list((int *)(uintptr_t)message_hooks_address);
    free_tracked_memory((int)message_hooks_address);
  }
  engine->message_hooks = 0;

  unregister_event_registry();
  CoUninitialize();
}

void destroy_game_engine(void)
{
  if (!game_engine_address)
    return;

  shutdown_game_engine((uint32_t *)(uintptr_t)game_engine_address);
  if (game_engine_address) {
    uint32_t *engine = (uint32_t *)(uintptr_t)game_engine_address;
    uint32_t *methods = (uint32_t *)(uintptr_t)engine[0];
    ((EngineDestructorMethod)(uintptr_t)methods[0])(engine, 1);
  }
}

int __thiscall get_engine_object_by_id(uint32_t *engine_words,
                                       uint16_t resource_id)
{
  GameEngine *engine = (GameEngine *)engine_words;
  EngineObjectCollection *resources = &engine->object_collections[0];
  return vector_element_value((uint32_t *)resources, resource_id);
}

int __thiscall release_engine_object_by_id(uint32_t *engine_words,
                                          uint16_t resource_id)
{
  int object = get_engine_object_by_id(engine_words, resource_id);
  uint32_t *methods = *(uint32_t **)(uintptr_t)object;
  ResourceReleaseMethod release =
      (ResourceReleaseMethod)(uintptr_t)methods[16 / 4];
  return release(object);
}

char __thiscall initialize_game_engine(uint32_t *engine_words, HWND window,
                                       HINSTANCE instance, int command_line)
{
  GameEngine *engine = (GameEngine *)engine_words;
  CoInitialize(NULL);
  engine->window = (uint32_t)(uintptr_t)window;
  engine->instance = (uint32_t)(uintptr_t)instance;
  engine->command_line = (uint32_t)command_line;
  initialize_event_registry();

  MessageHooks *message_hooks = (MessageHooks *)allocate_tracked_memory(sizeof(*message_hooks));
  if (message_hooks) {
    message_hooks->instance_byte = (uint8_t)((uintptr_t)instance >> 8);
    MessageHookListHead *head = (MessageHookListHead *)allocate_tracked_memory(sizeof(*head));
    head->next = (uint32_t)(uintptr_t)head;
    head->previous = (uint32_t)(uintptr_t)head;
    message_hooks->list_head = (uint32_t)(uintptr_t)head;
    message_hooks->count = 0;
  }
  engine->message_hooks = (uint32_t)(uintptr_t)message_hooks;

  char *cd_monitor_memory = (char *)allocate_tracked_memory(128);
  engine->cd_monitor = (uint32_t)(uintptr_t)(cd_monitor_memory
      ? construct_cd_monitor(cd_monitor_memory) : NULL);

  uint32_t *methods = (uint32_t *)(uintptr_t)engine->methods;
  ((EngineSetupMethod)(uintptr_t)methods[ENGINE_SETUP_METHOD_SLOT])(engine_words);

  uint32_t *sound_manager_memory = allocate_tracked_memory(148);
  ObjectRegistration *registration = find_or_create_registry_entry(
      sound_manager_registry, (unsigned int)(uintptr_t)sound_manager_memory);
  registration->category = 3;
  engine->sound_manager = sound_manager_memory
      ? (uint32_t)construct_sound_manager((int)(uintptr_t)sound_manager_memory) : 0;

  initialize_graphics_resources(engine_words);
  methods = (uint32_t *)(uintptr_t)engine->methods;
  ((EngineSetupMethod)(uintptr_t)methods[ENGINE_FINAL_SETUP_METHOD_SLOT])(engine_words);

  if (accelerator_resource_id)
    hAccTable = LoadAcceleratorsA(instance, MAKEINTRESOURCEA((uint16_t)accelerator_resource_id));

  WPARAM exit_code;
  char result = pump_game_messages(window, &exit_code);
  engine->initialized = 1;
  return result;
}

char *get_mouse_cursor_worker_manager(void)
{
  if (!painter_registration_initialized) {
    painter_registration_initialized = 1;
    ObjectRegistration *registration = find_or_create_registry_entry(
        painter_type_descriptor,
        (unsigned int)(uintptr_t)active_painter_address);
    registration->category = 3;
  }

  if ((mouse_cursor_worker_manager_initialization_flags & 1) == 0) {
    mouse_cursor_worker_manager_initialization_flags |= 1;
    construct_mouse_cursor_worker_manager(mouse_cursor_worker_manager_storage);
    atexit(unknown_libname_237);
  }

  return mouse_cursor_worker_manager_storage;
}

int __thiscall invoke_graphics_resource_method_by_id(
    uint32_t *engine, uint16_t object_id)
{
  const uint32_t resource_address =
      (uint32_t)get_engine_object_by_id(engine, object_id);
  const uint32_t methods_address =
      *(uint32_t *)(uintptr_t)resource_address;
  const uint32_t method_address =
      *(uint32_t *)(uintptr_t)(methods_address + 60);
  typedef int (__thiscall *GraphicsResourceMethod)(int resource);

  return ((GraphicsResourceMethod)(uintptr_t)method_address)(
      (int)resource_address);
}

char __cdecl collect_pause_cookie_sound(int sound_id, int *context)
{
  GameEngine *engine =
      (GameEngine *)(uintptr_t)(uint32_t)game_engine_address;
  int *sound_manager = (int *)(uintptr_t)engine->sound_manager;
  const uint32_t cookie_address = (uint32_t)context[0];
  const uint32_t methods_address =
      *(uint32_t *)(uintptr_t)cookie_address;
  const uint32_t match_method_address =
      *(uint32_t *)(uintptr_t)(methods_address + 8);
  typedef uint8_t (__thiscall *CookieSoundMatchMethod)(int cookie,
                                                       int sound_id);

  if (is_sound_paused_by_id(sound_manager, sound_id))
    return 0;
  if (!((CookieSoundMatchMethod)(uintptr_t)match_method_address)(
          (int)cookie_address, sound_id))
    return 0;

  int *sound_ids = (int *)(uintptr_t)(uint32_t)context[1];
  insert_repeated_array_value(
      sound_ids, (uint32_t *)(uintptr_t)(uint32_t)sound_ids[2], 1,
      (uint32_t *)&sound_id);
  return 1;
}

void __thiscall pause_resources_for_cookie(uint32_t *this, int *a2)
{
  char *v3; // edx
  char *v4; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  _DWORD v9[2]; // [esp+4h] [ebp-18h] BYREF
  char *v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h] BYREF
  _DWORD *v13; // [esp+18h] [ebp-4h]
  char *v14; // [esp+24h] [ebp+8h]

  v13 = this;
  if (a2)
  {
    v3 = (char *)this[96];
    v14 = v3;
    v4 = v3;
    v11 = &v3[4 * this[97]];
    if (v3 != v11)
    {
      while (1)
      {
        v5 = *(uint32_t *)v4;
        if (*(uint32_t *)v4)
        {
          if (*(uint16_t *)(v5 + 6))
          {
            v6 = *(uint32_t *)(v5 + 48);
            if ((v6 & 4) != 0 && (v6 & 0x21) == 0)
            {
              v7 = (int)(v4 - v3);
              v8 = *a2;
              v12 = (*(uint16_t *)(v5 + 4) << 16) | (uint16_t)(v7 >> 2);
              if ((*(uint8_t (__thiscall **)(int *, int))(v8 + 4))(a2, v12))
              {
                if (*((uint8_t *)a2 + 4))
                  (*(void (__thiscall **)(int, _DWORD, _DWORD))
                      (*(uint32_t *)v5 + 52))(v5, 0, 0);
                else
                  (*(void (__thiscall **)(int))(*(uint32_t *)v5 + 56))(v5);
                insert_repeated_array_value(a2 + 6, (uint32_t *)(uintptr_t)a2[8], 1,
                           (uint32_t *)&v12);
              }
            }
          }
        }
        v4 += 4;
        if (v4 == v11)
          break;
        v3 = v14;
      }
      this = v13;
    }
    if (this[53])
    {
      v9[0] = (uint32_t)(uintptr_t)a2;
      v9[1] = (uint32_t)(uintptr_t)(a2 + 2);
      if (*((uint8_t *)a2 + 4))
        remove_sounds_matching(*(int **)(game_engine_address + 212),
                   (uint8_t (__cdecl *)(uint32_t))collect_pause_cookie_sound,
                   (int)(uintptr_t)v9, 0);
      else
        pause_sounds_matching(*(char ***)(game_engine_address + 212),
                   (uint8_t (__cdecl *)(uint32_t))collect_pause_cookie_sound,
                   (int)(uintptr_t)v9);
      (*(void (__thiscall **)(_DWORD))(*(uint32_t *)v13[53] + 24))(v13[53]);
    }
  }
}

void __thiscall resume_resources_for_cookie(uint32_t *this, int *a2)
{
  _DWORD *v3; // ebx
  _DWORD *i; // edi
  int v5; // ebx
  int *v6; // ebx
  int *v7; // edi
  int v8; // eax
  int v9; // eax
  int *j; // [esp+10h] [ebp+8h]

  if (a2)
  {
    v3 = (_DWORD *)(uintptr_t)(uint32_t)a2[8];
    for (i = (_DWORD *)(uintptr_t)(uint32_t)a2[7]; i != v3; ++i)
    {
      if (*i && (*(uint8_t (__thiscall **)(int *, _DWORD))(*a2 + 12))(a2, *i))
        invoke_graphics_resource_method_by_id(this, (uint16_t)*i);
    }
    v5 = a2[7];
    destroy_trivial_array_elements((uint32_t)v5, (uint32_t)a2[8]);
    a2[8] = v5;
    free_dynamic_array_storage(a2 + 6);
    v6 = (int *)(uintptr_t)(uint32_t)a2[4];
    v7 = (int *)(uintptr_t)(uint32_t)a2[3];
    for (j = (int *)(uintptr_t)this[53]; v7 != v6; ++v7)
    {
      if (*v7)
      {
        if ((*(uint8_t (__thiscall **)(int *, int))(*a2 + 16))(a2, *v7))
          resume_sound_by_id(j, *v7);
      }
    }
    v8 = a2[3];
    a2[4] = v8;
    free_tracked_memory(v8);
    a2[3] = 0;
    a2[4] = 0;
    a2[5] = 0;
    v9 = (*(int (__thiscall **)(uint32_t *))(*(uint32_t *)this + 28))(this);
    set_previous_frame_time(this, (uint32_t)v9);
  }
}

void __thiscall adjust_mouse_cursor_activity_count(
    struct _RTL_CRITICAL_SECTION *this, char active)
{
  struct _RTL_CRITICAL_SECTION *lock = this + 4;
  if (lock[1].DebugInfo)
    EnterCriticalSection(lock);

  PRTL_CRITICAL_SECTION_DEBUG count = get_mouse_cursor_activity_state(this);
  set_mouse_cursor_activity_state(this, (PRTL_CRITICAL_SECTION_DEBUG)
                       ((char *)count + (active ? 1 : -1)));

  if (lock[1].DebugInfo)
    LeaveCriticalSection(lock);
}

int __thiscall shutdown_mouse_cursor_worker_manager(int manager_address)
{
  int result = 0;
  uint32_t *manager = (uint32_t *)(uintptr_t)manager_address;

  if (*(uint8_t *)manager) {
    *(uint8_t *)manager = 0;
    stop_mouse_cursor_worker_thread((HANDLE *)manager);
    if (manager[1])
      release_engine_object_by_id((uint32_t *)(uintptr_t)game_engine_address,
                                  (uint16_t)manager[1]);
    if (manager[2])
      result = release_engine_object_by_id(
          (uint32_t *)(uintptr_t)game_engine_address,
          (uint16_t)manager[2]);
    manager[1] = 0;
    manager[2] = 0;
  }
  return result;
}

HANDLE __thiscall stop_mouse_cursor_worker_thread(HANDLE *manager)
{
  HANDLE result = manager[16];
  if (result) {
    DWORD exit_code;
    SetEvent(manager[15]);
    ResumeThread(manager[16]);
    do {
      result = (HANDLE)GetExitCodeThread(manager[16], &exit_code);
      if (exit_code != STILL_ACTIVE)
        break;
      Sleep(0);
    } while (1);
  }
  manager[16] = 0;
  return result;
}

void __thiscall set_mouse_cursor_activity_state(
    struct _RTL_CRITICAL_SECTION *manager,
    struct _RTL_CRITICAL_SECTION_DEBUG *value)
{
  struct _RTL_CRITICAL_SECTION *lock = manager + 4;
  if (manager[5].DebugInfo)
    EnterCriticalSection(lock);

  const char was_active = (intptr_t)get_mouse_cursor_activity_state(manager) > 0;
  manager[2].DebugInfo = value;
  const char is_active = (intptr_t)get_mouse_cursor_activity_state(manager) > 0;
  if (was_active != is_active) {
    uint32_t *painter_methods =
        *(uint32_t **)(uintptr_t)active_painter_address;
    void (__thiscall *set_active)(int, struct _RTL_CRITICAL_SECTION_DEBUG *) =
        (void (__thiscall *)(int, struct _RTL_CRITICAL_SECTION_DEBUG *))
            (uintptr_t)painter_methods[12 / sizeof(uint32_t)];
    set_active(active_painter_address, (struct _RTL_CRITICAL_SECTION_DEBUG *)
                                      (uintptr_t)is_active);
  }

  if (lock[1].DebugInfo)
    LeaveCriticalSection(lock);
}

PRTL_CRITICAL_SECTION_DEBUG __thiscall get_mouse_cursor_activity_state(
    struct _RTL_CRITICAL_SECTION *manager)
{
  struct _RTL_CRITICAL_SECTION *lock = manager + 4;
  if (manager[5].DebugInfo)
    EnterCriticalSection(lock);

  PRTL_CRITICAL_SECTION_DEBUG value = manager[2].DebugInfo;
  if (lock[1].DebugInfo)
    LeaveCriticalSection(lock);
  return value;
}

void __thiscall pause_game_engine(int engine_address, char flip_to_gdi_surface)
{
  GameEngine *engine = (GameEngine *)(uintptr_t)engine_address;
  if (!engine || !engine->initialized || engine->paused)
    return;

  engine->paused = 1;
  pause_engine_clock((uint32_t *)engine);
  if (!engine->handling_fatal_error)
    pause_resources_for_cookie((uint32_t *)engine, (int *)(uintptr_t)engine->pause_cookie);

  if (*(const uint8_t *)(uintptr_t)fullscreen_flag_address
      && direct_draw_address && flip_to_gdi_surface) {
    uint32_t *direct_draw_methods = *(uint32_t **)(uintptr_t)direct_draw_address;
    ((FlipToGdiSurfaceMethod)(uintptr_t)
        direct_draw_methods[DIRECT_DRAW_FLIP_TO_GDI_SLOT])(direct_draw_address);
  }

  HWND window = (HWND)(uintptr_t)engine->window;
  DrawMenuBar(window);
  RedrawWindow(window, NULL, NULL, RDW_FRAME);

  if (!engine->handling_fatal_error) {
    uint32_t *methods = (uint32_t *)(uintptr_t)engine->methods;
    ((EnginePauseMethod)(uintptr_t)methods[ENGINE_PAUSE_METHOD_SLOT])(engine_address);
  }

  adjust_mouse_cursor_activity_count(get_mouse_cursor_worker_manager(), 0);
}

void __thiscall pause_game_engine_with_gdi_surface(void *engine)
{
  pause_game_engine((int)(uintptr_t)engine, 1);
}

void __thiscall resume_game_engine(int engine_address)
{
  GameEngine *engine = (GameEngine *)(uintptr_t)engine_address;
  if (!engine || !engine->initialized || engine->paused != 1)
    return;

  HWND active_window = GetActiveWindow();
  WINDOWPLACEMENT placement = {.length = sizeof(placement)};
  GetWindowPlacement((HWND)(uintptr_t)engine->window, &placement);
  if (!active_window || placement.showCmd == SW_SHOWMINIMIZED)
    return;

  engine->paused = 0;
  resume_engine_clock((uint32_t *)engine);
  adjust_mouse_cursor_activity_count(get_mouse_cursor_worker_manager(), 1);

  uint32_t *methods = (uint32_t *)(uintptr_t)engine->methods;
  if (!engine->handling_fatal_error) {
    resume_resources_for_cookie((uint32_t *)engine, (int *)(uintptr_t)engine->pause_cookie);
    ((EngineResumeMethod)(uintptr_t)methods[ENGINE_RESUME_METHOD_SLOT])(engine_address);
  }
  ((EngineResumeMethod)(uintptr_t)methods[ENGINE_POST_RESUME_METHOD_SLOT])(engine_address);
}

int __thiscall restore_lost_graphics_surfaces(int engine_address, char force)
{
  GameEngine *engine = (GameEngine *)(uintptr_t)(uint32_t)engine_address;
  const int surface_addresses[] = {
    primary_surface_address,
    screen_surface_address,
    secondary_screen_surface_address,
    z_buffer_surface_address
  };
  int restored_surface = 0;

  for (size_t index = 0;
       index < sizeof(surface_addresses) / sizeof(surface_addresses[0]);
       ++index) {
    const int surface_address = surface_addresses[index];
    if (!surface_address)
      continue;

    uint32_t *methods = *(uint32_t **)(uintptr_t)surface_address;
    typedef int (__stdcall *SurfaceIsLostMethod)(int surface);
    typedef int (__stdcall *SurfaceRestoreMethod)(int surface);
    const int surface_lost =
        ((SurfaceIsLostMethod)(uintptr_t)methods[96 / sizeof(uint32_t)])(
            surface_address);
    if (surface_lost == (int)0x887601C2u || force) {
      ((SurfaceRestoreMethod)(uintptr_t)methods[108 / sizeof(uint32_t)])(
          surface_address);
      restored_surface = 1;
    }
  }

  if (restored_surface && direct_draw4_address) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)direct_draw4_address;
    typedef int (__stdcall *RestoreAllSurfacesMethod)(int direct_draw4);
    ((RestoreAllSurfacesMethod)(uintptr_t)methods[100 / sizeof(uint32_t)])(
        direct_draw4_address);
  }

  if (engine->uses_non_software_renderer && force) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)direct3d_interface_address;
    typedef int (__stdcall *EvictManagedTexturesMethod)(int direct3d);
    ((EvictManagedTexturesMethod)(uintptr_t)methods[44 / sizeof(uint32_t)])(
        direct3d_interface_address);
  }

  const uint8_t *fullscreen_flag =
      (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (*fullscreen_flag) {
    HWND window = (HWND)(uintptr_t)engine->window;
    SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOSIZE | SWP_NOMOVE);
  }

  if (restored_surface && engine->gamma_ramp_refresh_enabled) {
    GammaRampController *gamma_ramp =
        (GammaRampController *)(uintptr_t)engine->gamma_ramp_controller;
    apply_gamma_ramp((float *)gamma_ramp, gamma_ramp->current_gamma, 1.0f);
  }

  return restored_surface;
}

int __thiscall report_missing_resource(GameEngine *engine,
                                       const char *resource_type,
                                       const char *resource_name)
{
  if (!engine->used_default_resource) {
    report_engine_message((int)(uintptr_t)engine,
               "%s '%s' not found. Other missing resources will be listed in the error log",
               resource_type, resource_name);
  }
  engine->used_default_resource = 1;
  return log_engine_message((int)(uintptr_t)engine, "%s '%s' not found.",
                            resource_type, resource_name);
}

int __stdcall set_global_file_manager(int file_manager)
{
  file_manager_address = file_manager;
  return file_manager;
}
