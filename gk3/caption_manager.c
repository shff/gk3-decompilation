#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/registry.c */
extern uint32_t *__thiscall erase_map_entry_impl(uint32_t *map,
                                                 uint32_t address);

/* engine/settings.c */
extern char __thiscall select_settings_section(uint32_t *settings,
                                               const char *section);
extern char __thiscall read_boolean_setting_or_default(
    uint32_t *settings, const char *name, char fallback);
extern int __thiscall read_integer_setting_or_default(
    uint32_t *settings, const char *name, int fallback);

/* engine/controls.c */
extern int __thiscall construct_control(int object);
extern int __thiscall set_control_active(uint8_t *control, char active);

/* gk3/GK3R_rest.c */
extern uint32_t caption_manager_registry[] __asm__("dword_7641A0");
extern int caption_manager_registry_offset __asm__("dword_764198");
extern uint32_t caption_manager_vtable[] __asm__("off_6AE970");
extern uint32_t embedded_caption_control_vtable[] __asm__("off_6AEA48");
extern int caption_manager_restore_value __asm__("dword_764190");
extern int caption_manager_current_value __asm__("dword_764194");
extern int game_engine_instance_address __asm__("dword_765A2C");
extern int caption_manager_saved_state_pointer __asm__("dword_7715C8");
extern int caption_manager_default_layout __asm__("dword_76D3C0");

extern int __thiscall sub_447B7E(int object);
extern uint32_t *__thiscall sub_447C29(uint32_t *object);
extern int __thiscall sub_566D10(uint32_t *registry, uint32_t address);
extern int __thiscall sub_45B25C(uint32_t *object, char *default_value);
extern int __thiscall sub_45B1E5(void *object);
extern int __thiscall sub_45AF2F(uint8_t *object, int enabled);
extern int __thiscall sub_476C91(uint32_t *object, int *layout);
extern char *__thiscall sub_46C1FA(uint32_t *settings, const char *name,
                                   int fallback);
extern uint32_t *__cdecl sub_45A0F8(int size);
extern uint32_t *__thiscall sub_46B4E2(uint32_t *object,
                                      const char *filename, int flags);
extern int __thiscall destroy_embedded_caption_control(uint32_t *object)
    __asm__("sub_45A0A1");
extern int __thiscall sub_45B2D5(uint32_t *list);
extern int __thiscall sub_5065FE(uint8_t *object, int context);
extern int __cdecl write_caption_manager_diagnostic(
    const char *source_file, int line, int category, int flags,
    const char *format, int color) __asm__("sub_557404");
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address) __asm__("sub_566D10");

uint32_t *__thiscall construct_caption_manager(uint32_t *manager)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  char default_value;
  uint32_t *settings;
  uint32_t *control;
  char *caption_color;
  uint32_t *font_colors;

  sub_447B7E((int)(uintptr_t)manager);
  find_or_create_registry_entry(
      caption_manager_registry,
      (uint32_t)(uintptr_t)manager + (uint32_t)caption_manager_registry_offset
          + 197);
  sub_45B25C((uint32_t *)(void *)(bytes + 376), &default_value);
  construct_control((int)(uintptr_t)(bytes + 424));
  sub_45B1E5(bytes + 468);
  *(uint32_t *)(void *)(bytes + 468) = 0;
  *(uint32_t *)(void *)(bytes + 424) =
      (uint32_t)(uintptr_t)embedded_caption_control_vtable;
  *(float *)(void *)(bytes + 472) = 1.0f;
  manager[0] = (uint32_t)(uintptr_t)caption_manager_vtable;
  memset(bytes + 200, 0, 176);
  sub_45AF2F(bytes, 1);
  caption_manager_current_value =
      *(uint32_t *)(uintptr_t)caption_manager_saved_state_pointer;
  caption_manager_restore_value = 0;
  sub_476C91(manager, &caption_manager_default_layout);

  uint32_t *application_components = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  settings = (uint32_t *)(uintptr_t)application_components[25];
  select_settings_section(settings, "Captions");
  bytes[476] = (uint8_t)read_boolean_setting_or_default(
      settings, "Shaded Captions", 0);

  const float darkness = (float)read_integer_setting_or_default(
      settings, "Shaded Caption Darkness", 50) * 0.01f;
  control = (uint32_t *)(void *)(bytes + 424);
  caption_color = sub_46C1FA(settings, "Shaded Caption Color", 0);
  if (darkness != *(float *)(void *)(bytes + 472)) {
    *(float *)(void *)(bytes + 472) = darkness;
    ((void (__thiscall *)(uint32_t *))(uintptr_t)
        *(uint32_t *)(uintptr_t)(control[0] + 156))(control);
  }
  if (*(char **)(void *)(bytes + 468) != caption_color) {
    *(uint32_t *)(void *)(bytes + 468) = (uint32_t)(uintptr_t)caption_color;
    ((void (__thiscall *)(uint32_t *))(uintptr_t)
        *(uint32_t *)(uintptr_t)(control[0] + 156))(control);
  }

  font_colors = sub_45A0F8(60);
  manager[120] = (uint32_t)(uintptr_t)(font_colors
      ? sub_46B4E2(font_colors, "fontcolor.txt", 0)
      : NULL);
  uint32_t *font_color_file = (uint32_t *)(uintptr_t)manager[120];
  if (!((int (__thiscall *)(uint32_t *, int))(uintptr_t)
          *(uint32_t *)(uintptr_t)(font_color_file[0] + 4))(
              font_color_file, 1)) {
    write_caption_manager_diagnostic(
        "Z:\\Proj\\GK3\\gk3app\\Source\\CaptionMgr.cpp", 356, 6, 0,
        "Unable to find/load/read font color config file 'fontcolor.txt'.\n",
        -1);
  }
  set_control_active(bytes, 1);
  return manager;
}

uint32_t *__thiscall destroy_caption_manager_members(uint32_t *manager)
{
  manager[0] = (uint32_t)(uintptr_t)caption_manager_vtable;
  uint32_t *font_color_file = (uint32_t *)(uintptr_t)manager[120];
  if (font_color_file) {
    ((void (__thiscall *)(uint32_t *, int))(uintptr_t)
        *(uint32_t *)(uintptr_t)font_color_file[0])(
            font_color_file, 1);
  }

  destroy_embedded_caption_control(manager + 106);
  while (manager[105])
    sub_45B2D5(manager + 94);
  erase_map_entry_impl(
      caption_manager_registry,
      (uint32_t)(uintptr_t)manager + (uint32_t)caption_manager_registry_offset
          + 197);
  return sub_447C29(manager);
}

uint32_t *__thiscall destroy_caption_manager(uint32_t *manager,
                                            char release_memory)
{
  destroy_caption_manager_members(manager);
  if (release_memory & 1)
    free_tracked_memory((int)(uintptr_t)manager);
  return manager;
}

uint32_t *__thiscall construct_caption_manager_with_context(
    uint32_t *manager, int context)
{
  uint8_t *bytes = (uint8_t *)(void *)manager;
  char default_value;

  sub_5065FE(bytes, context);
  find_or_create_registry_entry(
      caption_manager_registry,
      (uint32_t)(uintptr_t)manager + (uint32_t)caption_manager_registry_offset
          + 197);
  sub_45B25C((uint32_t *)(void *)(bytes + 376), &default_value);
  manager[0] = (uint32_t)(uintptr_t)caption_manager_vtable;
  return manager;
}

uint32_t *__cdecl allocate_registered_caption_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(caption_manager_registry,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *create_registered_caption_manager(void)
{
  uint32_t *memory = allocate_registered_caption_manager(484);
  return memory ? construct_caption_manager_with_context(memory, 0) : NULL;
}
