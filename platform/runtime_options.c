#include <stdint.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int application_instance;

/* platform/window_creation.c */
extern HWND __cdecl create_game_window(HINSTANCE instance, uint32_t previous_instance, uint32_t command_line);

/* platform/message_loop.c */
extern uint32_t __cdecl run_game_message_loop(uint32_t window);

/* platform/command_line_options.c */
extern uint32_t *apply_display_command_line_options(uint8_t *command_line);

typedef uint32_t (__cdecl *WindowCreationCallback)(HINSTANCE instance, uint32_t previous_instance, uint32_t command_line);
typedef uint32_t (__cdecl *MessageLoopCallback)(uint32_t window);

WindowCreationCallback window_creation_callback = (WindowCreationCallback)create_game_window;
MessageLoopCallback message_loop_callback = run_game_message_loop;

static WindowCreationCallback previous_window_creation_callback;
static MessageLoopCallback previous_message_loop_callback;

/* The exception filter writes its crash report through write_exception_crash_report. */
static uint32_t __cdecl forward_window_creation(HINSTANCE instance, uint32_t previous_instance, uint32_t command_line)
{
  return previous_window_creation_callback(instance, previous_instance, command_line);
}

static uint32_t __cdecl forward_message_loop(uint32_t window)
{
  return previous_message_loop_callback(window);
}

static WindowCreationCallback set_window_creation_callback(WindowCreationCallback callback)
{
  WindowCreationCallback previous = window_creation_callback;
  window_creation_callback = callback;
  return previous;
}

static MessageLoopCallback set_message_loop_callback(MessageLoopCallback callback)
{
  MessageLoopCallback previous = message_loop_callback;
  message_loop_callback = callback;
  return previous;
}

void init_runtime_and_options(HINSTANCE instance, HINSTANCE previous_instance, LPSTR command_line)
{
  (void)previous_instance;
  application_instance = (int)(intptr_t)instance;
  previous_window_creation_callback = set_window_creation_callback(forward_window_creation);
  previous_message_loop_callback = set_message_loop_callback(forward_message_loop);
  apply_display_command_line_options((uint8_t *)command_line);
}
