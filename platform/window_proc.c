#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <windows.h>

typedef uint32_t _DWORD;

typedef struct SpriteResourceState {
  uint32_t vtable_address;
  uint16_t reserved_4;
  uint16_t is_loaded;
  uint8_t reserved_8[36];
  uint32_t last_used_frame;
  uint32_t surface_wrapper_address;
} SpriteResourceState;

typedef struct SurfaceLockState {
  uint8_t reserved_0[48];
  uint32_t locked_pixel_buffer_address;
} SurfaceLockState;

_Static_assert(offsetof(SpriteResourceState, is_loaded) == 6,
               "sprite loaded flag offset");
_Static_assert(offsetof(SpriteResourceState, last_used_frame) == 44,
               "sprite last-used frame offset");
_Static_assert(offsetof(SpriteResourceState, surface_wrapper_address) == 48,
               "sprite surface wrapper offset");
_Static_assert(offsetof(SurfaceLockState, locked_pixel_buffer_address) == 48,
               "surface lock buffer offset");

typedef struct WindowMessageHook {
  struct WindowMessageHook *next;
  struct WindowMessageHook *previous;
  uint8_t (__stdcall *callback)(HWND, UINT, WPARAM, LPARAM, LPARAM, WPARAM *);
  LPARAM context;
  int priority;
} WindowMessageHook;

typedef struct {
  uint32_t reserved;
  uint32_t list_head;
  uint32_t count;
} WindowMessageHookRegistry;

typedef struct {
  uint32_t next;
  uint32_t previous;
  uint32_t callback;
  uint32_t context;
  int32_t priority;
} WindowMessageHookEntry;

_Static_assert(sizeof(WindowMessageHookRegistry) == 12,
               "message hook registry layout");
_Static_assert(sizeof(WindowMessageHookEntry) == 20,
               "message hook entry layout");

typedef int (__thiscall *MessageFilter)(void *, UINT, WPARAM, LPARAM);
typedef void (__thiscall *PointHandler)(void *, POINT *);
typedef void (__thiscall *KeyHandler)(void *, WPARAM, LPARAM);
typedef int (__thiscall *SystemKeyHandler)(void *, WPARAM, LPARAM);
typedef void (__thiscall *CharacterHandler)(void *, WPARAM, LPARAM);

enum {
  ENGINE_WINDOW_OFFSET = 16,
  ENGINE_OUTER_WINDOW_BOUNDS_OFFSET = 40,
  ENGINE_VIEWPORT_BOUNDS_OFFSET = 56,
  ENGINE_CLIENT_AREA_ORIGIN_OFFSET = 72,
  ENGINE_COORDINATE_ORIGIN_X_OFFSET = 80,
  ENGINE_COORDINATE_ORIGIN_Y_OFFSET = 84,
  ENGINE_PAUSED_OFFSET = 100,
  ENGINE_INITIALIZED_OFFSET = 204,
  ENGINE_RENDER_FLAGS_OFFSET = 528,
  ENGINE_MESSAGE_HOOKS_OFFSET = 1080,

  ENGINE_CHARACTER_HANDLER = 44 / 4,
  ENGINE_KEY_DOWN = 64 / 4,
  ENGINE_KEY_UP = 68 / 4,
  ENGINE_LEFT_BUTTON_DOWN = 72 / 4,
  ENGINE_LEFT_BUTTON_UP = 76 / 4,
  ENGINE_MIDDLE_BUTTON_DOWN = 80 / 4,
  ENGINE_MIDDLE_BUTTON_UP = 84 / 4,
  ENGINE_MOUSE_MOVE = 88 / 4,
  ENGINE_RIGHT_BUTTON_DOWN = 104 / 4,
  ENGINE_RIGHT_BUTTON_UP = 108 / 4,
  ENGINE_SYSTEM_CHARACTER = 120 / 4,
  ENGINE_SYSTEM_KEY_DOWN = 124 / 4,
  ENGINE_SYSTEM_KEY_UP = 128 / 4,
  ENGINE_MESSAGE_FILTER = 152 / 4
};

/* gk3/GK3R_rest.c */
extern int game_engine_address;
extern int fullscreen_flag_address;
extern int window_menu_resource_id;
extern char byte_75D7E4;
extern char byte_77368C;
extern int zero_point_x;
extern int zero_point_y;

/* engine/game_engine.c */
extern void destroy_game_engine(void);
extern void __thiscall pause_game_engine_with_gdi_surface(void *engine);
extern void __thiscall resume_game_engine(int engine);
extern int __thiscall get_engine_object_by_id(uint32_t *engine, uint16_t resource_id);

/* platform/window_proc.c */
extern char __thiscall render_game_window_paint_region(uint32_t *engine,
                                                       PAINTSTRUCT *paint);

/* platform/window_geometry.c */
extern int __thiscall update_cached_window_geometry(int engine);
extern int __thiscall clamp_rectangle_to_bounds(int *rectangle, int *bounds);

/* engine/game_engine.c */
extern int __thiscall restore_lost_graphics_surfaces(int engine, char force);

typedef char (__thiscall *EnginePaintCallback)(uint32_t *engine);

/* gk3/GK3R_rest.c */
extern int frame_number;
extern void __thiscall lock_critical_section_pair(LPCRITICAL_SECTION *section);

/* gk3/GK3R_rest.c */
extern uint32_t *__thiscall intersect_rectangles(uint32_t *result, uint32_t *rectangle,
                                       uint32_t *bounds);
extern int __thiscall translate_rectangle(uint32_t *rectangle, int x, int y);

/* gk3/GK3R_rest.c */
extern int __thiscall probe_surface_lock(int surface, int flags);
extern bool __thiscall copy_surface_region(int destination_surface, int source_surface,
                                  uint32_t *destination_rectangle,
                                  uint32_t *source_rectangle);
extern uint32_t *__thiscall initialize_sprite_blit_context(
    uint32_t *temporary, int destination_surface, int source_surface,
    uint32_t *destination_rectangle, uint32_t *source_rectangle, int options);
extern void __thiscall destroy_sprite_blit_context(int temporary);

/* platform/window_proc.c */
extern char __thiscall blit_surface_region(
    int *destination, uint32_t *source, int *origin,
    uint32_t *paint_rectangle, uint32_t *options);

/* common/memory.c */
extern void __cdecl free_tracked_memory(int address);
extern uint32_t *__cdecl allocate_tracked_memory(int size);

int __thiscall destroy_message_hook_list(int *message_hook_words)
{
  WindowMessageHookRegistry *registry =
      (WindowMessageHookRegistry *)(void *)message_hook_words;
  WindowMessageHookEntry *head =
      (WindowMessageHookEntry *)(uintptr_t)registry->list_head;
  WindowMessageHookEntry *hook =
      (WindowMessageHookEntry *)(uintptr_t)head->next;

  while (hook != head) {
    WindowMessageHookEntry *next =
        (WindowMessageHookEntry *)(uintptr_t)hook->next;
    WindowMessageHookEntry *previous =
        (WindowMessageHookEntry *)(uintptr_t)hook->previous;
    previous->next = hook->next;
    next->previous = hook->previous;
    free_tracked_memory((int)(intptr_t)hook);
    --registry->count;
    hook = next;
  }

  free_tracked_memory((int)(intptr_t)head);
  registry->list_head = 0;
  registry->count = 0;
  return 0;
}

/* Loads the sprite on demand, then returns its surface wrapper. */
int __thiscall get_sprite_surface(uint32_t *source)
{
  SpriteResourceState *sprite = (SpriteResourceState *)(void *)source;
  if (!sprite->is_loaded) {
    typedef void (__thiscall *LoadSpriteMethod)(SpriteResourceState *);
    uint32_t *methods = (uint32_t *)(uintptr_t)sprite->vtable_address;
    ((LoadSpriteMethod)(uintptr_t)methods[1])(sprite);
  }

  sprite->last_used_frame = (uint32_t)frame_number;
  return (int)sprite->surface_wrapper_address;
}

/* Clips and blits a region between two DirectDraw surfaces. */
char __thiscall blit_clipped_surface_region(int this, int a2, int a3, int a4, _DWORD *a5,
                           _DWORD *a6)
{
  int v6; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int *v12; // ecx
  int v13; // eax
  int v14; // ebx
  int v15; // ecx
  int v16; // esi
  int *v18; // esi
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // esi
  _DWORD *v23; // eax
  void (__thiscall **v24)(_DWORD *); // edx
  void (__stdcall *v25)(LPCRITICAL_SECTION); // esi
  bool v26; // bl
  struct _RTL_CRITICAL_SECTION *v27; // eax
  _DWORD v28[20];
  _DWORD v29[4];
  _DWORD v30[2];
  int v31;
  int v32;
  _DWORD v33[2];
  int v34;
  int v35;
  _DWORD v36[4];
  int v37;
  int v38;
  int v39;
  int v40;
  int v41;
  int v42;
  int v43;
  int v44;
  LPCRITICAL_SECTION lpCriticalSection;
  LPCRITICAL_SECTION v46;
  int v47;
  int v48;

  v6 = a2;
  v46 = (LPCRITICAL_SECTION)(a2 + 16);
  lpCriticalSection = (LPCRITICAL_SECTION)(this + 16);
  lock_critical_section_pair(&lpCriticalSection);
  v8 = *(int *)(a2 + 56);
  v31 = *(int *)(this + 56);
  v9 = *(int *)(a2 + 60);
  v32 = *(int *)(this + 60);
  v10 = zero_point_x;
  v47 = 0;
  v34 = zero_point_x + v8;
  v33[0] = zero_point_x;
  v35 = zero_point_y + v9;
  v29[0] = zero_point_x;
  v29[2] = zero_point_x + v31;
  v33[1] = zero_point_y;
  v29[1] = zero_point_y;
  v29[3] = v32 + zero_point_y;
  if (a5) {
    v12 = (int *)intersect_rectangles(v30, (uint32_t *)a5, (uint32_t *)v33);
    v10 = *v12;
    v41 = v10;
    v42 = v12[1];
    v13 = v12[2];
    v48 = v42 - a5[1];
    v14 = v10 - *a5;
    v43 = v13;
    v15 = v12[3];
    a3 += v14;
    v16 = v42;
    a4 += v48;
    v6 = a2;
    v44 = v15;
  } else {
    v15 = v35;
    v16 = zero_point_y;
    v13 = v34;
    v41 = zero_point_x;
    v42 = zero_point_y;
    v43 = v34;
    v44 = v35;
  }
  if (v10 >= v13 || v16 >= v15) {
    if (lpCriticalSection[1].DebugInfo)
      LeaveCriticalSection(lpCriticalSection);
    if (v46[1].DebugInfo) {
      LeaveCriticalSection(v46);
      return 1;
    }
    return 1;
  }
  v39 = zero_point_x + v13 - v10;
  v38 = zero_point_y;
  v37 = zero_point_x;
  v40 = v15 - v16 + zero_point_y;
  translate_rectangle((uint32_t *)&v37, a3, a4);
  v18 = (int *)intersect_rectangles(v30, (uint32_t *)&v37, (uint32_t *)v29);
  v19 = *v18;
  v36[0] = v19;
  v20 = v18[1];
  v36[1] = v20;
  v21 = v18[2];
  v36[2] = v21;
  v22 = v18[3];
  v36[3] = v22;
  if (v19 >= v21 || v20 >= v22) {
    if (lpCriticalSection[1].DebugInfo)
      LeaveCriticalSection(lpCriticalSection);
    if (v46[1].DebugInfo) {
      LeaveCriticalSection(v46);
      return 1;
    }
    return 1;
  }
  v41 += v19 - v37;
  v42 += v20 - v38;
  v43 += v21 - v39;
  v44 += v22 - v40;
  if (!a6 || !*a6) {
    v25 = LeaveCriticalSection;
    v26 = copy_surface_region(this, v6, (uint32_t *)v36, (uint32_t *)&v41);
    if (lpCriticalSection[1].DebugInfo)
      LeaveCriticalSection(lpCriticalSection);
    v27 = v46;
    if (!v46[1].DebugInfo)
      return v26;
    goto LABEL_32;
  }
  if (probe_surface_lock(v6, 0xFFFF) && probe_surface_lock(this, 0xFFFF)) {
    v23 = initialize_sprite_blit_context(v28, this, v6, (uint32_t *)v36,
                     (uint32_t *)&v41, (int)a6);
    v24 = (void (__thiscall **)(_DWORD *))*v23;
    LOBYTE(v47) = 1;
    (*v24)(v23);
    LOBYTE(v47) = 0;
    destroy_sprite_blit_context((int)v28);
    if (lpCriticalSection[1].DebugInfo)
      LeaveCriticalSection(lpCriticalSection);
    if (v46[1].DebugInfo)
      LeaveCriticalSection(v46);
    return 1;
  }
  v25 = LeaveCriticalSection;
  v26 = copy_surface_region(this, v6, (uint32_t *)v36, (uint32_t *)&v41);
  if (lpCriticalSection[1].DebugInfo)
    LeaveCriticalSection(lpCriticalSection);
  v27 = v46;
  if (v46[1].DebugInfo)
LABEL_32:
    v25(v27);
  return v26;
}

char __thiscall blit_surface_region(
    int *destination, uint32_t *source, int *origin,
    uint32_t *paint_rectangle, uint32_t *options)
{
  return blit_clipped_surface_region(destination[12], get_sprite_surface(source),
                    origin[0], origin[1], paint_rectangle, options);
}

uint32_t *__thiscall register_window_message_hook(
    uint32_t *engine, uint32_t callback, uint32_t context,
    char insert_before_equal_priority, int priority)
{
  WindowMessageHookRegistry *registry =
      (WindowMessageHookRegistry *)(uintptr_t)engine[ENGINE_MESSAGE_HOOKS_OFFSET / 4];
  WindowMessageHookEntry *head =
      (WindowMessageHookEntry *)(uintptr_t)registry->list_head;
  WindowMessageHookEntry *hook =
      (WindowMessageHookEntry *)(uintptr_t)head->next;

  while (hook != head) {
    if (hook->callback == callback && hook->context == context)
      return (uint32_t *)(uintptr_t)hook;
    hook = (WindowMessageHookEntry *)(uintptr_t)hook->next;
  }

  hook = (WindowMessageHookEntry *)allocate_tracked_memory(sizeof(*hook));
  WindowMessageHookEntry *position =
      (WindowMessageHookEntry *)(uintptr_t)head->next;
  while (position != head
         && (insert_before_equal_priority
                 ? priority > position->priority
                 : priority >= position->priority)) {
    position = (WindowMessageHookEntry *)(uintptr_t)position->next;
  }

  WindowMessageHookEntry *previous =
      (WindowMessageHookEntry *)(uintptr_t)position->previous;
  hook->next = (uint32_t)(uintptr_t)position;
  hook->previous = (uint32_t)(uintptr_t)previous;
  hook->callback = callback;
  hook->context = context;
  hook->priority = priority;
  previous->next = (uint32_t)(uintptr_t)hook;
  position->previous = (uint32_t)(uintptr_t)hook;
  ++registry->count;
  return (uint32_t *)(uintptr_t)registry;
}

static char is_sprite_surface_locked(int sprite_address)
{
  const SpriteResourceState *sprite =
      (const SpriteResourceState *)(uintptr_t)(uint32_t)sprite_address;
  if (!sprite->is_loaded || !sprite->surface_wrapper_address)
    return 0;

  const SurfaceLockState *surface = (const SurfaceLockState *)(uintptr_t)
      sprite->surface_wrapper_address;
  return surface->locked_pixel_buffer_address != 0;
}

char __thiscall render_game_window_paint_region(uint32_t *engine,
                                                 PAINTSTRUCT *paint)
{
  if (!engine[ENGINE_INITIALIZED_OFFSET / sizeof(uint32_t)])
    return 0;

  uint32_t *engine_methods = (uint32_t *)(uintptr_t)engine[0];
  const EnginePaintCallback update_paint = (EnginePaintCallback)(uintptr_t)
      engine_methods[52 / sizeof(uint32_t)];
  const uint8_t *fullscreen_flag =
      (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (*fullscreen_flag)
    return update_paint(engine);

  update_paint(engine);

  RECT paint_rectangle = paint->rcPaint;
  const POINT client_area_origin = *(const POINT *)
      ((const uint8_t *)engine + ENGINE_CLIENT_AREA_ORIGIN_OFFSET);
  POINT render_origin = {
    client_area_origin.x + paint_rectangle.left,
    client_area_origin.y + paint_rectangle.top
  };

  const uint16_t destination_id = (uint16_t)engine[8];
  const uint16_t source_id = (uint16_t)engine[6];
  if (is_sprite_surface_locked(get_engine_object_by_id(engine, destination_id)))
    return 1;
  if (is_sprite_surface_locked(get_engine_object_by_id(engine, source_id)))
    return 1;

  int *destination = (int *)(uintptr_t)(uint32_t)
      get_engine_object_by_id(engine, destination_id);
  uint32_t *source = (uint32_t *)(uintptr_t)(uint32_t)
      get_engine_object_by_id(engine, source_id);
  return blit_surface_region(destination, source, (int *)&render_origin,
                             (uint32_t *)&paint_rectangle, NULL);
}

static void __thiscall update_window_geometry_after_move(uint8_t *engine)
{
  const uint8_t *fullscreen_flag = (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (!*fullscreen_flag)
    update_cached_window_geometry((int)(uintptr_t)engine);
}

static void __thiscall adjust_moving_window_rectangle(uint8_t *engine, RECT *rectangle)
{
  const uint8_t *fullscreen_flag = (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (*fullscreen_flag) {
    *rectangle = *(const RECT *)(engine + ENGINE_OUTER_WINDOW_BOUNDS_OFFSET);
    return;
  }

  if (!byte_75D7E4)
    return;

  if (byte_77368C) {
    POINT origin = {rectangle->left, rectangle->top};
    ScreenToClient(*(HWND *)(engine + ENGINE_WINDOW_OFFSET), &origin);
    const LONG horizontal_shift = origin.x - rectangle->left;
    const LONG vertical_shift = origin.y - rectangle->top;
    rectangle->left = origin.x;
    rectangle->top = origin.y;
    rectangle->right += horizontal_shift;
    rectangle->bottom += vertical_shift;
    return;
  }

  RECT bounds;
  const int virtual_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
  const int virtual_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
  if (virtual_width > 0) {
    bounds.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
    bounds.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
    bounds.right = bounds.left + virtual_width;
    bounds.bottom = bounds.top + virtual_height;
  } else {
    bounds.left = zero_point_x;
    bounds.top = zero_point_y;
    bounds.right = bounds.left + GetSystemMetrics(SM_CXSCREEN);
    bounds.bottom = bounds.top + GetSystemMetrics(SM_CYSCREEN);
  }
  clamp_rectangle_to_bounds((int *)rectangle, (int *)&bounds);
}

static void __thiscall set_window_size_limits(const uint8_t *engine, MINMAXINFO *limits)
{
  const RECT *saved_window_rectangle =
      (const RECT *)(engine + ENGINE_OUTER_WINDOW_BOUNDS_OFFSET);
  const LONG width = saved_window_rectangle->right - saved_window_rectangle->left;
  const LONG height = saved_window_rectangle->bottom - saved_window_rectangle->top;

  limits->ptMaxSize.x = width;
  limits->ptMaxSize.y = height;
  limits->ptMinTrackSize.x = width;
  limits->ptMinTrackSize.y = height;
  limits->ptMaxTrackSize.x = width;
  limits->ptMaxTrackSize.y = height;

  const uint8_t *fullscreen_flag = (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (*fullscreen_flag) {
    limits->ptMaxPosition.x = saved_window_rectangle->left;
    limits->ptMaxPosition.y = saved_window_rectangle->top;
  }
}

LRESULT CALLBACK game_window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)game_engine_address;
  const uint8_t *fullscreen_flag = (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  if (!engine || !*(uint32_t *)(engine + ENGINE_INITIALIZED_OFFSET))
    return DefWindowProcA(window, message, wparam, lparam);

  POINT mouse_position = {0};
  LPARAM forwarded_lparam = lparam;
  if (message >= WM_MOUSEMOVE && message <= WM_MBUTTONDBLCLK) {
    mouse_position.x = (int16_t)LOWORD(lparam)
        + *(int32_t *)(engine + ENGINE_COORDINATE_ORIGIN_X_OFFSET);
    mouse_position.y = (int16_t)HIWORD(lparam)
        + *(int32_t *)(engine + ENGINE_COORDINATE_ORIGIN_Y_OFFSET);

    const RECT *cursor_bounds = (const RECT *)(engine + ENGINE_VIEWPORT_BOUNDS_OFFSET);
    const int paused = *(int32_t *)(engine + ENGINE_PAUSED_OFFSET);
    const uint32_t render_flags = *(uint32_t *)(engine + ENGINE_RENDER_FLAGS_OFFSET);
    if (*fullscreen_flag && paused <= 0 && !(render_flags & 1)
        && (mouse_position.x < cursor_bounds->left
            || mouse_position.y < cursor_bounds->top
            || mouse_position.x >= cursor_bounds->right
            || mouse_position.y >= cursor_bounds->bottom)) {
      if (mouse_position.x < cursor_bounds->left)
        mouse_position.x = cursor_bounds->left;
      else if (mouse_position.x >= cursor_bounds->right)
        mouse_position.x = cursor_bounds->right - 1;

      if (mouse_position.y < cursor_bounds->top)
        mouse_position.y = cursor_bounds->top;
      else if (mouse_position.y >= cursor_bounds->bottom)
        mouse_position.y = cursor_bounds->bottom - 1;

      SetCursorPos(mouse_position.x, mouse_position.y);
      forwarded_lparam = MAKELPARAM(mouse_position.x, mouse_position.y);
    }
  }

  uint8_t *hook_registry = *(uint8_t **)(engine + ENGINE_MESSAGE_HOOKS_OFFSET);
  if (hook_registry) {
    WindowMessageHook *head = *(WindowMessageHook **)(hook_registry + 4);
    for (WindowMessageHook *hook = head->next; hook != head; hook = hook->next) {
      WPARAM hook_result = 0;
      if (hook->callback) {
        if (hook->callback(window, message, wparam, forwarded_lparam,
                           hook->context, &hook_result) == 1)
          return (LRESULT)hook_result;
        engine = (uint8_t *)(uintptr_t)game_engine_address;
      }
    }
  }

  void **methods = *(void ***)engine;
  if (((MessageFilter)methods[ENGINE_MESSAGE_FILTER])(engine, message, wparam,
                                                       forwarded_lparam) == 1)
    return 0;
  engine = (uint8_t *)(uintptr_t)game_engine_address;
  methods = *(void ***)engine;

  switch (message) {
    case WM_MOVE:
      update_window_geometry_after_move(engine);
      return 0;

    case WM_SIZE:
      if (wparam == SIZE_MINIMIZED)
        pause_game_engine_with_gdi_surface(engine);
      else if (wparam == SIZE_RESTORED || wparam == SIZE_MAXIMIZED)
        resume_game_engine(game_engine_address);
      return 0;

    case WM_ACTIVATE:
      if (!window_menu_resource_id)
        break;
      if (LOWORD(wparam) == WA_INACTIVE)
        pause_game_engine_with_gdi_surface(engine);
      else
        resume_game_engine((int)(uintptr_t)engine);
      return 0;

    case WM_PAINT: {
      if (!*(uint32_t *)(engine + ENGINE_INITIALIZED_OFFSET) || IsIconic(window))
        break;
      PAINTSTRUCT paint;
      BeginPaint(window, &paint);
      if (paint.rcPaint.left < paint.rcPaint.right
          && paint.rcPaint.top < paint.rcPaint.bottom)
        render_game_window_paint_region((uint32_t *)engine, &paint);
      EndPaint(window, &paint);
      return 0;
    }

    case WM_CLOSE:
      destroy_game_engine();
      PostQuitMessage(0);
      break;

    case WM_ACTIVATEAPP:
      if (*(uint8_t *)(engine + ENGINE_RENDER_FLAGS_OFFSET) & 1)
        return 0;
      if (wparam) {
        restore_lost_graphics_surfaces((int)(uintptr_t)engine, 1);
        engine = (uint8_t *)(uintptr_t)game_engine_address;
        if (*fullscreen_flag) {
          const RECT *saved_rect = (const RECT *)(engine + ENGINE_OUTER_WINDOW_BOUNDS_OFFSET);
          if (saved_rect->left < saved_rect->right
              && saved_rect->top < saved_rect->bottom) {
            HWND game_window = *(HWND *)(engine + ENGINE_WINDOW_OFFSET);
            MoveWindow(game_window, saved_rect->left, saved_rect->top,
                       saved_rect->right - saved_rect->left,
                       saved_rect->bottom - saved_rect->top, FALSE);
            ShowWindow(game_window, SW_MAXIMIZE);
          }
        }
        resume_game_engine(game_engine_address);
      } else {
        if (*fullscreen_flag)
          ShowWindow(*(HWND *)(engine + ENGINE_WINDOW_OFFSET), SW_MINIMIZE);
        pause_game_engine_with_gdi_surface((void *)(uintptr_t)game_engine_address);
      }
      return 0;

    case WM_SETCURSOR:
      if (LOWORD(lparam) != HTCLIENT
          || *(int32_t *)(engine + ENGINE_PAUSED_OFFSET) > 0)
        break;
      SetCursor(NULL);
      return TRUE;

    case WM_MOUSEACTIVATE:
      return MA_ACTIVATEANDEAT;

    case WM_GETMINMAXINFO:
      set_window_size_limits(engine, (MINMAXINFO *)(uintptr_t)lparam);
      return 0;

    case WM_DISPLAYCHANGE:
      if (*fullscreen_flag
          && *(int32_t *)(engine + ENGINE_PAUSED_OFFSET) <= 0)
        restore_lost_graphics_surfaces((int)(uintptr_t)engine, 0);
      return 0;

    case WM_NCHITTEST: {
      if (*fullscreen_flag)
        break;
      LRESULT hit = DefWindowProcA(window, message, wparam, forwarded_lparam);
      return hit >= HTLEFT && hit <= HTBOTTOMRIGHT ? HTCAPTION : hit;
    }

    case WM_KEYDOWN:
      ((KeyHandler)methods[ENGINE_KEY_DOWN])(engine, wparam, forwarded_lparam);
      return 0;

    case WM_KEYUP:
      ((KeyHandler)methods[ENGINE_KEY_UP])(engine, wparam, forwarded_lparam);
      return 0;

    case WM_CHAR:
      ((CharacterHandler)methods[ENGINE_CHARACTER_HANDLER])(engine, wparam,
                                                              forwarded_lparam);
      return 0;

    case WM_SYSKEYDOWN:
      if (wparam == VK_F10) {
        ((KeyHandler)methods[ENGINE_KEY_DOWN])(engine, wparam, forwarded_lparam);
        return 1;
      }
      if (((SystemKeyHandler)methods[ENGINE_SYSTEM_KEY_DOWN])(engine, wparam,
                                                               forwarded_lparam))
        return 0;
      break;

    case WM_SYSKEYUP:
      if (wparam == VK_F10) {
        ((KeyHandler)methods[ENGINE_KEY_UP])(engine, wparam, forwarded_lparam);
        return 1;
      }
      if (((SystemKeyHandler)methods[ENGINE_SYSTEM_KEY_UP])(engine, wparam,
                                                             forwarded_lparam))
        return 0;
      break;

    case WM_SYSCHAR:
      if (((SystemKeyHandler)methods[ENGINE_SYSTEM_CHARACTER])(engine, wparam,
                                                                 forwarded_lparam))
        return 0;
      break;

    case WM_SYSCOMMAND:
      if ((wparam & 0xfff0) == SC_SCREENSAVE
          || (wparam & 0xfff0) == SC_MONITORPOWER)
        return 0;
      break;

    case WM_MOUSEMOVE:
      ((PointHandler)methods[ENGINE_MOUSE_MOVE])(engine, &mouse_position);
      return 0;

    case WM_LBUTTONDOWN:
      if (*(int32_t *)(engine + ENGINE_PAUSED_OFFSET) <= 0)
        ((PointHandler)methods[ENGINE_LEFT_BUTTON_DOWN])(engine, &mouse_position);
      return 0;

    case WM_LBUTTONUP:
      ((PointHandler)methods[ENGINE_LEFT_BUTTON_UP])(engine, &mouse_position);
      return 0;

    case WM_RBUTTONDOWN:
      if (*(int32_t *)(engine + ENGINE_PAUSED_OFFSET) <= 0)
        ((PointHandler)methods[ENGINE_RIGHT_BUTTON_DOWN])(engine, &mouse_position);
      return 0;

    case WM_RBUTTONUP:
      ((PointHandler)methods[ENGINE_RIGHT_BUTTON_UP])(engine, &mouse_position);
      return 0;

    case WM_MBUTTONDOWN:
      if (*(int32_t *)(engine + ENGINE_PAUSED_OFFSET) <= 0)
        ((PointHandler)methods[ENGINE_MIDDLE_BUTTON_DOWN])(engine, &mouse_position);
      return 0;

    case WM_MBUTTONUP:
      ((PointHandler)methods[ENGINE_MIDDLE_BUTTON_UP])(engine, &mouse_position);
      return 0;

    case WM_MOVING:
      adjust_moving_window_rectangle(engine, (RECT *)(uintptr_t)forwarded_lparam);
      return 0;
  }

  return DefWindowProcA(window, message, wparam, forwarded_lparam);
}
