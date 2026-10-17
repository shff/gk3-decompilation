#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

/* Layouts of the cleanup objects allocated by the 32-bit executable. */
typedef struct WindowCleanupNode {
  void *methods;
  struct WindowCleanupNode *next;
  HWND window;
} WindowCleanupNode;

typedef struct ClassCleanupNode {
  void *methods;
  struct ClassCleanupNode *next;
} ClassCleanupNode;

typedef BOOL (__thiscall *QueueEngineStartMethod)(int engine);

/* gk3/GK3R_rest.c */
extern int window_icon_resource_id;
extern UINT window_title_resource_id;
extern int window_menu_resource_id;
extern int requested_window_x;
extern int requested_window_y;
extern int display_width;
extern int display_height;
extern char fullscreen_enabled;
extern int game_engine_address; /* Current game engine object. */
extern int window_cleanup_head;
extern int zero_point_x; /* X of the shared zero point. */
extern int zero_point_y; /* Y of the shared zero point. */
extern LPCSTR game_window_class_name;
extern void (*cleanup_pure_virtual_method)(void);
extern void (*class_cleanup_method)(void);
extern void *window_cleanup_method;

/* platform/window_proc.c */
extern LRESULT CALLBACK game_window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* platform/window_geometry.c */
extern int __thiscall clamp_rectangle_to_bounds(int *rectangle, int *bounds);

/* engine/game_engine.c */
extern char *__cdecl create_game_engine(int command_line);
extern char __thiscall initialize_game_engine(uint32_t *engine, HWND window, HINSTANCE instance, int command_line);
extern void __thiscall pause_game_engine(int engine, char flip_to_gdi_surface);

HWND __cdecl create_game_window(HINSTANCE instance, uint32_t previous_instance, uint32_t command_line)
{
  const int icon_id = window_icon_resource_id ? (uint16_t)window_icon_resource_id : 32512;
  const bool fullscreen = fullscreen_enabled != 0;
  const int client_width = display_width;
  const int client_height = display_height;
  HICON icon = LoadIconA(window_icon_resource_id ? instance : NULL, MAKEINTRESOURCEA(icon_id));

  if (!previous_instance) {
    WNDCLASSA window_class = {0};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = game_window_proc;
    window_class.hInstance = instance;
    window_class.hIcon = icon;
    window_class.hCursor = LoadCursorA(NULL, IDC_WAIT);
    window_class.hbrBackground = GetStockObject(BLACK_BRUSH);
    window_class.lpszMenuName = window_menu_resource_id ? MAKEINTRESOURCEA((uint16_t)window_menu_resource_id) : NULL;
    window_class.lpszClassName = game_window_class_name;
    if (!RegisterClassA(&window_class))
      return NULL;
  }

  char title[52] = {0};
  if (window_title_resource_id)
    LoadStringA(instance, window_title_resource_id, title, 50);

  RECT screen;
  const int virtual_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
  const int virtual_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
  if (virtual_width > 0) {
    screen.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
    screen.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
    screen.right = screen.left + virtual_width;
    screen.bottom = screen.top + virtual_height;
  } else {
    screen.left = zero_point_x;
    screen.top = zero_point_y;
    screen.right = screen.left + GetSystemMetrics(SM_CXSCREEN);
    screen.bottom = screen.top + GetSystemMetrics(SM_CYSCREEN);
  }

  const int frame_width = 2 * GetSystemMetrics(SM_CXFRAME);
  int frame_height = GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYFRAME);
  if (window_menu_resource_id)
    frame_height += GetSystemMetrics(SM_CYMENU);

  RECT rectangle = {
    zero_point_x,
    zero_point_y,
    zero_point_x + frame_width + client_width,
    zero_point_y + frame_height + client_height
  };
  int x = requested_window_x;
  int y = requested_window_y;

  if (fullscreen) {
    x = 0;
    y = 0;
  } else {
    if (x != (int)0x80000000u) {
      const int width = rectangle.right - rectangle.left;
      rectangle.left = x == 0x40000000
        ? rectangle.left + (screen.left + screen.right) / 2 - (rectangle.left + rectangle.right) / 2
        : x;
      rectangle.right = rectangle.left + width;
      clamp_rectangle_to_bounds((int *)&rectangle, (int *)&screen);
      x = rectangle.left;
    }
    if (y != (int)0x80000000u) {
      const int height = rectangle.bottom - rectangle.top;
      rectangle.top = y == 0x40000000
        ? rectangle.top + (screen.top + screen.bottom) / 2 - (rectangle.top + rectangle.bottom) / 2
        : y;
      rectangle.bottom = rectangle.top + height;
      clamp_rectangle_to_bounds((int *)&rectangle, (int *)&screen);
      y = rectangle.top;
    }
  }

  HWND window = CreateWindowExA(
    fullscreen ? WS_EX_TOPMOST : 0,
    game_window_class_name, title, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
    x, y, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top,
    NULL, NULL, instance, NULL);
  if (!window)
    return NULL;

  WindowCleanupNode *window_cleanup = (WindowCleanupNode *)allocate_tracked_memory(sizeof(WindowCleanupNode));
  if (window_cleanup) {
    window_cleanup->methods = &cleanup_pure_virtual_method;
    window_cleanup->next = (WindowCleanupNode *)(uintptr_t)window_cleanup_head;
    window_cleanup_head = (int)(uintptr_t)window_cleanup;
    window_cleanup->window = window;
    window_cleanup->methods = &window_cleanup_method;
  }
  if (icon) {
    SendMessageA(window, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessageA(window, WM_SETICON, ICON_SMALL, (LPARAM)icon);
  }
  ClassCleanupNode *class_cleanup = (ClassCleanupNode *)allocate_tracked_memory(sizeof(ClassCleanupNode));
  if (class_cleanup) {
    class_cleanup->methods = &cleanup_pure_virtual_method;
    class_cleanup->next = (ClassCleanupNode *)(uintptr_t)window_cleanup_head;
    window_cleanup_head = (int)(uintptr_t)class_cleanup;
    class_cleanup->methods = &class_cleanup_method;
  }

  int engine_address = (int)(uintptr_t)create_game_engine((int)command_line);
  game_engine_address = engine_address;
  initialize_game_engine((uint32_t *)(uintptr_t)engine_address, window, instance, (int)command_line);
  SetClassLongA(window, GCL_HCURSOR, (LONG)LoadCursorA(NULL, IDC_ARROW));
  SetCursor(NULL);
  uint32_t *vtable = *(uint32_t **)(uintptr_t)engine_address;
  /* Vtable slot 9 posts WM_USER + 1, which starts the game after setup. */
  ((QueueEngineStartMethod)(uintptr_t)vtable[9])(engine_address);
  pause_game_engine(engine_address, 0);
  return window;
}
