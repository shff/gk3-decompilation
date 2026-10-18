#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t layer_manager_type_descriptor[];
extern int layer_manager_base_offset_adjustment;
extern int game_engine_instance_address;
extern uint32_t layer_manager_vtable[];
extern int get_or_create_rc_bar_popper(void);
extern uint32_t *__thiscall remove_interface_layer(uint32_t *manager,
                                                   int layer_address);
extern int __cdecl destroy_interface_owned_layer(uint32_t *member);
extern uint32_t *__cdecl allocate_registered_caption_manager(int size);
extern uint32_t *__thiscall construct_caption_manager(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_binocs_layer(int size);
extern uint32_t *__thiscall construct_binocs_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_close_up_layer(int size);
extern uint32_t *__thiscall construct_close_up_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_config_controls_layer(int size);
extern uint32_t *__thiscall construct_config_controls_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_confirm_quit_layer(int size);
extern uint32_t *__thiscall construct_confirm_quit_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_driving_layer(int size);
extern uint32_t *__thiscall construct_driving_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_fingerprint_layer(int size);
extern uint32_t *__thiscall construct_fingerprint_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_game_help_layer(int size);
extern uint32_t *__thiscall construct_game_help_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_game_layer(int size);
extern uint32_t *__thiscall construct_game_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_inventory_layer(int size);
extern uint32_t *__thiscall construct_inventory_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_load_save_layer(int size);
extern uint32_t *__thiscall construct_load_save_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_lsr_layer(int size);
extern uint32_t *__thiscall construct_lsr_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_modal_message_layer(int size);
extern uint32_t *__thiscall construct_modal_message_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_movie_layer(int size);
extern uint32_t *__thiscall construct_movie_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_pause_layer(int size);
extern uint32_t *__thiscall construct_pause_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_save_game_layer(int size);
extern uint32_t *__thiscall construct_save_game_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_private_bottom_layer(int size);
extern uint32_t *__thiscall construct_private_bottom_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_time_block_layer(int size);
extern uint32_t *__thiscall construct_time_block_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_title_layer(int size);
extern uint32_t *__thiscall construct_title_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_death_layer(int size);
extern uint32_t *__thiscall construct_death_layer(uint32_t *object);
extern uint32_t *__cdecl allocate_registered_finished_layer(int size);
extern uint32_t *__thiscall construct_finished_layer(uint32_t *object);
extern int __stdcall assign_layer_name_string(const char *value,
                                              size_t length);

char *__thiscall get_game_layer_slot(char *manager, int layer_id,
                                     char create_if_missing);

char __thiscall has_game_layer_object(uint32_t *manager, int layer_id);
int __thiscall detach_game_layer_18(uint32_t *manager);
uint32_t *__thiscall get_or_create_caption_manager(uint32_t *manager);
char __thiscall has_caption_manager(uint32_t *manager);

int get_scene_layer(void)
{
  const uint32_t application_context =
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  char *layer_manager = (char *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(application_context + 72);
  char *scene_slot = get_game_layer_slot(layer_manager, 15, 1);
  return *(int *)(void *)scene_slot;
}

uint32_t *__thiscall construct_registered_layer_manager(uint32_t *object,
                                                         int unused)
{
  find_or_create_registry_entry(
      layer_manager_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)layer_manager_base_offset_adjustment + 4);
  object[0] = (uint32_t)(uintptr_t)layer_manager_vtable;
  return object;
}

uint32_t *__thiscall construct_layer_manager(uint32_t *object)
{
  find_or_create_registry_entry(layer_manager_type_descriptor,
             (uint32_t)(uintptr_t)object
                 + (uint32_t)layer_manager_base_offset_adjustment + 4);
  object[0] = (uint32_t)(uintptr_t)layer_manager_vtable;
  memset(object + 1, 0, 0x58);
  get_or_create_rc_bar_popper();
  return object;
}

uint32_t *__cdecl allocate_registered_layer_manager(int size)
{
  uint32_t *memory = allocate_tracked_memory(size);
  find_or_create_registry_entry(layer_manager_type_descriptor,
                                (uint32_t)(uintptr_t)memory)[2] = 1;
  return memory;
}

uint32_t *construct_application_layer_manager(void)
{
  uint32_t *memory = allocate_registered_layer_manager(92);
  return memory ? construct_layer_manager(memory) : NULL;
}

uint32_t *__cdecl create_registered_layer_manager(void)
{
  uint32_t *memory = allocate_registered_layer_manager(92);
  return memory ? construct_registered_layer_manager(memory, 0) : NULL;
}

char __thiscall is_game_layer_visible(char *manager, int layer_id)
{
  char *layer_slot = get_game_layer_slot(manager, layer_id, 0);
  uint32_t *layer = (uint32_t *)(uintptr_t)*(uint32_t *)(void *)layer_slot;
  if (!layer)
    return 0;

  uint32_t *vtable = (uint32_t *)(uintptr_t)layer[0];
  typedef int (__thiscall *IsLayerVisibleMethod)(uint32_t *);
  const IsLayerVisibleMethod is_visible =
      (IsLayerVisibleMethod)(uintptr_t)vtable[232 / sizeof(uint32_t)];
  return (char)is_visible(layer);
}

char __thiscall is_game_layer_active(char *manager, int layer_id)
{
  char *layer_slot = get_game_layer_slot(manager, layer_id, 0);
  uint32_t *layer = (uint32_t *)(uintptr_t)*(uint32_t *)(void *)layer_slot;
  if (!layer)
    return 0;

  uint32_t *vtable = (uint32_t *)(uintptr_t)layer[0];
  typedef int (__thiscall *IsLayerActiveMethod)(uint32_t *);
  const IsLayerActiveMethod is_active =
      (IsLayerActiveMethod)(uintptr_t)vtable[228 / sizeof(uint32_t)];
  return (char)is_active(layer);
}

int __thiscall close_game_layer(char *manager, int layer_id)
{
  char *layer_slot = get_game_layer_slot(manager, layer_id, 0);
  uint32_t *layer = (uint32_t *)(uintptr_t)*(uint32_t *)(void *)layer_slot;
  uint32_t *vtable = (uint32_t *)(uintptr_t)layer[0];
  typedef int (__thiscall *CloseLayerMethod)(uint32_t *);
  const CloseLayerMethod close_layer =
      (CloseLayerMethod)(uintptr_t)vtable[220 / sizeof(uint32_t)];
  return close_layer(layer);
}

int __thiscall set_game_layer_state(char *manager, int layer_id, int state)
{
  char *layer_slot = get_game_layer_slot(manager, layer_id, 1);
  uint32_t *layer = (uint32_t *)(uintptr_t)*(uint32_t *)(void *)layer_slot;
  uint32_t *vtable = (uint32_t *)(uintptr_t)layer[0];
  typedef int (__thiscall *SetLayerStateMethod)(uint32_t *, int);
  const SetLayerStateMethod set_state =
      (SetLayerStateMethod)(uintptr_t)vtable[216 / sizeof(uint32_t)];
  return set_state(layer, state);
}

char *__thiscall get_game_layer_slot(char *manager, int layer_id,
                                     char create_if_missing)
{
  uint32_t *slot = (uint32_t *)(void *)(manager + 4 * layer_id + 4);
  uint32_t *memory;
  uint32_t *layer;

  if (*slot || !create_if_missing)
    return (char *)(void *)slot;

  switch (layer_id) {
    case 0:
      memory = allocate_registered_binocs_layer(460);
      layer = memory ? construct_binocs_layer(memory) : NULL;
      break;
    case 1:
      memory = allocate_registered_close_up_layer(564);
      layer = memory ? construct_close_up_layer(memory) : NULL;
      break;
    case 2:
      memory = allocate_registered_config_controls_layer(616);
      layer = memory ? construct_config_controls_layer(memory) : NULL;
      break;
    case 3:
      memory = allocate_registered_confirm_quit_layer(804);
      layer = memory ? construct_confirm_quit_layer(memory) : NULL;
      break;
    case 4:
      memory = allocate_registered_driving_layer(796);
      layer = memory ? construct_driving_layer(memory) : NULL;
      break;
    case 5:
      memory = allocate_registered_fingerprint_layer(1752);
      layer = memory ? construct_fingerprint_layer(memory) : NULL;
      break;
    case 6:
      memory = allocate_registered_game_help_layer(1008);
      layer = memory ? construct_game_help_layer(memory) : NULL;
      break;
    case 7:
    case 15: {
      memory = allocate_registered_game_layer(328);
      layer = memory ? construct_game_layer(memory) : NULL;
      *slot = (uint32_t)(uintptr_t)layer;
      const char *name = layer_id == 15 ? "SceneLayer" : "InsetLayer";
      assign_layer_name_string(name, strlen(name));
      get_game_layer_slot(manager, 15, 1);
      return (char *)(void *)slot;
    }
    case 8:
      memory = allocate_registered_inventory_layer(648);
      layer = memory ? construct_inventory_layer(memory) : NULL;
      break;
    case 9:
      memory = allocate_registered_load_save_layer(852);
      layer = memory ? construct_load_save_layer(memory) : NULL;
      break;
    case 10:
      memory = allocate_registered_lsr_layer(672);
      layer = memory ? construct_lsr_layer(memory) : NULL;
      break;
    case 11:
      memory = allocate_registered_modal_message_layer(428);
      layer = memory ? construct_modal_message_layer(memory) : NULL;
      break;
    case 12:
      memory = allocate_registered_movie_layer(380);
      layer = memory ? construct_movie_layer(memory) : NULL;
      break;
    case 13:
      memory = allocate_registered_pause_layer(328);
      layer = memory ? construct_pause_layer(memory) : NULL;
      break;
    case 14:
      memory = allocate_registered_save_game_layer(1012);
      layer = memory ? construct_save_game_layer(memory) : NULL;
      break;
    case 16:
      memory = allocate_registered_private_bottom_layer(1848);
      layer = memory ? construct_private_bottom_layer(memory) : NULL;
      break;
    case 17:
      memory = allocate_registered_time_block_layer(996);
      layer = memory ? construct_time_block_layer(memory) : NULL;
      break;
    case 18:
      memory = allocate_registered_title_layer(388);
      layer = memory ? construct_title_layer(memory) : NULL;
      break;
    case 19:
      memory = allocate_registered_death_layer(800);
      layer = memory ? construct_death_layer(memory) : NULL;
      break;
    case 20:
      memory = allocate_registered_finished_layer(324);
      layer = memory ? construct_finished_layer(memory) : NULL;
      break;
    default:
      return (char *)(void *)slot;
  }

  *slot = (uint32_t)(uintptr_t)layer;
  return (char *)(void *)slot;
}

char __thiscall has_game_layer_object(uint32_t *manager, int layer_id)
{
  return manager[layer_id + 1] != 0;
}

int __thiscall detach_game_layer_18(uint32_t *manager)
{
  if (!has_game_layer_object(manager, 18))
    return 0;

  uint32_t *application_components = (uint32_t *)(uintptr_t)
      *(uint32_t *)(uintptr_t)(game_engine_instance_address + 1092);
  uint32_t *interface_manager =
      (uint32_t *)(uintptr_t)application_components[17];
  remove_interface_layer(interface_manager, (int)manager[19]);
  return destroy_interface_owned_layer(manager + 19);
}

uint32_t *__thiscall get_or_create_caption_manager(uint32_t *manager)
{
  uint32_t *caption_manager = (uint32_t *)(uintptr_t)manager[22];
  if (!caption_manager) {
    uint32_t *memory = allocate_registered_caption_manager(484);
    caption_manager = memory
        ? construct_caption_manager(memory)
        : NULL;
    manager[22] = (uint32_t)(uintptr_t)caption_manager;
  }
  return caption_manager;
}

char __thiscall has_caption_manager(uint32_t *manager)
{
  return manager[22] != 0;
}
