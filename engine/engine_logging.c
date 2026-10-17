#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

typedef int (__thiscall *ReportEngineMessageMethod)(
    int engine, const char *message, int flags, int context);
typedef int (__thiscall *LogEngineMessageMethod)(
    int engine, const char *format, va_list arguments);

int report_engine_message(int engine_address, const char *format, ...)
{
  char message[6000];
  va_list arguments;
  va_start(arguments, format);
  vsnprintf(message, sizeof(message), format, arguments);
  va_end(arguments);

  const uint32_t *methods =
      *(const uint32_t **)(uintptr_t)engine_address;
  const ReportEngineMessageMethod report =
      (ReportEngineMessageMethod)(uintptr_t)methods[144 / sizeof(uint32_t)];
  return report(engine_address, message, 0, 0);
}

int log_engine_message(int engine_address, const char *format, ...)
{
  va_list arguments;
  va_start(arguments, format);

  const uint32_t *methods =
      *(const uint32_t **)(uintptr_t)engine_address;
  const LogEngineMessageMethod log =
      (LogEngineMessageMethod)(uintptr_t)methods[16 / sizeof(uint32_t)];
  const int result = log(engine_address, format, arguments);

  va_end(arguments);
  return result;
}
