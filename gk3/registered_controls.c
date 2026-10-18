#include <stdint.h>

/* engine/registry.c */
extern uint32_t *__thiscall find_or_create_registry_entry(
    uint32_t *registry, uint32_t address);

/* gk3/GK3R_rest.c */
extern int registered_control_base_offset_adjustment
    __asm__("dword_76496C");
extern uint32_t registered_control_type_descriptor[15]
    __asm__("dword_764970");
extern int sprite_control_base_offset_adjustment __asm__("dword_7648EC");
extern uint32_t sprite_control_type_descriptor[15] __asm__("dword_7648F0");
extern uint32_t registered_control_vtable[] __asm__("off_6AAEE4");
extern uint32_t sprite_control_vtable[] __asm__("off_6AC590");
extern uint32_t *__thiscall construct_registered_game_object_base(
    uint32_t *object, int mode) __asm__("sub_42BFC0");

uint32_t *__thiscall construct_registered_control(uint32_t *object, int mode)
{
  construct_registered_game_object_base(object, mode);
  find_or_create_registry_entry(
      registered_control_type_descriptor,
      (uint32_t)(uintptr_t)object
          + (uint32_t)registered_control_base_offset_adjustment + 13u);
  object[0] = (uint32_t)(uintptr_t)registered_control_vtable;
  return object;
}

int __thiscall construct_registered_sprite_control(int object, int mode)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)object;

  construct_registered_control((uint32_t *)(void *)bytes, mode);
  find_or_create_registry_entry(
      sprite_control_type_descriptor,
      (uint32_t)object + (uint32_t)sprite_control_base_offset_adjustment + 44u);
  *(uint32_t *)(void *)(bytes + 44) = 0;
  *(uint32_t *)(void *)(bytes + 48) = 0;
  *(float *)(void *)(bytes + 52) = 1.0f;
  *(float *)(void *)(bytes + 56) = 1.0f;
  *(uint32_t *)(void *)(bytes + 60) = 0;
  *(uint32_t *)(void *)(bytes + 64) = 0;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)sprite_control_vtable;
  return object;
}
