#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

typedef int (__thiscall *ReportEngineMessageMethod)(
    int engine, const char *message, int flags, int context);
typedef int (__thiscall *LogEngineMessageMethod)(
    int engine, const char *format, va_list arguments);
typedef int (__thiscall *WriteEngineLogMessageMethod)(
    int engine, int format, va_list arguments);

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

int write_engine_log_message(int engine_address, int format, ...)
{
  va_list arguments;
  va_start(arguments, format);

  const uint32_t *methods =
      *(const uint32_t **)(uintptr_t)engine_address;
  const WriteEngineLogMessageMethod write =
      (WriteEngineLogMessageMethod)(uintptr_t)
          methods[20 / sizeof(uint32_t)];
  const int result = write(engine_address, format, arguments);

  va_end(arguments);
  return result;
}

/* gk3/GK3R_rest.c */
extern int game_engine_address;

int __cdecl log_engine_setting_value(const char *name, const char *value)
{
  return write_engine_log_message(game_engine_address,
                                  (int)(uintptr_t)"%-35s: %s",
                                  name, value);
}

int __cdecl log_engine_boolean_setting(const char *name, char enabled)
{
  return log_engine_setting_value(name, enabled ? "TRUE" : "FALSE");
}
