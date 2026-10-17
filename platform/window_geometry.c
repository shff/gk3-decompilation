#include <stddef.h>
#include <stdint.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int fullscreen_flag_address;
extern int display_width;
extern int display_height;
extern int zero_point_x;
extern int zero_point_y;

typedef struct {
  RECT outer_window_bounds;
  RECT viewport_bounds;
  POINT client_area_origin;
  POINT coordinate_origin;
} CachedWindowGeometry;

_Static_assert(sizeof(CachedWindowGeometry) == 48, "cached window geometry size");
_Static_assert(offsetof(CachedWindowGeometry, viewport_bounds) == 16,
               "viewport bounds offset");
_Static_assert(offsetof(CachedWindowGeometry, client_area_origin) == 32,
               "client origin offset");
_Static_assert(offsetof(CachedWindowGeometry, coordinate_origin) == 40,
               "coordinate origin offset");

int __thiscall clamp_rectangle_to_bounds(int *rectangle, int *bounds)
{
  enum { LEFT, TOP, RIGHT, BOTTOM };

  if (rectangle[LEFT] >= bounds[LEFT] && rectangle[TOP] >= bounds[TOP]
      && rectangle[RIGHT] <= bounds[RIGHT] && rectangle[BOTTOM] <= bounds[BOTTOM])
    return 0;

  int horizontal_shift = 0;
  if (rectangle[LEFT] < bounds[LEFT])
    horizontal_shift = bounds[LEFT] - rectangle[LEFT];
  else if (rectangle[RIGHT] > bounds[RIGHT])
    horizontal_shift = bounds[RIGHT] - rectangle[RIGHT];
  rectangle[LEFT] += horizontal_shift;
  rectangle[RIGHT] += horizontal_shift;

  int vertical_shift = 0;
  if (rectangle[TOP] < bounds[TOP])
    vertical_shift = bounds[TOP] - rectangle[TOP];
  else if (rectangle[BOTTOM] > bounds[BOTTOM])
    vertical_shift = bounds[BOTTOM] - rectangle[BOTTOM];
  rectangle[TOP] += vertical_shift;
  rectangle[BOTTOM] += vertical_shift;

  return 1;
}

int __thiscall update_cached_window_geometry(int engine_address)
{
  uint8_t *engine = (uint8_t *)(uintptr_t)(uint32_t)engine_address;
  HWND window = (HWND)(uintptr_t)*(uint32_t *)(engine + 16);
  CachedWindowGeometry *geometry =
      (CachedWindowGeometry *)(engine + 40);

  if (IsIconic(window))
    return 1;

  GetWindowRect(window, &geometry->outer_window_bounds);

  RECT client_bounds;
  GetClientRect(window, &client_bounds);
  POINT client_origin = {client_bounds.left, client_bounds.top};
  POINT client_end = {client_bounds.right, client_bounds.bottom};
  ClientToScreen(window, &client_origin);
  ClientToScreen(window, &client_end);

  const uint8_t *fullscreen_flag =
      (const uint8_t *)(uintptr_t)fullscreen_flag_address;
  const RECT *outer = &geometry->outer_window_bounds;
  RECT *viewport = &geometry->viewport_bounds;
  if (*fullscreen_flag) {
    if ((*(uint32_t *)(engine + 152) & 0x100) != 0) {
      viewport->left = zero_point_x;
      viewport->top = zero_point_y;
      viewport->right = zero_point_x + outer->right - outer->left;
      viewport->bottom = zero_point_y + outer->bottom - outer->top;
      geometry->client_area_origin.x = outer->left;
      geometry->client_area_origin.y = outer->top;
    } else {
      viewport->left = 0;
      viewport->top = 0;
      viewport->right = display_width;
      viewport->bottom = display_height;
      geometry->client_area_origin.x = zero_point_x;
      geometry->client_area_origin.y = zero_point_y;
    }

    geometry->coordinate_origin.x = client_origin.x - outer->left;
    geometry->coordinate_origin.y = client_origin.y - outer->top;
    return geometry->coordinate_origin.x;
  }

  const LONG client_width = client_end.x - client_origin.x;
  const LONG client_height = client_end.y - client_origin.y;
  viewport->left = zero_point_x;
  viewport->top = zero_point_y;
  viewport->right = zero_point_x + client_width;
  viewport->bottom = zero_point_y + client_height;
  geometry->client_area_origin.x = client_origin.x;
  geometry->client_area_origin.y = client_origin.y;
  geometry->coordinate_origin.x = zero_point_x;
  geometry->coordinate_origin.y = zero_point_y;
  return zero_point_x;
}
