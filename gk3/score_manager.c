#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t reserved;
  uint32_t data;
  uint32_t length;
  uint32_t capacity;
} ScoreRuntimeString;

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t score_manager_type_descriptor[];
extern int score_manager_base_offset_adjustment;
extern int game_engine_instance_address;
extern uint32_t score_points_by_id[385];
extern int game_engine_address;
extern int serialized_value_default;
extern int score_id_default_value[8];
extern char default_false_boolean_value;
extern const char Key[4];
extern char *score_names_by_id[385];
extern int __cdecl format_integer_string(int string_storage, int value);
extern int __cdecl serialize_integer_value_field(
    uint8_t *serializer, const char *field_name, int *value,
    int *default_value);
extern char __cdecl serialize_boolean_field(uint8_t *serializer,
                                            const char *field_name,
                                            char *value,
                                            char *default_value);
extern uint8_t *__thiscall construct_std_string_from_c_string(
    uint8_t *storage, char *value);
extern int __thiscall tidy_std_string_storage(char *storage, char mode);
extern int __thiscall log_engine_message(int engine_address,
                                         const char *format, ...);
extern uint8_t *__thiscall resize_score_flag_vector(
    int *vector, unsigned int count, uint8_t *fill_value);
extern char __thiscall select_settings_section(uint32_t *settings,
                                               char *section_name);
extern char *__thiscall read_integer_setting_or_default(
    uint32_t *settings, char *key, char *default_value);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern int __cdecl find_string_index(int *names, int count, int name,
                                     int flags);
extern int __thiscall queue_engine_event(uint32_t *engine, int *event);
extern int __cdecl get_or_create_rc_bar_popper(void);
extern int __cdecl log_source_message(
    int source_file, int line, int severity, int flags, const char *format,
    ...);
uint32_t *__cdecl allocate_registered_score_manager(int size);

uint8_t *__thiscall initialize_score_id_flags(int *object)
{
  uint8_t fill_value = 0;
  return resize_score_flag_vector(object + 2, 0x181u, &fill_value);
}

char *__thiscall reset_score_state(uint32_t *object, char mode)
{
  uint8_t *score_flags = (uint8_t *)(uintptr_t)object[3];
  char *result = (char *)(uintptr_t)385;

  for (int index = 0; index < 385; ++index)
    score_flags[index] = 0;

  if (!mode)
  {
    uint32_t application = (uint32_t)game_engine_instance_address;
    uint32_t settings_address =
        *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)(application + 1092)
                                 + 100);
    uint32_t *settings = (uint32_t *)(uintptr_t)settings_address;

    select_settings_section(settings, "Logic");
    result = read_integer_setting_or_default(settings, "Max Score", NULL);
    object[0] = (uint32_t)(uintptr_t)result;
  }

  object[1] = 0;
  return result;
}

int __thiscall destroy_score_id_flags(int *object)
{
  free_tracked_memory(object[1]);
  object[1] = 0;
  object[2] = 0;
  object[3] = 0;
  return 0;
}

char *__cdecl score_name_for_id(int score_id)
{
  return score_names_by_id[score_id];
}

char __cdecl find_score_id_by_name(const char *name, int *score_id)
{
  const int index = find_string_index(
      (int *)score_names_by_id, 385, (int)(uintptr_t)name, 0);
  if (index == -1) {
    return 0;
  }
  *score_id = index;
  return 1;
}

char __thiscall has_linked_score_flag(uint32_t *manager, int score_id)
{
  int linked_score_id;

  switch (score_id) {
    case 105: linked_score_id = 106; break;
    case 106: linked_score_id = 105; break;
    case 112: linked_score_id = 113; break;
    case 113: linked_score_id = 112; break;
    case 127: linked_score_id = 181; break;
    case 162: linked_score_id = 163; break;
    case 163: linked_score_id = 162; break;
    case 181: linked_score_id = 127; break;
    case 289: linked_score_id = 294; break;
    case 294: linked_score_id = 289; break;
    case 346: linked_score_id = 347; break;
    case 347: linked_score_id = 346; break;
    default: return 0;
  }

  const uint8_t *score_flags =
      (const uint8_t *)(uintptr_t)manager[3];
  return score_flags[linked_score_id] != 0;
}

char __thiscall award_score(uint32_t *manager, int score_id)
{
  uint32_t result = manager[3];
  uint8_t *score_flags = (uint8_t *)(uintptr_t)manager[3];

  if (score_flags[score_id] == 0) {
    result = (uint8_t)has_linked_score_flag(manager, score_id);
    if ((uint8_t)result == 0) {
      score_flags[score_id] = 1;
      manager[1] += score_points_by_id[score_id];
      int popper = get_or_create_rc_bar_popper();
      int event[2] = {0, -114};
      event[0] = popper != 0
          ? *(int *)(uintptr_t)(popper + 20)
          : 8;
      result = (uint8_t)queue_engine_event(
          (uint32_t *)(uintptr_t)game_engine_address, event);
    }
  }
  return (char)result;
}

void __thiscall increase_score_by_name(uint32_t *manager, const char *name)
{
  int score_id;

  if (find_score_id_by_name(name, &score_id)) {
    award_score(manager, score_id);
  } else {
    log_source_message((int)(uintptr_t)
                   "Z:\\Proj\\GK3\\gk3app\\Source\\ScoreMgr.cpp",
               161, 6, 0,
               "ScoreMgr::IncreaseScore: Illegal score name(%s)\n",
               name);
  }
}

char __cdecl is_valid_score_id(int score_id)
{
  return score_id >= 0 && score_id <= 384;
}

char __thiscall serialize_score_id_field(uint8_t *serializer,
                                         const char *field_name,
                                         int *score_id,
                                         int *default_score_id)
{
  typedef char (__thiscall *SerializeScoreNameMethod)(
      uint8_t *, const char *, ScoreRuntimeString *, uint32_t);
  const uint32_t *methods = *(const uint32_t **)serializer;
  const SerializeScoreNameMethod serialize_name =
      (SerializeScoreNameMethod)(uintptr_t)methods[4 / sizeof(uint32_t)];
  ScoreRuntimeString text = { 0 };

  if (serializer[4]) {
    construct_std_string_from_c_string(
        (uint8_t *)(void *)&text, score_name_for_id(*score_id));
    serialize_name(serializer, field_name, &text, 0);
    tidy_std_string_storage((char *)(void *)&text, 1);
    return 1;
  }

  char result = serialize_name(serializer, field_name, &text, 0);
  if (result) {
    const char *name = text.data
        ? (const char *)(uintptr_t)text.data : Key;
    if (!find_score_id_by_name(name, score_id)) {
      log_engine_message(
          game_engine_address,
          "Error: unable to convert value '%s' for key '%s'", name,
          field_name);
      result = 0;
      *score_id = *default_score_id;
    }
  } else {
    *score_id = *default_score_id;
  }
  tidy_std_string_storage((char *)(void *)&text, 1);
  return result;
}

static int __cdecl read_current_score_flag(int score_id)
{
  const uint32_t application =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  const uint32_t manager = *(uint32_t *)(uintptr_t)(application + 84);
  const uint8_t *flags = (const uint8_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(manager + 12);
  return flags[score_id];
}

static void __cdecl write_current_score_flag(int score_id, int value)
{
  const uint32_t application =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  const uint32_t manager = *(uint32_t *)(uintptr_t)(application + 84);
  uint8_t *flags = (uint8_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(manager + 12);
  flags[score_id] = (uint8_t)value;
}

int __thiscall serialize_score_flag_map(uint32_t *manager,
                                        uint8_t *serializer,
                                        int first_score_id,
                                        int last_score_id,
                                        const char *field_name)
{
  typedef void (__thiscall *BeginCollectionMethod)(uint8_t *, const char *);
  typedef void (__thiscall *BeginEntryMethod)(uint8_t *, const char *);
  typedef void (__thiscall *EndEntryMethod)(uint8_t *);
  typedef int (__thiscall *EndCollectionMethod)(uint8_t *);
  const uint32_t *methods = *(const uint32_t **)serializer;
  const BeginCollectionMethod begin_collection =
      (BeginCollectionMethod)(uintptr_t)methods[40 / sizeof(uint32_t)];
  const BeginEntryMethod begin_entry =
      (BeginEntryMethod)(uintptr_t)methods[48 / sizeof(uint32_t)];
  const EndEntryMethod end_entry =
      (EndEntryMethod)(uintptr_t)methods[52 / sizeof(uint32_t)];
  const EndCollectionMethod end_collection =
      (EndCollectionMethod)(uintptr_t)methods[44 / sizeof(uint32_t)];
  uint8_t *score_flags = (uint8_t *)(uintptr_t)manager[3];
  int count = last_score_id - first_score_id + 1;

  begin_collection(serializer, field_name);
  serialize_integer_value_field(serializer, "count", &count, &count);

  if (serializer[4]) {
    for (int score_id = first_score_id; score_id <= last_score_id;
         ++score_id) {
      uint8_t entry_index_storage[16] = { 0 };
      int entry_index_address = format_integer_string(
          (int)(uintptr_t)entry_index_storage, score_id - first_score_id);
      const char *entry_name = *(const char **)(uintptr_t)(
          (uint32_t)entry_index_address + 4);
      if (!entry_name)
        entry_name = Key;
      begin_entry(serializer, entry_name);
      tidy_std_string_storage((char *)(void *)entry_index_storage, 1);

      int serialized_score_id = score_id;
      char enabled = (char)read_current_score_flag(score_id);
      serialize_score_id_field(serializer, "score", &serialized_score_id,
                               score_id_default_value);
      serialize_boolean_field(serializer, "set", &enabled, &default_false_boolean_value);
      end_entry(serializer);
    }
  } else {
    for (int entry_index = 0; entry_index < count; ++entry_index) {
      uint8_t entry_index_storage[16] = { 0 };
      int entry_index_address = format_integer_string(
          (int)(uintptr_t)entry_index_storage, entry_index);
      const char *entry_name = *(const char **)(uintptr_t)(
          (uint32_t)entry_index_address + 4);
      if (!entry_name)
        entry_name = Key;
      begin_entry(serializer, entry_name);
      tidy_std_string_storage((char *)(void *)entry_index_storage, 1);

      int serialized_score_id = *score_id_default_value;
      char enabled = default_false_boolean_value;
      serialize_score_id_field(serializer, "score", &serialized_score_id,
                               score_id_default_value);
      serialize_boolean_field(serializer, "set", &enabled, &default_false_boolean_value);
      end_entry(serializer);
      if (is_valid_score_id(serialized_score_id))
        write_current_score_flag(serialized_score_id, enabled);
    }
  }

  return end_collection(serializer);
}

char __thiscall serialize_score_manager(uint32_t *manager,
                                         uint8_t *serializer, char mode)
{
  (void)mode;
  if (!serializer[4])
    reset_score_state(manager, 1);
  serialize_integer_value_field(serializer, "maxGameScore", (int *)manager,
                                &serialized_value_default);
  serialize_integer_value_field(serializer, "gameScore", (int *)(manager + 1),
                                &serialized_value_default);
  return (char)serialize_score_flag_map(manager, serializer, 0, 384,
                                       "setScores");
}

char __cdecl serialize_registered_score_manager(int object,
                                                 uint8_t *serializer,
                                                 char mode)
{
  return serialize_score_manager((uint32_t *)(uintptr_t)object, serializer,
                                 mode);
}

int __thiscall construct_score_manager(int object)
{
  char default_value;
  find_or_create_registry_entry(score_manager_type_descriptor,
      (uint32_t)object + (uint32_t)score_manager_base_offset_adjustment);
  *(uint8_t *)(uintptr_t)(object + 8) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 12) = 0;
  *(uint32_t *)(uintptr_t)(object + 16) = 0;
  *(uint32_t *)(uintptr_t)(object + 20) = 0;
  initialize_score_id_flags((int *)(uintptr_t)object);
  reset_score_state((uint32_t *)(uintptr_t)object, 0);
  return object;
}

int __thiscall construct_registered_score_manager(int object, int unused)
{
  char default_value;

  find_or_create_registry_entry(score_manager_type_descriptor,
                                (uint32_t)object
                                    + (uint32_t)score_manager_base_offset_adjustment);
  *(uint8_t *)(uintptr_t)(object + 8) = (uint8_t)default_value;
  *(uint32_t *)(uintptr_t)(object + 12) = 0;
  *(uint32_t *)(uintptr_t)(object + 16) = 0;
  *(uint32_t *)(uintptr_t)(object + 20) = 0;
  initialize_score_id_flags((int *)(uintptr_t)object);
  return object;
}

uint32_t *__cdecl create_registered_score_manager(void)
{
  uint32_t *memory = allocate_registered_score_manager(24);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_score_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

uint32_t *__cdecl allocate_registered_score_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(score_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_score_manager(void)
{
  uint32_t *memory = allocate_registered_score_manager(24);
  return memory
      ? (uint32_t *)(uintptr_t)construct_score_manager((int)(uintptr_t)memory)
      : NULL;
}

uint32_t *__thiscall destroy_score_manager(int *object)
{
  destroy_score_id_flags(object + 2);
  return erase_map_entry_impl(
      score_manager_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)score_manager_base_offset_adjustment);
}
