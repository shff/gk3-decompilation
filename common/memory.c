#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int game_engine_address;
extern int __thiscall sub_566550(char *engine, int target_bytes);
extern int dword_76D530;
extern CRITICAL_SECTION stru_76D518;
extern int dword_76D534;

/* Microsoft C runtime import (named malloc_1 by IDA). */
extern void *__cdecl malloc_1(size_t size);

uint32_t *__cdecl allocate_tracked_memory(int size)
{
  uint32_t *allocation;

  if (dword_76D530)
    EnterCriticalSection(&stru_76D518);

  allocation = malloc_1(size + (int)sizeof(*allocation));
  if (!allocation) {
    for (;;) {
      if (!game_engine_address)
        exit(1);
      if (!sub_566550((char *)(uintptr_t)game_engine_address, 1000000))
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
  dword_76D534 += size;
  if (dword_76D530)
    LeaveCriticalSection(&stru_76D518);
  return allocation + 1;
}

void __cdecl free_tracked_memory(int address)
{
  if (address) {
    if (dword_76D530)
      EnterCriticalSection(&stru_76D518);
    dword_76D534 -= *(uint32_t *)(uintptr_t)(address - (int)sizeof(uint32_t));
    free((void *)(uintptr_t)(address - (int)sizeof(uint32_t)));
    if (dword_76D530)
      LeaveCriticalSection(&stru_76D518);
  }
}
