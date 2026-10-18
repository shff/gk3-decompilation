#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
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

uint32_t *__thiscall delete_game_engine_object(uint32_t *engine,
                                               int free_memory);
extern int __thiscall handle_cd_drive_list_change(int engine, int change);
extern int __thiscall update_timed_objects(uint32_t *engine, int elapsed);
extern int __thiscall cleanup_expired_engine_objects(uint32_t *engine,
                                                     unsigned int frame);
extern void __thiscall log_engine_message_v(int engine, char *format,
                                            va_list arguments);
extern FILE *__thiscall write_engine_log_message_v(const char *engine,
                                                    char *format,
                                                    va_list arguments);
extern DWORD __thiscall read_engine_clock(uint32_t *engine);
extern uint32_t __thiscall get_game_time(uint32_t *engine);
extern int __thiscall get_application_relative_time(void *engine);
extern BOOL __thiscall post_game_start_message(HWND *engine);
extern uint32_t *__thiscall validate_animation_notification(
    uint32_t *engine, int first, int second, const char *name);
extern void __stdcall dispatch_application_event(int application, int event);
void __thiscall empty_game_engine_callback(uint32_t *engine);
int *__thiscall refresh_resources_after_resume(uint32_t *engine);
uint32_t *__thiscall destroy_game_engine_instance(uint32_t *engine);
/* The original entry receives engine in ECX and context in EDI. */
extern int finalize_game_engine_initialization(int engine, int context);
extern int __thiscall apply_display_options_from_settings(uint32_t *engine);
extern void __thiscall set_input_event_state(uint32_t *engine, int state,
                                             int value);
extern void __thiscall clear_input_event_state(uint32_t *engine, int state,
                                               int value);
extern void __thiscall pointer_button_1_pressed(uint32_t *engine, int *point);
extern void __thiscall pointer_button_1_released(int engine, int *point);
extern void __thiscall pointer_button_2_pressed(int engine, int *point);
extern void __thiscall pointer_button_2_released(int *engine, int *point);
extern void __thiscall handle_pointer_movement(int engine, uint32_t *point);
extern void __thiscall pause_game_engine_callback(uint8_t *engine);
extern int __thiscall destroy_game_engine_members(uint32_t *engine);
extern int __thiscall initialize_game_engine_runtime(int engine);
extern void __thiscall pointer_button_3_pressed(int engine, int *point);
extern void __thiscall pointer_button_3_released(uint32_t *engine, int *point);
extern void __thiscall resume_game_engine_callback(uint8_t *engine);
extern int __thiscall prepare_game_engine_shutdown(int engine);
extern int __stdcall empty_engine_input_callback(int first, int second);
extern BOOL __thiscall set_pointer_input_state(uint32_t *engine, int state,
                                               int value);
extern BOOL __thiscall clear_pointer_input_state(uint32_t *engine, int state,
                                                 int value);
void __thiscall empty_game_engine_callback_2(uint32_t *engine);
extern int __thiscall update_game_state(void *engine, int time);
extern int __thiscall report_engine_error(void *engine, int error);
extern int __thiscall show_engine_message_box(HWND *engine, LPCSTR message,
                                              CHAR *caption, UINT flags);
extern int __thiscall report_out_of_memory(void *engine);
extern int __thiscall process_game_window_message(int engine,
                                                  unsigned int message,
                                                  uint16_t wparam, int lparam);
extern int __thiscall load_ambient_map_bitmap(uint32_t *engine, int mode,
                                              int resource, int target);
extern char __thiscall handle_scene_change(uint8_t *engine, int scene);
extern int __thiscall reset_game_engine_content(int *engine);
extern void __thiscall persist_resources_with_logging(int *engine,
                                                      float first,
                                                      float second);
extern int __thiscall persist_engine_resources(int engine, uint32_t *archive,
                                               int mode);
extern int __thiscall dispatch_engine_resource_persistence(void *engine,
                                                            int mode);
extern int __thiscall forward_engine_object_collection_notification(
    void *engine, int event);
extern void log_engine_diagnostic_message(int engine, char *format, ...);
extern int __thiscall notify_engine_object_collections(void *engine,
                                                       int event);
extern int report_engine_error(int engine, char *format, ...);
extern void *__thiscall load_display_options_from_settings(
    uint32_t **context, void *display_options);
extern DWORD __thiscall check_engine_shutdown_warning(uint32_t *engine);
extern int *__thiscall set_minimum_engine_render_skip_count(int *engine,
                                                            int value);
extern int __thiscall get_engine_input_state(uint32_t *engine, char value);
extern int __thiscall handle_engine_close_request(uint8_t *application);
extern int __thiscall handle_engine_command_message(uint8_t *application,
                                                    int command);
extern HCURSOR __thiscall finish_game_startup(int engine);
extern void __thiscall restart_game_engine(int engine);
extern LONG dword_786904;
extern uint64_t qword_786908;
extern CRITICAL_SECTION stru_786910;
extern int cursor_default_coordinate_x;
extern int cursor_default_coordinate_y;
extern int dword_7739E0;
extern int dword_7739E4;
extern int pointer_drag_threshold_x;
extern int pointer_drag_threshold_y;
extern int __thiscall update_input_context_pointer_position(int context,
                                                            int *point);
extern int __thiscall notify_input_context_pointer_activity(void *context,
                                                            int point,
                                                            int state);
extern int __thiscall dispatch_pointer_event(
    int *context, int *point, int (__thiscall *callback)(int, int *),
    int flags);
extern int __thiscall dispatch_pointer_event_with_state(
    uint32_t *context, int point, int state,
    int (__thiscall *callback)(int, int, int), int flags);
extern int __thiscall dispatch_pointer_drag_event(
    uint32_t *context, int point, int start,
    int state, int (__thiscall *callback)(int, int, int, int), int flags);
extern int __thiscall dispatch_pointer_motion_event(
    uint32_t *context, int point, int delta,
    int state, int (__thiscall *callback)(int, int, int, int), int flags);
extern int __thiscall dispatch_input_event(
    int *context, int event, int value,
    int (__thiscall *callback)(int, int, int), int flags);
extern int __thiscall set_input_context_event_state(int context, int event,
                                                   int value);
extern int __thiscall dispatch_pointer_button_1_press(int context,
                                                      int *point);
extern int __thiscall dispatch_pointer_button_2_press(int context,
                                                      int *point);
extern int __thiscall dispatch_pointer_button_3_press(int context,
                                                      int *point);
extern BOOL __cdecl has_application_event_dispatcher(void);
extern int __thiscall sub_44D8FE(void *value);
extern int __thiscall sub_44D903(void *value);
extern int __thiscall sub_44D908(void *value);
extern int __thiscall sub_44D915(void *value);
extern int __thiscall sub_44D927(void *value);
extern int __thiscall sub_44D940(void *value);
extern int __thiscall sub_44D94A(void *value);
extern int __thiscall sub_44D94F(void *value);
extern int __thiscall sub_44D954(void *value);
extern int __thiscall sub_44D959(void *value);
extern int system_profile_address;
extern char byte_765A30[260];
extern int caption_manager_saved_state_pointer;
extern int screen_width_address;
extern const char Str1[4];
extern char __stdcall sub_4B5E23(char *text);
extern int __cdecl serialize_sprite_collection(uint32_t *archive, uint32_t *field,
                              int mode, int flags, char final_flag);
extern int __cdecl serialize_texture_collection(uint32_t *archive, uint32_t *field,
                              int mode, int flags, char final_flag);
extern int __cdecl serialize_bitmap8_collection(uint32_t *archive, uint32_t *field,
                              int mode, int flags, char final_flag);
extern int __cdecl serialize_model_collection(uint8_t *archive, uint32_t *field,
                              int extra_field, int mode, int zero_flag,
                              char final_flag);
extern int __cdecl serialize_animation_collection(uint8_t *archive, uint32_t *field,
                              int extra_field, int mode, int zero_flag,
                              char final_flag);
extern int __cdecl serialize_scene_collection(uint32_t *archive, uint32_t *field,
                              int mode, int zero_flag, char final_flag);
extern int __cdecl sub_573120(uint32_t *archive, uint32_t *field,
                              int mode, int zero_flag, char final_flag);
extern int *__thiscall get_engine_viewport_rectangle(int *engine, int *rectangle,
                                 float *first, float *second,
                                 float *output);
extern void __thiscall set_engine_viewport_rectangle(uint32_t *engine, uint32_t *rectangle,
                                 float first, float second, float third,
                                 int mode);
extern char byte_765770;
extern int animation_notification_ids_begin;
extern int animation_notification_ids_end;
extern int animation_notification_ids_capacity;
extern char byte_765780;
extern void __cdecl loc_4B7BB2(void);
extern int __thiscall remember_animation_notification_id(int registry,
                                                        int *value);
extern char *__thiscall get_animation_resource_name(uint32_t *engine, char *result,
                                   int animation);
extern void log_source_message(int source, int line, int severity, size_t flags,
                       char *format, ...);
extern uint32_t event_handle_vtable[];
extern unsigned char byte_6C19B8[12];
extern unsigned char byte_6C19C4[12];
extern unsigned char byte_6C19D0[12];
extern uint32_t *__thiscall construct_engine_shutdown_timer(
    uint32_t *memory, char *name, int mode, uint32_t interval,
    uint32_t grace_period, uint32_t warning_event);
extern int __thiscall sub_4DB8B7(int memory, char *first, int first_count,
                                 char *second, int second_count,
                                 char *third, int third_count, int timeout);
extern int __thiscall sub_4DBBE0(void *lock, int thread_id,
                                 HANDLE thread_handle);
extern int __thiscall configure_engine_log_files(char *engine);
extern char __thiscall initialize_game_engine_state(int engine);
extern int __thiscall load_game_engine_settings(int engine);
extern int __thiscall apply_game_engine_command_line_options(int engine,
                                                             uint8_t *window);
extern int __stdcall save_display_options_to_settings(
    int mode, uint8_t width, uint8_t height, char fullscreen,
    GUID device_identity, int option_8);
extern int __thiscall check_game_disk_space(void *engine);
extern int update_game_viewport_geometry(void);
extern int __thiscall load_executable_version_info(int version_info,
                                                   CHAR *path, int flags);
extern char *__thiscall format_executable_version_summary(
    void *version_info, char *result);
/* engine/engine_logging.c */
extern int write_engine_log_message(int engine, int format, ...);
extern char *__thiscall read_audio_sample_rate_setting(uint32_t **settings);
extern char *__thiscall read_sound_quality_setting(uint32_t **settings);
extern char *__thiscall read_sound_volume_setting(uint32_t **settings);
extern char __thiscall ensure_sound_system_initialized(uint32_t *audio_settings);
extern int __thiscall apply_loaded_game_engine_settings(int engine);
/* gk3/game_application.c */
extern uint32_t *__cdecl allocate_registered_game_application(int size);
extern int __thiscall construct_game_application(int object);
extern int initialize_game_application(int object, int context);
extern int __thiscall initialize_engine_rendering_state(int engine);
extern int __thiscall destroy_file_version_info(int *version_info);

static const GameEngineMethod game_engine_vtable[] = {
  (GameEngineMethod)delete_game_engine_object,
  (GameEngineMethod)handle_cd_drive_list_change,
  (GameEngineMethod)update_timed_objects,
  (GameEngineMethod)cleanup_expired_engine_objects,
  (GameEngineMethod)log_engine_message_v,
  (GameEngineMethod)write_engine_log_message_v,
  (GameEngineMethod)read_engine_clock,
  (GameEngineMethod)get_game_time,
  (GameEngineMethod)get_application_relative_time,
  (GameEngineMethod)post_game_start_message,
  (GameEngineMethod)validate_animation_notification,
  (GameEngineMethod)dispatch_application_event,
  (GameEngineMethod)empty_game_engine_callback,
  (GameEngineMethod)refresh_resources_after_resume,
  (GameEngineMethod)finalize_game_engine_initialization,
  (GameEngineMethod)apply_display_options_from_settings,
  (GameEngineMethod)set_input_event_state,
  (GameEngineMethod)clear_input_event_state,
  (GameEngineMethod)pointer_button_1_pressed,
  (GameEngineMethod)pointer_button_1_released,
  (GameEngineMethod)pointer_button_2_pressed,
  (GameEngineMethod)pointer_button_2_released,
  (GameEngineMethod)handle_pointer_movement,
  (GameEngineMethod)pause_game_engine_callback,
  (GameEngineMethod)destroy_game_engine_members,
  (GameEngineMethod)initialize_game_engine_runtime,
  (GameEngineMethod)pointer_button_3_pressed,
  (GameEngineMethod)pointer_button_3_released,
  (GameEngineMethod)resume_game_engine_callback,
  (GameEngineMethod)prepare_game_engine_shutdown,
  (GameEngineMethod)empty_engine_input_callback,
  (GameEngineMethod)set_pointer_input_state,
  (GameEngineMethod)clear_pointer_input_state,
  (GameEngineMethod)empty_game_engine_callback_2,
  (GameEngineMethod)update_game_state,
  (GameEngineMethod)report_engine_error,
  (GameEngineMethod)show_engine_message_box,
  (GameEngineMethod)report_out_of_memory,
  (GameEngineMethod)process_game_window_message,
  (GameEngineMethod)load_ambient_map_bitmap,
  (GameEngineMethod)handle_scene_change,
  (GameEngineMethod)reset_game_engine_content,
  (GameEngineMethod)persist_resources_with_logging,
  (GameEngineMethod)persist_engine_resources,
  (GameEngineMethod)dispatch_engine_resource_persistence,
  (GameEngineMethod)forward_engine_object_collection_notification,
  (GameEngineMethod)log_engine_diagnostic_message
};

_Static_assert(sizeof(game_engine_vtable) / sizeof(game_engine_vtable[0]) == 47,
               "game-engine vtable slot count");
_Static_assert(sizeof(GameEngineMethod) == sizeof(uint32_t),
               "game-engine vtable requires 32-bit function pointers");
extern uint32_t g_engine_type_descriptor[15];
extern uint32_t g_engine_vtable[];
extern uint32_t engine_object_collection_vtable[];
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
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                 unsigned int address);
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
extern int game_engine_instance_address;
extern int interface_layer_type_descriptor;
extern int active_scene_controller_address;
extern int g_engine_base_offset_adjustment;
extern int (__stdcall *engine_pointer_vector_vtable)(char);
uint32_t *__thiscall destroy_engine_base(int engine_address);
extern int __thiscall get_engine_render_region_count(uint32_t *engine);
extern int __thiscall sub_4BA969(int collection);
extern int *__thiscall sub_588EA0(uint32_t *collection, int *key_and_value);
extern int __thiscall sub_593ED0(int *collection);
extern int __stdcall sub_5719F0(int first, int end);
extern void __thiscall verify_display_mode_state_unchanged(int16_t *state);
extern uint32_t *__thiscall sub_574230(int16_t *object);
extern int __thiscall destroy_pointer_vector_elements(int *collection);
extern int __thiscall process_game_engine_frame(int engine, int elapsed,
                                                int first, int second);
extern int __thiscall shutdown_game_application(uint32_t *application);
extern void __cdecl destroy_callback_registry(void);
extern int __cdecl destroy_and_clear_owned_object_4bb176(uint32_t *field);
extern void *__thiscall reset_engine_input_state(int engine);
extern const char *__thiscall find_string_map_entry(
    int *collection, const char *key, int *index);
extern int __thiscall clear_game_engine_collections(int *engine);
extern void __thiscall sub_570DD0(const char *engine, char *format,
                                  va_list arguments);
extern int has_application_log_manager(void);
extern void sub_557366(int source, int line, int severity, int flags,
                       char *format, va_list arguments);
extern int __thiscall sub_4E7BC0(uint32_t *time_source, int base_time);
extern char *__thiscall get_engine_object_name(uint32_t *engine, char *result,
                                   int resource_id);
extern int __thiscall sub_56B580(uint32_t *engine, int mode, int resource,
                                 int target);
extern char __thiscall sub_5308A5(int context);
extern const char Key[4];
extern void __thiscall search_for_new_barn_files(uint32_t *object);
extern void __thiscall refresh_barn_files(uint32_t *object);
extern int __thiscall set_active_cd_volume(uint32_t *engine, int volume_id,
                                           int mode);
extern int __thiscall refresh_cd_resource_roots(uint32_t *engine);
extern char __thiscall advance_timed_animation(int *object, int elapsed,
                                              int flags);
extern char __thiscall advance_active_animation(int object, int elapsed);
extern FILE *__thiscall sub_570E10(const char *engine, char *format,
                                   va_list arguments);
extern int sub_570BA0(int engine, int error);
extern int __thiscall sub_4E8BDE(int *application, int first, int second);
extern int dword_786928;
extern uint64_t qword_78692C;
extern CRITICAL_SECTION stru_786934;
extern uint64_t __rdtsc(void);
extern uint32_t *__cdecl sub_4852CC(uint32_t *message, int code, int time);
extern int get_application_event_dispatcher(void);
extern void __thiscall sub_4E825C(int target, uint32_t *message);
extern void __thiscall sub_594650(int *engine, int first, int second,
                                  int third);
extern int __thiscall create_interface_input_object(uint32_t *collection, char *name,
                                int mode);
extern void __thiscall sub_5948E0(int *engine);
extern int dword_76472C;
extern int default_cursor_spec_name_address;
extern int __thiscall sub_5A7A10(int engine, int first,
                                 CRITICAL_SECTION *section, int mode);
extern uint32_t *__thiscall sub_59BCD0(uint32_t *monitor, uint32_t *value);
extern int __cdecl destroy_and_clear_owned_object_4bb160(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb18c(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb1a2(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb1b8(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb1ce(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb1e4(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb1fa(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb210(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb226(uint32_t *field);
extern int __cdecl destroy_and_clear_owned_object_4bb23c(uint32_t *field);
extern char mouse_cursor_worker_manager_storage[];
extern char mouse_cursor_worker_manager_initialization_flags;
extern char painter_registration_initialized;
extern uint32_t painter_type_descriptor[15];
extern int active_painter_address;
extern void __cdecl unknown_libname_237(void);
extern uint8_t __thiscall is_sound_paused_by_id(int *manager, int sound_id);
extern void __thiscall finish_active_animation(int resource_address, int value);
extern int release_global_rasterizer_workspace(void);
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
extern int default_g_engine_render_flags;
/* gk3/GK3R_rest.c: remaining DirectDraw/Direct3D state pointers. */
extern int dword_773664;
extern int dword_773668;
extern int dword_77366C;
extern int dword_773674;
extern int dword_773678;

/* common/runtime_string.c */
extern void __thiscall destroy_runtime_string(void *string_storage);

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
  uint32_t clock_start_tick;
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
  EngineStringStorage runtime_strings[6];
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
_Static_assert(offsetof(GameEngine, clock_start_tick) == 208,
               "clock start tick offset");
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
_Static_assert(offsetof(GameEngine, runtime_strings) == 1224,
               "runtime strings offset");
_Static_assert(offsetof(GameEngine, mouse_smoothing_enabled) == 1373,
               "mouse smoothing offset");

uint32_t *__thiscall delete_game_engine_object(uint32_t *engine,
                                               int free_memory)
{
  destroy_game_engine_instance(engine);
  if ((free_memory & 1) != 0)
    free_tracked_memory((int)(intptr_t)engine);
  return engine;
}

uint32_t *__thiscall destroy_game_engine_instance(uint32_t *engine_words)
{
  GameEngine *engine = (GameEngine *)(void *)engine_words;

  engine->methods = (uint32_t)(uintptr_t)game_engine_vtable;
  game_engine_instance_address = 0;
  destroy_callback_registry();

  for (int index = 3; index < 6; ++index)
    destroy_runtime_string(&engine->runtime_strings[index]);
  for (int index = 0; index < 3; ++index)
    destroy_runtime_string(&engine->runtime_strings[index]);

  tidy_std_string_storage((char *)(void *)&engine->startup_sheep, 1);
  tidy_std_string_storage((char *)(void *)&engine->startup_arguments, 1);

  uint32_t registered_base = engine_words
      ? (uint32_t)(uintptr_t)(engine_words + 271)
      : 0;
  erase_map_entry_impl(
      game_engine_type_descriptor,
      game_engine_base_offset_adjustment + registered_base);
  return destroy_engine_base((int)(intptr_t)engine_words);
}

void __thiscall empty_game_engine_callback(uint32_t *engine)
{
  (void)engine;
}

int *__thiscall refresh_resources_after_resume(uint32_t *engine_words)
{
  uint32_t *entry_words =
      (uint32_t *)(void *)((GameEngine *)(void *)engine_words)->runtime_strings;
  uint32_t entry_count = (uint32_t)get_engine_render_region_count(engine_words);
  uint32_t *end_words = entry_words + entry_count *
      (sizeof(EngineStringStorage) / sizeof(*entry_words));
  int *result = (int *)(uintptr_t)entry_count;

  while (entry_words != end_words) {
    sub_4BA969((int)(intptr_t)entry_words);
    result = sub_588EA0(entry_words, &interface_layer_type_descriptor);
    entry_words += sizeof(EngineStringStorage) / sizeof(*entry_words);
  }

  if (active_scene_controller_address) {
    uintptr_t context_address = (uint32_t)active_scene_controller_address;
    uint32_t renderer_address =
        *(uint32_t *)(uintptr_t)(context_address + 0x50);
    if (renderer_address) {
      uint32_t *methods = *(uint32_t **)(uintptr_t)renderer_address;
      typedef int *(__thiscall *RendererResumeMethod)(uint32_t *renderer);
      RendererResumeMethod notify_renderer =
          (RendererResumeMethod)(uintptr_t)methods[0x98 / sizeof(uint32_t)];
      return notify_renderer((uint32_t *)(uintptr_t)renderer_address);
    }
  }
  return result;
}

uint32_t *__thiscall destroy_engine_base(int engine_address)
{
  uint8_t *engine_bytes = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  GameEngine *engine = (GameEngine *)(void *)engine_bytes;

  engine->methods = (uint32_t)(uintptr_t)g_engine_vtable;
  game_engine_address = 0;
  free_vector_storage((int *)(void *)&engine->events);

  for (int index = 6; index >= 0; --index) {
    EngineObjectCollection *collection = &engine->object_collections[index];
    collection->methods =
        (uint32_t)(uintptr_t)&engine_pointer_vector_vtable;
    if (collection->reserved_after_count[2])
      destroy_pointer_vector_elements((int *)(void *)collection);
    sub_593ED0((int *)(void *)collection);
  }

  free_vector_storage((int *)(void *)(engine_bytes + 256));
  sub_5719F0(*(int *)(void *)(engine_bytes + 244),
             *(int *)(void *)(engine_bytes + 248));
  free_tracked_memory(*(int *)(void *)(engine_bytes + 244));
  *(uint32_t *)(void *)(engine_bytes + 244) = 0;
  *(uint32_t *)(void *)(engine_bytes + 248) = 0;
  *(uint32_t *)(void *)(engine_bytes + 252) = 0;

  tidy_std_string_storage((char *)(void *)(engine_bytes + 220), 1);
  verify_display_mode_state_unchanged((int16_t *)(void *)(engine_bytes + 216));

  free_tracked_memory(*(int *)(void *)(engine_bytes + 184));
  *(uint32_t *)(void *)(engine_bytes + 184) = 0;
  *(uint32_t *)(void *)(engine_bytes + 188) = 0;
  *(uint32_t *)(void *)(engine_bytes + 192) = 0;
  free_tracked_memory(*(int *)(void *)(engine_bytes + 160));
  *(uint32_t *)(void *)(engine_bytes + 160) = 0;
  *(uint32_t *)(void *)(engine_bytes + 164) = 0;
  *(uint32_t *)(void *)(engine_bytes + 168) = 0;

  uint32_t registry_address = (uint32_t)(uintptr_t)engine_bytes;
  if (engine_address)
    registry_address += 12;
  registry_address += (uint32_t)g_engine_base_offset_adjustment;
  erase_map_entry_impl(g_engine_type_descriptor, registry_address);
  return sub_574230((int16_t *)(void *)engine_bytes);
}

void __thiscall empty_game_engine_callback_2(uint32_t *engine)
{
  (void)engine;
}

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
  engine->clock_start_tick = timeGetTime();
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
  engine->render_flags = (uint32_t)default_g_engine_render_flags;
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
      finish_active_animation(object, value);
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
  release_global_rasterizer_workspace();
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

char *__thiscall construct_mouse_cursor_worker_manager(char *manager)
{
  uint32_t *fields = (uint32_t *)(void *)manager;
  fields[1] = 0;
  fields[2] = 0;
  fields[15] = 0;
  fields[14] = (uint32_t)(uintptr_t)event_handle_vtable;
  fields[15] = (uint32_t)(uintptr_t)CreateEventA(NULL, TRUE, FALSE, NULL);
  InitializeCriticalSection((LPCRITICAL_SECTION)(void *)(manager + 68));
  fields[23] = 1;
  InitializeCriticalSection((LPCRITICAL_SECTION)manager + 4);
  fields[30] = 1;
  manager[0] = 0;
  fields[1] = 0;
  fields[2] = 0;
  fields[12] = 0;
  fields[11] = 0;
  fields[16] = 0;
  return manager;
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

int __thiscall update_game_state(void *engine, int elapsed)
{
  return process_game_engine_frame((int)(intptr_t)engine, elapsed, 1, 1);
}

int __thiscall reset_game_engine_content(int *engine)
{
  reset_and_clear_engine_collection(engine, 0);
  broadcast_resource_command((uint32_t *)(void *)engine, 0xFFFF, 0);

  uint32_t application_address = (uint32_t)engine[273];
  if (application_address)
    shutdown_game_application((uint32_t *)(uintptr_t)application_address);
  destroy_and_clear_owned_object_4bb176(engine + 273);

  char *runtime_lock = get_mouse_cursor_worker_manager();
  set_mouse_cursor_activity_state(
      (CRITICAL_SECTION *)(void *)runtime_lock, NULL);
  reset_engine_input_state((int)(intptr_t)engine);

  const char *shadow = find_string_map_entry(engine + 77, "shadow", NULL);
  if (shadow) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)shadow;
    typedef void (__thiscall *ReleaseShadowMethod)(const char *shadow);
    ((ReleaseShadowMethod)(uintptr_t)methods[16 / sizeof(uint32_t)])(shadow);
  }
  return clear_game_engine_collections(engine);
}

void __thiscall log_engine_message_v(int engine_address, char *format,
                                     va_list arguments)
{
  sub_570DD0((const char *)(intptr_t)engine_address, format, arguments);
  if (*(uint8_t *)(uintptr_t)((uint32_t)engine_address + 1088) &&
      has_application_log_manager()) {
    sub_557366((int)(intptr_t)"Z:\\Proj\\GK3\\gk3app\\Source\\GameEngine.cpp",
               675, 6, 0, format, arguments);
  }
}

int __thiscall get_application_relative_time(void *engine)
{
  uint32_t *methods = *(uint32_t **)(uintptr_t)engine;
  typedef int (__thiscall *GetEngineTimeMethod)(void *engine);
  int engine_time =
      ((GetEngineTimeMethod)(uintptr_t)methods[28 / sizeof(uint32_t)])(engine);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  uint32_t time_object_address =
      *(uint32_t *)(uintptr_t)(application_address + 68);
  return sub_4E7BC0((uint32_t *)(uintptr_t)time_object_address, engine_time);
}

void log_engine_diagnostic_message(int engine_address, char *format, ...)
{
  char buffer[6000];
  va_list arguments;

  va_start(arguments, format);
  if (*(uint8_t *)(uintptr_t)((uint32_t)engine_address + 1088) &&
      has_application_log_manager()) {
    sub_557366((int)(intptr_t)"Z:\\Proj\\GK3\\gk3app\\Source\\GameEngine.cpp",
               803, 4, 0, format, arguments);
  } else {
    _vsnprintf(buffer, 0x1770u, format, arguments);
  }
  va_end(arguments);
}

int __thiscall load_ambient_map_bitmap(uint32_t *engine, int mode,
                                       int resource, int target)
{
  if (target != 1)
    return sub_56B580(engine, mode, resource, target);

  char localized_name[16] = {0};
  char *localized_name_storage =
      get_engine_object_name(engine, localized_name, mode);
  const char *name =
      *(const char **)(void *)(localized_name_storage + sizeof(uint32_t));
  if (!name)
    name = Key;

  char path[260];
  sprintf(path, "p:\\content\\ambient maps\\%s.bmp", name);
  tidy_std_string_storage(localized_name, 1);
  return sub_56B580(engine, mode, (int)(intptr_t)path, 1);
}

char __thiscall handle_scene_change(uint8_t *engine, int scene)
{
  (void)scene;
  if (!engine[1114] && active_scene_controller_address)
    return sub_5308A5(active_scene_controller_address);
  return 0;
}

BOOL __thiscall post_game_start_message(HWND *engine)
{
  return PostMessageA((HWND)(uintptr_t)(uint32_t)engine[4], 0x401u, 0, 0);
}

BOOL __thiscall post_engine_restart_message(uint32_t *engine)
{
  return PostMessageA((HWND)(uintptr_t)engine[4], 0x403u, 0, 0);
}

int *__thiscall apply_engine_display_state(int *engine, int state,
                                           char center_surface)
{
  uint32_t *surface = NULL;
  uint32_t surface_size[2] = {0};
  uint32_t centered_position[2] = {0};
  typedef void (__thiscall *GetSurfaceSizeMethod)(
      uint32_t *, uint32_t *, uint32_t);
  typedef int (__thiscall *SetSurfacePositionMethod)(
      uint32_t *, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t);

  sub_594650(engine, state, 0, 0);
  if (center_surface) {
    uint32_t *interface_manager = (uint32_t *)(uintptr_t)
        *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
    uint32_t *surface_collection = (uint32_t *)(uintptr_t)
        interface_manager[12];
    uint32_t *surface_entry = (uint32_t *)(uintptr_t)
        create_interface_input_object(surface_collection,
                   (char *)(uintptr_t)default_cursor_spec_name_address, 1);
    surface = (uint32_t *)(uintptr_t)surface_entry[4];
    uint32_t *vtable = (uint32_t *)(uintptr_t)surface[0];
    const GetSurfaceSizeMethod get_size =
        (GetSurfaceSizeMethod)(uintptr_t)vtable[20 / 4];
    const SetSurfacePositionMethod set_position =
        (SetSurfacePositionMethod)(uintptr_t)vtable[24 / 4];

    get_size(surface, surface_size, 0);
    uint32_t *display_bounds = (uint32_t *)(uintptr_t)dword_76472C;
    centered_position[0] = display_bounds[0] / 2 - surface_size[0] / 2;
    centered_position[1] = display_bounds[1] / 2 - surface_size[1] / 2;
    set_position(surface, surface[6], centered_position, 0, 0, 0);
  }

  sub_5948E0(engine);
  sub_594650(engine, state, 0, 0);
  if (center_surface) {
    uint32_t *vtable = (uint32_t *)(uintptr_t)surface[0];
    const SetSurfacePositionMethod set_position =
        (SetSurfacePositionMethod)(uintptr_t)vtable[24 / 4];
    set_position(surface, surface[6], centered_position, 0, 0, 0);
  }
  return refresh_resources_after_resume((uint32_t *)(void *)engine);
}

uint32_t *__thiscall validate_animation_notification(uint32_t *engine,
                                                    int notification_id,
                                                    int frame,
                                                    const char *notification)
{
  if ((byte_765780 & 1) == 0) {
    byte_765780 |= 1u;
    byte_765770 = (char)((unsigned int)notification_id >> 24);
    animation_notification_ids_begin = 0;
    animation_notification_ids_end = 0;
    animation_notification_ids_capacity = 0;
    atexit(loc_4B7BB2);
  }

  uint32_t *entry = (uint32_t *)(uintptr_t)animation_notification_ids_begin;
  uint32_t *end = (uint32_t *)(uintptr_t)animation_notification_ids_end;
  while (entry != end && *entry != (uint32_t)notification_id)
    ++entry;
  if (entry != end)
    return entry;

  remember_animation_notification_id((int)(intptr_t)&byte_765770,
                                     &notification_id);
  char animation_name_storage[16];
  char *animation_name_storage_address =
      get_animation_resource_name(engine, animation_name_storage, notification_id);
  const char *animation_name =
      *(const char **)(void *)(animation_name_storage_address + sizeof(uint32_t));
  if (!animation_name)
    animation_name = Key;
  log_source_message(
      (int)(intptr_t)"Z:\\Proj\\GK3\\gk3app\\Source\\GameEngine.cpp",
      1905, 6, 0,
      "Illegal .anm notify on frame %d in anim %s: '%s'.\n",
      frame, animation_name, notification);
  return (uint32_t *)(intptr_t)tidy_std_string_storage(
      animation_name_storage, 1);
}

int __thiscall report_engine_error(void *engine, int error)
{
  return sub_570BA0((int)(intptr_t)engine, error);
}

void __stdcall dispatch_application_event(int first, int second)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);

  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  uint32_t event_dispatcher_address =
      *(uint32_t *)(uintptr_t)(application_address + 68);
  sub_4E8BDE((int *)(uintptr_t)event_dispatcher_address, first, second);

  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
}

int __stdcall empty_engine_input_callback(int first, int second)
{
  (void)first;
  (void)second;
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
  return 0;
}

int __thiscall prepare_game_engine_shutdown(int engine_address)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  *(uint8_t *)(void *)(engine + 1088) = 0;

  const char *shadow =
      find_string_map_entry((int *)(void *)(engine + 308), "shadow", NULL);
  if (shadow) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)shadow;
    typedef void (__thiscall *ReleaseShadowMethod)(const char *shadow);
    ((ReleaseShadowMethod)(uintptr_t)methods[16 / sizeof(uint32_t)])(shadow);
  }

  broadcast_resource_command((uint32_t *)(void *)engine, 0xFFFF, 0);
  if (!*(uint32_t *)(void *)(engine + 88) &&
      *(uint32_t *)(void *)(engine + 24) &&
      *(uint32_t *)(void *)(engine + 36)) {
    sub_594650((int *)(void *)engine, 0, 0, 0);
    sub_5A7A10(engine_address, 0, (CRITICAL_SECTION *)(uintptr_t)1, 1);
  }

  uint32_t monitor_address = *(uint32_t *)(void *)(game_engine_address + 276);
  sub_59BCD0((uint32_t *)(uintptr_t)monitor_address, 0);
  uint32_t application_address = *(uint32_t *)(void *)(engine + 1092);
  if (application_address)
    shutdown_game_application((uint32_t *)(uintptr_t)application_address);
  destroy_and_clear_owned_object_4bb176(engine + 273);
  destroy_and_clear_owned_object_4bb18c(engine + 299);
  destroy_and_clear_owned_object_4bb1a2(engine + 298);
  destroy_and_clear_owned_object_4bb160(engine + 300);
  return destroy_and_clear_owned_object_4bb1b8(engine + 301);
}

int __thiscall destroy_game_engine_members(uint32_t *engine)
{
  destroy_and_clear_owned_object_4bb1ce(engine + 305);
  destroy_and_clear_owned_object_4bb1ce(engine + 304);
  destroy_and_clear_owned_object_4bb1e4(engine + 303);
  destroy_and_clear_owned_object_4bb1ce(engine + 302);
  destroy_and_clear_owned_object_4bb1fa(engine + 297);
  game_engine_instance_address = 0;
  destroy_and_clear_owned_object_4bb210(engine + 294);
  destroy_and_clear_owned_object_4bb226(engine + 293);
  return destroy_and_clear_owned_object_4bb23c(engine + 295);
}

void __thiscall pause_game_engine_callback(uint8_t *engine)
{
  if (engine[1088] && has_application_event_dispatcher()) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)engine;
    typedef int (__thiscall *GetEngineTimeMethod)(uint8_t *engine);
    int current_time =
        ((GetEngineTimeMethod)(uintptr_t)methods[28 / sizeof(uint32_t)])(
            engine);
    uint32_t message[6] = {0};
    message[2] = (uint32_t)(uintptr_t)message;
    sub_4852CC(message, 1025, current_time);
    message[5] = UINT32_MAX;
    sub_4E825C(get_application_event_dispatcher(),
               (uint32_t *)(uintptr_t)message[0]);
  }
}

void __thiscall resume_game_engine_callback(uint8_t *engine)
{
  if (engine[1088] && has_application_event_dispatcher()) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)engine;
    typedef int (__thiscall *GetEngineTimeMethod)(uint8_t *engine);
    int current_time =
        ((GetEngineTimeMethod)(uintptr_t)methods[28 / sizeof(uint32_t)])(
            engine);
    uint32_t message[3] = {0};
    message[2] = (uint32_t)(uintptr_t)message;
    sub_4852CC(message, 1024, current_time);
    sub_4E825C(get_application_event_dispatcher(),
               (uint32_t *)(uintptr_t)message[0]);
  }
}

int __thiscall handle_cd_drive_list_change(int engine_address, int change)
{
  uint8_t *engine =
      (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint32_t cd_change_handler =
      *(uint32_t *)(void *)(engine + 1212);

  if (change == 0) {
    search_for_new_barn_files((uint32_t *)(uintptr_t)cd_change_handler);
    return refresh_cd_resource_roots((uint32_t *)(void *)engine);
  }

  if (change == 1 && *(int *)(uintptr_t)((uint32_t)system_profile_address + 100) == 4) {
    refresh_barn_files((uint32_t *)(uintptr_t)cd_change_handler);
    set_active_cd_volume((uint32_t *)(void *)engine,
                         *(int *)(void *)(engine + 1184), 1);
    return refresh_cd_resource_roots((uint32_t *)(void *)engine);
  }
  return change - 1;
}

int __thiscall cleanup_expired_engine_objects(uint32_t *engine, unsigned int age)
{
  int result = (int)engine[97];
  int index = 0;

  while (result > 0 && index < result) {
    int object = *(int *)(uintptr_t)vector_element_address(engine + 95, index);
    if (object && *(uint16_t *)(uintptr_t)(object + 6) &&
        *(int *)(uintptr_t)(object + 40) <= 0 &&
        *(uint32_t *)(uintptr_t)(object + 120) &&
        frame_number - *(int *)(uintptr_t)(object + 44) > (int)age) {
      uint32_t *methods = *(uint32_t **)(uintptr_t)object;
      typedef void (__thiscall *ExpireObjectMethod)(int object);
      ((ExpireObjectMethod)(uintptr_t)methods[8 / sizeof(uint32_t)])(object);
    }
    result = (int)engine[97];
    ++index;
  }
  return result;
}

int __thiscall update_timed_objects(uint32_t *engine, int elapsed)
{
  for (int index = 0; index < (int)engine[97]; ++index) {
    int *object = *(int **)(uintptr_t)vector_element_address(engine + 95, index);
    if (object) {
      int flags = object[12];
      if ((flags & 4) != 0 && (flags & 0x21) == 0)
        advance_timed_animation(object, elapsed, 0);
    }
  }

  int result = (int)engine[103];
  for (int index = 0; index < result; ++index) {
    int object = *(int *)(uintptr_t)vector_element_address(engine + 101, index);
    if (!object)
      continue;

    int current_frame = *(int *)(uintptr_t)(object + 108);
    int final_frame = *(int *)(uintptr_t)(object + 112) - 1;
    if (current_frame < final_frame)
      advance_active_animation(object, elapsed);
    if (*(int *)(uintptr_t)(object + 108) >= final_frame) {
      uint32_t *methods = *(uint32_t **)(uintptr_t)object;
      typedef void (__thiscall *DeleteObjectMethod)(int object,
                                                    int free_memory);
      ((DeleteObjectMethod)(uintptr_t)methods[0])(object, 1);
      set_vector_element(engine + 101, index, 0);
    }
  }
  return (int)(intptr_t)engine;
}

FILE *__thiscall write_engine_log_message_v(const char *engine, char *format,
                                            va_list arguments)
{
  return sub_570E10(engine, format, arguments);
}

DWORD __thiscall read_engine_clock(uint32_t *engine)
{
  return 43200000u - engine[52] + timeGetTime();
}

int __thiscall show_engine_message_box(HWND *engine, LPCSTR message,
                                       CHAR *caption, UINT flags)
{
  CHAR window_caption[100];
  HWND window = (HWND)(uintptr_t)(uint32_t)engine[4];
  CHAR *resolved_caption = caption;

  if (!resolved_caption) {
    GetWindowTextA(window, window_caption, sizeof(window_caption));
    resolved_caption = window_caption;
  }

  if (*(uint8_t *)(uintptr_t)fullscreen_flag_address && direct_draw_address) {
    uint32_t *methods = *(uint32_t **)(uintptr_t)direct_draw_address;
    ((FlipToGdiSurfaceMethod)(uintptr_t)
        methods[DIRECT_DRAW_FLIP_TO_GDI_SLOT])(direct_draw_address);
  }
  return MessageBoxA(window, message, resolved_caption, flags);
}

int __thiscall apply_display_options_from_settings(uint32_t *engine)
{
  uint8_t display_options[36];

  engine[330] = 0;
  engine[331] = 0;
  memcpy(engine + 28,
         load_display_options_from_settings(
             *(uint32_t ***)(uintptr_t)((uint32_t)game_engine_instance_address + 1192),
             display_options),
         sizeof(display_options));
  if (*(uint8_t *)(uintptr_t)fullscreen_flag_address)
    engine[23] = 1;
  return fullscreen_flag_address;
}

int __thiscall forward_engine_object_collection_notification(void *engine,
                                                              int event)
{
  return notify_engine_object_collections(engine, event);
}

int __thiscall report_out_of_memory(void *engine)
{
  return report_engine_error((int)(intptr_t)engine, "Out of memory.");
}

void __thiscall set_input_event_state(uint32_t *engine, int event, int value)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);
  switch (event) {
  case 16:
    engine[332] |= 8u;
    break;
  case 17:
    engine[332] |= 0x10u;
    break;
  case 18:
    engine[332] |= 0x20u;
    break;
  }
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  set_input_context_event_state(*(int *)(uintptr_t)(application_address + 68), event, value);
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
}

void __thiscall clear_input_event_state(uint32_t *engine, int event, int value)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);
  switch (event) {
  case 16:
    engine[332] &= ~8u;
    break;
  case 17:
    engine[332] &= ~0x10u;
    break;
  case 18:
    engine[332] &= ~0x20u;
    break;
  }
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_input_event((int *)(uintptr_t)*(uint32_t *)(uintptr_t)(application_address + 68),
             event, value,
             (int (__thiscall *)(int, int, int))sub_44D927, 0);
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
}

BOOL __thiscall set_pointer_input_state(uint32_t *engine, int event, int value)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);
  engine[332] |= 0x20u;
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  set_input_context_event_state(*(int *)(uintptr_t)(application_address + 68), event, value);
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
  return event == 18;
}

BOOL __thiscall clear_pointer_input_state(uint32_t *engine, int event,
                                          int value)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786928);
  if (event == 16)
    engine[332] &= ~8u;
  else if (event == 17)
    engine[332] &= ~0x10u;
  engine[332] &= ~0x20u;
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_input_event((int *)(uintptr_t)*(uint32_t *)(uintptr_t)(application_address + 68),
             event, value,
             (int (__thiscall *)(int, int, int))sub_44D927, 0);
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786934);
  qword_78692C += elapsed_ticks;
  LeaveCriticalSection(&stru_786934);
  return event == 18;
}

void __thiscall pointer_button_1_pressed(uint32_t *engine, int *point)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_pointer_button_1_press(*(int *)(uintptr_t)(application_address + 68), point);
  engine[332] |= 1u;
  engine[333] = cursor_default_coordinate_x;
  engine[334] = cursor_default_coordinate_y;
  engine[337] = point[0];
  engine[338] = point[1];
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall pointer_button_2_pressed(int engine_address, int *point)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_pointer_button_2_press(*(int *)(uintptr_t)(application_address + 68), point);
  *(uint32_t *)(void *)(engine + 1328) |= 2u;
  if (!engine[1372]) {
    *(int *)(void *)(engine + 1364) = point[0];
    *(int *)(void *)(engine + 1368) = point[1];
  }
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall pointer_button_3_pressed(int engine_address, int *point)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_pointer_button_3_press(*(int *)(uintptr_t)(application_address + 68), point);
  *(uint32_t *)(void *)(engine + 1328) |= 4u;
  if (!engine[1372]) {
    *(int *)(void *)(engine + 1356) = point[0];
    *(int *)(void *)(engine + 1360) = point[1];
  }
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall handle_pointer_movement(int engine_address, uint32_t *point)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);

  if (*(int *)(void *)(engine + 1332) == cursor_default_coordinate_x &&
      *(int *)(void *)(engine + 1336) == cursor_default_coordinate_y) {
    *(int *)(void *)(engine + 1332) = (int)point[0];
    *(int *)(void *)(engine + 1336) = (int)point[1];
    memset(engine + 1376, 0, 0x10u);
  }

  int *current_point = (int *)(void *)(engine + 1340);
  current_point[0] = (int)point[0];
  current_point[1] = (int)point[1];
  int delta_x = current_point[0] - *(int *)(void *)(engine + 1332);
  int delta_y = current_point[1] - *(int *)(void *)(engine + 1336);
  int smoothed_delta[2] = {delta_x, delta_y};

  if (!engine[1373] && engine[1374]) {
    if (dword_7739E0 == delta_x && dword_7739E4 == delta_y) {
      *(int *)(void *)(engine + 1384) /= 2;
      *(int *)(void *)(engine + 1388) /= 2;
    }
    smoothed_delta[0] =
        (delta_x + *(int *)(void *)(engine + 1376) +
         *(int *)(void *)(engine + 1384)) /
        3;
    smoothed_delta[1] =
        (delta_y + *(int *)(void *)(engine + 1380) +
         *(int *)(void *)(engine + 1388)) /
        3;

    if (!smoothed_delta[0])
      smoothed_delta[0] = (delta_x > 0) - (delta_x < 0);
    if (!smoothed_delta[1])
      smoothed_delta[1] = (delta_y > 0) - (delta_y < 0);

    current_point[0] =
        smoothed_delta[0] + *(int *)(void *)(engine + 1332);
    *(int *)(void *)(engine + 1376) = *(int *)(void *)(engine + 1384);
    int previous_smoothed_y = *(int *)(void *)(engine + 1388);
    current_point[1] =
        smoothed_delta[1] + *(int *)(void *)(engine + 1336);
    *(int *)(void *)(engine + 1380) = previous_smoothed_y;
    *(int *)(void *)(engine + 1384) = smoothed_delta[0];
    *(int *)(void *)(engine + 1388) = smoothed_delta[1];
  }

  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  int input_context = *(int *)(uintptr_t)(application_address + 68);
  update_input_context_pointer_position(input_context, current_point);
  if (engine[1372]) {
    dispatch_pointer_motion_event((uint32_t *)(uintptr_t)input_context,
               (int)(intptr_t)current_point,
               (int)(intptr_t)smoothed_delta,
               *(int *)(void *)(engine + 1328),
               (int (__thiscall *)(int, int, int, int))sub_44D908, 0);
  } else if ((*(uint8_t *)(void *)(engine + 1328) & 1) != 0 &&
             (abs(current_point[0] - *(int *)(void *)(engine + 1348)) >
                  pointer_drag_threshold_x ||
              abs(current_point[1] - *(int *)(void *)(engine + 1352)) >
                  pointer_drag_threshold_y)) {
    engine[1372] = 1;
    dispatch_pointer_drag_event((uint32_t *)(uintptr_t)input_context,
               (int)(intptr_t)current_point,
               (int)(intptr_t)(engine + 1348),
               *(int *)(void *)(engine + 1328),
               (int (__thiscall *)(int, int, int, int))sub_44D8FE, 0);
    *(int *)(void *)(engine + 1348) = cursor_default_coordinate_x;
    *(int *)(void *)(engine + 1352) = cursor_default_coordinate_y;
    *(int *)(void *)(engine + 1356) = cursor_default_coordinate_x;
    *(int *)(void *)(engine + 1360) = cursor_default_coordinate_y;
    *(int *)(void *)(engine + 1364) = cursor_default_coordinate_x;
    *(int *)(void *)(engine + 1368) = cursor_default_coordinate_y;
  } else {
    dispatch_pointer_motion_event((uint32_t *)(uintptr_t)input_context,
               (int)(intptr_t)current_point,
               (int)(intptr_t)smoothed_delta,
               *(int *)(void *)(engine + 1328),
               (int (__thiscall *)(int, int, int, int))sub_44D954, 0);
  }

  *(int *)(void *)(engine + 1332) = current_point[0];
  *(int *)(void *)(engine + 1336) = current_point[1];
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall pointer_button_1_released(int engine_address, int *point)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  dispatch_pointer_event(
      (int *)(uintptr_t)*(uint32_t *)(uintptr_t)(application_address + 68),
      point, (int (__thiscall *)(int, int *))sub_44D94F, 0);
  *(uint32_t *)(void *)(engine + 1328) &= ~1u;
  *(int *)(void *)(engine + 1332) = cursor_default_coordinate_x;
  *(int *)(void *)(engine + 1336) = cursor_default_coordinate_y;
  int button_state = *(int *)(void *)(engine + 1328);
  int (__thiscall *callback)(void *) = NULL;
  if (engine[1372]) {
    engine[1372] = 0;
    callback = sub_44D915;
  } else if ((button_state & 7) == 0) {
    callback = sub_44D940;
  }
  if (callback) {
    dispatch_pointer_event_with_state((uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application_address + 68),
               (int)(intptr_t)point, button_state,
               (int (__thiscall *)(int, int, int))callback, 0);
  }
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall pointer_button_2_released(int *engine, int *point)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  int input_context = *(int *)(uintptr_t)(application_address + 68);
  dispatch_pointer_event((int *)(uintptr_t)input_context, point,
             (int (__thiscall *)(int, int *))sub_44D959, 0);
  engine[332] &= ~2u;
  if (abs(point[0] - engine[341]) <= pointer_drag_threshold_x &&
      abs(point[1] - engine[342]) <= pointer_drag_threshold_y &&
      (engine[332] & 7) == 0) {
    notify_input_context_pointer_activity((void *)(uintptr_t)input_context, (int)(intptr_t)point,
               engine[332]);
  }
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

void __thiscall pointer_button_3_released(uint32_t *engine, int *point)
{
  uint64_t start_tick = __rdtsc();
  InterlockedIncrement(&dword_786904);
  uint32_t application_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
  int input_context = *(int *)(uintptr_t)(application_address + 68);
  dispatch_pointer_event((int *)(uintptr_t)input_context, point,
             (int (__thiscall *)(int, int *))sub_44D903, 0);
  engine[332] &= ~4u;
  if (abs(point[0] - (int)engine[339]) <= pointer_drag_threshold_x &&
      abs(point[1] - (int)engine[340]) <= pointer_drag_threshold_y) {
    int button_state = (int)engine[332];
    if ((button_state & 7) == 0) {
      dispatch_pointer_event_with_state((uint32_t *)(uintptr_t)input_context,
                 (int)(intptr_t)point, button_state,
                 (int (__thiscall *)(int, int, int))sub_44D94A, 0);
    }
  }
  uint64_t elapsed_ticks = __rdtsc() - start_tick;
  EnterCriticalSection(&stru_786910);
  qword_786908 += elapsed_ticks;
  LeaveCriticalSection(&stru_786910);
}

int __thiscall process_game_window_message(int engine_address,
                                          unsigned int message,
                                          uint16_t wparam, int lparam)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  (void)lparam;
  if ((!engine[1088] || !has_application_event_dispatcher() ||
       *(int *)(void *)(engine + 104) > 0) &&
      message >= 0x100 &&
      (message <= 0x107 || (message > 0x1FF && message <= 0x209))) {
    return 1;
  }

  check_engine_shutdown_warning((uint32_t *)(void *)engine);
  GetLocalTime((LPSYSTEMTIME)(void *)(engine + 1098));
  int result = 0;
  switch (message) {
  case 6:
  case 0x1C: {
    set_minimum_engine_render_skip_count((int *)(void *)engine, 2);
    int input_state = get_engine_input_state((uint32_t *)(void *)engine, 1) & 0xF8;
    *(int *)(void *)(engine + 1328) = input_state;
    if (engine[1372]) {
      engine[1372] = 0;
      uint32_t application_address =
          *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092);
      dispatch_pointer_event_with_state(
          (uint32_t *)(uintptr_t)*(uint32_t *)(uintptr_t)(application_address + 68),
          (int)(intptr_t)(engine + 1340), input_state,
          (int (__thiscall *)(int, int, int))sub_44D915, 0);
    }
    return result;
  }
  case 0x10: {
    if (*(uint8_t *)(uintptr_t)(*(uint32_t *)(void *)(engine + 276) + 20))
      return result;
    HWND window = *(HWND *)(void *)(engine + 16);
    if (IsIconic(window)) {
      ShowWindow(window, 9);
      PostMessageA(window, 0x10u, 0, 0);
      return 1;
    }
    return handle_engine_close_request(
        (uint8_t *)(uintptr_t)*(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092));
  }
  case 0x111:
    return handle_engine_command_message(
        (uint8_t *)(uintptr_t)*(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1092),
        wparam);
  case 0x401:
    finish_game_startup(engine_address);
    return 1;
  case 0x402:
    sub_4B5E23(byte_765A30);
    return 1;
  case 0x403:
    restart_game_engine(engine_address);
    return 1;
  default:
    return result;
  }
}

int __thiscall persist_engine_resources(int engine_address,
                                        uint32_t *archive, int mode)
{
  int archive_mode = mode;
  int zero_flag = mode == 0;
  if (mode) {
    serialize_sprite_collection(archive, (uint32_t *)(uintptr_t)(engine_address + 284),
               archive_mode, 0, 0);
    serialize_texture_collection(archive, (uint32_t *)(uintptr_t)(engine_address + 308),
               archive_mode, 0, 0);
    serialize_bitmap8_collection(archive, (uint32_t *)(uintptr_t)(engine_address + 332),
               archive_mode, 0, 0);
  }
  int result = serialize_model_collection((uint8_t *)archive,
                          (uint32_t *)(uintptr_t)(engine_address + 356),
                          engine_address + 180, archive_mode, zero_flag, 1);
  result += serialize_animation_collection((uint8_t *)archive,
                       (uint32_t *)(uintptr_t)(engine_address + 380),
                       engine_address + 156, archive_mode, zero_flag, 1);
  if (*(uint8_t *)(uintptr_t)(engine_address + 109))
    return serialize_scene_collection(archive,
                      (uint32_t *)(uintptr_t)(engine_address + 428),
                      archive_mode, zero_flag, 1) + result;
  return sub_573120(archive,
                    (uint32_t *)(uintptr_t)(engine_address + 428),
                    archive_mode, zero_flag, 1) + result;
}

int __thiscall initialize_game_engine_runtime(int engine_address)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint32_t *event = allocate_tracked_memory(8);
  if (event) {
    event[0] = (uint32_t)(uintptr_t)event_handle_vtable;
    event[1] = (uint32_t)(uintptr_t)CreateEventA(NULL, FALSE, FALSE, NULL);
  }
  *(uint32_t **)(void *)(engine + 1172) = event;

  uint32_t *timer_memory = allocate_tracked_memory(52);
  uint32_t *timer = timer_memory
                        ? construct_engine_shutdown_timer(
                              timer_memory, NULL, 1, 0x2710u, 0x1D4C0u,
                              *(uint32_t *)(void *)(engine + 1172))
                        : NULL;
  *(uint32_t **)(void *)(engine + 1176) = timer;

  void *lock = NULL;
  uint32_t *lock_memory = allocate_tracked_memory(112);
  if (lock_memory) {
    lock = (void *)(intptr_t)sub_4DB8B7(
        (int)(intptr_t)lock_memory, (char *)byte_6C19B8, 3,
        (char *)byte_6C19C4, 3, (char *)byte_6C19D0, 3, 1000);
  }
  *(void **)(void *)(engine + 1180) = lock;
  sub_4DBBE0(lock, (int)GetCurrentThreadId(), GetCurrentThread());

  game_engine_instance_address = engine_address;
  configure_engine_log_files((char *)engine);
  initialize_game_engine_state(engine_address);
  load_game_engine_settings(engine_address);
  apply_game_engine_command_line_options(
      engine_address, *(uint8_t **)(void *)(engine + 20));

  GUID initialization_data[3];
  memcpy(initialization_data, engine + 112, 0x24u);
  save_display_options_to_settings(
      initialization_data[0].Data1,
      initialization_data[0].Data2,
      initialization_data[0].Data4[0],
      initialization_data[0].Data4[4],
      initialization_data[1], initialization_data[2].Data1);
  return check_game_disk_space(engine);
}

int finalize_game_engine_initialization(int engine_address, int context)
{
  /* The original call enters with the engine in ECX and context in EDI. */
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  uint32_t info_string[10];
  char info_text_storage[16];
  update_game_viewport_geometry();
  load_executable_version_info((int)(intptr_t)info_string, NULL, 0);

  if (*(uint8_t *)(void *)info_string) {
    char *info_text =
        *(char **)(void *)(format_executable_version_summary(
                               info_string, info_text_storage) + 4);
    if (!info_text)
      info_text = (char *)Key;
    write_engine_log_message(engine_address,
                             (int)(intptr_t)"Build info: %s", info_text);
    tidy_std_string_storage((char *)info_string, 1);
  }

  uint32_t *engine_methods = *(uint32_t **)(void *)engine;
  typedef uint32_t (__thiscall *GetEngineTimeMethod)(uint8_t *engine);
  uint32_t seed = ((GetEngineTimeMethod)(uintptr_t)engine_methods[28 / 4])(
      engine);
  srand(seed);

  uint32_t settings_address =
      *(uint32_t *)(uintptr_t)((uint32_t)game_engine_instance_address + 1192);
  uint32_t audio_settings = *(uint32_t *)(void *)(engine + 212);
  uint32_t *audio_methods = *(uint32_t **)(uintptr_t)audio_settings;
  char *sample_rate =
      read_audio_sample_rate_setting((uint32_t **)(uintptr_t)settings_address);
  typedef void (__thiscall *SetAudioOptionMethod)(uint32_t audio,
                                                  char *value);
  ((SetAudioOptionMethod)(uintptr_t)audio_methods[20 / 4])(
      audio_settings, sample_rate);

  if (ensure_sound_system_initialized((uint32_t *)(uintptr_t)audio_settings)) {
    char *quality_setting =
        read_sound_quality_setting((uint32_t **)(uintptr_t)settings_address);
    ((SetAudioOptionMethod)(uintptr_t)audio_methods[68 / 4])(
        audio_settings, quality_setting);
    int configured_volume = (int)(intptr_t)
        read_sound_volume_setting((uint32_t **)(uintptr_t)settings_address);
    int maximum_volume = *(int *)(uintptr_t)(audio_settings + 40);
    if (configured_volume < 0)
      configured_volume = 0;
    else if (configured_volume > maximum_volume)
      configured_volume = maximum_volume;
    *(int *)(uintptr_t)(audio_settings + 44) = configured_volume;
  }

  apply_loaded_game_engine_settings(engine_address);
  uint32_t *application_memory = allocate_registered_game_application(116);
  int application = application_memory
      ? construct_game_application((int)(intptr_t)application_memory) : 0;
  *(int *)(void *)(engine + 1092) = application;
  initialize_game_application(application, context);
  initialize_engine_rendering_state(engine_address);
  return destroy_file_version_info((int *)info_string);
}

int __thiscall dispatch_engine_resource_persistence(void *engine, int mode)
{
  uint32_t *methods = *(uint32_t **)(uintptr_t)engine;
  typedef int (__thiscall *PersistEngineResourcesMethod)(void *engine,
                                                         int mode,
                                                         int flags);
  return ((PersistEngineResourcesMethod)(uintptr_t)methods[172 / 4])(
      engine, mode, 0);
}

void __thiscall persist_resources_with_logging(int *engine, float logger_value,
                                               float second_value)
{
  uint32_t logger_address;
  memcpy(&logger_address, &logger_value, sizeof(logger_address));
  uint32_t *logger_vtable = *(uint32_t **)(uintptr_t)logger_address;
  typedef void (__cdecl *WriteResourceLogMethod)(float logger,
                                                 const char *message);
  WriteResourceLogMethod write_log =
      (WriteResourceLogMethod)(uintptr_t)logger_vtable[56 / 4];
  write_log(logger_value, Str1);
  write_log(logger_value, Str1);
  write_log(logger_value, Str1);
  write_log(logger_value, "--- GEngine resource persistence begins here ---");
  write_log(logger_value, Str1);

  uint32_t *engine_vtable = *(uint32_t **)(void *)engine;
  typedef void (__thiscall *PersistEngineResourcesMethod)(int *engine,
                                                         float logger,
                                                         float second);
  ((PersistEngineResourcesMethod)(uintptr_t)engine_vtable[172 / 4])(
      engine, logger_value, second_value);

  write_log(logger_value, Str1);
  write_log(logger_value, "--- GEngine resource persistence ends here ---");
  write_log(logger_value, Str1);
  write_log(logger_value, Str1);
  write_log(logger_value, Str1);

  if (!*(uint8_t *)(uintptr_t)(logger_address + 4)) {
    int rectangle[4];
    float first_value;
    get_engine_viewport_rectangle(engine, rectangle, &first_value, &second_value,
               &logger_value);

    int bounds_left = *(int *)(uintptr_t)screen_width_address;
    int bounds_top = *(int *)(uintptr_t)caption_manager_saved_state_pointer;
    int left = rectangle[0] < 0 ? 0 : rectangle[0];
    int top = rectangle[1] < 0 ? 0 : rectangle[1];
    int right = bounds_left < rectangle[2] ? bounds_left : rectangle[2];
    int bottom = bounds_top < rectangle[3] ? bounds_top : rectangle[3];
    if (left >= right || top >= bottom) {
      left = 0;
      top = 0;
      right = 0;
      bottom = 0;
    }
    rectangle[0] = left;
    rectangle[1] = top;
    rectangle[2] = right;
    rectangle[3] = bottom;
    set_engine_viewport_rectangle((uint32_t *)(void *)engine, (uint32_t *)rectangle,
               first_value, second_value, logger_value, 1);
  }
}
