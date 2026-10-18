#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int game_engine_address;
extern int __thiscall reclaim_engine_resources(char *engine,
                                                int target_bytes);
extern int tracked_memory_lock_initialized;
extern CRITICAL_SECTION stru_76D518;
extern int tracked_memory_total_bytes;

/* Microsoft C runtime import (named malloc_1 by IDA). */
extern void *__cdecl malloc_1(size_t size);

uint32_t *__cdecl allocate_tracked_memory(int size)
{
  uint32_t *allocation;

  if (tracked_memory_lock_initialized)
    EnterCriticalSection(&stru_76D518);

  allocation = malloc_1(size + (int)sizeof(*allocation));
  if (!allocation) {
    for (;;) {
      if (!game_engine_address)
        exit(1);
      if (!reclaim_engine_resources(
              (char *)(uintptr_t)game_engine_address, 1000000))
        break;
      allocation = malloc_1(size + (int)sizeof(*allocation));
      if (allocation)
        goto allocation_succeeded;
    }

    if (game_engine_address) {
      (*(void (**)(int, const char *, ...))
           (*(uint32_t *)(uintptr_t)game_engine_address + 184))(
          game_engine_address,
          "Out of memory (requested %d bytes).\n",
          size);
      (*(void (__thiscall **)(int))
           (*(uint32_t *)(uintptr_t)game_engine_address + 148))(
          game_engine_address);
    }
    exit(1);
  }

allocation_succeeded:
  *allocation = (uint32_t)size;
  tracked_memory_total_bytes += size;
  if (tracked_memory_lock_initialized)
    LeaveCriticalSection(&stru_76D518);
  return allocation + 1;
}

void __cdecl free_tracked_memory(int address)
{
  if (address) {
    if (tracked_memory_lock_initialized)
      EnterCriticalSection(&stru_76D518);
    tracked_memory_total_bytes -=
        *(uint32_t *)(uintptr_t)(address - (int)sizeof(uint32_t));
    free((void *)(uintptr_t)(address - (int)sizeof(uint32_t)));
    if (tracked_memory_lock_initialized)
      LeaveCriticalSection(&stru_76D518);
  }
}
