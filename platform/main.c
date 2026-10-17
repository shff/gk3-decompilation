#include <stdint.h>
#include <windows.h>

/* platform/runtime_options.c */
extern void init_runtime_and_options(HINSTANCE instance, HINSTANCE previous_instance, LPSTR command_line);

/* platform/system_profile.c */
extern void init_system_profile(uint8_t *profile);
extern void clear_system_profile(void);

/* gk3/GK3R_rest.c */
extern LONG __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *exception_info);

/* platform/window_resources.c */
extern void cleanup_window_resources(void);

/* platform/runtime_options.c */
extern uint32_t (__cdecl *window_creation_callback)(HINSTANCE instance, uint32_t previous_instance, uint32_t command_line);
extern uint32_t (__cdecl *message_loop_callback)(uint32_t window);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  uint8_t system_profile[108];
  int exit_code = 0;

  (void)nShowCmd;
  SetUnhandledExceptionFilter(TopLevelExceptionFilter);
  init_system_profile(system_profile);
  init_runtime_and_options(hInstance, hPrevInstance, lpCmdLine);

  const uint32_t window = window_creation_callback(hInstance, (uint32_t)(uintptr_t)hPrevInstance, (uint32_t)(uintptr_t)lpCmdLine);
  if (window != 0) {
    exit_code = message_loop_callback(window);
  }

  cleanup_window_resources();
  clear_system_profile();
  return exit_code;
}
