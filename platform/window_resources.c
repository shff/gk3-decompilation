#include <stdint.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int window_cleanup_head;
extern void (*cleanup_pure_virtual_method)(void);

/* common/memory.c */
extern void __cdecl free_tracked_memory(int address);

typedef void (__cdecl *CleanupMethod)(int);

typedef struct CleanupListNode {
  CleanupMethod *methods;
  struct CleanupListNode *next;
} CleanupListNode;

void cleanup_window_resources(void)
{
  while (window_cleanup_head != 0) {
    CleanupListNode *node = (CleanupListNode *)(uintptr_t)window_cleanup_head;
    node->methods[0](window_cleanup_head);

    if (window_cleanup_head == 0) {
      break;
    }

    node = (CleanupListNode *)(uintptr_t)window_cleanup_head;
    CleanupListNode *next = node->next;
    node->methods = (CleanupMethod *)&cleanup_pure_virtual_method;
    window_cleanup_head = (int)(intptr_t)next;
    free_tracked_memory((int)(intptr_t)node);
  }
}
