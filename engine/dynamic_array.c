#include <stdint.h>
#include <string.h>

#include "../common/runtime_lockit.h"

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

typedef struct {
  uint32_t reserved;
  uint32_t begin;
  uint32_t end;
  uint32_t capacity;
} PointerVector;

_Static_assert(sizeof(PointerVector) == 16, "vector header layout");

enum { INITIAL_VECTOR_STORAGE_BYTES = 512 };

PointerVector *__thiscall initialize_16_byte_vector(PointerVector *vector)
{
  vector->reserved = 0;
  uint32_t *storage = allocate_tracked_memory(INITIAL_VECTOR_STORAGE_BYTES);
  if (!storage) {
    vector->begin = 0;
    vector->end = 0;
    vector->capacity = 0;
    return vector;
  }
  const uint32_t begin = (uint32_t)(uintptr_t)storage;
  vector->begin = begin;
  vector->end = begin;
  vector->capacity = begin + INITIAL_VECTOR_STORAGE_BYTES;
  return vector;
}

static uint32_t vector_length(const PointerVector *vector)
{
  return vector->begin && vector->end >= vector->begin
      ? (vector->end - vector->begin) / sizeof(uint32_t) : 0;
}

int __thiscall free_vector_storage(int *collection)
{
  PointerVector *vector = (PointerVector *)(void *)collection;
  free_tracked_memory((int)vector->begin);
  vector->begin = 0;
  vector->end = 0;
  vector->capacity = 0;
  return 0;
}

int __thiscall destroy_object_vector(int *collection)
{
  PointerVector *vector = (PointerVector *)(void *)collection;
  uint32_t *objects = (uint32_t *)(uintptr_t)vector->begin;
  const uint32_t count = vector_length(vector);

  for (uint32_t index = 0; index < count; ++index) {
    const uint32_t object_address = objects[index];
    if (object_address) {
      uint32_t *methods = *(uint32_t **)(uintptr_t)object_address;
      void (__thiscall *destroy)(uint32_t *object, int free_memory) =
          (void (__thiscall *)(uint32_t *, int))(uintptr_t)methods[1];
      destroy((uint32_t *)(uintptr_t)object_address, 1);
    }
  }

  return free_vector_storage(collection);
}

int __thiscall set_vector_element(uint32_t *collection, int index, int value)
{
  PointerVector *vector = (PointerVector *)(void *)collection;
  if (index < 0)
    return 0;

  uint32_t count = vector_length(vector);
  uint32_t capacity = vector->begin && vector->capacity >= vector->begin
      ? (vector->capacity - vector->begin) / sizeof(uint32_t) : 0;
  if ((uint32_t)index >= capacity) {
    uint32_t new_capacity = capacity ? capacity : 4;
    while (new_capacity <= (uint32_t)index)
      new_capacity *= 2;

    uint32_t *new_items = allocate_tracked_memory(
        (int)(new_capacity * sizeof(*new_items)));
    if (!new_items)
      return 0;
    if (count)
      memcpy(new_items, (const void *)(uintptr_t)vector->begin,
             count * sizeof(*new_items));
    free_tracked_memory((int)vector->begin);
    vector->begin = (uint32_t)(uintptr_t)new_items;
    vector->end = vector->begin + count * sizeof(*new_items);
    vector->capacity = vector->begin + new_capacity * sizeof(*new_items);
  }

  uint32_t *items = (uint32_t *)(uintptr_t)vector->begin;
  while (count <= (uint32_t)index)
    items[count++] = 0;
  items[index] = (uint32_t)value;
  vector->end = vector->begin + count * sizeof(*items);
  return (int)(uintptr_t)&items[index];
}

/* Preserve the original entry points used by unextracted code. */
int __thiscall destroy_pointer_vector_elements(int *collection)
{
  return destroy_object_vector(collection);
}

int __thiscall free_pointer_vector_storage(int *collection)
{
  return free_vector_storage(collection);
}

int __thiscall set_pointer_vector_element(uint32_t *collection, int index, int value)
{
  return set_vector_element(collection, index, value);
}

PointerVector *__thiscall initialize_pointer_vector(void *vector)
{
  return initialize_16_byte_vector((PointerVector *)vector);
}

int __thiscall free_dynamic_array_storage(int *array)
{
  return free_vector_storage(array);
}

void __stdcall destroy_trivial_array_elements(uint32_t begin, uint32_t end)
{
  (void)begin;
  (void)end;
}

int __thiscall vector_element_address(uint32_t *collection, int index)
{
  uint32_t lock_storage = 0;
  int address;

  construct_runtime_lockit(&lock_storage);
  address = (int)(collection[1] + sizeof(uint32_t) * (uint32_t)index);
  destroy_runtime_lockit(&lock_storage);
  return address;
}

int __thiscall vector_element_value(uint32_t *collection, int index)
{
  uint32_t lock_storage = 0;
  uint32_t address;
  int value;

  construct_runtime_lockit(&lock_storage);
  address = collection[1] + sizeof(uint32_t) * (uint32_t)index;
  value = *(int *)(uintptr_t)address;
  destroy_runtime_lockit(&lock_storage);
  return value;
}

int __thiscall insert_repeated_array_value(
    int *array, uint32_t *position, int count, uint32_t *value)
{
  PointerVector *vector = (PointerVector *)(void *)array;
  uint32_t *items = (uint32_t *)(uintptr_t)vector->begin;
  const size_t old_count = vector->begin && vector->end >= vector->begin
      ? (vector->end - vector->begin) / sizeof(uint32_t) : 0;
  const size_t old_capacity = vector->begin && vector->capacity >= vector->begin
      ? (vector->capacity - vector->begin) / sizeof(uint32_t) : 0;
  const size_t position_index = vector->begin
      ? ((uintptr_t)position - vector->begin) / sizeof(uint32_t) : 0;
  const size_t tail_count = old_count - position_index;

  if (count < 0 || position_index > old_count)
    return 0;
  if (count == 0)
    return (int)tail_count;

  const size_t inserted_count = (size_t)count;
  const uint32_t inserted_value = *value;
  const size_t free_count = old_capacity >= old_count
      ? old_capacity - old_count : 0;
  if (free_count >= inserted_count) {
    uint32_t *insertion_point = items + position_index;
    memmove(insertion_point + inserted_count, insertion_point,
            tail_count * sizeof(*items));
    for (size_t index = 0; index < inserted_count; ++index)
      insertion_point[index] = inserted_value;
    vector->end += (uint32_t)(inserted_count * sizeof(*items));

    /* The original routine returns different pointers in its two in-place paths. */
    return tail_count >= inserted_count
        ? (int)(uintptr_t)(insertion_point + inserted_count)
        : (int)(uintptr_t)(items + old_count);
  }

  const size_t growth = inserted_count > old_count ? inserted_count : old_count;
  const size_t new_capacity = old_count + growth;
  uint32_t *new_items = allocate_tracked_memory(
      (int)(new_capacity * sizeof(*new_items)));
  if (!new_items)
    return 0;

  if (position_index)
    memcpy(new_items, items, position_index * sizeof(*new_items));
  for (size_t index = 0; index < inserted_count; ++index)
    new_items[position_index + index] = inserted_value;
  if (tail_count)
    memcpy(new_items + position_index + inserted_count, items + position_index,
           tail_count * sizeof(*new_items));

  free_tracked_memory((int)vector->begin);
  vector->begin = (uint32_t)(uintptr_t)new_items;
  vector->end = vector->begin + (uint32_t)(old_count + inserted_count) * sizeof(*new_items);
  vector->capacity = vector->begin + (uint32_t)new_capacity * sizeof(*new_items);
  return (int)(uintptr_t)(new_items + old_count + inserted_count);
}

int __thiscall append_dynamic_array_pair(int *array, const uint32_t *entry)
{
  PointerVector *vector = (PointerVector *)(void *)array;
  const uint32_t begin = vector->begin;
  const uint32_t end = vector->end;
  const uint32_t capacity = vector->capacity;
  const size_t count = begin && end >= begin
      ? (end - begin) / (2 * sizeof(uint32_t)) : 0;

  if (begin && end >= begin && capacity >= end &&
      capacity - end >= 2 * sizeof(uint32_t)) {
    memcpy((void *)(uintptr_t)end, entry, 2 * sizeof(uint32_t));
    vector->end += 2 * sizeof(uint32_t);
    return (int)(uintptr_t)vector->end;
  }

  const size_t new_capacity = count + (count ? count : 1);
  uint32_t *new_entries = allocate_tracked_memory(
      (int)(new_capacity * 2 * sizeof(*new_entries)));
  if (!new_entries)
    return 0;

  if (count)
    memcpy(new_entries, (const void *)(uintptr_t)begin,
           count * 2 * sizeof(*new_entries));
  memcpy(new_entries + count * 2, entry, 2 * sizeof(*new_entries));
  free_tracked_memory((int)begin);

  vector->begin = (uint32_t)(uintptr_t)new_entries;
  vector->end = vector->begin + (uint32_t)((count + 1) * 2 * sizeof(*new_entries));
  vector->capacity = vector->begin + (uint32_t)(new_capacity * 2 * sizeof(*new_entries));
  return (int)(uintptr_t)vector->end;
}
