#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../common/runtime_lockit.h"

typedef struct {
  uint32_t registry;
  uint32_t registration_index;
  uint32_t category;
} ObjectRegistration;

typedef struct {
  uint32_t left;
  uint32_t parent;
  uint32_t right;
  uint32_t key;
  ObjectRegistration value;
  uint32_t color;
} AddressMapNode;

typedef struct {
  uint32_t proxy;
  uint32_t header;
  uint8_t allow_duplicate_keys;
  uint8_t reserved_mode[3];
  uint32_t node_count;
} AddressMap;

typedef struct {
  uint32_t reserved_before_registration_index[13];
  uint32_t next_registration_index;
  uint32_t instances_by_address;
  uint32_t reserved_after_instance_map;
} RuntimeTypeDescriptor;

typedef struct {
  uint32_t key;
  ObjectRegistration initial_value;
} RegistrationMapEntry;

_Static_assert(offsetof(AddressMapNode, key) == 12, "map node key offset");
_Static_assert(offsetof(AddressMapNode, value) == 16,
               "map node value offset");
_Static_assert(offsetof(AddressMapNode, color) == 28, "map node color offset");
_Static_assert(sizeof(AddressMapNode) == 32, "map node size");
_Static_assert(offsetof(AddressMap, header) == 4, "map header offset");
_Static_assert(offsetof(AddressMap, allow_duplicate_keys) == 8,
               "map duplicate-key mode offset");
_Static_assert(offsetof(AddressMap, node_count) == 12, "map node count offset");
_Static_assert(offsetof(RuntimeTypeDescriptor, next_registration_index)
                   == 52,
               "registry registration counter offset");
_Static_assert(offsetof(RuntimeTypeDescriptor, instances_by_address) == 56,
               "registry address map offset");

/* engine/registry.c */
extern uint32_t *__thiscall erase_ordered_map_node(uint32_t *tree,
                                                   uint32_t *result,
                                                   uint32_t *node);
extern uint32_t *__thiscall insert_ordered_map_node(
    uint32_t *tree, uint32_t *result, int child, uint32_t *parent,
    uint32_t *key_value);
extern uint32_t *__thiscall erase_ordered_map_range(
    uint32_t *tree, uint32_t *result, uint32_t *first, uint32_t *last);
extern void __stdcall destroy_ordered_map_subtree(uint32_t root_address);
extern uint32_t *__cdecl copy_ordered_map_entry_data(uint32_t *destination,
                                                     uint32_t *source);

/* gk3/GK3R_rest.c */
extern uint32_t registry_tree_nil_node_address;
#define REGISTRY_NIL_NODE_ADDRESS registry_tree_nil_node_address
#define REGISTRY_NODE_POOL_ADDRESS ordered_map_node_pool_address
extern int ordered_map_node_pool_address;
extern int __thiscall allocate_pool_block(void *pool, int size);
extern void __thiscall free_pool_block(uint32_t *pool, uint32_t address);
extern int __thiscall destroy_block_arena(int arena_address);
extern uint8_t *__thiscall construct_block_arena(uint8_t *storage,
                                                int block_size,
                                                int block_count);
extern int (__stdcall *ordered_map_node_pool_deleting_vtable)(char);
extern uint8_t shared_arena_allocator_storage[64];
extern int address_map_instance_count;
extern int ordered_map_allocator_reference_count;
extern int ordered_map_arena_address;

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* Acquires a reference to the shared ordered-map node pool, creating it once. */
uint32_t *__cdecl retain_ordered_map_node_pool(void)
{
  uint32_t *result = (uint32_t *)(uintptr_t)
      (ordered_map_allocator_reference_count + 1);

  if (ordered_map_allocator_reference_count++ == 0) {
    uint8_t *arena_storage = allocate_tracked_memory(60);
    uint8_t *arena = arena_storage
        ? construct_block_arena(arena_storage, 2048, 32)
        : NULL;
    ordered_map_arena_address = (int)(uintptr_t)arena;

    uint32_t *node_pool = allocate_tracked_memory(48);
    if (node_pool) {
      uint32_t *backing_arena = arena
          ? (uint32_t *)(void *)arena
          : (uint32_t *)(void *)shared_arena_allocator_storage;
      node_pool[1] = 4;
      node_pool[2] = (uint32_t)(uintptr_t)backing_arena;
      node_pool[3] = backing_arena[1];
      node_pool[4] = backing_arena[1] - 28;
      node_pool[0] =
          (uint32_t)(uintptr_t)&ordered_map_node_pool_deleting_vtable;
      memset(node_pool + 5, 0, 28);
      ordered_map_node_pool_address = (int)(uintptr_t)node_pool;
      result = NULL;
    } else {
      ordered_map_node_pool_address = 0;
    }
  }

  return result;
}

uint32_t *__thiscall find_first_map_node_not_less_than(uint32_t *tree,
                                                       uint32_t *key)
{
  AddressMap *map = (AddressMap *)(void *)tree;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  AddressMapNode *candidate = header;
  AddressMapNode *node = (AddressMapNode *)(uintptr_t)header->parent;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  while ((uint32_t *)node !=
         (uint32_t *)(uintptr_t)REGISTRY_NIL_NODE_ADDRESS) {
    if (node->key >= *key) {
      candidate = node;
      node = (AddressMapNode *)(uintptr_t)node->left;
    } else {
      node = (AddressMapNode *)(uintptr_t)node->right;
    }
  }
  destroy_runtime_lockit(&lock_storage);
  return (uint32_t *)(void *)candidate;
}

void __thiscall advance_ordered_map_node(int *node_address)
{
  uint32_t current_address = (uint32_t)*node_address;
  AddressMapNode *node = (AddressMapNode *)(uintptr_t)current_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  if (node->right == REGISTRY_NIL_NODE_ADDRESS) {
    AddressMapNode *parent;
    uint32_t parent_address;

    for (;;) {
      parent_address = node->parent;
      parent = (AddressMapNode *)(uintptr_t)parent_address;
      if (current_address != parent->right)
        break;
      current_address = parent_address;
      node = parent;
    }
    parent_address = node->parent;
    parent = (AddressMapNode *)(uintptr_t)parent_address;
    if (node->right != parent_address)
      current_address = parent_address;
    *node_address = (int)current_address;
  } else {
    uint32_t inner_lock_storage = 0;

    construct_runtime_lockit(&inner_lock_storage);
    node = (AddressMapNode *)(uintptr_t)node->right;
    while (node->left != REGISTRY_NIL_NODE_ADDRESS)
      node = (AddressMapNode *)(uintptr_t)node->left;
    *node_address = (int)(uintptr_t)node;
    destroy_runtime_lockit(&inner_lock_storage);
  }
  destroy_runtime_lockit(&lock_storage);
}

void __thiscall move_to_previous_ordered_map_node(int **node_address)
{
  AddressMapNode *node = (AddressMapNode *)(uintptr_t)(uint32_t)*node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  AddressMapNode *parent = (AddressMapNode *)(uintptr_t)node->parent;
  if (node->color != 0 || parent->parent != (uint32_t)(uintptr_t)node) {
    if (node->left == REGISTRY_NIL_NODE_ADDRESS) {
      while ((uint32_t *)node ==
             (uint32_t *)(uintptr_t)parent->left) {
        node = parent;
        parent = (AddressMapNode *)(uintptr_t)node->parent;
      }
      node = parent;
    } else {
      node = (AddressMapNode *)(uintptr_t)node->left;
      uint32_t inner_lock_storage = 0;
      construct_runtime_lockit(&inner_lock_storage);
      while (node->right != REGISTRY_NIL_NODE_ADDRESS)
        node = (AddressMapNode *)(uintptr_t)node->right;
      destroy_runtime_lockit(&inner_lock_storage);
    }
  } else {
    node = (AddressMapNode *)(uintptr_t)node->right;
  }
  *node_address = (int *)(void *)node;
  destroy_runtime_lockit(&lock_storage);
}

uint32_t *__cdecl copy_ordered_map_entry_data(uint32_t *destination,
                                             uint32_t *source)
{
  if (destination) {
    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];
    destination[3] = source[3];
  }
  return destination;
}

int **__thiscall find_or_insert_map_node_impl(
    int map_address, int **result, uint32_t *key)
{
  AddressMap *map = (AddressMap *)(uintptr_t)(uint32_t)map_address;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  AddressMapNode *node = (AddressMapNode *)(uintptr_t)header->parent;
  AddressMapNode *parent = header;
  int insert_left = 1;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  while ((uint32_t *)node !=
         (uint32_t *)(uintptr_t)REGISTRY_NIL_NODE_ADDRESS) {
    parent = node;
    insert_left = *key < node->key;
    node = (AddressMapNode *)(uintptr_t)
        (insert_left ? node->left : node->right);
  }
  destroy_runtime_lockit(&lock_storage);

  if (map->allow_duplicate_keys)
    goto insert_node;

  AddressMapNode *candidate = parent;
  if (insert_left) {
    if (parent == (AddressMapNode *)(uintptr_t)header->left) {
      uint32_t *inserted = (uint32_t *)(uintptr_t)*insert_ordered_map_node(
          (uint32_t *)(void *)map, (uint32_t *)&key,
          (int)(uintptr_t)node, (uint32_t *)(void *)parent, key);
      result[0] = (int *)inserted;
      result[1] = (int *)(uintptr_t)1;
      return result;
    }
    move_to_previous_ordered_map_node((int **)&candidate);
  }

  if (candidate->key < *key) {
insert_node:
    {
      uint32_t *inserted = (uint32_t *)(uintptr_t)*insert_ordered_map_node(
          (uint32_t *)(void *)map, (uint32_t *)&key,
          (int)(uintptr_t)node, (uint32_t *)(void *)parent, key);
      result[0] = (int *)inserted;
      result[1] = (int *)(uintptr_t)1;
      return result;
    }
  }

  result[0] = (int *)(void *)candidate;
  result[1] = 0;
  return result;
}

int __thiscall find_map_value_impl(uint32_t *registry, uint32_t address)
{
  RuntimeTypeDescriptor *type_descriptor =
      (RuntimeTypeDescriptor *)(void *)registry;
  AddressMap *map =
      (AddressMap *)(uintptr_t)type_descriptor->instances_by_address;
  AddressMapNode *candidate = (AddressMapNode *)
      find_first_map_node_not_less_than((uint32_t *)(void *)map, &address);
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;

  if (candidate == header || address < candidate->key)
    return 0;
  return (int)(uintptr_t)&candidate->value;
}

uint32_t *__thiscall erase_map_entry_impl(uint32_t *registry,
                                          uint32_t address)
{
  RuntimeTypeDescriptor *type_descriptor =
      (RuntimeTypeDescriptor *)(void *)registry;
  AddressMap *map =
      (AddressMap *)(uintptr_t)type_descriptor->instances_by_address;
  AddressMapNode *candidate = (AddressMapNode *)
      find_first_map_node_not_less_than((uint32_t *)(void *)map, &address);
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  if (candidate == header || address < candidate->key)
    return (uint32_t *)(void *)header;

  uint32_t *node = (uint32_t *)(void *)candidate;
  return erase_ordered_map_node((uint32_t *)(void *)map,
                                (uint32_t *)(void *)&node, node);
}

int **__thiscall find_or_insert_map_node(int map, int **result,
                                         uint32_t *key)
{
  return find_or_insert_map_node_impl(map, result, key);
}

int __thiscall find_map_value(uint32_t *registry, uint32_t address)
{
  return find_map_value_impl(registry, address);
}

uint32_t *__thiscall erase_map_entry(uint32_t *registry, uint32_t address)
{
  return erase_map_entry_impl(registry, address);
}

/* Creates or finds an object's registration entry in its owning registry. */
uint32_t *__thiscall find_or_create_registry_entry(uint32_t *registry_storage,
                                                    uint32_t address)
{
  RuntimeTypeDescriptor *type_descriptor =
      (RuntimeTypeDescriptor *)(void *)registry_storage;
  RegistrationMapEntry initial_entry = { .key = address };
  int *result[2];
  int **position = find_or_insert_map_node(
      (int)type_descriptor->instances_by_address, result,
      (uint32_t *)(void *)&initial_entry);
  ObjectRegistration *entry = (ObjectRegistration *)
      (void *)((uint32_t *)position[0] + 4);

  if (!entry->registry) {
    entry->registry = (uint32_t)(uintptr_t)registry_storage;
    entry->registration_index = type_descriptor->next_registration_index++;
  }
  return (uint32_t *)(void *)entry;
}

/* gk3/GK3R_rest.c */
extern uint32_t registered_event_registry[18];
extern uint32_t g_notify_target_list_registry[16];

int initialize_event_registry(void)
{
  find_or_create_registry_entry(
      g_notify_target_list_registry,
      (uint32_t)(uintptr_t)registered_event_registry);
  ObjectRegistration *entry = (ObjectRegistration *)(uintptr_t)find_map_value(
      g_notify_target_list_registry,
      (uint32_t)(uintptr_t)registered_event_registry);
  entry->category = 3;
  return (int)(uintptr_t)entry;
}

uint32_t *unregister_event_registry(void)
{
  return erase_map_entry(g_notify_target_list_registry,
                         (uint32_t)(uintptr_t)registered_event_registry);
}

/* Finds the registered object address whose assigned index matches index. */
int __thiscall find_registered_address_by_index(uint32_t *registry_storage,
                                               int index)
{
  RuntimeTypeDescriptor *type_descriptor =
      (RuntimeTypeDescriptor *)(void *)registry_storage;
  AddressMap *map =
      (AddressMap *)(uintptr_t)type_descriptor->instances_by_address;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  AddressMapNode *node = (AddressMapNode *)(uintptr_t)header->left;

  while (node != header) {
    if (node->value.registration_index == (uint32_t)index)
      return (int)node->key;

    uint32_t node_address = (uint32_t)(uintptr_t)node;
    advance_ordered_map_node((int *)&node_address);
    node = (AddressMapNode *)(uintptr_t)node_address;
  }
  return 0;
}

int __stdcall allocate_ordered_map_header_node(int parent_address, int color)
{
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)(uint32_t)
      allocate_pool_block((void *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
                          (int)sizeof(*header));
  header->parent = (uint32_t)parent_address;
  header->color = (uint32_t)color;
  return (int)(uintptr_t)header;
}

void __stdcall destroy_ordered_map_subtree(uint32_t root_address)
{
  uint32_t lock_storage = 0;
  uint32_t node_address = root_address;

  construct_runtime_lockit(&lock_storage);
  while (node_address != REGISTRY_NIL_NODE_ADDRESS) {
    AddressMapNode *node = (AddressMapNode *)(uintptr_t)node_address;
    uint32_t left_address = node->left;
    destroy_ordered_map_subtree(node->right);
    free_pool_block((uint32_t *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
                    node_address);
    node_address = left_address;
  }
  destroy_runtime_lockit(&lock_storage);
}

uint32_t *__thiscall insert_ordered_map_node(
    uint32_t *tree, uint32_t *result_node_address, int child_node,
    uint32_t *parent_node_storage, uint32_t *entry_data)
{
  AddressMap *map = (AddressMap *)(void *)tree;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  AddressMapNode *parent = (AddressMapNode *)(void *)parent_node_storage;
  AddressMapNode *node;
  AddressMapNode *grandparent;
  AddressMapNode *uncle;
  AddressMapNode *pivot;
  AddressMapNode *rotation_parent;
  uint32_t node_address;
  uint32_t parent_address;
  uint32_t grandparent_address;
  uint32_t pivot_address;
  uint32_t rotation_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  node = (AddressMapNode *)(uintptr_t)(uint32_t)allocate_pool_block(
      (void *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
      (int)sizeof(*node));
  node_address = (uint32_t)(uintptr_t)node;
  parent_address = (uint32_t)(uintptr_t)parent;
  node->left = REGISTRY_NIL_NODE_ADDRESS;
  node->parent = parent_address;
  node->right = REGISTRY_NIL_NODE_ADDRESS;
  node->color = 0;
  copy_ordered_map_entry_data(&node->key, entry_data);
  ++map->node_count;

  if (parent == header
      || (uint32_t)child_node != REGISTRY_NIL_NODE_ADDRESS
      || node->key < parent->key) {
    parent->left = node_address;
    if (parent == header) {
      header->parent = node_address;
      header->left = node_address;
      header->right = node_address;
    } else if (parent_address == header->left) {
      header->left = node_address;
    }
  } else {
    parent->right = node_address;
    if (parent_address == header->right)
      header->right = node_address;
  }

  while (node_address != header->parent) {
    parent = (AddressMapNode *)(uintptr_t)node->parent;
    if (parent->color != 0)
      break;
    parent_address = (uint32_t)(uintptr_t)parent;
    grandparent = (AddressMapNode *)(uintptr_t)parent->parent;
    grandparent_address = (uint32_t)(uintptr_t)grandparent;

    if (parent_address == grandparent->left) {
      uncle = (AddressMapNode *)(uintptr_t)grandparent->right;
      if (uncle->color == 0) {
        parent->color = 1;
        uncle->color = 1;
        grandparent->color = 0;
        node = grandparent;
        node_address = grandparent_address;
      } else {
        if (node_address == parent->right) {
          node = parent;
          node_address = parent_address;
          pivot = (AddressMapNode *)(uintptr_t)node->right;
          pivot_address = (uint32_t)(uintptr_t)pivot;
          rotation_parent = (AddressMapNode *)(uintptr_t)node->parent;
          rotation_node_address = node_address;
          node->right = pivot->left;
          if (pivot->left != REGISTRY_NIL_NODE_ADDRESS)
            ((AddressMapNode *)(uintptr_t)pivot->left)->parent =
                rotation_node_address;
          pivot->parent = node->parent;
          if (rotation_parent == header)
            header->parent = pivot_address;
          else if (rotation_node_address == rotation_parent->left)
            rotation_parent->left = pivot_address;
          else
            rotation_parent->right = pivot_address;
          pivot->left = rotation_node_address;
          node->parent = pivot_address;
        }
        parent = (AddressMapNode *)(uintptr_t)node->parent;
        parent_address = (uint32_t)(uintptr_t)parent;
        grandparent = (AddressMapNode *)(uintptr_t)parent->parent;
        grandparent_address = (uint32_t)(uintptr_t)grandparent;
        parent->color = 1;
        grandparent->color = 0;

        pivot = (AddressMapNode *)(uintptr_t)grandparent->left;
        pivot_address = (uint32_t)(uintptr_t)pivot;
        rotation_parent = (AddressMapNode *)(uintptr_t)grandparent->parent;
        grandparent->left = pivot->right;
        if (pivot->right != REGISTRY_NIL_NODE_ADDRESS)
          ((AddressMapNode *)(uintptr_t)pivot->right)->parent =
              grandparent_address;
        pivot->parent = grandparent->parent;
        if (rotation_parent == header)
          header->parent = pivot_address;
        else if (grandparent_address == rotation_parent->left)
          rotation_parent->left = pivot_address;
        else
          rotation_parent->right = pivot_address;
        pivot->right = grandparent_address;
        grandparent->parent = pivot_address;
      }
    } else {
      uncle = (AddressMapNode *)(uintptr_t)grandparent->left;
      if (uncle->color == 0) {
        parent->color = 1;
        uncle->color = 1;
        grandparent->color = 0;
        node = grandparent;
        node_address = grandparent_address;
      } else {
        if (node_address == parent->left) {
          node = parent;
          node_address = parent_address;
          pivot = (AddressMapNode *)(uintptr_t)node->left;
          pivot_address = (uint32_t)(uintptr_t)pivot;
          rotation_parent = (AddressMapNode *)(uintptr_t)node->parent;
          rotation_node_address = node_address;
          node->left = pivot->right;
          if (pivot->right != REGISTRY_NIL_NODE_ADDRESS)
            ((AddressMapNode *)(uintptr_t)pivot->right)->parent =
                rotation_node_address;
          pivot->parent = node->parent;
          if (rotation_parent == header)
            header->parent = pivot_address;
          else if (rotation_node_address == rotation_parent->left)
            rotation_parent->left = pivot_address;
          else
            rotation_parent->right = pivot_address;
          pivot->right = rotation_node_address;
          node->parent = pivot_address;
        }
        parent = (AddressMapNode *)(uintptr_t)node->parent;
        parent_address = (uint32_t)(uintptr_t)parent;
        grandparent = (AddressMapNode *)(uintptr_t)parent->parent;
        grandparent_address = (uint32_t)(uintptr_t)grandparent;
        parent->color = 1;
        grandparent->color = 0;

        pivot = (AddressMapNode *)(uintptr_t)grandparent->right;
        pivot_address = (uint32_t)(uintptr_t)pivot;
        rotation_parent = (AddressMapNode *)(uintptr_t)grandparent->parent;
        grandparent->right = pivot->left;
        if (pivot->left != REGISTRY_NIL_NODE_ADDRESS)
          ((AddressMapNode *)(uintptr_t)pivot->left)->parent =
              grandparent_address;
        pivot->parent = grandparent->parent;
        if (rotation_parent == header)
          header->parent = pivot_address;
        else if (grandparent_address == rotation_parent->left)
          rotation_parent->left = pivot_address;
        else
          rotation_parent->right = pivot_address;
        pivot->left = grandparent_address;
        grandparent->parent = pivot_address;
      }
    }
  }

  ((AddressMapNode *)(uintptr_t)header->parent)->color = 1;
  *result_node_address = node_address;
  destroy_runtime_lockit(&lock_storage);
  return result_node_address;
}

uint32_t *__thiscall erase_ordered_map_node(
    uint32_t *tree, uint32_t *result_node_address, uint32_t *node_storage)
{
  AddressMap *map = (AddressMap *)(void *)tree;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  AddressMapNode *erased_node = (AddressMapNode *)(void *)node_storage;
  AddressMapNode *replacement;
  AddressMapNode *child;
  AddressMapNode *parent;
  AddressMapNode *sibling;
  AddressMapNode *pivot;
  AddressMapNode *rotation_node;
  AddressMapNode *rotation_parent;
  uint32_t header_address = (uint32_t)(uintptr_t)header;
  uint32_t erased_address = (uint32_t)(uintptr_t)erased_node;
  uint32_t next_address = erased_address;
  uint32_t child_address;
  uint32_t child_parent_address;
  uint32_t sibling_address;
  uint32_t pivot_address;
  uint32_t rotation_node_address;
  uint32_t removed_color;
  uint32_t *parent_fields;
  uint32_t *sibling_fields;
  uint32_t *pivot_fields;
  int direction;
  int sibling_side;
  int near_side;
  int far_side;
  int rotation_direction;
  int pivot_side;
  int middle_side;
  uint32_t lock_storage = 0;

  advance_ordered_map_node((int *)&next_address);
  construct_runtime_lockit(&lock_storage);

  replacement = erased_node;
  removed_color = replacement->color;
  if (erased_node->left == REGISTRY_NIL_NODE_ADDRESS) {
    child_address = erased_node->right;
    child_parent_address = erased_node->parent;
    parent = (AddressMapNode *)(uintptr_t)child_parent_address;
    parent_fields = (uint32_t *)parent;
    if (child_parent_address == header_address)
      header->parent = child_address;
    else if (erased_address == parent->left)
      parent->left = child_address;
    else
      parent->right = child_address;
    if (child_address != REGISTRY_NIL_NODE_ADDRESS)
      ((AddressMapNode *)(uintptr_t)child_address)->parent =
          child_parent_address;
  } else if (erased_node->right == REGISTRY_NIL_NODE_ADDRESS) {
    child_address = erased_node->left;
    child_parent_address = erased_node->parent;
    parent = (AddressMapNode *)(uintptr_t)child_parent_address;
    parent_fields = (uint32_t *)parent;
    if (child_parent_address == header_address)
      header->parent = child_address;
    else if (erased_address == parent->left)
      parent->left = child_address;
    else
      parent->right = child_address;
    if (child_address != REGISTRY_NIL_NODE_ADDRESS)
      ((AddressMapNode *)(uintptr_t)child_address)->parent =
          child_parent_address;
  } else {
    replacement = (AddressMapNode *)(uintptr_t)erased_node->right;
    while (replacement->left != REGISTRY_NIL_NODE_ADDRESS)
      replacement = (AddressMapNode *)(uintptr_t)replacement->left;
    removed_color = replacement->color;
    child_address = replacement->right;

    if (replacement->parent == erased_address) {
      child_parent_address = (uint32_t)(uintptr_t)replacement;
    } else {
      child_parent_address = replacement->parent;
      parent = (AddressMapNode *)(uintptr_t)child_parent_address;
      parent->left = child_address;
      if (child_address != REGISTRY_NIL_NODE_ADDRESS)
        ((AddressMapNode *)(uintptr_t)child_address)->parent =
            child_parent_address;
      replacement->right = erased_node->right;
      ((AddressMapNode *)(uintptr_t)replacement->right)->parent =
          (uint32_t)(uintptr_t)replacement;
    }

    parent = (AddressMapNode *)(uintptr_t)erased_node->parent;
    if (erased_node->parent == header_address)
      header->parent = (uint32_t)(uintptr_t)replacement;
    else if (erased_address == parent->left)
      parent->left = (uint32_t)(uintptr_t)replacement;
    else
      parent->right = (uint32_t)(uintptr_t)replacement;
    replacement->parent = erased_node->parent;
    replacement->left = erased_node->left;
    ((AddressMapNode *)(uintptr_t)replacement->left)->parent =
        (uint32_t)(uintptr_t)replacement;
    replacement->color = erased_node->color;
  }

  if (removed_color == 1) {
    child = (AddressMapNode *)(uintptr_t)child_address;
    while (child_address != header->parent && child->color == 1) {
      parent = (AddressMapNode *)(uintptr_t)child_parent_address;
      parent_fields = (uint32_t *)parent;
      direction = child_address == parent->left ? 0 : 1;
      sibling_side = direction ? 0 : 2;
      near_side = direction ? 2 : 0;
      far_side = direction ? 0 : 2;
      sibling_address = parent_fields[sibling_side];
      sibling = (AddressMapNode *)(uintptr_t)sibling_address;

      if (sibling->color == 0) {
        sibling->color = 1;
        parent->color = 0;
        rotation_node = parent;
        rotation_node_address = child_parent_address;
        rotation_parent = (AddressMapNode *)(uintptr_t)rotation_node->parent;
        rotation_direction = direction;
        pivot_side = rotation_direction ? 0 : 2;
        middle_side = rotation_direction ? 2 : 0;
        pivot_fields = (uint32_t *)rotation_node;
        pivot_address = pivot_fields[pivot_side];
        pivot = (AddressMapNode *)(uintptr_t)pivot_address;
        pivot_fields[pivot_side] = ((uint32_t *)pivot)[middle_side];
        if (((uint32_t *)pivot)[middle_side] != REGISTRY_NIL_NODE_ADDRESS)
          ((AddressMapNode *)(uintptr_t)((uint32_t *)pivot)[middle_side])->parent =
              rotation_node_address;
        pivot->parent = rotation_node->parent;
        if ((uint32_t)(uintptr_t)rotation_parent == header_address)
          header->parent = pivot_address;
        else if (rotation_node_address == rotation_parent->left)
          rotation_parent->left = pivot_address;
        else
          rotation_parent->right = pivot_address;
        ((uint32_t *)pivot)[middle_side] = rotation_node_address;
        rotation_node->parent = pivot_address;
        sibling_address = ((uint32_t *)parent)[sibling_side];
        sibling = (AddressMapNode *)(uintptr_t)sibling_address;
      }

      sibling_fields = (uint32_t *)sibling;
      if (((AddressMapNode *)(uintptr_t)sibling_fields[near_side])->color == 1
          && ((AddressMapNode *)(uintptr_t)sibling_fields[far_side])->color == 1) {
        sibling->color = 0;
        child_address = child_parent_address;
        child_parent_address = parent->parent;
        child = (AddressMapNode *)(uintptr_t)child_address;
      } else {
        if (((AddressMapNode *)(uintptr_t)sibling_fields[far_side])->color == 1) {
          ((AddressMapNode *)(uintptr_t)sibling_fields[near_side])->color = 1;
          sibling->color = 0;
          rotation_node = sibling;
          rotation_node_address = sibling_address;
          rotation_parent = (AddressMapNode *)(uintptr_t)rotation_node->parent;
          rotation_direction = 1 - direction;
          pivot_side = rotation_direction ? 0 : 2;
          middle_side = rotation_direction ? 2 : 0;
          pivot_fields = (uint32_t *)rotation_node;
          pivot_address = pivot_fields[pivot_side];
          pivot = (AddressMapNode *)(uintptr_t)pivot_address;
          pivot_fields[pivot_side] = ((uint32_t *)pivot)[middle_side];
          if (((uint32_t *)pivot)[middle_side] != REGISTRY_NIL_NODE_ADDRESS)
            ((AddressMapNode *)(uintptr_t)((uint32_t *)pivot)[middle_side])->parent =
                rotation_node_address;
          pivot->parent = rotation_node->parent;
          if ((uint32_t)(uintptr_t)rotation_parent == header_address)
            header->parent = pivot_address;
          else if (rotation_node_address == rotation_parent->left)
            rotation_parent->left = pivot_address;
          else
            rotation_parent->right = pivot_address;
          ((uint32_t *)pivot)[middle_side] = rotation_node_address;
          rotation_node->parent = pivot_address;
          sibling_address = ((uint32_t *)parent)[sibling_side];
          sibling = (AddressMapNode *)(uintptr_t)sibling_address;
          sibling_fields = (uint32_t *)sibling;
        }

        sibling->color = parent->color;
        parent->color = 1;
        ((AddressMapNode *)(uintptr_t)sibling_fields[far_side])->color = 1;
        rotation_node = parent;
        rotation_node_address = child_parent_address;
        rotation_parent = (AddressMapNode *)(uintptr_t)rotation_node->parent;
        rotation_direction = direction;
        pivot_side = rotation_direction ? 0 : 2;
        middle_side = rotation_direction ? 2 : 0;
        pivot_fields = (uint32_t *)rotation_node;
        pivot_address = pivot_fields[pivot_side];
        pivot = (AddressMapNode *)(uintptr_t)pivot_address;
        pivot_fields[pivot_side] = ((uint32_t *)pivot)[middle_side];
        if (((uint32_t *)pivot)[middle_side] != REGISTRY_NIL_NODE_ADDRESS)
          ((AddressMapNode *)(uintptr_t)((uint32_t *)pivot)[middle_side])->parent =
              rotation_node_address;
        pivot->parent = rotation_node->parent;
        if ((uint32_t)(uintptr_t)rotation_parent == header_address)
          header->parent = pivot_address;
        else if (rotation_node_address == rotation_parent->left)
          rotation_parent->left = pivot_address;
        else
          rotation_parent->right = pivot_address;
        ((uint32_t *)pivot)[middle_side] = rotation_node_address;
        rotation_node->parent = pivot_address;
        child_address = header->parent;
        child_parent_address = header_address;
        child = (AddressMapNode *)(uintptr_t)child_address;
      }
    }
    if (child_address != REGISTRY_NIL_NODE_ADDRESS)
      child->color = 1;
  }

  --map->node_count;
  if (!map->node_count) {
    header->parent = REGISTRY_NIL_NODE_ADDRESS;
    header->left = header_address;
    header->right = header_address;
  } else {
    AddressMapNode *minimum = (AddressMapNode *)(uintptr_t)header->parent;
    AddressMapNode *maximum = minimum;
    while (minimum->left != REGISTRY_NIL_NODE_ADDRESS)
      minimum = (AddressMapNode *)(uintptr_t)minimum->left;
    while (maximum->right != REGISTRY_NIL_NODE_ADDRESS)
      maximum = (AddressMapNode *)(uintptr_t)maximum->right;
    header->left = (uint32_t)(uintptr_t)minimum;
    header->right = (uint32_t)(uintptr_t)maximum;
  }

  free_pool_block((uint32_t *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
                  erased_address);
  *result_node_address = next_address;
  destroy_runtime_lockit(&lock_storage);
  return result_node_address;
}

uint32_t *__thiscall erase_ordered_map_range(
    uint32_t *tree, uint32_t *result_node_address, uint32_t *first_node,
    uint32_t *last_node)
{
  AddressMap *map = (AddressMap *)(void *)tree;
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  uint32_t first_address = (uint32_t)(uintptr_t)first_node;
  uint32_t last_address = (uint32_t)(uintptr_t)last_node;

  if (map->node_count != 0 && first_address == header->left
      && last_address == map->header) {
    uint32_t outer_lock_storage = 0;
    uint32_t inner_lock_storage = 0;
    uint32_t node_address = header->parent;

    construct_runtime_lockit(&outer_lock_storage);
    construct_runtime_lockit(&inner_lock_storage);
    while (node_address != REGISTRY_NIL_NODE_ADDRESS) {
      AddressMapNode *node = (AddressMapNode *)(uintptr_t)node_address;
      uint32_t left_address = node->left;
      destroy_ordered_map_subtree(node->right);
      free_pool_block(
          (uint32_t *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
          node_address);
      node_address = left_address;
    }
    destroy_runtime_lockit(&inner_lock_storage);

    header->parent = REGISTRY_NIL_NODE_ADDRESS;
    map->node_count = 0;
    header->left = map->header;
    header->right = map->header;
    *result_node_address = header->left;
    destroy_runtime_lockit(&outer_lock_storage);
    return result_node_address;
  }

  while (first_address != last_address) {
    uint32_t current_address = first_address;
    uint32_t ignored_result = 0;
    advance_ordered_map_node((int *)&first_address);
    erase_ordered_map_node(tree, &ignored_result,
                           (uint32_t *)(uintptr_t)current_address);
  }
  *result_node_address = first_address;
  return result_node_address;
}

/* Releases a map's nodes, header, and shared node-pool resources. */
void __thiscall destroy_address_map(AddressMap *map)
{
  AddressMapNode *header = (AddressMapNode *)(uintptr_t)map->header;
  uint32_t ignored_result = 0;
  uint32_t lock_storage = 0;

  erase_ordered_map_range((uint32_t *)(void *)map, &ignored_result,
                          (uint32_t *)(uintptr_t)header->left,
                          (uint32_t *)(void *)header);
  free_pool_block((uint32_t *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
                  map->header);
  map->header = 0;
  map->node_count = 0;

  construct_runtime_lockit(&lock_storage);
  if (!--address_map_instance_count) {
    free_pool_block((uint32_t *)(uintptr_t)(uint32_t)REGISTRY_NODE_POOL_ADDRESS,
                    REGISTRY_NIL_NODE_ADDRESS);
    registry_tree_nil_node_address = 0;
  }
  destroy_runtime_lockit(&lock_storage);

  if (!--ordered_map_allocator_reference_count) {
    if (ordered_map_arena_address) {
      destroy_block_arena(ordered_map_arena_address);
      free_tracked_memory(ordered_map_arena_address);
    }
    ordered_map_arena_address = 0;
    if (ordered_map_node_pool_address) {
      typedef void(__thiscall *OrderedMapPoolDestroy)(int, int);
      uintptr_t vtable_address = *(uint32_t *)(uintptr_t)
          (uint32_t)ordered_map_node_pool_address;
      OrderedMapPoolDestroy *pool_vtable =
          (OrderedMapPoolDestroy *)vtable_address;
      pool_vtable[0](ordered_map_node_pool_address, 1);
    }
    ordered_map_node_pool_address = 0;
  }
}

/* Destroys the address-to-instance metadata map owned by a runtime type. */
void __thiscall destroy_runtime_type_instance_map(
    RuntimeTypeDescriptor *type_descriptor)
{
  uint32_t map_address = type_descriptor->instances_by_address;

  if (map_address) {
    destroy_address_map((AddressMap *)(uintptr_t)map_address);
    free_tracked_memory((int)map_address);
  }
  type_descriptor->instances_by_address = 0;
}
