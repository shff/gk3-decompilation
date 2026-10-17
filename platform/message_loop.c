#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

typedef struct CleanupListNode {
  void *methods;
  struct CleanupListNode *next;
} CleanupListNode;

typedef struct {
  uint8_t reserved[100];
  int paused;
} GameEngineState;

typedef HRESULT (WINAPI *TestCooperativeLevelMethod)(int direct_draw);

/* gk3/GK3R_rest.c */
extern HACCEL hAccTable;
extern int game_engine_address;
extern int direct_draw4_address;
extern int frame_number; /* Shared game-frame counter; serialized as gFrame. */
extern int previous_frame; /* Serialized as gPrevFrame. */
extern int window_cleanup_head;
extern void (*cleanup_pure_virtual_method)(void);

/* engine/game_frame.c */
extern int __thiscall run_game_frame(uint32_t *engine);
extern int __thiscall process_pending_engine_events(uint32_t *engine);

/* engine/game_engine.c */
extern void destroy_game_engine(void);

/* common/memory.c */
extern void __cdecl free_tracked_memory(int address);

char __cdecl pump_game_messages(HWND window, WPARAM *exit_code)
{
  MSG message;
  for (;;) {
    if (!PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
      if (game_engine_address) {
        GameEngineState *engine = (GameEngineState *)(uintptr_t)game_engine_address;
        if (engine->paused <= 0) {
          bool can_render_frame = !direct_draw4_address;
          if (!can_render_frame) {
            uint32_t *vtable = *(uint32_t **)(uintptr_t)direct_draw4_address;
            can_render_frame = SUCCEEDED(((TestCooperativeLevelMethod)(uintptr_t)vtable[26])(
                direct_draw4_address));
            if (can_render_frame)
              engine = (GameEngineState *)(uintptr_t)game_engine_address;
          }
          if (can_render_frame) {
            run_game_frame((uint32_t *)engine);
            previous_frame = frame_number++;
            return 0;
          }
        }
        WaitMessage();
      }
      return 0;
    }

    if (message.message == WM_QUIT) {
      *exit_code = message.wParam;
      return 1;
    }
    if (!hAccTable || !TranslateAcceleratorA(window, hAccTable, &message)) {
      TranslateMessage(&message);
      DispatchMessageA(&message);
    }
    GameEngineState *engine = (GameEngineState *)(uintptr_t)game_engine_address;
    if (engine && engine->paused <= 0)
      process_pending_engine_events((uint32_t *)engine);
  }
}

uint32_t __cdecl run_game_message_loop(uint32_t window)
{
  WPARAM exit_code = 0;
  while (!pump_game_messages((HWND)(uintptr_t)window, &exit_code)) {
    /* Idle iterations update the engine inside pump_game_messages. */
  }

  destroy_game_engine();
  while (window_cleanup_head) {
    CleanupListNode *node = (CleanupListNode *)(uintptr_t)window_cleanup_head;
    window_cleanup_head = (int)(uintptr_t)node->next;
    node->methods = &cleanup_pure_virtual_method;
    free_tracked_memory((int)(uintptr_t)node);
  }
  return (uint32_t)exit_code;
}
