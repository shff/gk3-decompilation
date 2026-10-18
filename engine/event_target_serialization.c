#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void (__thiscall *BeginNamedFieldMethod)(
    void *reader, const char *field_name);
typedef void (__thiscall *EndNamedFieldMethod)(void *reader);
typedef unsigned char (__thiscall *ReadIntegerFieldMethod)(
    void *reader, const char *field_name, int *value, int size);
typedef unsigned char (__thiscall *ReadByteFieldMethod)(
    void *reader, const char *field_name, char *value, int size);
typedef void (__thiscall *WriteStringFieldMethod)(
    void *reader, const char *field_name, void *value, uint32_t flags);
typedef unsigned char (__thiscall *ReadStringFieldMethod)(
    void *reader, const char *field_name, void *value, uint32_t flags);

typedef struct {
  uint32_t reserved;
  uint32_t data;
  uint32_t length;
  uint32_t capacity;
} RuntimeString;

typedef struct {
  int32_t target;
  int32_t code;
} EventTargetBinding;

/* gk3/GK3R_rest.c */
extern int serialized_value_default;
extern int event_reference_default;
extern int game_engine_address;
extern const char Key[4];

/* common/runtime_string.c */
extern void __thiscall destroy_runtime_string(RuntimeString *string);

/* gk3/GK3R_rest.c */
extern int __cdecl format_integer_string(int string, int value);
extern char __cdecl parse_integer_string(char *string, int *value);
extern uint8_t *__cdecl format_event_reference(uint8_t *string,
                                                unsigned int value);
extern char __cdecl parse_event_reference(char *string, int *value);
extern char __thiscall serialize_boolean_field_as_string(
    uint8_t *reader, const char *field_name, char *value,
    char *default_value);

/* engine/engine_logging.c */
extern int log_engine_message(int engine_address, const char *format, ...);

_Static_assert(sizeof(RuntimeString) == 16, "runtime string layout");

char __thiscall serialize_integer_field(
    uint8_t *reader, const char *field_name, int *value, int *default_value)
{
  uint32_t *methods = *(uint32_t **)reader;
  RuntimeString text = {0};

  if (reader[4]) {
    const WriteStringFieldMethod write_string =
        (WriteStringFieldMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];
    format_integer_string((int)(intptr_t)&text, *value);
    write_string(reader, field_name, &text, 0);
    destroy_runtime_string(&text);
    return 1;
  }

  const ReadStringFieldMethod read_string =
      (ReadStringFieldMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];
  unsigned char result = read_string(reader, field_name, &text, 0);
  if (result) {
    const char *string_value = text.data
        ? (const char *)(uintptr_t)text.data : Key;
    if (!parse_integer_string((char *)string_value, value)) {
      log_engine_message(game_engine_address,
                         "Error: unable to convert value '%s' for key '%s'",
                         string_value, field_name);
      result = 0;
      *value = *default_value;
    }
  } else {
    *value = *default_value;
  }
  destroy_runtime_string(&text);
  return (char)result;
}

char __cdecl serialize_boolean_field(uint8_t *reader, const char *field_name,
                                     char *value, char *default_value)
{
  if (reader[5])
    return serialize_boolean_field_as_string(reader, field_name, value,
                                             default_value);

  uint32_t *methods = *(uint32_t **)reader;
  const ReadByteFieldMethod read_byte =
      (ReadByteFieldMethod)(uintptr_t)methods[16 / sizeof(uint32_t)];
  if (!read_byte(reader, field_name, value, 1)) {
    *value = *default_value;
    return 0;
  }
  return 1;
}

char __thiscall read_serialized_event_reference(
    uint8_t *reader, const char *field_name, int *value, int *default_value)
{
  uint32_t *methods = *(uint32_t **)reader;
  RuntimeString text = {0};

  if (reader[4]) {
    const WriteStringFieldMethod write_string =
        (WriteStringFieldMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];
    format_event_reference((uint8_t *)&text, (unsigned int)*value);
    write_string(reader, field_name, &text, 0);
    destroy_runtime_string(&text);
    return 1;
  }

  const ReadStringFieldMethod read_string =
      (ReadStringFieldMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];
  unsigned char result = read_string(reader, field_name, &text, 0);
  if (result) {
    const char *string_value = text.data
        ? (const char *)(uintptr_t)text.data : Key;
    if (!parse_event_reference((char *)string_value, value)) {
      log_engine_message(game_engine_address,
                         "Error: unable to convert value '%s' for key '%s'",
                         string_value, field_name);
      result = 0;
      *value = *default_value;
    }
  } else {
    *value = *default_value;
  }
  destroy_runtime_string(&text);
  return (char)result;
}

_Static_assert(offsetof(EventTargetBinding, target) == 0,
               "event target field offset");
_Static_assert(offsetof(EventTargetBinding, code) == 4,
               "event code field offset");
_Static_assert(sizeof(EventTargetBinding) == 8,
               "event target binding size");

char __thiscall deserialize_event_target_fields(int *target, uint8_t *reader)
{
  EventTargetBinding *binding = (EventTargetBinding *)(void *)target;
  const bool target_read =
      read_serialized_event_reference(reader, "m_Target", &binding->target,
                                      &event_reference_default) != 0;
  int *code = &binding->code;

  if (reader[5])
    return serialize_integer_field(
               reader, "m_Code", code, &serialized_value_default)
        ? target_read : 0;

  uint32_t *methods = *(uint32_t **)reader;
  const ReadIntegerFieldMethod read_integer =
      (ReadIntegerFieldMethod)(uintptr_t)methods[16 / 4];
  if (!read_integer(reader, "m_Code", code, sizeof(*code))) {
    *code = 0;
    return 0;
  }
  return target_read;
}

bool __thiscall deserialize_event_target(
    int *target, void *reader, const char *field_name)
{
  uint32_t *methods = *(uint32_t **)reader;
  const BeginNamedFieldMethod begin_field =
      (BeginNamedFieldMethod)(uintptr_t)methods[48 / 4];
  const EndNamedFieldMethod end_field =
      (EndNamedFieldMethod)(uintptr_t)methods[52 / 4];

  begin_field(reader, field_name);
  const bool result = deserialize_event_target_fields(target, reader);
  end_field(reader);
  return result;
}
