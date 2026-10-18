#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* gk3/GK3R_rest.c */
extern int game_engine_address;
extern int direct_draw_gamma_control_address;
extern int screen_blit_surface_address;
extern int z_buffer_blit_surface_address;
extern int window_clipper_address;
extern int direct3d_viewport_address;
extern int direct_draw_address;
extern int direct_draw4_address;
extern int primary_surface_address;
extern int screen_surface_address;
extern int secondary_screen_surface_address;
extern int z_buffer_surface_address;
extern int direct3d_interface_address;
extern uint16_t red_gamma_ramp_values[];
extern uint16_t green_gamma_ramp_values[];
extern uint16_t blue_gamma_ramp_values[];
extern int red_channel_destination_shift;
extern int red_channel_source_shift;
extern int green_channel_destination_shift;
extern int green_channel_source_shift;
extern int blue_channel_destination_shift;
extern int blue_channel_source_shift;
extern int software_color_channel_index_max;
extern int hardware_rasterizer_address;
extern uint16_t software_color_lookup_tables[2048];
extern int software_gamma_lookup_table[63];
extern int displayed_surface_cache_size_bytes;
extern int cached_surface_list_sentinel;
extern int cached_surface_list_head;
extern int cached_surface_cache_size_bytes;
extern int pause_cookie_base_offset_adjustment; /* GPauseCookie base offset adjustment. */
extern uint32_t pause_cookie_type_descriptor[16]; /* GPauseCookie type descriptor. */
extern uint32_t g_camera_type_descriptor[15]; /* GCamera type descriptor. */
extern uint16_t z_buffer_test_reference_color;
typedef struct ZBufferTestRectangle {
  int left;
  int top;
  int right;
  int bottom;
} ZBufferTestRectangle;
extern ZBufferTestRectangle z_buffer_test_rectangle;
_Static_assert(sizeof(ZBufferTestRectangle) == 16,
               "Z-buffer test rectangle layout");
/* Pixel sampled from the test surface after the Z-buffer blits. */
extern int z_buffer_test_pixel_x;
extern int z_buffer_test_pixel_y;
/* Bits track one-time initialization of the probe parameters. */
extern char z_buffer_test_initialization_flags;
extern uint32_t pause_cookie_vtable[];

/* gk3/GK3R_rest.c */
extern uint32_t *__thiscall release_inactive_graphics_resources(uint32_t *engine);
extern int *__thiscall find_or_create_graphics_resource(uint32_t *engine, int *resource_id,
                                 const char *manager_name, int flags,
                                 int create, int category);
extern int __thiscall get_graphics_resource_by_id(uint32_t *engine, uint16_t resource_id);
extern int __thiscall initialize_graphics_state(int object);
extern uint32_t *__cdecl load_graphics_hardware_overrides(int object, char flags);
extern int16_t *__thiscall capture_display_mode_state(int16_t *temporary, uint16_t width,
                                     uint16_t height);
extern void __thiscall verify_display_mode_state_unchanged(int16_t *temporary);
extern void __cdecl report_directx_call_failure(int object, const char *device, int flags,
                               char ramp);
extern void __thiscall release_rasterizer_device_resources(int object);
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall initialize_pause_cookie_first_string_member(uint32_t *object, char *storage);
extern uint32_t *__thiscall initialize_pause_cookie_second_string_member(uint32_t *object, char *storage);
extern float *__thiscall construct_g_camera_resource(float *object);
extern void __thiscall initialize_directx_graphics(int engine);
extern void __thiscall initialize_graphics_surfaces(int engine);
extern int __thiscall append_dynamic_array_element(uint32_t *sprite_collection, int sprite);
extern int __thiscall clear_engine_screen_and_z_buffer(int engine, int flags, void *lock,
                                 int force);
extern int __thiscall get_engine_object_by_id(uint32_t *engine,
                                              uint16_t resource_id);
extern int __thiscall get_sprite_surface(int object);
extern int __thiscall probe_surface_lock(int surface, int flags);
extern void __cdecl noop_graphics_atexit_handler_1(void);
extern void __cdecl noop_graphics_atexit_handler_2(void);
extern char *get_mouse_cursor_worker_manager(void);

/* gk3/sprite.c */
extern uint16_t *__thiscall construct_named_sprite(uint16_t *memory,
                                                    const char *name);
extern int __thiscall set_sprite_surface(int sprite, int surface);
extern int __thiscall destroy_sprite_members(int sprite);
extern uint32_t __thiscall get_engine_sprite_pixel(uint32_t *engine,
                                                   uint16_t resource_id,
                                                   int x, int y);
extern uint32_t __thiscall get_sprite_pixel(uint16_t *sprite, int x, int y);

/* gk3/control_graphics.c */
extern int __thiscall lock_graphics_surface(int surface, int flags);
extern void __thiscall unlock_graphics_surface(int surface);
extern int __thiscall lock_sprite_pixels(int *sprite);
extern int __thiscall unlock_sprite_pixels(int *sprite);

/* engine/engine_logging.c */
extern int __cdecl log_engine_boolean_setting(const char *label,
                                              char enabled);
extern int write_engine_log_message(int engine, int format, ...);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

typedef int (__thiscall *GetGammaDeviceMethod)(int device);
typedef int (__thiscall *ResetEngineMethod)(int engine, uint32_t value);
typedef int (__stdcall *SetDisplayModeMethod)(int direct_draw, uint32_t window,
                                              int flags);
typedef int (__stdcall *ReleaseGraphicsInterfaceMethod)(int object);
typedef int (__thiscall *DirectDrawSurfaceBltMethod)(
    int surface, int destination, ZBufferTestRectangle *destination_rect,
    int source, ZBufferTestRectangle *source_rect, uint32_t flags,
    uint32_t effects);
typedef int (__stdcall *TestSpriteBltMethod)(
    int surface, ZBufferTestRectangle *destination_rect, int source,
    ZBufferTestRectangle *source_rect, uint32_t flags, uint32_t effects);

void __thiscall initialize_software_color_lookup_table(char *lookup_table);
void __thiscall rebuild_software_gamma_lookup_table(float *lookup_table,
                                                    float gamma);

uint32_t pack_float_rgb_to_argb32(const float rgb[3])
{
  const uint32_t red = (uint8_t)(int64_t)((double)rgb[0] * 255.0);
  const uint32_t green = (uint8_t)(int64_t)((double)rgb[1] * 255.0);
  const uint32_t blue = (uint8_t)(int64_t)((double)rgb[2] * 255.0);
  return 0xff000000u | (red << 16) | (green << 8) | blue;
}

float *add_scalar_to_vector3(float result[3], const float vector[3],
                             float scalar)
{
  result[0] = vector[0] + scalar;
  result[1] = vector[1] + scalar;
  result[2] = vector[2] + scalar;
  return result;
}

float *multiply_vector3_components(float result[3], const float left[3],
                                   const float right[3])
{
  result[0] = left[0] * right[0];
  result[1] = left[1] * right[1];
  result[2] = left[2] * right[2];
  return result;
}

int get_texture_manager_for_dimensions(int width, int height)
{
  const int byte_size = 2 * width * height;
  const char *manager_name;

  if (byte_size >= 0x20000) {
    manager_name = "TexMgr128K";
  } else if (byte_size < 0x8000) {
    manager_name = "TexMgrOther";
  } else if (byte_size < 0x10000) {
    manager_name = "TexMgr32K";
  } else {
    manager_name = "TexMgr64K";
  }

  int *registered_id = find_or_create_graphics_resource(
      (uint32_t *)(uintptr_t)game_engine_address, &height,
      manager_name, 0, 1, 2);
  return get_graphics_resource_by_id((uint32_t *)(uintptr_t)game_engine_address,
                    (uint16_t)*registered_id);
}

uint32_t *__thiscall initialize_graphics_settings_controller(
    uint32_t *controller)
{
  controller[0] = 1;
  controller[1] = 4;
  controller[2] = 5;
  ((float *)controller)[3] = 1.0f;
  ((float *)controller)[4] = 1.0f;
  ((float *)controller)[5] = -1.0f;
  ((float *)controller)[6] = 1.0f;
  controller[7] = 0;
  controller[8] = 0;
  controller[9] = 2;
  return controller;
}

int __thiscall initialize_graphics_resources(uint32_t *engine)
{
  uint32_t *settings_memory = allocate_tracked_memory(40);
  uint32_t *settings = settings_memory
      ? initialize_graphics_settings_controller(settings_memory) : NULL;
  engine[70] = (uint32_t)(uintptr_t)settings;

  uint32_t *pause_cookie_memory = allocate_tracked_memory(40);
  uint32_t *registration = find_or_create_registry_entry(
      pause_cookie_type_descriptor, (unsigned int)(uintptr_t)pause_cookie_memory);
  registration[2] = 1;
  if (pause_cookie_memory) {
    const uint32_t base_address =
        (uint32_t)(uintptr_t)pause_cookie_memory +
        (uint32_t)pause_cookie_base_offset_adjustment + 4;
    find_or_create_registry_entry(pause_cookie_type_descriptor, base_address);
    char first_string_storage[4];
    char second_string_storage[4];
    initialize_pause_cookie_first_string_member(pause_cookie_memory + 2, first_string_storage);
    initialize_pause_cookie_second_string_member(pause_cookie_memory + 6, second_string_storage);
    *pause_cookie_memory = (uint32_t)(uintptr_t)pause_cookie_vtable;
    ((uint8_t *)pause_cookie_memory)[4] = 0;
  }
  engine[113] = (uint32_t)(uintptr_t)pause_cookie_memory;
  initialize_directx_graphics((int)(uintptr_t)engine);

  float *camera_resource_memory = (float *)allocate_tracked_memory(208);
  registration = find_or_create_registry_entry(
      g_camera_type_descriptor, (unsigned int)(uintptr_t)camera_resource_memory);
  registration[2] = 1;
  engine[114] = (uint32_t)(uintptr_t)(camera_resource_memory
      ? construct_g_camera_resource(camera_resource_memory) : NULL);
  initialize_graphics_surfaces((int)(uintptr_t)engine);

  uint16_t *sprite_memory = (uint16_t *)allocate_tracked_memory(60);
  uint16_t *sprite = sprite_memory
      ? construct_named_sprite(sprite_memory, "(PrimarySprite)") : NULL;
  set_sprite_surface((int)(uintptr_t)sprite, primary_surface_address);
  uint32_t sprite_id = (uint16_t)append_dynamic_array_element(engine + 71,
                                            (int)(uintptr_t)sprite);
  sprite_id |= (uint32_t)(uint16_t)sprite[2] << 16;
  engine[8] = sprite_id;

  sprite_memory = (uint16_t *)allocate_tracked_memory(60);
  sprite = sprite_memory
      ? construct_named_sprite(sprite_memory, "(ScreenSprite)") : NULL;
  set_sprite_surface((int)(uintptr_t)sprite, screen_surface_address);
  sprite_id = (uint16_t)append_dynamic_array_element(engine + 71, (int)(uintptr_t)sprite);
  sprite_id |= (uint32_t)(uint16_t)sprite[2] << 16;
  engine[6] = sprite_id;

  if (secondary_screen_surface_address) {
    sprite_memory = (uint16_t *)allocate_tracked_memory(60);
    sprite = sprite_memory
        ? construct_named_sprite(sprite_memory, "(Screen2Sprite)") : NULL;
    set_sprite_surface((int)(uintptr_t)sprite,
                       secondary_screen_surface_address);
    sprite_id = (uint16_t)append_dynamic_array_element(engine + 71,
                                     (int)(uintptr_t)sprite);
    sprite_id |= (uint32_t)(uint16_t)sprite[2] << 16;
    engine[7] = sprite_id;
  }

  sprite_memory = (uint16_t *)allocate_tracked_memory(60);
  sprite = sprite_memory
      ? construct_named_sprite(sprite_memory, "(ZBufferSprite)") : NULL;
  set_sprite_surface((int)(uintptr_t)sprite, z_buffer_surface_address);
  sprite_id = (uint16_t)append_dynamic_array_element(engine + 71, (int)(uintptr_t)sprite);
  sprite_id |= (uint32_t)(uint16_t)sprite[2] << 16;
  engine[9] = sprite_id;

  clear_engine_screen_and_z_buffer((int)(uintptr_t)engine, 0, (void *)(uintptr_t)1, 1);
  if (*(uint8_t *)(uintptr_t)((uint8_t *)engine + 109)) {
    engine[38] &= ~7u;
    if (*(uint8_t *)(uintptr_t)(hardware_rasterizer_address + 52)) {
      int z_buffer_object = get_engine_object_by_id(engine,
                                                   (uint16_t)engine[9]);
      int z_buffer_surface = get_sprite_surface(z_buffer_object);
      if (probe_surface_lock(z_buffer_surface, 0xFFFF)) {
        uint16_t *pixel = (uint16_t *)(uintptr_t)
            lock_graphics_surface(z_buffer_surface, 0xFFFF);
        *pixel = 0x1234;
        if (*pixel == 0x1234)
          engine[38] |= 1u | 4u;
        unlock_graphics_surface(z_buffer_surface);
      }

      if ((z_buffer_test_initialization_flags & 1) == 0) {
        z_buffer_test_initialization_flags |= 1u;
        z_buffer_test_pixel_x = 0;
        z_buffer_test_pixel_y = 0;
        atexit(noop_graphics_atexit_handler_2);
      }
      if ((z_buffer_test_initialization_flags & 2) == 0) {
        z_buffer_test_initialization_flags |= 2u;
        z_buffer_test_rectangle.left = 0;
        z_buffer_test_rectangle.top = 0;
        z_buffer_test_rectangle.right = 1;
        z_buffer_test_rectangle.bottom = 1;
        atexit(noop_graphics_atexit_handler_1);
      }
      if ((z_buffer_test_initialization_flags & 4) == 0) {
        z_buffer_test_initialization_flags |= 4u;
        z_buffer_test_reference_color = (uint16_t)(
            (0x38u >> blue_channel_source_shift << blue_channel_destination_shift) |
            (0x22u >> green_channel_source_shift << green_channel_destination_shift) |
            (0x0Cu >> red_channel_source_shift << red_channel_destination_shift));
      }

      uint32_t test_sprite_storage[15] = {0};
      uint16_t *test_sprite = construct_named_sprite(
          (uint16_t *)test_sprite_storage, "test");
      set_sprite_surface((int)(uintptr_t)test_sprite, z_buffer_blit_surface_address);
      uint16_t *test_surface_description =
          (uint16_t *)(uintptr_t)lock_sprite_pixels((int *)test_sprite);
      *test_surface_description = z_buffer_test_reference_color;
      unlock_sprite_pixels((int *)test_sprite);

      int test_surface_object = get_sprite_surface((int)(uintptr_t)test_sprite);
      int test_surface = *(int *)(uintptr_t)(test_surface_object + 44);
          z_buffer_object = get_engine_object_by_id(engine,
                                                   (uint16_t)engine[9]);
      int z_buffer_sprite_surface = get_sprite_surface(z_buffer_object);
      int z_buffer_direct_draw_surface =
          *(int *)(uintptr_t)(z_buffer_sprite_surface + 44);
      uint32_t *z_buffer_methods =
          *(uint32_t **)(uintptr_t)z_buffer_direct_draw_surface;
      const DirectDrawSurfaceBltMethod copy_to_z_buffer =
          (DirectDrawSurfaceBltMethod)(uintptr_t)z_buffer_methods[20 / 4];
      int result = copy_to_z_buffer(
          z_buffer_direct_draw_surface, z_buffer_direct_draw_surface,
          &z_buffer_test_rectangle, test_surface,
          &z_buffer_test_rectangle, 0, 0);

      if (result >= 0) {
      uint32_t pixel = get_engine_sprite_pixel(
          engine, (uint16_t)engine[9], z_buffer_test_pixel_x,
          z_buffer_test_pixel_y);
        uint16_t packed_pixel = (uint16_t)(
            (((pixel & 0xFF0000u) >> (blue_channel_source_shift + 16)) << blue_channel_destination_shift) |
            (((pixel & 0xFF00u) >> (green_channel_source_shift + 8)) << green_channel_destination_shift) |
            (((uint8_t)pixel >> red_channel_source_shift) << red_channel_destination_shift));
        if (packed_pixel == z_buffer_test_reference_color) {
          test_surface_description =
              (uint16_t *)(uintptr_t)lock_sprite_pixels((int *)test_sprite);
          *test_surface_description = 0;
          unlock_sprite_pixels((int *)test_sprite);

          z_buffer_object = get_engine_object_by_id(engine,
                                                    (uint16_t)engine[9]);
          z_buffer_sprite_surface = get_sprite_surface(z_buffer_object);
          z_buffer_direct_draw_surface =
              *(int *)(uintptr_t)(z_buffer_sprite_surface + 44);
          test_surface_object = get_sprite_surface(
              (int)(uintptr_t)test_sprite);
          test_surface = *(int *)(uintptr_t)(test_surface_object + 44);
          uint32_t *test_surface_methods =
              *(uint32_t **)(uintptr_t)test_surface;
          const TestSpriteBltMethod copy_to_test_sprite =
              (TestSpriteBltMethod)(uintptr_t)test_surface_methods[20 / 4];
          result = copy_to_test_sprite(test_surface,
                                       &z_buffer_test_rectangle,
                                       z_buffer_direct_draw_surface,
                                       &z_buffer_test_rectangle, 0, 0);
          if (result >= 0) {
            pixel = get_sprite_pixel(test_sprite,
                                     z_buffer_test_rectangle.left,
                                     z_buffer_test_rectangle.top);
            packed_pixel = (uint16_t)(
                (((pixel & 0xFF0000u) >> (blue_channel_source_shift + 16)) << blue_channel_destination_shift) |
                (((pixel & 0xFF00u) >> (green_channel_source_shift + 8)) << green_channel_destination_shift) |
                (((uint8_t)pixel >> red_channel_source_shift) << red_channel_destination_shift));
            if (packed_pixel == z_buffer_test_reference_color)
              engine[38] |= 1u | 2u;
          }
        }
      }
      destroy_sprite_members((int)(uintptr_t)test_sprite);
    }
  } else {
    engine[38] |= 7u;
  }

  if ((engine[38] & 1u) != 0) {
    log_engine_boolean_setting("Z-buffer save/restore supported using Blt()",
                               (engine[38] & 2u) != 0);
    log_engine_boolean_setting("Z-buffer save/restore supported using memcpy()",
                               (engine[38] & 4u) != 0);
  } else {
    write_engine_log_message((int)(uintptr_t)engine,
               (int)"Z-buffer save/restore NOT supported");
  }

  if (*(uint8_t *)(uintptr_t)((uint8_t *)engine + 108))
    rebuild_software_gamma_lookup_table((float *)software_gamma_lookup_table, 1.0f);
  initialize_software_color_lookup_table((char *)software_color_lookup_tables);
  get_mouse_cursor_worker_manager();
  return write_engine_log_message((int)(uintptr_t)engine,
                    (int)"GEngine initialization complete");
}

double __thiscall get_display_gamma(float *controller)
{
  if (controller[5] >= 0.0f)
    return controller[5];

  if (hardware_rasterizer_address != 0) {
    controller[5] = *(float *)(uintptr_t)(hardware_rasterizer_address + 56);
    return controller[5];
  }

  if (!direct_draw_gamma_control_address) {
    controller[5] = 1.0f;
    return controller[5];
  }

  union {
    uint32_t alignment;
    uint8_t bytes[60];
  } gamma_query;
  initialize_graphics_state((int)(uintptr_t)gamma_query.bytes);
  load_graphics_hardware_overrides((int)(uintptr_t)gamma_query.bytes, 0);
  const float queried_gamma =
      *(const float *)(const void *)(gamma_query.bytes + 56);
  controller[5] = queried_gamma;
  if (fabs(queried_gamma) < 0.0000009999999974752427)
    controller[5] = 1.0f;
  return controller[5];
}

void __thiscall initialize_software_color_lookup_table(char *lookup_table)
{
  uint32_t *red_channel = (uint32_t *)(void *)lookup_table;
  uint32_t *green_channel = red_channel + 1024;
  uint32_t *blue_channel = red_channel + 2048;
  size_t index = 0;

  for (int row = 0; row < 32; ++row) {
    for (int column = 0; column < 32; ++column) {
      const int intensity = (row * column) / 4;
      red_channel[index] = (uint16_t)(intensity >> red_channel_source_shift
                                      << red_channel_destination_shift);
      green_channel[index] = (uint16_t)(intensity >> green_channel_source_shift
                                        << green_channel_destination_shift);
      blue_channel[index] = (uint16_t)(intensity >> blue_channel_source_shift
                                       << blue_channel_destination_shift);
      ++index;
    }
  }
}

typedef struct CachedSurfaceNode {
  uint32_t previous;
  uint32_t next;
  uint32_t pixels;
  uint16_t width;
  uint16_t height;
} CachedSurfaceNode;

_Static_assert(sizeof(CachedSurfaceNode) == 16,
               "cached-surface list node layout");

void clear_cached_surface_cache(void)
{
  const uint32_t sentinel_address = (uint32_t)(uintptr_t)&cached_surface_list_sentinel;
  uint32_t node_address = (uint32_t)cached_surface_list_head;

  while (node_address != sentinel_address && cached_surface_cache_size_bytes != 0) {
    CachedSurfaceNode *node = (CachedSurfaceNode *)(uintptr_t)node_address;
    const uint32_t previous_address = node->previous;
    const uint32_t next_address = node->next;

    free((void *)(uintptr_t)node->pixels);
    cached_surface_cache_size_bytes -= 2 * (int)node->width * (int)node->height;
    node->pixels = 0;
    ((CachedSurfaceNode *)(uintptr_t)previous_address)->next = next_address;
    ((CachedSurfaceNode *)(uintptr_t)next_address)->previous = previous_address;
    node_address = (uint32_t)cached_surface_list_head;
    displayed_surface_cache_size_bytes = cached_surface_cache_size_bytes;
  }
}

int __thiscall release_graphics_resources(uint32_t *engine)
{
  if (direct_draw_gamma_control_address) {
    ((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)direct_draw_gamma_control_address)[8 / sizeof(uint32_t)])(
            direct_draw_gamma_control_address);
    direct_draw_gamma_control_address = 0;
  }
  if (screen_blit_surface_address) {
    ((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)screen_blit_surface_address)[8 / sizeof(uint32_t)])(
            screen_blit_surface_address);
    screen_blit_surface_address = 0;
  }
  if (z_buffer_blit_surface_address) {
    ((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)z_buffer_blit_surface_address)[8 / sizeof(uint32_t)])(
            z_buffer_blit_surface_address);
    z_buffer_blit_surface_address = 0;
  }
  if (direct3d_viewport_address) {
    ((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)direct3d_viewport_address)[8 / sizeof(uint32_t)])(
            direct3d_viewport_address);
    direct3d_viewport_address = 0;
  }
  if (hardware_rasterizer_address) {
    release_rasterizer_device_resources(hardware_rasterizer_address);
    free_tracked_memory(hardware_rasterizer_address);
    hardware_rasterizer_address = 0;
  }
  if (z_buffer_surface_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)z_buffer_surface_address)[8 / sizeof(uint32_t)])(
            z_buffer_surface_address);
    z_buffer_surface_address = 0;
  }
  if (window_clipper_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)window_clipper_address)[8 / sizeof(uint32_t)])(
            window_clipper_address);
    window_clipper_address = 0;
  }
  if (secondary_screen_surface_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)secondary_screen_surface_address)[8 / sizeof(uint32_t)])(
            secondary_screen_surface_address);
    secondary_screen_surface_address = 0;
  }
  if (screen_surface_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)screen_surface_address)[8 / sizeof(uint32_t)])(
            screen_surface_address);
    screen_surface_address = 0;
  }

  int result = direct_draw_address;
  if (direct_draw_address) {
    result = ((SetDisplayModeMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)direct_draw_address)[80 / sizeof(uint32_t)])(
            direct_draw_address, engine[4], 8);
    report_directx_call_failure(result, "Z:\\Proj\\GK3\\GEngine\\ginit.cpp",
                                2123, 0);
    result = direct_draw_address;
  }
  if (primary_surface_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)primary_surface_address)[8 / sizeof(uint32_t)])(
            primary_surface_address);
    primary_surface_address = 0;
    result = direct_draw_address;
  }
  if (direct3d_interface_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)direct3d_interface_address)[8 / sizeof(uint32_t)])(
            direct3d_interface_address);
    direct3d_interface_address = 0;
    result = direct_draw_address;
  }
  if (direct_draw4_address) {
    (void)((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)direct_draw4_address)[8 / sizeof(uint32_t)])(
            direct_draw4_address);
    direct_draw4_address = 0;
    result = direct_draw_address;
  }
  if (result) {
    result = ((ReleaseGraphicsInterfaceMethod)(uintptr_t)
        (*(uint32_t **)(uintptr_t)result)[8 / sizeof(uint32_t)])(result);
    direct_draw_address = 0;
  }
  return result;
}

void __thiscall set_surface_quality(uint32_t *controller, int quality)
{
  controller[0] = (uint32_t)quality;

  const uint32_t *engine_methods =
      *(const uint32_t **)(uintptr_t)game_engine_address;
  ResetEngineMethod reset =
      (ResetEngineMethod)(uintptr_t)engine_methods[160 / sizeof(uint32_t)];

  if (*(uint8_t *)(uintptr_t)(game_engine_address + 109)) {
    if (direct3d_interface_address != 0) {
      const uint32_t *direct3d_methods =
          *(const uint32_t **)(uintptr_t)direct3d_interface_address;
      void (__stdcall *release)(int) =
          (void (__stdcall *)(int))(uintptr_t)direct3d_methods[44 / sizeof(uint32_t)];
      release(direct3d_interface_address);
    }
    reset(game_engine_address, 0);
    release_inactive_graphics_resources((uint32_t *)(uintptr_t)game_engine_address);
  } else {
    reset(game_engine_address, 0);
    clear_cached_surface_cache();
  }
}

void __thiscall set_scene_shade_mode(uint32_t *controller, int mode)
{
  controller[1] = (uint32_t)mode;

  const uint32_t *engine_methods =
      *(const uint32_t **)(uintptr_t)game_engine_address;
  ResetEngineMethod reset =
      (ResetEngineMethod)(uintptr_t)engine_methods[160 / sizeof(uint32_t)];
  reset(game_engine_address, 0);

  if (*(uint8_t *)(uintptr_t)(game_engine_address + 108))
    clear_cached_surface_cache();
}

int __thiscall set_model_shade_mode(uint32_t *controller, int mode)
{
  controller[2] = (uint32_t)mode;

  const uint32_t *engine_methods =
      *(const uint32_t **)(uintptr_t)game_engine_address;
  ResetEngineMethod reset =
      (ResetEngineMethod)(uintptr_t)engine_methods[160 / sizeof(uint32_t)];
  return reset(game_engine_address, 0);
}

void __thiscall rebuild_software_gamma_lookup_table(float *lookup_table,
                                                     float gamma)
{
  int16_t temporary_mode;
  int channel_value = 0;
  float inverse_gamma = 1.0f / gamma;
  float scale = 255.0f / pow(255.0, inverse_gamma);
  uint32_t *red_channel = (uint32_t *)lookup_table;
  uint32_t *green_channel = red_channel + 4096;
  uint32_t *blue_channel = red_channel + 8192;
  size_t index = 0;
  uint32_t pixel_format =
      *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)(game_engine_address + 280) + 36);

  software_color_channel_index_max = (32 * ((pixel_format & 2) == 0)) | 0x1f;
  capture_display_mode_state(&temporary_mode, 0xF00u, 0xC00u);
  lookup_table[12288] = gamma;

  for (int row = 0; row < 64; ++row) {
    channel_value = 0;
    for (int column = 0; column < 64; ++column) {
      float intensity = (float)((double)channel_value * 0.064247921);
      if ((pixel_format & 2) != 0)
        intensity += intensity;

      int corrected = (int)(pow(intensity, inverse_gamma) * scale + 0.5);
      if (corrected < 0)
        corrected = 0;
      else if (corrected > 255)
        corrected = 255;

      red_channel[index] = (uint16_t)(corrected >> red_channel_source_shift
                                      << red_channel_destination_shift);
      green_channel[index] = (uint16_t)(corrected >> green_channel_source_shift
                                        << green_channel_destination_shift);
      blue_channel[index] = (uint16_t)(corrected >> blue_channel_source_shift
                                       << blue_channel_destination_shift);
      channel_value += row;
      ++index;
    }
  }

  verify_display_mode_state_unchanged(&temporary_mode);
}

static int apply_software_gamma_ramp(float *controller)
{
  if (*(uint8_t *)(uintptr_t)(game_engine_address + 108)) {
    rebuild_software_gamma_lookup_table((float *)(uintptr_t)software_gamma_lookup_table,
                                        controller[4]);
    clear_cached_surface_cache();

    const uint32_t *methods =
        *(const uint32_t **)(uintptr_t)game_engine_address;
    ResetEngineMethod reset =
        (ResetEngineMethod)(uintptr_t)methods[160 / sizeof(uint32_t)];
    return reset(game_engine_address, 0);
  }
  return game_engine_address;
}

void __thiscall apply_gamma_ramp(float *controller, float gamma, float force)
{
  uint8_t force_flag;
  memcpy(&force_flag, &force, sizeof(force_flag));

  if (fabs(controller[4] - gamma) < 0.0000009999999974752427
      && !force_flag)
    return;

  controller[4] = gamma;
  if (!direct_draw_gamma_control_address) {
    if (*(uint8_t *)(uintptr_t)(game_engine_address + 108))
      apply_software_gamma_ramp(controller);
    return;
  }

  uint16_t gamma_ramp[3][256];
  const double inverse_gamma = 1.0 / gamma;
  const double scale = 65535.0 / pow(65535.0, inverse_gamma);
  for (int index = 0; index < 256; ++index) {
    gamma_ramp[0][index] = (uint16_t)(
        pow((double)red_gamma_ramp_values[index], inverse_gamma) * scale);
    gamma_ramp[1][index] = (uint16_t)(
        pow((double)green_gamma_ramp_values[index], inverse_gamma) * scale);
    gamma_ramp[2][index] = (uint16_t)(
        pow((double)blue_gamma_ramp_values[index], inverse_gamma) * scale);
  }

  int flags = 0;
  if ((*(uint32_t *)(uintptr_t)(game_engine_address + 152) & 0x80) != 0)
    flags = (*(uint32_t *)(uintptr_t)(game_engine_address + 528) & 0x8000) == 0;

  const uint32_t *methods = *(const uint32_t **)(uintptr_t)direct_draw_gamma_control_address;
  GetGammaDeviceMethod get_gamma_device =
      (GetGammaDeviceMethod)(uintptr_t)methods[16 / sizeof(uint32_t)];
  const int gamma_device = get_gamma_device(direct_draw_gamma_control_address);
  report_directx_call_failure(gamma_device, (const char *)(uintptr_t)direct_draw_gamma_control_address, flags,
             (char)(uintptr_t)gamma_ramp);
}
