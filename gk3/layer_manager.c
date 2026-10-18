#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern uint32_t unk_7666D0[];
extern int layer_manager_base_offset_adjustment;
extern int game_engine_instance_address;
extern uint32_t layer_manager_vtable[];
extern int get_or_create_rc_bar_popper(void);
extern uint32_t *__thiscall remove_interface_layer(uint32_t *manager,
                                                   int layer_address);
extern int __cdecl destroy_interface_owned_layer(uint32_t *member);
extern uint32_t *__cdecl allocate_registered_caption_manager(int size);
extern int __thiscall construct_caption_manager(int object);
extern uint32_t *__cdecl sub_449990(int size);
extern uint32_t *__thiscall sub_449A45(uint32_t *object);
extern uint32_t *__cdecl sub_463749(int size);
extern uint32_t *__thiscall sub_463808(uint32_t *object);
extern uint32_t *__cdecl sub_4EE51C(int size);
extern uint32_t *__thiscall sub_51D106(uint32_t *object);
extern uint32_t *__cdecl sub_4EE5CB(int size);
extern uint32_t *__thiscall sub_4FCE7C(uint32_t *object);
extern uint32_t *__cdecl sub_496005(int size);
extern uint32_t *__thiscall sub_495548(uint32_t *object);
extern uint32_t *__cdecl sub_4AA10A(int size);
extern uint32_t *__thiscall sub_4AA587(uint32_t *object);
extern uint32_t *__cdecl sub_4EE4F9(int size);
extern uint32_t *__thiscall sub_51B7A0(uint32_t *object);
extern uint32_t *__cdecl sub_4BB527(int size);
extern uint32_t *__thiscall sub_4BB5DC(uint32_t *object);
extern uint32_t *__cdecl sub_4E9FA3(int size);
extern uint32_t *__thiscall sub_4EA06C(uint32_t *object);
extern uint32_t *__cdecl sub_4EE53F(int size);
extern uint32_t *__thiscall sub_4F3D6D(uint32_t *object);
extern uint32_t *__cdecl sub_4EE585(int size);
extern uint32_t *__thiscall sub_4F7F4D(uint32_t *object);
extern uint32_t *__cdecl sub_4EE5EE(int size);
extern uint32_t *__thiscall sub_4FD325(uint32_t *object);
extern uint32_t *__cdecl sub_4EE67A(int size);
extern uint32_t *__thiscall sub_501A94(uint32_t *object);
extern uint32_t *__cdecl sub_4EE5A8(int size);
extern uint32_t *__thiscall sub_4FCBA4(uint32_t *object);
extern uint32_t *__cdecl sub_4EE562(int size);
extern uint32_t *__thiscall sub_4F402B(uint32_t *object);
extern uint32_t *__cdecl sub_4EE69D(int size);
extern uint32_t *__thiscall sub_687F8D(uint32_t *object);
extern uint32_t *__cdecl sub_4EE611(int size);
extern uint32_t *__thiscall sub_4FE08D(uint32_t *object);
extern uint32_t *__cdecl sub_4EE6C0(int size);
extern uint32_t *__thiscall sub_5581BD(uint32_t *object);
extern uint32_t *__cdecl sub_4EE634(int size);
extern uint32_t *__thiscall sub_4FF3B3(uint32_t *object);
extern uint32_t *__cdecl sub_4EE657(int size);
extern uint32_t *__thiscall sub_4FFAFA(uint32_t *object);
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
      unk_7666D0,
      (uint32_t)(uintptr_t)object
          + (uint32_t)layer_manager_base_offset_adjustment + 4);
  object[0] = (uint32_t)(uintptr_t)layer_manager_vtable;
  return object;
}

uint32_t *__thiscall construct_layer_manager(uint32_t *object)
{
  find_or_create_registry_entry(unk_7666D0,
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
  find_or_create_registry_entry(unk_7666D0,
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
      memory = sub_449990(460);
      layer = memory ? sub_449A45(memory) : NULL;
      break;
    case 1:
      memory = sub_463749(564);
      layer = memory ? sub_463808(memory) : NULL;
      break;
    case 2:
      memory = sub_4EE51C(616);
      layer = memory ? sub_51D106(memory) : NULL;
      break;
    case 3:
      memory = sub_4EE5CB(804);
      layer = memory ? sub_4FCE7C(memory) : NULL;
      break;
    case 4:
      memory = sub_496005(796);
      layer = memory ? sub_495548(memory) : NULL;
      break;
    case 5:
      memory = sub_4AA10A(1752);
      layer = memory ? sub_4AA587(memory) : NULL;
      break;
    case 6:
      memory = sub_4EE4F9(1008);
      layer = memory ? sub_51B7A0(memory) : NULL;
      break;
    case 7:
    case 15: {
      memory = sub_4BB527(328);
      layer = memory ? sub_4BB5DC(memory) : NULL;
      *slot = (uint32_t)(uintptr_t)layer;
      const char *name = layer_id == 15 ? "SceneLayer" : "InsetLayer";
      assign_layer_name_string(name, strlen(name));
      get_game_layer_slot(manager, 15, 1);
      return (char *)(void *)slot;
    }
    case 8:
      memory = sub_4E9FA3(648);
      layer = memory ? sub_4EA06C(memory) : NULL;
      break;
    case 9:
      memory = sub_4EE53F(852);
      layer = memory ? sub_4F3D6D(memory) : NULL;
      break;
    case 10:
      memory = sub_4EE585(672);
      layer = memory ? sub_4F7F4D(memory) : NULL;
      break;
    case 11:
      memory = sub_4EE5EE(428);
      layer = memory ? sub_4FD325(memory) : NULL;
      break;
    case 12:
      memory = sub_4EE67A(380);
      layer = memory ? sub_501A94(memory) : NULL;
      break;
    case 13:
      memory = sub_4EE5A8(328);
      layer = memory ? sub_4FCBA4(memory) : NULL;
      break;
    case 14:
      memory = sub_4EE562(1012);
      layer = memory ? sub_4F402B(memory) : NULL;
      break;
    case 16:
      memory = sub_4EE69D(1848);
      layer = memory ? sub_687F8D(memory) : NULL;
      break;
    case 17:
      memory = sub_4EE611(996);
      layer = memory ? sub_4FE08D(memory) : NULL;
      break;
    case 18:
      memory = sub_4EE6C0(388);
      layer = memory ? sub_5581BD(memory) : NULL;
      break;
    case 19:
      memory = sub_4EE634(800);
      layer = memory ? sub_4FF3B3(memory) : NULL;
      break;
    case 20:
      memory = sub_4EE657(324);
      layer = memory ? sub_4FFAFA(memory) : NULL;
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
        ? (uint32_t *)(uintptr_t)construct_caption_manager(
              (int)(uintptr_t)memory)
        : NULL;
    manager[22] = (uint32_t)(uintptr_t)caption_manager;
  }
  return caption_manager;
}

char __thiscall has_caption_manager(uint32_t *manager)
{
  return manager[22] != 0;
}
