#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int system_profile_address;
extern const char Key[4];
extern int __thiscall get_or_create_control_tooltip_storage(
    uint32_t *control);
extern int __thiscall notify_control_tooltip_text_changed(uint8_t *control);
extern bool __cdecl strings_differ(const char *first, char *second,
                                   size_t max_count);
extern char *__thiscall assign_std_string_storage(char *storage,
                                                  const char *value,
                                                  size_t length);
extern void __cdecl report_directx_call_failure(int result,
                                                const char *source,
                                                int line, char flags);

char __thiscall set_control_tooltip_text(uint32_t *control, char *text)
{
  char *storage =
      (char *)(uintptr_t)get_or_create_control_tooltip_storage(control);
  const char *current_text = *(const char **)(void *)(storage + 8);

  if (current_text == NULL)
    current_text = Key;

  if (!strings_differ(current_text, text, (size_t)-1))
    return 0;

  storage =
      (char *)(uintptr_t)get_or_create_control_tooltip_storage(control);
  assign_std_string_storage(storage, text, strlen(text));
  return (char)notify_control_tooltip_text_changed(
      (uint8_t *)(void *)control);
}

int __thiscall lock_graphics_surface(int surface, int flags)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)surface;
  CRITICAL_SECTION *lock = (CRITICAL_SECTION *)(void *)(bytes + 16);
  uint32_t description[31];

  if (*(int32_t *)(void *)(bytes + 40) != 0)
    EnterCriticalSection(lock);

  int lock_count = ++*(int32_t *)(void *)(bytes + 52);
  if (lock_count == 1) {
    if ((bytes[4] & 8) != 0) {
      *(uint32_t *)(void *)(bytes + 48) = (uint32_t)(surface + 14);
    } else {
      memset(description, 0, 0x6c);
      description[0] = 108;

      uint32_t lock_flags = 1;
      if (flags == 1)
        lock_flags = 17;
      else if (flags == 2)
        lock_flags = 33;
      if (*(int32_t *)(uintptr_t)(system_profile_address + 100) != 3)
        lock_flags |= 0x800;

      uint32_t *surface_interface =
          *(uint32_t **)(void *)(bytes + 44);
      typedef int (__stdcall *LockSurfaceMethod)(uint32_t, uint32_t,
                                                 uint32_t *, int, uint32_t);
      LockSurfaceMethod lock_surface = (LockSurfaceMethod)(uintptr_t)
          *(uint32_t *)(uintptr_t)(surface_interface[0] + 100);
      int result = lock_surface((uint32_t)(uintptr_t)surface_interface,
                                0, description, (int)lock_flags, 0);
      report_directx_call_failure(
          result, "Z:\\Proj\\GK3\\GEngine\\gsurface.cpp", 975, 0);
      *(uint32_t *)(void *)(bytes + 48) = description[9];
    }
  }

  int address = *(int32_t *)(void *)(bytes + 48);
  if (*(int32_t *)(void *)(bytes + 40) != 0)
    LeaveCriticalSection(lock);
  return address;
}

void __thiscall unlock_graphics_surface(int surface)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)surface;
  CRITICAL_SECTION *lock = (CRITICAL_SECTION *)(void *)(bytes + 16);

  if (*(int32_t *)(void *)(bytes + 40) != 0)
    EnterCriticalSection(lock);

  int lock_count = --*(int32_t *)(void *)(bytes + 52);
  if (lock_count == 0) {
    if ((bytes[4] & 8) == 0) {
      uint32_t *surface_interface =
          *(uint32_t **)(void *)(bytes + 44);
      typedef int (__stdcall *UnlockSurfaceMethod)(uint32_t, uint32_t);
      UnlockSurfaceMethod unlock_surface = (UnlockSurfaceMethod)(uintptr_t)
          *(uint32_t *)(uintptr_t)(surface_interface[0] + 128);
      int result = unlock_surface((uint32_t)(uintptr_t)surface_interface, 0);
      report_directx_call_failure(
          result, "Z:\\Proj\\GK3\\GEngine\\gsurface.cpp", 1002, 0);
    }
    *(uint32_t *)(void *)(bytes + 48) = 0;
  }

  if (*(int32_t *)(void *)(bytes + 40) != 0)
    LeaveCriticalSection(lock);
}

int __thiscall lock_sprite_pixels(int *sprite)
{
  uint32_t *methods = (uint32_t *)(uintptr_t)*sprite;
  typedef void (__thiscall *PrepareSpritePixelsMethod)(int *sprite);
  PrepareSpritePixelsMethod prepare = (PrepareSpritePixelsMethod)(uintptr_t)
      methods[12 / sizeof(uint32_t)];
  prepare(sprite);
  return lock_graphics_surface(sprite[12], 0xffff);
}

int __thiscall unlock_sprite_pixels(int *sprite)
{
  unlock_graphics_surface(sprite[12]);

  uint32_t *methods = (uint32_t *)(uintptr_t)*sprite;
  typedef int (__thiscall *FinishSpritePixelsMethod)(int *sprite);
  FinishSpritePixelsMethod finish = (FinishSpritePixelsMethod)(uintptr_t)
      methods[16 / sizeof(uint32_t)];
  return finish(sprite);
}
