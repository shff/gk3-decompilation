#include <stdint.h>
#include <windows.h>

void __thiscall update_synchronization_context_activity(char *context,
                                                        int beginning);

char *__thiscall initialize_synchronization_context(char *context)
{
  char *critical_section = context + 12;

  InitializeCriticalSection((LPCRITICAL_SECTION)critical_section);
  ((uint32_t *)critical_section)[6] = 1;
  *(uint32_t *)context = 0;
  ((uint32_t *)context)[1] =
      (uint32_t)(uintptr_t)CreateEventA(NULL, TRUE, TRUE, NULL);
  ((uint32_t *)context)[2] =
      (uint32_t)(uintptr_t)CreateMutexA(NULL, FALSE, NULL);
  return context;
}

void __thiscall destroy_synchronization_context(HANDLE *context)
{
  uint32_t *fields = (uint32_t *)(void *)context;

  CloseHandle((HANDLE)(uintptr_t)fields[1]);
  CloseHandle((HANDLE)(uintptr_t)fields[2]);
  DeleteCriticalSection((LPCRITICAL_SECTION)(fields + 3));
  fields[9] = 0;
}

BOOL __thiscall begin_synchronization_context_activity(int context_address)
{
  char *context = (char *)(uintptr_t)(uint32_t)context_address;
  HANDLE mutex = (HANDLE)(uintptr_t)*(uint32_t *)(void *)(context + 8);

  WaitForSingleObject(mutex, 0x1388u);
  update_synchronization_context_activity(context, 1);
  return ReleaseMutex(mutex);
}

void __thiscall end_synchronization_context_activity(char *context)
{
  update_synchronization_context_activity(context, 0);
}

DWORD __thiscall lock_synchronization_context(HANDLE *context)
{
  uint32_t *fields = (uint32_t *)(void *)context;

  WaitForSingleObject((HANDLE)(uintptr_t)fields[2], INFINITE);
  return WaitForSingleObject((HANDLE)(uintptr_t)fields[1], INFINITE);
}

BOOL __thiscall unlock_synchronization_context(HANDLE *context)
{
  return ReleaseMutex((HANDLE)(uintptr_t)((uint32_t *)(void *)context)[2]);
}

void __thiscall update_synchronization_context_activity(char *context,
                                                        int beginning)
{
  LPCRITICAL_SECTION critical_section =
      (LPCRITICAL_SECTION)(void *)(context + 12);
  uint32_t *fields = (uint32_t *)(void *)context;
  HANDLE activity_event = (HANDLE)(uintptr_t)fields[1];

  if (fields[9] != 0)
    EnterCriticalSection(critical_section);

  if (beginning) {
    ++fields[0];
    ResetEvent(activity_event);
  } else {
    if (fields[0] > 0)
      --fields[0];
    if (fields[0] == 0)
      SetEvent(activity_event);
  }

  if (fields[9] != 0)
    LeaveCriticalSection(critical_section);
}
