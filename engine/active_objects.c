#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t reserved_00;
  uint8_t state_flags;
  uint8_t reserved_02[6];
  uint32_t active_flags;
  uint8_t reserved_0C[44];
  uint32_t children;
  int32_t child_count;
  uint8_t reserved_40[24];
  uint8_t child_mode;
} ActiveObjectNode;

typedef struct {
  uint8_t reserved_00[6];
  uint16_t initialized;
  uint8_t reserved_08[40];
  uint8_t flags;
  uint8_t reserved_31[103];
  uint32_t children;
  int32_t child_count;
} ActiveObject;

_Static_assert(offsetof(ActiveObjectNode, state_flags) == 1,
               "active node state flags offset");
_Static_assert(offsetof(ActiveObjectNode, active_flags) == 8,
               "active node flags offset");
_Static_assert(offsetof(ActiveObjectNode, children) == 56,
               "active node children offset");
_Static_assert(offsetof(ActiveObjectNode, child_count) == 60,
               "active node child count offset");
_Static_assert(offsetof(ActiveObjectNode, child_mode) == 88,
               "active node mode offset");
_Static_assert(offsetof(ActiveObject, initialized) == 6,
               "active object initialized offset");
_Static_assert(offsetof(ActiveObject, flags) == 48,
               "active object flags offset");
_Static_assert(offsetof(ActiveObject, children) == 152,
               "active object children offset");
_Static_assert(offsetof(ActiveObject, child_count) == 156,
               "active object child count offset");

int __thiscall has_active_child(int object_address, int child_index)
{
  ActiveObjectNode *object = (ActiveObjectNode *)(uintptr_t)object_address;

  if (child_index != -1) {
    uint32_t *children = (uint32_t *)(uintptr_t)object->children;
    ActiveObjectNode *child = (ActiveObjectNode *)(uintptr_t)children[child_index];
    return child->active_flags & 8u;
  }

  if (!(object->state_flags & 0x20))
    return 0;

  if (object->child_count <= 0)
    return 0;

  uint32_t *children = (uint32_t *)(uintptr_t)object->children;
  for (int index = 0; index < object->child_count; ++index) {
    ActiveObjectNode *child = (ActiveObjectNode *)(uintptr_t)children[index];
    if (child->active_flags & 8u)
      return 1;
  }
  return 0;
}

int __thiscall is_active_object(int object_address)
{
  ActiveObject *object = (ActiveObject *)(uintptr_t)object_address;
  if (!(object->flags & 1))
    return 0;

  if (object->child_count <= 0)
    return 0;

  uint32_t *children = (uint32_t *)(uintptr_t)object->children;
  for (int index = 0; index < object->child_count; ++index) {
    if (has_active_child((int)children[index], -1))
      return 1;
  }
  return 0;
}

static char __thiscall refresh_active_child_flags(ActiveObjectNode *object)
{
  if (!has_active_child((int)(uintptr_t)object, -1))
    return 0;

  const uint8_t retained_flags = object->child_mode ? 0x30 : 0x20;
  object->state_flags &= retained_flags;
  return (char)retained_flags;
}

void __thiscall refresh_active_object_children(int object_address)
{
  ActiveObject *object = (ActiveObject *)(uintptr_t)object_address;
  if (!object->initialized
      || !is_active_object(object_address))
    return;

  uint32_t *children = (uint32_t *)(uintptr_t)object->children;
  for (int index = 0; index < object->child_count; ++index)
    refresh_active_child_flags((ActiveObjectNode *)(uintptr_t)children[index]);
}
