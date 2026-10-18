#include <stddef.h>
#include <stdint.h>

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/game_frame.c */
extern int frame_number;

/* gk3/GK3R_rest.c */
extern uint32_t sprite_vtable[];
extern uint32_t named_sprite_base_vtable[];
extern uint16_t *__thiscall construct_named_sprite_base(
    uint16_t *sprite, const char *name);
extern int __thiscall release_all_sprite_locks(uint32_t *sprite);
extern int __thiscall mark_sprite_loaded(uint16_t *sprite);
extern int __thiscall initialize_sprite_state(uint32_t *sprite);
extern int __thiscall destroy_sprite_surface(uint32_t *sprite);
extern char *__thiscall construct_graphics_surface(char *surface, char flags);
extern int __thiscall initialize_surface_from_source(
    uint32_t *surface, int source_surface);
extern uint32_t __thiscall sample_surface_pixel(uint32_t *surface, int x, int y);
extern int __thiscall get_engine_object_by_id(uint32_t *engine,
                                              uint16_t resource_id);

typedef void (__thiscall *SpriteMethod)(int sprite);

uint16_t *__thiscall construct_named_sprite(uint16_t *sprite,
                                            const char *name)
{
  construct_named_sprite_base(sprite, name);
  *(uint32_t *)(void *)sprite = (uint32_t)(uintptr_t)sprite_vtable;
  initialize_sprite_state((uint32_t *)(void *)sprite);
  return sprite;
}

int __thiscall destroy_sprite_members(int sprite)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)sprite;
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)sprite_vtable;
  release_all_sprite_locks((uint32_t *)(void *)bytes);
  int result = destroy_sprite_surface((uint32_t *)(void *)bytes);
  *(uint32_t *)(void *)bytes = (uint32_t)(uintptr_t)named_sprite_base_vtable;
  *(uint16_t *)(void *)(bytes + 4) = 0;
  return result;
}

int __thiscall set_sprite_surface(int sprite, int source_surface)
{
  uint8_t *bytes = (uint8_t *)(uintptr_t)sprite;
  uint32_t *methods = *(uint32_t **)(void *)bytes;
  ((SpriteMethod)(uintptr_t)methods[20 / sizeof(uint32_t)])(sprite);
  methods = *(uint32_t **)(void *)bytes;
  ((SpriteMethod)(uintptr_t)methods[8 / sizeof(uint32_t)])(sprite);
  mark_sprite_loaded((uint16_t *)(void *)bytes);
  methods = *(uint32_t **)(void *)bytes;
  ((SpriteMethod)(uintptr_t)methods[12 / sizeof(uint32_t)])(sprite);

  char *surface_memory = (char *)allocate_tracked_memory(80);
  char *surface = surface_memory != NULL
      ? construct_graphics_surface(surface_memory, 0)
      : NULL;
  *(uint32_t *)(void *)(bytes + 48) = (uint32_t)(uintptr_t)surface;
  int result = initialize_surface_from_source(
      (uint32_t *)(void *)surface, source_surface);
  uint32_t flags = *(uint32_t *)(void *)(bytes + 52);
  *(uint32_t *)(void *)(bytes + 52) = (flags & 0xfffffff9u) | 2u;
  return result;
}

uint32_t __thiscall get_sprite_pixel(uint16_t *sprite, int x, int y)
{
  uint8_t *bytes = (uint8_t *)(void *)sprite;
  if (sprite[3] == 0) {
    uint32_t *methods = *(uint32_t **)(void *)bytes;
    SpriteMethod initialize = (SpriteMethod)(uintptr_t)
        methods[4 / sizeof(uint32_t)];
    initialize((int)(uintptr_t)sprite);
  }

  *(int32_t *)(void *)(bytes + 44) = frame_number;
  uint32_t *surface = *(uint32_t **)(void *)(bytes + 48);
  return sample_surface_pixel(surface, x, y);
}

uint32_t __thiscall get_engine_sprite_pixel(uint32_t *engine,
                                            uint16_t resource_id,
                                            int x, int y)
{
  uint16_t *sprite = (uint16_t *)(uintptr_t)
      get_engine_object_by_id(engine, resource_id);
  return get_sprite_pixel(sprite, x, y);
}
