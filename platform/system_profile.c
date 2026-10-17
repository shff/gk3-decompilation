#include <stdint.h>
#include <string.h>
#include <windows.h>

/* gk3/GK3R_rest.c */
extern int system_profile_address;

void init_system_profile(uint8_t *profile)
{
  enum {
    name_size = 32,
    user_name_offset = 32,
    system_info_offset = 64,
    os_version_offset = 100,
    memory_size_offset = 104,
  };

  system_profile_address = (int)(intptr_t)profile;

  DWORD name_length = name_size;
  char *computer_name = (char *)profile;
  if (!GetComputerNameA(computer_name, &name_length) || computer_name[0] == '\0' || name_length == 0) {
    strcpy(computer_name, "(unknown machine)");
  }

  name_length = name_size;
  char *user_name = (char *)(profile + user_name_offset);
  if (!GetUserNameA(user_name, &name_length) || user_name[0] == '\0' || name_length == 0) {
    strcpy(user_name, "(unknown user)");
  }

  GetSystemInfo((SYSTEM_INFO *)(profile + system_info_offset));

  OSVERSIONINFOA version = { .dwOSVersionInfoSize = sizeof(version) };
  GetVersionExA(&version);
  uint32_t os_version = 0;
  if (version.dwPlatformId == 1) {
    os_version = (version.dwMinorVersion != 0) + 1;
  } else if (version.dwPlatformId == 2) {
    if (version.dwMajorVersion == 3 || version.dwMajorVersion == 4) {
      os_version = 3;
    } else if (version.dwMajorVersion == 5) {
      os_version = 4;
    }
  }
  memcpy(profile + os_version_offset, &os_version, sizeof(os_version));

  MEMORYSTATUS memory = { .dwLength = sizeof(memory) };
  GlobalMemoryStatus(&memory);
  uint32_t total_memory = memory.dwTotalPhys;
  memcpy(profile + memory_size_offset, &total_memory, sizeof(total_memory));
}

void clear_system_profile(void)
{
  system_profile_address = 0;
}
