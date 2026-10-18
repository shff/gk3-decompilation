#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                                  uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t report_manager_type_descriptor[];
extern int report_manager_registry_offset;
extern uint32_t report_entry_registry[16];
extern uint32_t report_manager_vtable[];
extern int system_profile_address;
extern int interface_layer_type_descriptor;
extern int game_engine_instance_address;
extern int default_stacked_hook_control;
extern int game_engine_address;
extern uint32_t *file_path_context_vtable;
extern const char Key[4];
extern char *warning_indicator_resource_name_table[];
extern char *error_indicator_icon_resource_name_table[];
extern char *error_indicator_label_resource_name_table[];
extern int __thiscall construct_console_control_base(int object);
extern int *__thiscall set_registry_object_flags(
    uint32_t *registry, uint32_t address, int flags);
extern char *report_entry_category_name(int index);
extern char *__thiscall construct_report_entry(char *object, char *name);
extern int __thiscall insert_pointer_array_element(
    int *array, uint32_t *position, char **value);
extern uint8_t *__thiscall initialize_std_string_storage(uint8_t *string, uint8_t *value);
extern uint8_t *__cdecl append_string_storage(uint8_t *result, char *first,
                                   uint8_t *second);
extern uint8_t *__thiscall assign_std_string_storage_from_c_string(uint8_t *string, char *value,
                                      uint8_t *delimiter);
extern uint8_t *__cdecl append_string_suffix(uint8_t *result, char *first,
                                   char *second);
extern void *__thiscall assign_std_string_storage(void *string, uint8_t *value);
extern int __thiscall tidy_std_string_storage(char *string_storage, char mode);
extern uint32_t *__thiscall append_std_string_storage_bytes(uint32_t *string, const void *value,
                                       char *length);
extern void __thiscall set_report_entry_output_flags(
    uint32_t *entry, uint32_t flags);
extern uint8_t *combine_text_prefix_and_string_storage(
    uint8_t *result, char *prefix, uint8_t *suffix);
extern char __thiscall set_report_entry_filename(int entry, char *filename);
extern void __thiscall write_report_entry_line(
    int entry, const char *source, int line);
extern int __thiscall erase_std_string_range(char *string, int position,
                                             int count);
extern int report_engine_error(int engine_address, const char *format, ...);
extern void __stdcall OutputDebugStringA(const char *text);
extern int __cdecl _vsnprintf(char *buffer, size_t count,
                              const char *format, va_list arguments);
extern uint8_t *__cdecl find_character_before_string_end(
    uint8_t *string, int character, int count);
void __thiscall write_report_entry_output_chunk(int entry_address,
                                                uint8_t *bytes,
                                                size_t size);
void __thiscall write_report_entry_output_bytes(int entry_address,
                                                uint8_t *bytes,
                                                size_t size);
extern int __cdecl record_file_system_activity(int activity, int value);
extern int __thiscall open_tracked_file(uint32_t *file, char *file_name,
                                        uint32_t desired_access,
                                        uint32_t share_mode,
                                        uint32_t creation_disposition,
                                        uint32_t flags_and_attributes);
extern uint8_t *__cdecl resolve_file_path(uint8_t *result, char *path);
extern uint8_t *__cdecl resolve_profile_directory(uint8_t *result, int mode);
extern int __thiscall set_file_path_context_path(uint32_t *context,
                                                uint8_t *path);
extern uint8_t *__thiscall construct_file_path_context(uint8_t *context);
extern uint8_t *__thiscall initialize_file_path_context_strings(
    uint8_t *string);
extern uint8_t *__thiscall get_file_path_context_resolved_path(
    uint32_t *context, uint8_t *string);
extern int __thiscall destroy_file_path_context(uint32_t *context);
extern uint32_t __stdcall SetFilePointer(void *file, int32_t distance,
                                         int32_t *distance_high,
                                         uint32_t move_method);
extern void __thiscall close_tracked_file(void **file);
extern int report_engine_message(int engine_address, const char *format, ...);
extern void __thiscall write_debug_manager_console_text(
    int manager_address, char *text);
extern int __stdcall WriteFile(void *file, const void *buffer,
                               uint32_t byte_count, uint32_t *bytes_written,
                               void *overlapped);
bool __thiscall ensure_report_entry_log_file_open(int entry_address);
void __thiscall write_report_entry_message(
    uint32_t *manager, const char *source, int line, int entry_index,
    int flags, char *message, size_t size);
extern int __thiscall attach_control_to_service(int service, int manager, char active);
extern int __stdcall get_report_indicator_resource_ids(
    int *warning_id, int *error_id);
extern uint32_t *allocate_registered_report_indicator(int size);
extern uint32_t *__thiscall construct_report_indicator(
    uint32_t *object, char *name, char *label, int active);
extern int __thiscall resize_report_indicators(uint32_t **manager);
extern uint32_t *__thiscall resize_pointer_array(
    int *field, unsigned int count, uint32_t *fill_value);
extern uint32_t *__thiscall insert_control_into_control_container(uint8_t *manager, int object,
                                       char active);
extern int __thiscall destroy_report_manager_members(uint32_t *manager);
extern int __thiscall construct_control_container_base(char *object, int mode);
extern void __thiscall detach_control_from_service(int manager, uint8_t *object);
extern int __thiscall set_control_bounds(uint32_t *object, int height);
extern int __thiscall destroy_report_auxiliary_pointer_array(
    int *collection);
extern int __thiscall destroy_report_entry_pointer_array(int *collection);
extern uint32_t *__thiscall destroy_mini_console_control_base(uint32_t *object);

int __cdecl destroy_report_entry_reference(uint32_t *reference);
int __cdecl destroy_report_control_reference(uint32_t *reference);
int __cdecl destroy_report_indicator_reference(uint32_t *reference);

/* gk3/control_graphics.c */
extern char __thiscall set_control_tooltip_text(uint32_t *object,
                                                char *label);

extern int caption_manager_saved_state_pointer;
extern uint32_t *__cdecl allocate_registered_frame_delay_graph(int size);
extern uint32_t *__thiscall construct_frame_delay_graph(
    uint32_t *object, int *position, int interval);
extern uint32_t *__cdecl allocate_registered_page_fault_graph(int size);
extern uint32_t *__thiscall construct_page_fault_graph(
    uint32_t *object, int *position, int interval);
extern int is_psapi_available(void);
extern int __cdecl find_report_entry_category_index(int text, int *result);
extern int __cdecl compare_cursor_spec_names(const char *first, char *second,
                              size_t count);
extern uint32_t *__cdecl allocate_registered_report_entry(int size);
extern int __thiscall append_pointer_array_element(int array,
                                                  uint32_t **value);
extern void __cdecl write_source_message(const char *source, int line, int category,
                               int flags, char *message, size_t size);
extern uint32_t *__thiscall insert_control_into_control_container(uint8_t *manager, int object,
                                       char active);

int __thiscall record_warning_report_entry_completion(uint32_t *manager)
{
  uint32_t *stream = (uint32_t *)(uintptr_t)manager[54];

  ++stream[15];
  ++stream[16];
  if (*(uint8_t *)(void *)((uint8_t *)stream + 24) == 0)
    ((void (__thiscall *)(uint32_t *, int))
        (uintptr_t)(*(uint32_t *)(void *)stream + 176))(stream, 1);
  return ((int (__thiscall *)(uint32_t *))
      (uintptr_t)(*(uint32_t *)(void *)stream + 152))(stream);
}

int __thiscall record_error_report_entry_completion(uint32_t *manager)
{
  uint32_t *stream = (uint32_t *)(uintptr_t)manager[55];

  ++stream[15];
  ++stream[16];
  if (*(uint8_t *)(void *)((uint8_t *)stream + 24) == 0)
    ((void (__thiscall *)(uint32_t *, int))
        (uintptr_t)(*(uint32_t *)(void *)stream + 176))(stream, 1);
  return ((int (__thiscall *)(uint32_t *))
      (uintptr_t)(*(uint32_t *)(void *)stream + 152))(stream);
}

void __thiscall disable_report_entry_file_output(int entry_address,
                                                 const char *operation)
{
  uint8_t *entry = (uint8_t *)(uintptr_t)entry_address;
  const char *category = *(const char **)(void *)(entry + 8);
  const char *file_name = *(const char **)(void *)(entry + 36);

  if (category == NULL)
    category = Key;
  if (file_name == NULL)
    file_name = Key;

  report_engine_message(
      game_engine_address,
      "Unable to %s '%s' for reporting. Shutting off file reporting for category '%s'.",
      operation, file_name, category);
  if (*(int *)(void *)(entry + 52) != -1)
    close_tracked_file((void **)(void *)(entry + 48));
  *(uint32_t *)(void *)(entry + 24) &= ~1u;
}

bool __thiscall ensure_report_entry_log_file_open(int entry_address)
{
  uint8_t *entry = (uint8_t *)(uintptr_t)entry_address;
  uint8_t temporary_path[16] = {0};
  uint8_t combined_path[16] = {0};

  if (*(int *)(void *)(entry + 52) == -1) {
    if (*(int *)(void *)(entry + 40) == 0) {
      append_string_suffix(temporary_path, (char *)(void *)(entry + 4), ".log");
      assign_std_string_storage((void *)(entry + 32), temporary_path);
      tidy_std_string_storage((char *)temporary_path, 1);
    }

    char *file_name = *(char **)(void *)(entry + 36);
    if (file_name == NULL)
      file_name = (char *)Key;
    resolve_file_path(combined_path, file_name);
    assign_std_string_storage((void *)(entry + 32), combined_path);
    tidy_std_string_storage((char *)combined_path, 1);

    file_name = *(char **)(void *)(entry + 36);
    if (file_name == NULL)
      file_name = (char *)Key;
    if (!open_tracked_file((uint32_t *)(void *)(entry + 48), file_name,
                    0xC0000000, 3, entry[56] != 0 ? 2 : 4, 0x80)) {
      uint32_t path_context[17] = {0};
      uint8_t context_strings[32] = {0};
      uint8_t resolved_path[16] = {0};
      uint8_t base_directory[16] = {0};
      uint8_t full_path[16] = {0};

      construct_file_path_context((uint8_t *)path_context);
      initialize_file_path_context_strings(context_strings);
      path_context[0] = (uint32_t)(uintptr_t)&file_path_context_vtable;
      set_file_path_context_path(
          path_context, (uint8_t *)(void *)(entry + 32));
      get_file_path_context_resolved_path(path_context, resolved_path);
      resolve_profile_directory(base_directory, 1);
      append_string_storage(full_path, (char *)base_directory, resolved_path);
      assign_std_string_storage((void *)(entry + 32), full_path);
      tidy_std_string_storage((char *)full_path, 1);
      tidy_std_string_storage((char *)base_directory, 1);
      tidy_std_string_storage((char *)resolved_path, 1);
      destroy_file_path_context(path_context);

      file_name = *(char **)(void *)(entry + 36);
      if (file_name == NULL)
        file_name = (char *)Key;
      uint32_t creation_disposition = entry[56] != 0 ? 2 : 4;
      if (!open_tracked_file((uint32_t *)(void *)(entry + 48), file_name,
                      0xC0000000, 3, creation_disposition, 0x80)) {
        disable_report_entry_file_output(entry_address,
                                         "create or open file");
        return false;
      }
    }
  }

  uint32_t end = SetFilePointer((void *)(uintptr_t)
                                    *(uint32_t *)(void *)(entry + 52),
                                0, NULL, 2);
  if (end == UINT32_MAX) {
    disable_report_entry_file_output(entry_address, "seek to end of file");
    return false;
  }
  return true;
}

int __thiscall set_report_graph_active(uint32_t *manager, int graph_index,
                                       int active)
{
  uint32_t *graph = (uint32_t *)(uintptr_t)manager[57 + graph_index];

  if ((uint8_t)active != 0 || graph != NULL) {
    if (graph != NULL) {
      if (*(uint8_t *)(void *)((uint8_t *)graph + 24) != (uint8_t)active)
        return ((int (__thiscall *)(uint32_t *, int))
            (uintptr_t)(*(uint32_t *)(void *)graph + 176))(graph, active);
      return active;
    }

    int position[4] = {20, 0, 120, 0};
    position[1] = *(int *)(uintptr_t)caption_manager_saved_state_pointer
        - 2 * (5 * graph_index + 20);
    position[3] = position[1] + 25;

    if (graph_index == 0) {
      uint32_t *new_graph = allocate_registered_frame_delay_graph(288);
      if (new_graph != NULL)
        graph = construct_frame_delay_graph(new_graph, position, 250);
    } else if (graph_index == 1 && is_psapi_available()) {
      uint32_t *new_graph = allocate_registered_page_fault_graph(260);
      if (new_graph != NULL)
        graph = construct_page_fault_graph(new_graph, position, 1000);
    } else if (graph_index == 1) {
      write_source_message(
          "Z:\\Proj\\GK3\\gk3app\\Source\\ReportMgr.cpp", 918, 6, 0,
          "Unable to create graph - PSAPI.DLL not available on this system",
          0xFFFFFFFF);
    }

    manager[57 + graph_index] = (uint32_t)(uintptr_t)graph;
    if (graph != NULL)
      insert_control_into_control_container((uint8_t *)(void *)manager,
                 (int)(uintptr_t)graph, 1);
    if (graph != NULL) {
      if (*(uint8_t *)(void *)((uint8_t *)graph + 24) != (uint8_t)active)
        return ((int (__thiscall *)(uint32_t *, int))
            (uintptr_t)(*(uint32_t *)(void *)graph + 176))(graph, active);
      return active;
    }
  }
  return (int)manager[57 + graph_index];
}

void __thiscall close_report_entry(uint32_t *manager, int entry_index)
{
  uint8_t *entry = (uint8_t *)(uintptr_t)(manager[51] + 4 * entry_index);
  uint32_t *entry_fields = (uint32_t *)(void *)entry;

  int reference_count = (int)entry_fields[19];
  entry_fields[19] = (uint32_t)(reference_count - 1);
  entry[81] = 0;
  if (reference_count != 1 || entry[80] == 0)
    return;

  if ((entry[28] & 4) != 0)
    write_report_entry_output_bytes((int)(uintptr_t)entry,
                                    (uint8_t *)"\n", 1);

  if ((entry_fields[6] & 2) != 0 && entry_fields[17] != 0) {
    const char *category = *(const char **)(void *)(entry + 64);
    if (category == NULL)
      category = Key;

    typedef void (__thiscall *GameEngineMessage)(int engine,
                                                const char *message,
                                                int first, int second);
    GameEngineMessage show_message = (GameEngineMessage)(uintptr_t)
        (*(uint32_t *)(uintptr_t)game_engine_address + 144);
    show_message(game_engine_address, category, 0, 0);
    erase_std_string_range((char *)(void *)(entry + 64), 0, -1);
  }

  switch (entry_fields[5]) {
    case 1:
      record_warning_report_entry_completion(
          (uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)
              (game_engine_instance_address + 1092) + 80));
      break;
    case 2:
      record_error_report_entry_completion(
          (uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)
              (game_engine_instance_address + 1092) + 80));
      break;
    case 3:
      if (*(uint32_t *)(uintptr_t)(game_engine_address + 88) == 0) {
        const char *category_name = *(const char **)(void *)(entry + 8);
        if (category_name == NULL)
          category_name = Key;
        report_engine_error(
            game_engine_address,
            "Cannot continue after previous error (category '%s') [see error log for more information]. Aborting...",
            category_name);
      }
      break;
    default:
      if (entry_fields[5] == 5) {
        typedef int (__thiscall *GameEnginePrompt)(int engine,
                                                   const char *message,
                                                   const char *title,
                                                   int flags);
        GameEnginePrompt ask_to_continue = (GameEnginePrompt)(uintptr_t)
            (*(uint32_t *)(uintptr_t)game_engine_address + 144);
        if (ask_to_continue(
                game_engine_address,
                "An error has occurred and we recommend that you quit and reload the game. Ignore this advice and keep playing anyway?",
                "Continue Playing?", 20) != 6)
          report_engine_error(game_engine_address, "Smart move");
      }
      break;
  }
}

void __thiscall write_report_entry_message_v(
    uint32_t *manager, int first, int second, int entry_index,
    size_t size, char *format, va_list arguments)
{
  uint8_t *entry = (uint8_t *)(uintptr_t)(manager[51] + 4 * entry_index);
  if (entry[80] == 0 || (entry[28] & 2) == 0)
    return;

  char message[5004];
  message[5000] = '\0';
  int length = _vsnprintf(message, 5000, format, arguments);
  if (length < 0) {
    OutputDebugStringA(
        "Warning: report truncated due to length via _vsnprintf > buffer size. Consider using ReportRaw() instead.\n");
    length = 5000;
  }
  write_report_entry_message(manager, (const char *)(uintptr_t)first, second,
                             entry_index, (int)size, message, (size_t)length);
}

void __thiscall write_report_entry_message(
    uint32_t *manager, const char *source, int line, int entry_index,
    int flags, char *message, size_t size)
{
  uint8_t *entry = (uint8_t *)(uintptr_t)(manager[51] + 4 * entry_index);
  uint32_t *entry_fields = (uint32_t *)(void *)entry;
  if (entry[80] == 0 || entry_fields[6] == 0)
    return;

  int was_open = entry_fields[19] != 0;
  if (!was_open)
    write_report_entry_line((int)(uintptr_t)entry, source, line);

  if ((entry[28] & 2) != 0) {
    size_t remaining = size;
    if (remaining == (size_t)-1 || remaining == UINT32_MAX)
      remaining = strlen(message);

    if (flags <= 0) {
      write_report_entry_output_bytes((int)(uintptr_t)entry,
                                      (uint8_t *)message, remaining);
    } else {
      char indentation[51];
      memset(indentation, ' ', (size_t)flags);
      indentation[flags] = '\0';
      if (entry[81] == 0) {
        entry[81] = 1;
        write_report_entry_output_bytes((int)(uintptr_t)entry,
                                        (uint8_t *)indentation,
                                        (size_t)flags);
      }

      uint8_t *line_end = find_character_before_string_end(
          (uint8_t *)message, '\n', (int)remaining);
      while (line_end != NULL) {
        uint8_t *next_line = line_end + 1;
        remaining -= (size_t)(next_line - (uint8_t *)message);
        write_report_entry_output_bytes((int)(uintptr_t)entry,
                                        (uint8_t *)message,
                                        (size_t)(next_line - (uint8_t *)message));
        message = (char *)next_line;
        if (*message != '\0' && remaining != 0) {
          write_report_entry_output_bytes((int)(uintptr_t)entry,
                                          (uint8_t *)indentation,
                                          (size_t)-1);
        } else {
          entry[81] = 0;
        }
        line_end = find_character_before_string_end(
            (uint8_t *)message, '\n', (int)remaining);
      }
      write_report_entry_output_bytes((int)(uintptr_t)entry,
                                      (uint8_t *)message, remaining);
    }
  }

  if (!was_open)
    close_report_entry(manager, entry_index);
}

void __thiscall write_report_entry_output_bytes(int entry_address,
                                                uint8_t *bytes,
                                                size_t size)
{
  uint32_t *entry = (uint32_t *)(uintptr_t)entry_address;
  uint8_t buffer[257];
  if (entry[6] == 0 || *bytes == '\0' || size == 0)
    return;
  if (size == (size_t)-1 || size == UINT32_MAX)
    size = strlen((const char *)bytes);

  while (size > 256) {
    memcpy(buffer, bytes, 256);
    buffer[256] = '\0';
    write_report_entry_output_chunk(entry_address, buffer, 256);
    bytes += 256;
    size -= 256;
  }
  if (size != 0) {
    memcpy(buffer, bytes, size);
    buffer[size] = '\0';
    write_report_entry_output_chunk(entry_address, buffer, size);
  }
}

void __thiscall write_report_entry_output_chunk(int entry_address,
                                                uint8_t *bytes,
                                                size_t size)
{
  uint8_t *remaining_bytes = bytes;
  uint32_t *entry = (uint32_t *)(uintptr_t)entry_address;

  if ((entry[6] & 1) != 0 && ensure_report_entry_log_file_open(entry_address)) {
    uint32_t bytes_written;
    bool write_succeeded = true;

    while (true) {
      uint8_t *newline = find_character_before_string_end(
          remaining_bytes, '\n', (int)size);
      if (newline == NULL)
        break;

      uint32_t bytes_before_newline = (uint32_t)(newline - remaining_bytes);
      if (bytes_before_newline > 0) {
        record_file_system_activity(0, (int)bytes_before_newline);
        write_succeeded = WriteFile(
            (void *)(uintptr_t)entry[13], remaining_bytes,
            bytes_before_newline, &bytes_written, NULL);
      }

      if (write_succeeded) {
        static const char windows_newline[] = "\r\n";
        record_file_system_activity(0, 2);
        write_succeeded = WriteFile(
            (void *)(uintptr_t)entry[13], windows_newline, 2,
            &bytes_written, NULL);
      }

      remaining_bytes = newline + 1;
      size -= (size_t)bytes_before_newline + 1;
      if (!write_succeeded) {
        disable_report_entry_file_output(entry_address,
                                         "write stream to file");
        break;
      }
    }

    if (write_succeeded) {
      record_file_system_activity(0, (int)size);
      if (!WriteFile((void *)(uintptr_t)entry[13], remaining_bytes,
                     (uint32_t)size, &bytes_written, NULL))
        disable_report_entry_file_output(entry_address,
                                         "write stream to file");
    }
  }

  if ((entry[6] & 2) != 0)
    append_std_string_storage_bytes((uint32_t *)(void *)(entry + 15), bytes,
               (char *)(uintptr_t)size);
  if ((entry[6] & 4) != 0)
    OutputDebugStringA((const char *)bytes);
  if ((entry[6] & 0x10) != 0)
    write_debug_manager_console_text(
        *(int *)(uintptr_t)(*(uint32_t *)(uintptr_t)
            (game_engine_instance_address + 1092) + 104),
        (char *)bytes);
}

int __thiscall find_or_create_report_entry_index(uint32_t *manager,
                                                 char *category)
{
  int index;

  find_report_entry_category_index((int)(uintptr_t)category, &index);
  if (index != -1)
    return index;

  uint32_t *entries = (uint32_t *)(uintptr_t)manager[51];
  uint32_t *entries_end = (uint32_t *)(uintptr_t)manager[52];
  if (entries != NULL) {
    for (uint32_t *entry_slot = entries + 24;
         entry_slot != entries_end; ++entry_slot) {
      uint32_t *entry = (uint32_t *)(uintptr_t)*entry_slot;
      const char *entry_name = (const char *)(uintptr_t)entry[2];
      if (entry_name == NULL)
        entry_name = Key;
      if (compare_cursor_spec_names(entry_name, category, 0xFFFFFFFF))
        return (int)(entry_slot - entries);
    }
  }

  uint32_t *entry = allocate_registered_report_entry(84);
  if (entry != NULL)
    entry = (uint32_t *)construct_report_entry((char *)entry, category);
  append_pointer_array_element((int)(uintptr_t)(manager + 50), &entry);
  entries = (uint32_t *)(uintptr_t)manager[51];
  entries_end = (uint32_t *)(uintptr_t)manager[52];
  int count = entries != NULL ? (int)(entries_end - entries) : 0;
  return count - 1;
}

int __thiscall refresh_report_manager_display(uint32_t **manager, int a2,
                                             int a3, int a4)
{
  (void)a2;
  (void)a3;
  (void)a4;
  typedef int (__thiscall *ReportManagerMethod)(uint32_t **manager,
                                                int argument);
  uint32_t *vtable = (uint32_t *)(uintptr_t)*manager;
  ReportManagerMethod update = (ReportManagerMethod)(uintptr_t)vtable[42];
  update(manager, interface_layer_type_descriptor);
  return resize_report_indicators(manager);
}

uint32_t *__thiscall destroy_report_manager(uint32_t *manager)
{
  *manager = (uint32_t)(uintptr_t)report_manager_vtable;
  destroy_report_auxiliary_pointer_array(
      (int *)(void *)(manager + 56));
  destroy_report_entry_pointer_array((int *)(void *)(manager + 50));
  erase_map_entry_impl(
      report_manager_type_descriptor, (uint32_t)report_manager_registry_offset
          + (manager != NULL ? (uint32_t)(uintptr_t)manager + 197 : 0));
  return destroy_mini_console_control_base(manager);
}

uint32_t *__thiscall release_report_manager(uint32_t *manager, char flags)
{
  destroy_report_manager(manager);
  if ((flags & 1) != 0)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}

int __thiscall destroy_report_manager_members(uint32_t *manager)
{
  const uint32_t *report_entries =
      (const uint32_t *)(uintptr_t)manager[51];
  const uint32_t *report_entries_end =
      (const uint32_t *)(uintptr_t)manager[52];

  for (const uint32_t *entry = report_entries;
       entry != report_entries_end; ++entry) {
    destroy_report_entry_reference((uint32_t *)(uintptr_t)entry);
  }

  if (manager[54] != 0) {
    detach_control_from_service((int)(uintptr_t)manager,
               (uint8_t *)(uintptr_t)manager[54]);
    destroy_report_control_reference(manager + 54);
  }

  if (manager[55] != 0) {
    detach_control_from_service((int)(uintptr_t)manager,
               (uint8_t *)(uintptr_t)manager[55]);
    destroy_report_control_reference(manager + 55);
  }

  int *indicators = (int *)(uintptr_t)manager[57];
  int *indicators_end = (int *)(uintptr_t)manager[58];
  for (int *indicator = indicators; indicator != indicators_end; ++indicator) {
    if (*indicator != 0) {
      detach_control_from_service((int)(uintptr_t)manager,
                 (uint8_t *)(uintptr_t)*indicator);
      destroy_report_indicator_reference((uint32_t *)indicator);
    }
  }

  return 0;
}

int __cdecl destroy_report_entry_reference(uint32_t *reference)
{
  int result = 0;
  if (*reference != 0) {
    uint32_t *object = (uint32_t *)(uintptr_t)*reference;
    uint32_t *methods = (uint32_t *)(uintptr_t)object[0];
    uint32_t *(__thiscall *destroy)(uint32_t *object, int free_memory) =
        (uint32_t *(__thiscall *)(uint32_t *, int))(uintptr_t)methods[0];
    result = (int)(uintptr_t)destroy(object, 1);
  }
  *reference = 0;
  return result;
}

int __cdecl destroy_report_control_reference(uint32_t *reference)
{
  int result = 0;
  if (*reference != 0) {
    uint32_t *object = (uint32_t *)(uintptr_t)*reference;
    uint32_t *methods = (uint32_t *)(uintptr_t)object[0];
    uint32_t *(__thiscall *destroy)(uint32_t *object, int free_memory) =
        (uint32_t *(__thiscall *)(uint32_t *, int))(uintptr_t)methods[0];
    result = (int)(uintptr_t)destroy(object, 1);
  }
  *reference = 0;
  return result;
}

int __cdecl destroy_report_indicator_reference(uint32_t *reference)
{
  int result = 0;
  if (*reference != 0) {
    uint32_t *object = (uint32_t *)(uintptr_t)*reference;
    uint32_t *methods = (uint32_t *)(uintptr_t)object[0];
    uint32_t *(__thiscall *destroy)(uint32_t *object, int free_memory) =
        (uint32_t *(__thiscall *)(uint32_t *, int))(uintptr_t)methods[0];
    result = (int)(uintptr_t)destroy(object, 1);
  }
  *reference = 0;
  return result;
}

int __thiscall resize_report_indicators(uint32_t **manager)
{
  int warning_resource_id;
  int error_resource_id;

  get_report_indicator_resource_ids(&warning_resource_id, &error_resource_id);
  set_control_bounds(manager[54],
      *(int *)(uintptr_t)(default_stacked_hook_control + 12)
      - *(int *)(uintptr_t)(warning_resource_id + 72)
      - *(int *)(uintptr_t)(error_resource_id + 72)
      - *(int *)(uintptr_t)(warning_resource_id + 56)
      - *(int *)(uintptr_t)(error_resource_id + 56)
      - 14);
  return set_control_bounds(manager[55],
      *(int *)(uintptr_t)(default_stacked_hook_control + 12)
      - *(int *)(uintptr_t)(error_resource_id + 72)
      - *(int *)(uintptr_t)(error_resource_id + 56)
      - 12);
}

int __thiscall construct_registered_report_manager(int object, int mode)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;
  uint8_t mode_byte = (uint8_t)((uint32_t)mode >> 24);

  construct_control_container_base((char *)(void *)bytes, mode);
  find_or_create_registry_entry(
      report_manager_type_descriptor,
      (uint32_t)report_manager_registry_offset + (uint32_t)object + 197);
  bytes[200] = mode_byte;
  *(uint32_t *)(void *)(bytes + 204) = 0;
  *(uint32_t *)(void *)(bytes + 208) = 0;
  *(uint32_t *)(void *)(bytes + 212) = 0;
  bytes[224] = mode_byte;
  *(uint32_t *)(void *)(bytes + 228) = 0;
  *(uint32_t *)(void *)(bytes + 232) = 0;
  *(uint32_t *)(void *)(bytes + 236) = 0;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)report_manager_vtable;
  return object;
}

int __thiscall construct_report_manager(int object)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)object;
  char default_value;
  char delimiter;
  char report_path[16];
  char path_separator[16];
  uint32_t report_filename[6];

  construct_console_control_base(object);
  find_or_create_registry_entry(report_manager_type_descriptor,
             (uint32_t)report_manager_registry_offset + (uint32_t)object + 197);
  manager[200] = (uint8_t)default_value;
  *(uint32_t *)(void *)(manager + 204) = 0;
  *(uint32_t *)(void *)(manager + 208) = 0;
  *(uint32_t *)(void *)(manager + 212) = 0;
  manager[224] = (uint8_t)default_value;
  *(uint32_t *)(void *)(manager + 228) = 0;
  *(uint32_t *)(void *)(manager + 232) = 0;
  *(uint32_t *)(void *)(manager + 236) = 0;
  *(uint32_t *)(void *)manager = (uint32_t)(uintptr_t)report_manager_vtable;

  for (int index = 0; index < 24; ++index) {
    char *entry_memory = (char *)allocate_tracked_memory(84);
    set_registry_object_flags(report_entry_registry,
                              (uint32_t)(uintptr_t)entry_memory, 1);
    char *entry = entry_memory
        ? construct_report_entry(entry_memory, report_entry_category_name(index))
        : NULL;
    uint32_t *entry_collection = (uint32_t *)(uintptr_t)
        *(uint32_t *)(void *)(manager + 208);
    insert_pointer_array_element((int *)(void *)(manager + 200),
                                 entry_collection, &entry);
  }

  initialize_std_string_storage((uint8_t *)report_filename, (uint8_t *)&default_value);
  assign_std_string_storage_from_c_string((uint8_t *)path_separator, "-", (uint8_t *)&delimiter);
  uint8_t *profile_path = append_string_suffix(
      (uint8_t *)report_path, path_separator,
      (char *)(uintptr_t)system_profile_address);
  assign_std_string_storage(report_filename, profile_path);
  tidy_std_string_storage(report_path, 1);
  tidy_std_string_storage(path_separator, 1);
  size_t extension_length = strlen(".log");
  append_std_string_storage_bytes(report_filename, ".log", (char *)(uintptr_t)extension_length);

  uint32_t *report_entries = (uint32_t *)(uintptr_t)
      *(uint32_t *)(void *)(manager + 204);
  uint32_t *entry = (uint32_t *)(uintptr_t)report_entries[1];
  uint32_t entry_flags = entry[6];
  entry[5] = 2;
  set_report_entry_output_flags(entry, entry_flags | 1);
  entry[7] = (entry[7] & 0xFFFFFF00u) | ((entry[7] & 0xFFu) | 0xD0u);
  uint32_t *setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "errors", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);

  *(uint32_t *)(void *)(manager + 216) = 0;
  *(uint32_t *)(void *)(manager + 220) = 0;
  entry = (uint32_t *)(uintptr_t)*report_entries;
  entry[5] = 3;
  set_report_entry_output_flags(entry, 5);
  entry[7] = 0xFFFF;
  setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "errors", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);

  entry = (uint32_t *)(uintptr_t)report_entries[6];
  entry_flags = entry[6];
  entry[5] = 2;
  set_report_entry_output_flags(entry, entry_flags | 1);
  entry[7] = (entry[7] & 0xFFFFFF00u) | ((entry[7] & 0xFFu) | 0xD0u);
  setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "errors", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);

  entry = (uint32_t *)(uintptr_t)report_entries[5];
  entry_flags = entry[6];
  entry[5] = 1;
  set_report_entry_output_flags(entry, entry_flags | 1);
  entry[7] = (entry[7] & 0xFFFFFF00u) | ((entry[7] & 0xFFu) | 0xD0u);
  setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "errors", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);

  entry = (uint32_t *)(uintptr_t)report_entries[9];
  set_report_entry_output_flags(entry, 4);
  entry[7] = 2;
  entry = (uint32_t *)(uintptr_t)report_entries[2];
  entry[5] = 4;
  set_report_entry_output_flags(entry, 1);
  entry[7] |= 3u << 8;
  setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "ResTrack", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);
  *((uint8_t *)(void *)entry + 56) = 1;
  write_report_entry_line((int)(uintptr_t)entry,
             "Z:\\Proj\\GK3\\gk3app\\Source\\ReportMgr.cpp", 761);

  entry = (uint32_t *)(uintptr_t)report_entries[10];
  entry[5] = 1;
  set_report_entry_output_flags(entry, 7);
  entry[7] = (entry[7] & 0xFFFFFF00u) | ((entry[7] & 0xFFu) | 0xD0u);
  setting = (uint32_t *)(void *)combine_text_prefix_and_string_storage(
      (uint8_t *)report_path, "errors", (uint8_t *)report_filename);
  set_report_entry_filename((int)(uintptr_t)entry,
             setting[1] ? (char *)(uintptr_t)setting[1] : (char *)Key);
  tidy_std_string_storage(report_path, 1);

  ((uint32_t *)(uintptr_t)report_entries[13])[7] = 2;
  ((uint32_t *)(uintptr_t)report_entries[3])[7] = 2;
  ((uint32_t *)(uintptr_t)report_entries[8])[7] = 2;
  entry = (uint32_t *)(uintptr_t)report_entries[12];
  entry_flags = entry[6] & ~0x10u;
  entry[7] = 2;
  set_report_entry_output_flags(entry, entry_flags);
  entry = (uint32_t *)(uintptr_t)report_entries[15];
  entry_flags = entry[6] & ~0x10u;
  entry[7] = 2;
  set_report_entry_output_flags(entry, entry_flags);
  ((uint32_t *)(uintptr_t)report_entries[4])[7] = 2;
  *((uint8_t *)(uintptr_t)((uint32_t)(uintptr_t)report_entries[16] + 80)) = 0;
  ((uint32_t *)(uintptr_t)report_entries[17])[5] = 1;
  ((uint32_t *)(uintptr_t)report_entries[18])[5] = 2;
  ((uint32_t *)(uintptr_t)report_entries[19])[5] = 2;
  ((uint32_t *)(uintptr_t)report_entries[23])[7] = 2;
  tidy_std_string_storage((char *)report_filename, 1);
  return object;
}

int __thiscall initialize_application_log_manager(int object)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)object;
  int message_type;
  int message_id;
  uint32_t *warning_counter = allocate_registered_report_indicator(68);
  uint32_t *error_counter;
  uint32_t text_setting = 0;
  uint32_t application_engine =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t log_service = *(uint32_t *)(uintptr_t)(application_engine + 68);
  int log_service_address =
      *(int *)(uintptr_t)(log_service + 28);

  attach_control_to_service(log_service_address, object, 1);
  get_report_indicator_resource_ids(&message_type, &message_id);
  if (warning_counter)
    warning_counter = construct_report_indicator(
        warning_counter, warning_indicator_resource_name_table[0],
        warning_indicator_resource_name_table[0], 0);
  *(uint32_t *)(void *)(manager + 216) =
      (uint32_t)(uintptr_t)warning_counter;
  set_control_tooltip_text(warning_counter, "Number of current warnings");

  error_counter = allocate_registered_report_indicator(68);
  if (error_counter)
    error_counter = construct_report_indicator(
        error_counter, error_indicator_icon_resource_name_table[0],
        error_indicator_label_resource_name_table[0], 0);
  *(uint32_t *)(void *)(manager + 220) = (uint32_t)(uintptr_t)error_counter;
  set_control_tooltip_text(error_counter, "Number of current errors");
  resize_report_indicators((uint32_t **)(void *)manager);
  resize_pointer_array((int *)(void *)(manager + 224), 2, &text_setting);
  insert_control_into_control_container(manager,
             (int)(uintptr_t)*(uint32_t *)(void *)(manager + 216), 1);
  insert_control_into_control_container(manager,
             (int)(uintptr_t)*(uint32_t *)(void *)(manager + 220), 1);

  typedef int (__thiscall *ReportManagerMethod)(int manager, int argument);
  uint32_t vtable = *(uint32_t *)(void *)manager;
  ReportManagerMethod set_reporting_mode =
      (ReportManagerMethod)(uintptr_t)(vtable + 168);
  ReportManagerMethod enable_reporting =
      (ReportManagerMethod)(uintptr_t)(vtable + 176);
  set_reporting_mode(object, interface_layer_type_descriptor);
  return enable_reporting(object, 1);
}

uint32_t *__cdecl allocate_registered_report_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(report_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_report_manager(void)
{
  uint32_t *memory = allocate_registered_report_manager(240);
  return memory
      ? (uint32_t *)(uintptr_t)construct_report_manager(
            (int)(uintptr_t)memory)
      : NULL;
}

uint32_t *__cdecl create_registered_report_manager(void)
{
  uint32_t *memory = allocate_registered_report_manager(240);
  return memory
      ? (uint32_t *)(uintptr_t)construct_registered_report_manager(
            (int)(uintptr_t)memory, 0)
      : NULL;
}

int shutdown_report_manager(uint32_t *manager)
{
  return destroy_report_manager_members(manager);
}
