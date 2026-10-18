#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* engine/event_dispatch.c */
extern uint16_t *__thiscall construct_registered_event_target(
    uint16_t *object);
extern uint16_t *__thiscall initialize_event_target_subobject(
    uint16_t *object, int mode) __asm__("sub_406D36");

/* gk3/GK3R_rest.c */
extern uint32_t action_manager_type_descriptor[15]
    __asm__("dword_762DD8");
extern int action_manager_base_offset_adjustment __asm__("dword_762DD4");
extern uint32_t action_manager_vtable[] __asm__("off_6A6950");
extern uint32_t registered_event_target_vtable[];
extern uint32_t registered_event_target_type_descriptor[16];
extern int registered_event_target_base_offset_adjustment;
extern uint32_t *__thiscall construct_action_descriptor(uint32_t *object);
extern uint32_t *__thiscall construct_current_noun_collection(
    uint32_t *collection, char *default_value);
extern void __thiscall initialize_event_reference(uint32_t *reference);
extern uint32_t *__thiscall construct_action_noun_collection(
    uint32_t *collection, char *default_value);
extern uint32_t *__thiscall construct_action_verb_collection(
    uint32_t *collection, char *default_value);
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);
extern uint32_t *__thiscall destroy_registered_event_target(uint16_t *object);
extern int *__thiscall replace_event_reference_and_queue_previous(
    int *reference, int *replacement);
extern uint32_t *__cdecl allocate_registered_noun_object(int size);
extern char *get_action_vocabulary_string(int string_id);
extern uint8_t *__thiscall construct_std_string_from_c_string(
    uint8_t *string_storage, char *value);
extern uint8_t *__thiscall construct_noun_object(
    uint8_t *object, int identifier, char value, int second, int third,
    int fourth, int fifth);
extern int system_profile_address;
extern uint8_t *__cdecl append_string_suffix(uint8_t *result, char *first,
                                             char *suffix)
    __asm__("sub_40157E");
extern void *__thiscall assign_std_string_storage(void *destination,
                                                  uint8_t *source)
    __asm__("sub_401C18");
extern uint8_t *__cdecl append_string_storage(uint8_t *result, char *first,
                                              uint8_t *second)
    __asm__("sub_404349");
extern uint8_t *__cdecl resolve_profile_directory(uint8_t *result, int mode)
    __asm__("sub_4A596D");
extern int __thiscall tidy_std_string_storage(char *string_storage,
                                              char mode);
extern void __thiscall replace_playing_action_state_lock(int *collection,
                                                         int value)
    __asm__("sub_409304");
extern void __thiscall replace_skipping_action_state_lock(int *collection,
                                                          int value)
    __asm__("sub_409344");
extern void __cdecl destroy_registered_noun_object(void **object)
    __asm__("sub_40AD04");
extern int __thiscall is_action_descriptor_empty(uint32_t *descriptor)
    __asm__("sub_40134E");
extern char __thiscall serialize_int16_field(uint8_t *serializer,
                                            const char *field,
                                            int16_t *value)
    __asm__("sub_40AE69");
extern char __cdecl serialize_integer_field(uint8_t *serializer,
                                           const char *field, int *value)
    __asm__("sub_4092C0");
extern void __thiscall destroy_playing_action_state_lock(int *object)
    __asm__("sub_4092ED");
extern void __thiscall destroy_skipping_action_state_lock(int *object)
    __asm__("sub_40932D");
extern int __thiscall clear_current_noun_collection(uint32_t *object)
    __asm__("sub_40936D");
extern int __thiscall clear_action_noun_collection(uint32_t *object)
    __asm__("sub_4093E9");
extern int __thiscall clear_action_verb_collection(uint32_t *object)
    __asm__("sub_409481");
extern int __thiscall serialize_action_descriptor(int object,
                                                  uint8_t *serializer,
                                                  int field)
    __asm__("sub_401356");
extern int __thiscall serialize_float_field(float *object,
                                            uint8_t *serializer, int field)
    __asm__("sub_40927C");
/* gk3/game_state.c */
extern char __cdecl serialize_playing_action_state_lock(
    uint8_t *serializer, const char *field, int *value);
extern char __cdecl serialize_skipping_action_state_lock(
    uint8_t *serializer, const char *field, int *value);
extern char __thiscall serialize_current_noun_collection(
    uint8_t *serializer, const char *field, int *value, char mode)
    __asm__("sub_40AA77");
extern char __thiscall serialize_action_noun_collection(
    uint8_t *serializer, const char *field, unsigned int value, int mode)
    __asm__("sub_40AAFE");
extern char __thiscall serialize_action_verb_collection(
    uint8_t *serializer, const char *field, unsigned int value, int mode)
    __asm__("sub_40AB82");
extern char __thiscall serialize_noun_collection_iterator(
    uint8_t *serializer, const char *field, int *iterator, int first,
    int second, int third, int fourth) __asm__("sub_40AC06");
extern char __thiscall serialize_verb_collection_iterator(
    uint8_t *serializer, const char *field, int *iterator, int first,
    int second, int third, int fourth) __asm__("sub_40AC85");
extern char __thiscall serialize_event_reference(int *event_reference,
                                                uint8_t *serializer,
                                                int field)
    __asm__("sub_575010");
extern char *__cdecl get_noun_vocabulary_string(int index)
    __asm__("sub_45C18B");
extern char *__cdecl get_verb_vocabulary_string(int index)
    __asm__("sub_55C36D");
extern int tidy_temporary_action_strings(void) __asm__("sub_402614");
extern uint32_t *__thiscall copy_action_descriptor(uint32_t *descriptor,
                                                   int source)
    __asm__("sub_402A2C");
extern int __cdecl log_source_message(int source_file, int line,
                                      int severity, int flags,
                                      const char *format, ...)
    __asm__("sub_5574A3");
extern uint32_t unk_766E08[16];
uint32_t *allocate_registered_action_manager(int size);
int __thiscall initialize_action_log_filename(int object);
int __thiscall reset_action_descriptor(uint32_t *descriptor);
int __thiscall restart_action(uint32_t *manager);

int __thiscall construct_action_manager(int object)
{
  struct ActionDescriptionArguments {
    char value;
    char padding[3];
    int second;
    int third;
    int fourth;
    int fifth;
  };
  char description_value;
  char string_value;
  struct ActionDescriptionArguments description_arguments;
  uint32_t *description;

  construct_registered_event_target((uint16_t *)(uintptr_t)object);
  find_or_create_registry_entry(action_manager_type_descriptor,
             (uint32_t)action_manager_base_offset_adjustment
                 + (uint32_t)object + 12);
  construct_action_descriptor((uint32_t *)(uintptr_t)(object + 20));
  *(uint32_t *)(uintptr_t)(object + 84) = 0;
  *(uint32_t *)(uintptr_t)(object + 88) = 0;
  construct_current_noun_collection((uint32_t *)(uintptr_t)(object + 92),
                                    &description_value);
  *(uint32_t *)(uintptr_t)(object + 144) = 0;
  initialize_event_reference((uint32_t *)(uintptr_t)(object + 144));
  *(uint8_t *)(uintptr_t)(object + 152) = 1;
  *(uint8_t *)(uintptr_t)(object + 160) = (uint8_t)description_value;
  tidy_std_string_storage((char *)(uintptr_t)(object + 160), 0);
  construct_action_noun_collection((uint32_t *)(uintptr_t)(object + 176),
                                   &description_value);
  *(uint32_t *)(uintptr_t)(object + 224) = 0;
  *(uint32_t *)(uintptr_t)(object + 228) = 0;
  *(uint32_t *)(uintptr_t)(object + 232) = 0;
  *(uint32_t *)(uintptr_t)(object + 236) = 0;
  construct_action_verb_collection((uint32_t *)(uintptr_t)(object + 240),
                                   &string_value);
  *(uint32_t *)(uintptr_t)(object + 288) = 0;
  *(uint32_t *)(uintptr_t)(object + 292) = 0;
  *(uint32_t *)(uintptr_t)(object + 296) = 0;
  *(uint32_t *)(uintptr_t)(object + 300) = 0;
  *(uint32_t *)(uintptr_t)object = (uint32_t)(uintptr_t)action_manager_vtable;
  *(uint16_t *)(uintptr_t)(object + 12) = 0;
  *(uint32_t *)(uintptr_t)(object + 16) = 0;
  *(uint32_t *)(uintptr_t)(object + 140) = 0;
  description = allocate_registered_noun_object(28);
  if (description) {
    char *default_label = get_action_vocabulary_string(1065);
    construct_std_string_from_c_string((uint8_t *)&description_arguments,
                                       default_label);
    description = (uint32_t *)(void *)construct_noun_object(
        (uint8_t *)description, 1065, description_arguments.value,
        description_arguments.second, description_arguments.third,
        description_arguments.fourth, description_arguments.fifth);
  } else {
    description = NULL;
  }
  *(uint32_t *)(uintptr_t)(object + 156) = (uint32_t)(uintptr_t)description;
  initialize_action_log_filename(object);
  return object;
}

int __thiscall construct_registered_action_manager(int object, int mode)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t mode_byte = (uint8_t)((uint32_t)mode >> 24);
  char verb_default;

  initialize_event_target_subobject((uint16_t *)(void *)bytes, mode);
  find_or_create_registry_entry(
      action_manager_type_descriptor,
      (uint32_t)action_manager_base_offset_adjustment
          + (uint32_t)(uintptr_t)(bytes + 12));
  construct_action_descriptor((uint32_t *)(void *)(bytes + 20));
  *(uint32_t *)(void *)(bytes + 84) = 0;
  *(uint32_t *)(void *)(bytes + 88) = 0;
  construct_current_noun_collection((uint32_t *)(void *)(bytes + 92),
                                    (char *)&mode_byte);
  *(uint32_t *)(void *)(bytes + 144) = 0;
  *(uint32_t *)(void *)(bytes + 148) = 0;
  bytes[152] = 1;
  bytes[160] = mode_byte;
  tidy_std_string_storage((char *)(void *)(bytes + 160), 0);
  construct_action_noun_collection((uint32_t *)(void *)(bytes + 176),
                                   (char *)&mode_byte);
  *(uint32_t *)(void *)(bytes + 224) = 0;
  *(uint32_t *)(void *)(bytes + 228) = 0;
  *(uint32_t *)(void *)(bytes + 232) = 0;
  *(uint32_t *)(void *)(bytes + 236) = 0;
  construct_action_verb_collection((uint32_t *)(void *)(bytes + 240),
                                   &verb_default);
  *(uint32_t *)(void *)(bytes + 288) = 0;
  *(uint32_t *)(void *)(bytes + 292) = 0;
  *(uint32_t *)(void *)(bytes + 296) = 0;
  *(uint32_t *)(void *)(bytes + 300) = 0;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)action_manager_vtable;
  return object;
}

uint32_t *__cdecl create_registered_action_manager(void)
{
  uint32_t *memory = allocate_registered_action_manager(304);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_action_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

void __thiscall reset_action_manager_state(int object)
{
  replace_skipping_action_state_lock((int *)(uintptr_t)(object + 88), 0);
  replace_playing_action_state_lock((int *)(uintptr_t)(object + 84), 0);
  destroy_registered_noun_object((void **)(uintptr_t)(object + 156));
}

char __thiscall serialize_action_manager(uint32_t *manager,
                                         uint8_t *serializer, int mode)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  (void)mode;

  serialize_int16_field(serializer, "mActionID",
                        (int16_t *)(void *)(bytes + 12));
  serialize_integer_field(serializer, "mCurrentState",
                           (int *)(void *)(bytes + 16));
  serialize_action_descriptor((int)(uintptr_t)(bytes + 20), serializer,
             (int)(uintptr_t)"mCurrentAction");
  serialize_float_field((float *)(void *)(bytes + 80), serializer,
             (int)(uintptr_t)"mSnapshot");
  serialize_playing_action_state_lock(
      serializer, "pActionLock", (int *)(void *)(bytes + 84));
  serialize_skipping_action_state_lock(
      serializer, "pSkipLock", (int *)(void *)(bytes + 88));
  serialize_current_noun_collection(serializer, "mCurrentNouns",
                                    (int *)(void *)(bytes + 92), 0);

  typedef void (__thiscall *SerializeObjectReferenceMethod)(
      uint8_t *, const char *, int, uint32_t *);
  const uint32_t *serializer_vtable =
      (const uint32_t *)(uintptr_t)*(uint32_t *)(void *)serializer;
  SerializeObjectReferenceMethod serialize_object_reference =
      (SerializeObjectReferenceMethod)(uintptr_t)serializer_vtable[68 / 4];
  serialize_object_reference(serializer, "mpCurrentObject",
                              (int)(uintptr_t)(bytes + 140), unk_766E08);
  serialize_event_reference((int *)(void *)(bytes + 144), serializer,
             (int)(uintptr_t)"mExtNotify");
  serialize_object_reference(serializer, "mpSheepCommandNoun",
                              (int)(uintptr_t)(bytes + 156), unk_766E08);
  serialize_action_noun_collection(serializer, "mTriggerNouns",
             (unsigned int)(uintptr_t)(bytes + 176), 1);
  serialize_action_verb_collection(serializer, "mTriggerVerbs",
             (unsigned int)(uintptr_t)(bytes + 240), 1);
  serialize_noun_collection_iterator(serializer, "mTriggerNounItr",
             (int *)(void *)(bytes + 224),
             *(int *)(void *)(bytes + 180), *(int *)(void *)(bytes + 184),
             *(int *)(void *)(bytes + 188), *(int *)(void *)(bytes + 192));
  char result = serialize_verb_collection_iterator(serializer,
             "mTriggerVerbItr",
             (int *)(void *)(bytes + 288), *(int *)(void *)(bytes + 244),
             *(int *)(void *)(bytes + 248), *(int *)(void *)(bytes + 252),
             *(int *)(void *)(bytes + 256));
  if (serializer[4] == 0)
    return (char)initialize_action_log_filename((int)(uintptr_t)manager);
  return result;
}

char __cdecl serialize_registered_action_manager(int object,
                                                  uint8_t *serializer,
                                                  int mode)
{
  return serialize_action_manager((uint32_t *)(uintptr_t)object,
                                  serializer, mode);
}

uint32_t *__thiscall destroy_action_manager_members(uint32_t *manager)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  manager[0] = (uint32_t)(uintptr_t)action_manager_vtable;
  reset_action_manager_state((int)(uintptr_t)manager);
  clear_action_verb_collection((uint32_t *)(void *)(bytes + 240));
  clear_action_noun_collection((uint32_t *)(void *)(bytes + 176));
  tidy_std_string_storage((char *)(void *)(bytes + 160), 1);
  replace_event_reference_and_queue_previous((int *)(void *)(bytes + 144),
                                             NULL);
  clear_current_noun_collection((uint32_t *)(void *)(bytes + 92));
  destroy_skipping_action_state_lock((int *)(void *)(bytes + 88));
  destroy_playing_action_state_lock((int *)(void *)(bytes + 84));
  tidy_temporary_action_strings();
  erase_map_entry_impl(action_manager_type_descriptor,
      (uint32_t)action_manager_base_offset_adjustment
          + (uint32_t)(uintptr_t)(bytes + 12));
  return destroy_registered_event_target((uint16_t *)(void *)manager);
}

void *__thiscall destroy_action_manager(void *object, char flags)
{
  destroy_action_manager_members((uint32_t *)object);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)object);
  return object;
}

uint32_t *__thiscall make_action_event_key(uint32_t *action,
                                           uint32_t *result,
                                           uint16_t action_state)
{
  result[0] = action[2];
  result[1] = (uint32_t)action_state
      | ((uint32_t)*(uint16_t *)(void *)((uint8_t *)(void *)action + 12)
         << 16);
  return result;
}

char __thiscall can_start_action_without_overlap(uint32_t *manager,
                                                 int action_id,
                                                 int verb_id,
                                                 int noun_id)
{
  if (manager[4] != 0)
    restart_action(manager);
  if (is_action_descriptor_empty(manager + 5))
    return 1;

  log_source_message(
      (int)(uintptr_t)
          "Z:\\Proj\\GK3\\gk3app\\Source\\ActionMgr.cpp",
      172, 6, 0,
      "Error: request to play NVC '%s:%s:%s' overlaps NVC '%s:%s:%s' that is already running.\n",
      get_action_vocabulary_string(action_id),
      get_verb_vocabulary_string(verb_id), get_noun_vocabulary_string(noun_id),
      get_action_vocabulary_string(manager[5]),
      get_verb_vocabulary_string((int)manager[6]),
      get_noun_vocabulary_string((int)manager[7]));
  return 0;
}

int __thiscall restart_action(uint32_t *manager)
{
  ++*(uint16_t *)(void *)((uint8_t *)(void *)manager + 12);
  int result = reset_action_descriptor((uint32_t *)(void *)
      ((uint8_t *)(void *)manager + 20));
  manager[4] = 0;
  return result;
}

int __thiscall reset_action_descriptor(uint32_t *descriptor)
{
  uint32_t temporary[3];
  construct_action_descriptor(temporary);
  copy_action_descriptor(descriptor, (int)(uintptr_t)temporary);
  return tidy_temporary_action_strings();
}

int __thiscall initialize_action_log_filename(int object)
{
  uint8_t prefix[20] = { 0 };
  uint8_t profile_log_name[20] = { 0 };
  uint8_t log_name[20] = { 0 };
  uint8_t directory[20] = { 0 };
  uint8_t full_path[20] = { 0 };

  construct_std_string_from_c_string(prefix, "nvc-");
  append_string_suffix(profile_log_name, (char *)prefix,
             (char *)(uintptr_t)system_profile_address);
  append_string_suffix(log_name, (char *)profile_log_name, ".log");
  resolve_profile_directory(directory, 1);
  append_string_storage(full_path, (char *)directory, log_name);
  assign_std_string_storage((void *)(uintptr_t)(object + 160), full_path);

  tidy_std_string_storage((char *)full_path, 1);
  tidy_std_string_storage((char *)directory, 1);
  tidy_std_string_storage((char *)log_name, 1);
  tidy_std_string_storage((char *)profile_log_name, 1);
  return tidy_std_string_storage((char *)prefix, 1);
}

uint32_t *allocate_registered_action_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(action_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_action_manager(void)
{
  uint32_t *memory = allocate_registered_action_manager(304);
  return memory
      ? (uint32_t *)(uintptr_t)construct_action_manager((int)(uintptr_t)memory)
      : NULL;
}

void shutdown_action_manager(uint32_t *manager)
{
  reset_action_manager_state((int)(uintptr_t)manager);
}
