#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dbt.h>

typedef struct {
  uint8_t state;
  uint8_t reserved[3];
  uint32_t data_address;
  uint32_t length;
  uint32_t capacity;
} CdMonitorString;

typedef struct {
  uint8_t state;
  uint8_t reserved[3];
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} CdVolumeList;

typedef struct {
  uint32_t vtable;
  uint32_t query_cancel_auto_play_message;
  uint32_t no_drive_type_auto_run;
  uint32_t poll_interval_ms;
  uint32_t last_poll_time;
  uint8_t paused;
  uint8_t reserved_21[7];
  uint32_t drive_event_worker;
  CdMonitorString game_identity;
  CdVolumeList drives;
  int32_t target_volume_id;
  CdMonitorString data_path;
  uint8_t polling_enabled;
  uint8_t reserved_85[3];
  uint32_t reserved_88;
  uint32_t reserved_92;
  uint32_t data_chunk_size;
  uint32_t data_wrap_offset;
  uint32_t data_probe_offset;
  uint8_t reserved_108[4];
  uint32_t volume_arrival_event[2];
  uint32_t volume_removal_event[2];
} CdMonitor;

typedef struct {
  char drive_letter;
  uint8_t reserved[3];
  int32_t volume_id;
  int32_t state;
} CdVolumeEntry;

_Static_assert(sizeof(CdMonitorString) == 16, "CD monitor string size");
_Static_assert(sizeof(CdVolumeList) == 16, "CD monitor drive-list size");
_Static_assert(offsetof(CdMonitor, poll_interval_ms) == 12,
               "CD monitor poll interval offset");
_Static_assert(offsetof(CdMonitor, last_poll_time) == 16,
               "CD monitor last poll time offset");
_Static_assert(offsetof(CdMonitor, paused) == 20,
               "CD monitor paused flag offset");
_Static_assert(offsetof(CdMonitor, game_identity) +
                   offsetof(CdMonitorString, data_address) == 36,
               "CD monitor game-identity pointer offset");
_Static_assert(offsetof(CdMonitor, drives) +
                   offsetof(CdVolumeList, begin) == 52,
               "CD monitor drive-list begin offset");
_Static_assert(offsetof(CdMonitor, drives) +
                   offsetof(CdVolumeList, end) == 56,
               "CD monitor drive-list end offset");
_Static_assert(offsetof(CdMonitor, drives) +
                   offsetof(CdVolumeList, capacity) == 60,
               "CD monitor drive-list capacity offset");
_Static_assert(offsetof(CdMonitor, target_volume_id) == 64,
               "CD monitor target volume ID offset");
_Static_assert(offsetof(CdMonitor, data_path) +
                   offsetof(CdMonitorString, data_address) == 72,
               "CD monitor data-path pointer offset");
_Static_assert(offsetof(CdMonitor, polling_enabled) == 84,
               "CD monitor enabled flag offset");
_Static_assert(offsetof(CdMonitor, data_chunk_size) == 96,
               "CD monitor data chunk size offset");
_Static_assert(offsetof(CdMonitor, data_wrap_offset) == 100,
               "CD monitor data wrap offset");
_Static_assert(offsetof(CdMonitor, data_probe_offset) == 104,
               "CD monitor probe offset");
_Static_assert(offsetof(CdMonitor, volume_arrival_event) == 112,
               "CD monitor volume-arrival event offset");
_Static_assert(offsetof(CdMonitor, volume_removal_event) == 120,
               "CD monitor volume-removal event offset");
_Static_assert(sizeof(CdMonitor) == 128, "CD monitor allocation size");
_Static_assert(sizeof(CdVolumeEntry) == 12, "CD volume entry size");

/* gk3/GK3R_rest.c */
extern const char Key[4];
extern int game_engine_address;
extern int system_profile_address;
extern int (__stdcall *off_6B87A0[2])(char);
extern int (__stdcall *off_6F3054)(char);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/event_dispatch.c */
extern int __thiscall queue_engine_event(uint32_t *engine, int *event);

/* platform/window_proc.c */
extern uint32_t *__thiscall register_window_message_hook(
    uint32_t *engine, int callback, int context,
    char insert_before_equal_priority, int priority);

typedef int (__thiscall *CdDriveWorkerToggle)(void *worker, int enabled);

unsigned int __thiscall insert_cd_volume_entries(
    int *list_words, char *position, int count, uint32_t *entries)
{
  CdVolumeList *list = (CdVolumeList *)list_words;
  const size_t entry_size = sizeof(CdVolumeEntry);
  const size_t maximum_capacity = INT32_MAX / entry_size;
  const uintptr_t begin_address = list->begin;
  const uintptr_t end_address = list->end;
  const uintptr_t capacity_address = list->capacity;
  uint8_t *begin = (uint8_t *)(uintptr_t)begin_address;
  uint8_t *insertion_point = (uint8_t *)position;

  if (count <= 0)
    return list->end;
  if ((size_t)count > maximum_capacity || end_address < begin_address
      || capacity_address < end_address)
    return list->end;

  const size_t current_count = begin
      ? (end_address - begin_address) / entry_size
      : 0;
  const uintptr_t insertion_address = (uintptr_t)insertion_point;
  if ((begin && (insertion_address < begin_address
                 || insertion_address > end_address
                 || (insertion_address - begin_address) % entry_size != 0))
      || current_count > maximum_capacity)
    return list->end;

  const size_t prefix_count = begin
      ? (insertion_address - begin_address) / entry_size
      : 0;
  const size_t inserted_count = (size_t)count;
  const size_t suffix_count = current_count - prefix_count;
  const size_t inserted_bytes = inserted_count * entry_size;
  const size_t available_bytes = capacity_address - end_address;

  if (begin && available_bytes >= inserted_bytes) {
    memmove(insertion_point + inserted_bytes, insertion_point,
            suffix_count * entry_size);
    memcpy(insertion_point, entries, inserted_bytes);
    list->end += (uint32_t)inserted_bytes;
    return list->end;
  }

  const size_t growth = current_count > inserted_count
      ? current_count
      : inserted_count;
  if (growth > maximum_capacity - current_count)
    return list->end;

  const size_t new_capacity = current_count + growth;
  const size_t new_count = current_count + inserted_count;
  uint8_t *new_begin = (uint8_t *)allocate_tracked_memory(
      (int)(new_capacity * entry_size));
  if (!new_begin)
    return list->end;

  if (prefix_count)
    memcpy(new_begin, begin, prefix_count * entry_size);
  memcpy(new_begin + prefix_count * entry_size, entries, inserted_bytes);
  if (suffix_count) {
    memcpy(new_begin + (prefix_count + inserted_count) * entry_size,
           insertion_point, suffix_count * entry_size);
  }

  if (begin)
    free_tracked_memory((int)begin_address);

  list->begin = (uint32_t)(uintptr_t)new_begin;
  list->end = (uint32_t)(uintptr_t)(new_begin + new_count * entry_size);
  list->capacity =
      (uint32_t)(uintptr_t)(new_begin + new_capacity * entry_size);
  return list->end;
}

CdVolumeEntry *__thiscall find_cd_volume_by_drive_index(
    CdMonitor *monitor, int drive_index)
{
  for (uint32_t entry_address = monitor->drives.begin;
       entry_address != monitor->drives.end;
       entry_address += sizeof(CdVolumeEntry)) {
    CdVolumeEntry *entry = (CdVolumeEntry *)(uintptr_t)entry_address;
    if (entry->drive_letter - 'A' == drive_index)
      return entry;
  }

  return NULL;
}

void __thiscall refresh_cd_volume_entry(CdVolumeEntry *entry,
                                        CdMonitorString *identity)
{
  char root_path[] = {entry->drive_letter, ':', '\\', '\0'};
  char volume_name[MAX_PATH];
  char file_system_name[MAX_PATH];
  DWORD volume_serial_number;
  DWORD maximum_component_length;
  DWORD file_system_flags;

  entry->volume_id = 0;
  entry->state = 1;

  const UINT previous_error_mode = SetErrorMode(SEM_FAILCRITICALERRORS);
  const BOOL has_volume_information = GetVolumeInformationA(
      root_path, volume_name, sizeof(volume_name), &volume_serial_number,
      &maximum_component_length, &file_system_flags, file_system_name,
      sizeof(file_system_name));
  SetErrorMode(previous_error_mode);

  if (!has_volume_information
      || strlen(volume_name) <= identity->length)
    return;

  const int volume_id = atoi(volume_name + identity->length);
  if (volume_id > 0) {
    entry->volume_id = volume_id;
    entry->state = 2;
  }
}

char __thiscall handle_cd_drive_arrival(int monitor_address, int drive_index)
{
  CdMonitor *monitor = (CdMonitor *)(uintptr_t)(uint32_t)monitor_address;
  CdVolumeEntry *entry = find_cd_volume_by_drive_index(monitor, drive_index);
  if (!entry)
    return 0;

  refresh_cd_volume_entry(entry, &monitor->game_identity);

  if (!monitor->paused) {
    if (entry->volume_id >= 1) {
      queue_engine_event(
          (uint32_t *)(uintptr_t)(uint32_t)game_engine_address,
          (int *)monitor->volume_arrival_event);
    }
    if (!monitor->paused)
      return 0;
  }

  if (monitor->target_volume_id != entry->volume_id) {
    uint32_t *worker = (uint32_t *)(uintptr_t)monitor->drive_event_worker;
    uint32_t *vtable = (uint32_t *)(uintptr_t)worker[0];
    CdDriveWorkerToggle toggle = (CdDriveWorkerToggle)(uintptr_t)vtable[8];
    toggle(worker, 0);
    Sleep(250);
    return (char)toggle(worker, 1);
  }

  return (char)monitor->target_volume_id;
}

char __thiscall handle_cd_drive_removal(int monitor_address, int drive_index)
{
  CdMonitor *monitor = (CdMonitor *)(uintptr_t)(uint32_t)monitor_address;
  CdVolumeEntry *entry = find_cd_volume_by_drive_index(monitor, drive_index);
  if (!entry)
    return 0;

  char result = (char)monitor->paused;
  if (!monitor->paused && entry->volume_id >= 1) {
    result = (char)queue_engine_event(
        (uint32_t *)(uintptr_t)(uint32_t)game_engine_address,
        (int *)monitor->volume_removal_event);
  }

  entry->volume_id = 0;
  entry->state = 1;
  return result;
}

char __thiscall handle_cd_volume_arrival_mask(void *monitor, int unit_mask)
{
  const int monitor_address = (int)(uintptr_t)monitor;
  char result = 0;

  for (int drive_index = 0; drive_index < 32; ++drive_index) {
    const uint32_t drive_bit = UINT32_C(1) << drive_index;
    if ((uint32_t)unit_mask & drive_bit) {
      const char drive_result = handle_cd_drive_arrival(
          monitor_address, drive_index);
      if (drive_index == 31)
        result = drive_result;
    }
  }

  return result;
}

char __thiscall handle_cd_volume_removal_mask(void *monitor, int unit_mask)
{
  const int monitor_address = (int)(uintptr_t)monitor;
  char result = 0;

  for (int drive_index = 0; drive_index < 32; ++drive_index) {
    const uint32_t drive_bit = UINT32_C(1) << drive_index;
    if ((uint32_t)unit_mask & drive_bit) {
      const char drive_result = handle_cd_drive_removal(
          monitor_address, drive_index);
      if (drive_index == 31)
        result = drive_result;
    }
  }

  return result;
}

char __thiscall handle_cd_monitor_window_message(
    uint32_t *monitor, int window, int message, int wparam, int lparam,
    uint32_t *result)
{
  (void)window;
  *result = 0;

  if (message == WM_DEVICECHANGE) {
    if (lparam && (wparam == DBT_DEVICEARRIVAL
                   || wparam == DBT_DEVICEREMOVECOMPLETE)) {
      const DEV_BROADCAST_HDR *device_header =
          (const DEV_BROADCAST_HDR *)(uintptr_t)(uint32_t)lparam;
      if (device_header->dbch_devicetype == DBT_DEVTYP_VOLUME) {
        const DEV_BROADCAST_VOLUME *volume_event =
            (const DEV_BROADCAST_VOLUME *)device_header;
        if (volume_event->dbcv_flags & DBTF_MEDIA) {
          if (wparam == DBT_DEVICEARRIVAL)
            handle_cd_volume_arrival_mask(
                monitor, (int)volume_event->dbcv_unitmask);
          else
            handle_cd_volume_removal_mask(
                monitor, (int)volume_event->dbcv_unitmask);
        }
      }
    }
    return 1;
  }

  if ((uint32_t)message == monitor[1]) {
    *result = 1;
    return 1;
  }

  return 0;
}

void initialize_cd_monitor_strings(char *memory)
{
  CdMonitor *monitor = (CdMonitor *)memory;
  CdMonitorString *game_identity = &monitor->game_identity;
  CdMonitorString *data_path = &monitor->data_path;
  static const char common_data_path[] = "/data/common.brn";

  memset(game_identity, 0, sizeof(*game_identity));
  memset(data_path, 0, sizeof(*data_path));

  const uint32_t path_length = sizeof(common_data_path) - 1;
  uint8_t *allocation = (uint8_t *)allocate_tracked_memory(
      (int)(path_length + 2));
  if (!allocation)
    return;

  allocation[0] = 0;
  memcpy(allocation + 1, common_data_path, sizeof(common_data_path));
  data_path->data_address = (uint32_t)(uintptr_t)(allocation + 1);
  data_path->length = path_length;
  data_path->capacity = path_length;
}

void set_cd_monitor_game_identity(char *memory)
{
  CdMonitor *monitor = (CdMonitor *)memory;
  CdMonitorString *game_identity = &monitor->game_identity;
  static const char game_identity_text[] = "GK3";
  const uint32_t identity_length = sizeof(game_identity_text) - 1;

  uint8_t *allocation = (uint8_t *)allocate_tracked_memory(
      (int)(identity_length + 2));
  if (!allocation)
    return;

  allocation[0] = 0;
  memcpy(allocation + 1, game_identity_text, sizeof(game_identity_text));
  game_identity->data_address = (uint32_t)(uintptr_t)(allocation + 1);
  game_identity->length = identity_length;
  game_identity->capacity = identity_length;
}

void __thiscall enumerate_cd_rom_drives(void *memory)
{
  CdMonitor *monitor = (CdMonitor *)memory;
  const DWORD logical_drives = GetLogicalDrives();

  for (unsigned int drive_index = 0; drive_index < 32; ++drive_index) {
    const DWORD drive_mask = (DWORD)1 << drive_index;
    if (!(logical_drives & drive_mask))
      continue;

    char drive_path[3] = {(char)('A' + drive_index), ':', '\0'};
    if (GetDriveTypeA(drive_path) != DRIVE_CDROM)
      continue;

    CdVolumeEntry entry = {
      .drive_letter = drive_path[0],
      .reserved = {0},
      .volume_id = 0,
      .state = 1
    };
    insert_cd_volume_entries((int *)&monitor->drives,
                             (char *)(uintptr_t)monitor->drives.end, 1,
                             (uint32_t *)&entry);
  }
}

char __stdcall cd_monitor_window_message_callback(
    int window, int message, int wparam, int lparam, uint32_t *monitor,
    uint32_t *result)
{
  return handle_cd_monitor_window_message(monitor, window, message, wparam,
                                          lparam, result);
}

char *__thiscall construct_cd_monitor(char *memory)
{
  CdMonitor *monitor = (CdMonitor *)memory;
  initialize_cd_monitor_strings(memory);

  monitor->vtable = (uint32_t)(uintptr_t)&off_6F3054;
  monitor->query_cancel_auto_play_message =
      RegisterWindowMessageA("QueryCancelAutoPlay");
  monitor->no_drive_type_auto_run = 149;
  monitor->poll_interval_ms = 3000;
  monitor->last_poll_time = 0;
  monitor->paused = 0;
  monitor->drive_event_worker = 0;

  monitor->drives.state = 0;
  monitor->drives.begin = 0;
  monitor->drives.end = 0;
  monitor->drives.capacity = 0;
  monitor->target_volume_id = 0;
  monitor->polling_enabled = 0;
  monitor->reserved_88 = 0;
  monitor->reserved_92 = 0;
  monitor->data_chunk_size = *(uint32_t *)(uintptr_t)
      ((uint32_t)system_profile_address + 92);
  monitor->data_wrap_offset = 0;
  monitor->data_probe_offset = 0;
  monitor->reserved_108[0] = 0;
  monitor->volume_arrival_event[0] = 0;
  monitor->volume_arrival_event[1] = 0;
  monitor->volume_removal_event[0] = 0;
  monitor->volume_removal_event[1] = 0;

  uint32_t *drive_event_worker = allocate_tracked_memory(8);
  if (drive_event_worker) {
    drive_event_worker[0] = (uint32_t)(uintptr_t)off_6B87A0;
    *((uint8_t *)drive_event_worker + 4) = 0;
  }
  monitor->drive_event_worker = (uint32_t)(uintptr_t)drive_event_worker;
  set_cd_monitor_game_identity(memory);

  enumerate_cd_rom_drives(monitor);
  register_window_message_hook(
      (uint32_t *)(uintptr_t)(uint32_t)game_engine_address,
      (int)(uintptr_t)cd_monitor_window_message_callback,
      (int)(uintptr_t)monitor, 1, 0);
  return memory;
}

int __thiscall find_cd_volume_by_id(uint32_t *monitor_words, int volume_id)
{
  CdMonitor *monitor = (CdMonitor *)monitor_words;
  if (volume_id <= 0)
    return 0;

  for (uint32_t entry_address = monitor->drives.begin;
       entry_address != monitor->drives.end;
       entry_address += sizeof(CdVolumeEntry)) {
    CdVolumeEntry *entry = (CdVolumeEntry *)(uintptr_t)entry_address;
    if (entry->volume_id == volume_id)
      return (int)entry_address;
  }

  return 0;
}

HANDLE __thiscall touch_next_cd_data_chunk(uint32_t *monitor_words,
                                            const char *drive)
{
  CdMonitor *monitor = (CdMonitor *)monitor_words;
  const char *data_path =
      (const char *)(uintptr_t)monitor->data_path.data_address;
  if (!data_path)
    data_path = Key;

  char file_name[MAX_PATH];
  snprintf(file_name, sizeof(file_name), "%s:%s", drive, data_path);

  HANDLE file = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ, NULL,
                            OPEN_EXISTING,
                            0x28000001, NULL);
  if (file == INVALID_HANDLE_VALUE)
    return file;

  HANDLE mapping = CreateFileMappingA(file, NULL, 0x18000002, 0, 0, NULL);
  if (mapping) {
    const void *view = MapViewOfFile(mapping, FILE_MAP_READ, 0,
                                     monitor->data_probe_offset,
                                     monitor->data_chunk_size);
    if (view)
      UnmapViewOfFile(view);
    CloseHandle(mapping);
  }

  monitor->data_probe_offset += 0x200000;
  const DWORD file_size = GetFileSize(file, NULL);
  if (monitor->data_probe_offset >= file_size - monitor->data_chunk_size) {
    const uint32_t next_offset = monitor->data_chunk_size +
        monitor->data_wrap_offset;
    monitor->data_wrap_offset = next_offset;
    monitor->data_probe_offset = next_offset;
  }

  return (HANDLE)(uintptr_t)CloseHandle(file);
}

char __thiscall poll_cd_monitor(int monitor_address, int current_time)
{
  CdMonitor *monitor = (CdMonitor *)(uintptr_t)
      (uint32_t)monitor_address;
  char result = (char)monitor->paused;

  if (!result) {
    result = (char)monitor->polling_enabled;
    if (result) {
      const uint32_t elapsed = (uint32_t)current_time -
          monitor->last_poll_time;
      result = (char)elapsed;

      if (elapsed >= monitor->poll_interval_ms) {
        const int drive_address = find_cd_volume_by_id(
            (uint32_t *)monitor, monitor->target_volume_id);
        result = (char)drive_address;

        if (drive_address) {
          monitor->last_poll_time = (uint32_t)current_time;
          result = (char)(uintptr_t)touch_next_cd_data_chunk(
              (uint32_t *)monitor,
              (const char *)(uintptr_t)(uint32_t)drive_address);
        }
      }
    }
  }

  return result;
}
