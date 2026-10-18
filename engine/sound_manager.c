#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../common/runtime_lockit.h"

/* platform/synchronization.c */
extern char *__thiscall initialize_synchronization_context(char *context);
extern int __thiscall begin_synchronization_context_activity(
    int context_address);
extern void __thiscall end_synchronization_context_activity(char *context);
extern DWORD __thiscall lock_synchronization_context(HANDLE *context);
extern BOOL __thiscall unlock_synchronization_context(HANDLE *context);

/* engine/dynamic_array.c */
extern int __thiscall insert_repeated_array_value(
    int *array, uint32_t *position, int count, uint32_t *value);
extern int __thiscall append_dynamic_array_pair(int *array,
                                                const uint32_t *entry);
extern int __thiscall free_vector_storage(int *array);

/* common/memory.c */
extern uint32_t *__cdecl allocate_tracked_memory(int size);
extern void __cdecl free_tracked_memory(int address);

/* engine/sound_manager.c */
int sound_option_tree_nil_node_address; /* Shared red-black tree nil node. */
int sound_option_map_instance_count; /* Sound-option maps using the nil node. */
int sound_resource_cache_address; /* Global sound-resource cache object. */

/* gk3/GK3R_rest.c */
extern uint32_t shared_zero_vector[3]; /* Shared zero-valued 3D vector. */
extern int active_sound_manager_address; /* Current sound manager instance. */
extern int game_engine_address; /* Engine used for sound failure logging. */
extern uint32_t sound_collection_vtable[];
extern uint32_t sound_manager_purecall_vtable[];
extern uint32_t sound_manager_vtable[];

/* C runtime */
extern int __cdecl _strcmpi(const char *left, const char *right);

/* gk3/GK3R_rest.c */
extern void __cdecl normalize_sound_volume(float volume);
extern uint32_t *__thiscall insert_sound_list_node(
    uint32_t *collection, uint32_t *insert_args, int anchor,
    uint32_t *sound_address);
extern int __thiscall start_sound_with_manager_pause_check(int sound,
                                                           int *event);
extern int __thiscall stop_sound_and_clear_flag_0x40(
    int (__thiscall ***sound)(void *));
extern int __thiscall queue_engine_event(uint32_t *engine, int *event);
extern int __thiscall advance_soundtrack_queue(uint32_t *soundtrack);
extern uint8_t *__thiscall select_random_soundtrack_entry(uint32_t *node);
extern uint32_t *__thiscall initialize_event_context(uint32_t *event_context,
                                                      int source, int code);
extern int *__thiscall play_or_update_soundtrack_sound(
    int sound_node, float volume, int event_value, char *event_name,
    int action);

char *__thiscall construct_sound_collection(char *collection);
uint32_t *__cdecl initialize_sound_resource_cache(void);

typedef struct {
  uint32_t next;
  uint32_t previous;
  uint32_t sound_address;
} SoundListNode;

typedef struct {
  uint8_t initialization_byte;
  uint8_t reserved[3];
  uint32_t begin_address;
  uint32_t end_address;
  uint32_t capacity_address;
} SoundRemovalList;

typedef struct {
  uint32_t sound_address;
  uint8_t notify;
  uint8_t reserved[3];
} DeferredSoundRelease;

typedef struct {
  uint32_t key;
  uint32_t enabled;
  float volume;
} SoundOptionMapEntry;

typedef struct {
  uint32_t left;
  uint32_t parent;
  uint32_t right;
  SoundOptionMapEntry value;
  uint32_t color;
} SoundOptionTreeNode;

typedef int (__thiscall *SoundStateHandler)(uint32_t *sound, int action);
typedef int (__thiscall *ObjectReferenceMethod)(void *object);

_Static_assert(sizeof(SoundListNode) == 12, "sound list node size");
_Static_assert(sizeof(SoundRemovalList) == 16, "sound removal list size");
_Static_assert(sizeof(DeferredSoundRelease) == 8,
               "deferred sound release size");
_Static_assert(sizeof(SoundOptionMapEntry) == 12,
               "sound option map entry size");
_Static_assert(sizeof(SoundOptionTreeNode) == 28,
               "sound option tree node size");

int __thiscall add_object_reference(void *object)
{
  uint32_t vtable_address = *(uint32_t *)(uintptr_t)object;
  uint32_t method_address =
      *(uint32_t *)(uintptr_t)(vtable_address + sizeof(uint32_t));
  ObjectReferenceMethod method =
      (ObjectReferenceMethod)(uintptr_t)method_address;
  return method(object);
}

int __thiscall release_object_reference(void *object)
{
  uint32_t vtable_address = *(uint32_t *)(uintptr_t)object;
  uint32_t method_address =
      *(uint32_t *)(uintptr_t)(vtable_address + 2 * sizeof(uint32_t));
  ObjectReferenceMethod method =
      (ObjectReferenceMethod)(uintptr_t)method_address;
  return method(object);
}

int __thiscall add_sound_object_reference(void *sound)
{
  return add_object_reference(sound);
}

int __thiscall release_sound_object_reference(void *sound)
{
  return release_object_reference(sound);
}

int __thiscall initialize_sound_reference(uint32_t *reference, void *sound)
{
  *reference = (uint32_t)(uintptr_t)sound;
  return sound ? add_object_reference(sound) : 0;
}

int __thiscall release_sound_reference(uint32_t *reference)
{
  void *sound = (void *)(uintptr_t)*reference;
  return sound ? release_object_reference(sound) : 0;
}

void __thiscall find_sound_in_collection(int collection_address, int sound_id,
                                         uint32_t *result)
{
  char *collection = (char *)(uintptr_t)(uint32_t)collection_address;
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;

  initialize_sound_reference(result, 0);
  begin_synchronization_context_activity((int)(intptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    if (((uint32_t *)(uintptr_t)sound_reference)[1] == (uint32_t)sound_id) {
      initialize_sound_reference(result,
                                 (void *)(uintptr_t)node->sound_address);
      release_sound_reference(&sound_reference);
      break;
    }
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);
}

int __thiscall find_sound_id_by_name(int collection_address,
                                     const char *sound_name)
{
  char *collection = (char *)(uintptr_t)(uint32_t)collection_address;
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;

  begin_synchronization_context_activity((int)(intptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    if (sound_reference != UINT32_C(0xfffffff8) &&
        _strcmpi((const char *)(uintptr_t)sound_reference + 8, sound_name) ==
            0) {
      int sound_id =
          (int)((uint32_t *)(uintptr_t)sound_reference)[1];
      release_sound_reference(&sound_reference);
      end_synchronization_context_activity(synchronization_context);
      return sound_id;
    }
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);
  return 0;
}

int __thiscall count_sounds_with_flag_mask_0x02(int collection_address)
{
  char *collection = (char *)(uintptr_t)(uint32_t)collection_address;
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;
  int count = 0;

  begin_synchronization_context_activity((int)(intptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    if ((((uint8_t *)(uintptr_t)sound_reference)[44] & 0x02u) != 0)
      ++count;
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);
  return count;
}

int __thiscall clear_sound_state(uint32_t *sound, int action)
{
  uint32_t state_mask = action != 32 ? 16u : 32u;
  uint32_t state_flags = sound[11];
  uint32_t vtable_address;
  uint32_t callback_address;
  SoundStateHandler callback;

  if ((state_flags & state_mask) == 0)
    return (int)state_mask;

  sound[11] = state_flags & ~state_mask;
  vtable_address = sound[0];
  callback_address = *(uint32_t *)(uintptr_t)(vtable_address + 28);
  callback = (int (__thiscall *)(uint32_t *, int))
      (uintptr_t)callback_address;
  return callback(sound, action);
}

int __thiscall set_sound_state(uint32_t *sound, int action)
{
  uint32_t state_mask = action != 32 ? 16u : 32u;
  uint32_t state_flags = sound[11];
  uint32_t vtable_address;
  uint32_t callback_address;
  SoundStateHandler callback;
  int result = (int)state_flags;

  if ((state_flags & state_mask) == 0) {
    if ((state_flags & 32u) != 0 && action == 16)
      clear_sound_state(sound, 32);

    vtable_address = sound[0];
    callback_address = *(uint32_t *)(uintptr_t)(vtable_address + 24);
    callback = (SoundStateHandler)(uintptr_t)callback_address;
    result = callback(sound, action);
    sound[11] |= state_mask;
  }
  return result;
}

void __thiscall find_sound_by_id(int *manager, int sound_id,
                                 uint32_t *result)
{
  find_sound_in_collection(manager[18], sound_id, result);
}

void __thiscall resume_all_sounds(char **manager)
{
  char *collection = (char *)(uintptr_t)(uint32_t)manager[18];
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;

  begin_synchronization_context_activity((int)(uintptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    clear_sound_state((uint32_t *)(uintptr_t)sound_reference, 16);
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);
}

bool __thiscall has_sound_id(uint32_t *manager, int sound_id)
{
  uint32_t sound = 0;

  find_sound_by_id((int *)(void *)manager, sound_id, &sound);
  bool active = sound != 0;
  release_sound_reference(&sound);
  return active;
}

void __thiscall construct_sound_setting_map(uint32_t *context)
{
  enum { SOUND_OPTION_TREE_NODE_SIZE = 28 };
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  if (!sound_option_tree_nil_node_address) {
    SoundOptionTreeNode *nil_node = (SoundOptionTreeNode *)
        allocate_tracked_memory(SOUND_OPTION_TREE_NODE_SIZE);
    nil_node->left = 0;
    nil_node->parent = 0;
    nil_node->right = 0;
    nil_node->color = 1;
    sound_option_tree_nil_node_address = (int)(uintptr_t)nil_node;
  }

  ++sound_option_map_instance_count;

  SoundOptionTreeNode *header = (SoundOptionTreeNode *)
      allocate_tracked_memory(SOUND_OPTION_TREE_NODE_SIZE);
  header->left = (uint32_t)(uintptr_t)header;
  header->parent = (uint32_t)sound_option_tree_nil_node_address;
  header->right = (uint32_t)(uintptr_t)header;
  header->color = 0;
  context[1] = (uint32_t)(uintptr_t)header;
  context[3] = 0;
  destroy_runtime_lockit(&lock_storage);
}

void __thiscall rotate_sound_option_tree_left(uint32_t *context,
                                              uint32_t node_address)
{
  SoundOptionTreeNode *header =
      (SoundOptionTreeNode *)(uintptr_t)context[1];
  SoundOptionTreeNode *node =
      (SoundOptionTreeNode *)(uintptr_t)node_address;
  SoundOptionTreeNode *pivot =
      (SoundOptionTreeNode *)(uintptr_t)node->right;
  uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  node->right = pivot->left;
  if (pivot->left != nil_node)
    ((SoundOptionTreeNode *)(uintptr_t)pivot->left)->parent = node_address;
  pivot->parent = node->parent;

  if (node_address == header->parent) {
    header->parent = (uint32_t)(uintptr_t)pivot;
  } else {
    SoundOptionTreeNode *parent =
        (SoundOptionTreeNode *)(uintptr_t)node->parent;
    if (node_address == parent->left)
      parent->left = (uint32_t)(uintptr_t)pivot;
    else
      parent->right = (uint32_t)(uintptr_t)pivot;
  }

  pivot->left = node_address;
  node->parent = (uint32_t)(uintptr_t)pivot;
  destroy_runtime_lockit(&lock_storage);
}

void __thiscall rotate_sound_option_tree_right(uint32_t *context,
                                               uint32_t node_address)
{
  SoundOptionTreeNode *header =
      (SoundOptionTreeNode *)(uintptr_t)context[1];
  SoundOptionTreeNode *node =
      (SoundOptionTreeNode *)(uintptr_t)node_address;
  SoundOptionTreeNode *pivot =
      (SoundOptionTreeNode *)(uintptr_t)node->left;
  uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  node->left = pivot->right;
  if (pivot->right != nil_node)
    ((SoundOptionTreeNode *)(uintptr_t)pivot->right)->parent = node_address;
  pivot->parent = node->parent;

  if (node_address == header->parent) {
    header->parent = (uint32_t)(uintptr_t)pivot;
  } else {
    SoundOptionTreeNode *parent =
        (SoundOptionTreeNode *)(uintptr_t)node->parent;
    if (node_address == parent->right)
      parent->right = (uint32_t)(uintptr_t)pivot;
    else
      parent->left = (uint32_t)(uintptr_t)pivot;
  }

  pivot->right = node_address;
  node->parent = (uint32_t)(uintptr_t)pivot;
  destroy_runtime_lockit(&lock_storage);
}

uint32_t *__cdecl find_rightmost_sound_option_tree_node(
    uint32_t node_address)
{
  SoundOptionTreeNode *node =
      (SoundOptionTreeNode *)(uintptr_t)node_address;
  const uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  while (node->right != nil_node)
    node = (SoundOptionTreeNode *)(uintptr_t)node->right;
  destroy_runtime_lockit(&lock_storage);
  return (uint32_t *)(void *)node;
}

static void __thiscall move_to_previous_sound_option_tree_node(
    int *node_address)
{
  uint32_t current_address = (uint32_t)*node_address;
  SoundOptionTreeNode *node =
      (SoundOptionTreeNode *)(uintptr_t)current_address;
  const uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  SoundOptionTreeNode *parent =
      (SoundOptionTreeNode *)(uintptr_t)node->parent;
  if (node->color != 0 || parent->parent != current_address) {
    if (node->left == nil_node) {
      while (current_address == parent->left) {
        current_address = (uint32_t)(uintptr_t)parent;
        node = parent;
        parent = (SoundOptionTreeNode *)(uintptr_t)node->parent;
      }
      current_address = (uint32_t)(uintptr_t)parent;
    } else {
      current_address = (uint32_t)(uintptr_t)
          find_rightmost_sound_option_tree_node(node->left);
    }
  } else {
    current_address = node->right;
  }
  *node_address = (int)current_address;
  destroy_runtime_lockit(&lock_storage);
}

static int **__thiscall insert_sound_option_tree_node(
    uint32_t *context, int **node_address, int cursor_address,
    int *parent_address, int *key_and_value)
{
  SoundOptionTreeNode *header =
      (SoundOptionTreeNode *)(uintptr_t)context[1];
  SoundOptionTreeNode *parent =
      (SoundOptionTreeNode *)(uintptr_t)parent_address;
  SoundOptionTreeNode *node;
  SoundOptionTreeNode *cursor;
  uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  node = (SoundOptionTreeNode *)allocate_tracked_memory(
      sizeof(SoundOptionTreeNode));
  node->color = 0;
  node->parent = (uint32_t)(uintptr_t)parent;
  node->left = nil_node;
  node->right = nil_node;
  node->value = *(SoundOptionMapEntry *)(void *)key_and_value;
  ++context[3];

  if (parent != header && (uint32_t)cursor_address == nil_node &&
      node->value.key >= parent->value.key) {
    parent->right = (uint32_t)(uintptr_t)node;
    if ((uint32_t)(uintptr_t)parent == header->right)
      header->right = (uint32_t)(uintptr_t)node;
  } else {
    parent->left = (uint32_t)(uintptr_t)node;
    if (parent == header) {
      header->parent = (uint32_t)(uintptr_t)node;
      header->right = (uint32_t)(uintptr_t)node;
    } else if ((uint32_t)(uintptr_t)parent == header->left) {
      header->left = (uint32_t)(uintptr_t)node;
    }
  }

  cursor = node;
  while ((uint32_t)(uintptr_t)cursor != header->parent) {
    SoundOptionTreeNode *parent_node =
        (SoundOptionTreeNode *)(uintptr_t)cursor->parent;
    if (parent_node->color != 0)
      break;

    SoundOptionTreeNode *grandparent =
        (SoundOptionTreeNode *)(uintptr_t)parent_node->parent;
    if ((uint32_t)(uintptr_t)parent_node == grandparent->left) {
      SoundOptionTreeNode *uncle =
          (SoundOptionTreeNode *)(uintptr_t)grandparent->right;
      if (uncle->color != 0) {
        if ((uint32_t)(uintptr_t)cursor == parent_node->right) {
          cursor = parent_node;
          rotate_sound_option_tree_left(
              context, (uint32_t)(uintptr_t)parent_node);
          parent_node = (SoundOptionTreeNode *)(uintptr_t)cursor->parent;
          grandparent =
              (SoundOptionTreeNode *)(uintptr_t)parent_node->parent;
        }
        parent_node->color = 1;
        grandparent->color = 0;
        rotate_sound_option_tree_right(
            context, (uint32_t)(uintptr_t)grandparent);
      } else {
        parent_node->color = 1;
        uncle->color = 1;
        grandparent->color = 0;
        cursor = grandparent;
      }
    } else {
      SoundOptionTreeNode *uncle =
          (SoundOptionTreeNode *)(uintptr_t)grandparent->left;
      if (uncle->color != 0) {
        if ((uint32_t)(uintptr_t)cursor == parent_node->left) {
          cursor = parent_node;
          rotate_sound_option_tree_right(
              context, (uint32_t)(uintptr_t)parent_node);
          parent_node = (SoundOptionTreeNode *)(uintptr_t)cursor->parent;
          grandparent =
              (SoundOptionTreeNode *)(uintptr_t)parent_node->parent;
        }
        parent_node->color = 1;
        grandparent->color = 0;
        rotate_sound_option_tree_left(
            context, (uint32_t)(uintptr_t)grandparent);
      } else {
        parent_node->color = 1;
        uncle->color = 1;
        grandparent->color = 0;
        cursor = grandparent;
      }
    }
  }

  ((SoundOptionTreeNode *)(uintptr_t)header->parent)->color = 1;
  *node_address = (int *)(void *)node;
  destroy_runtime_lockit(&lock_storage);
  return node_address;
}

int **__thiscall find_or_insert_sound_option_node(
    uint32_t *context, int **result, int *key_and_value);

int *__thiscall find_or_create_sound_option(void *context, int *key)
{
  int *search_result[2];
  SoundOptionMapEntry initial_entry = {
      (uint32_t)*key,
      1,
      100.0f
  };
  int **insert_result = find_or_insert_sound_option_node(
      (uint32_t *)context, search_result, (int *)&initial_entry);
  return insert_result[0] + 4;
}

int **__thiscall find_or_insert_sound_option_node(
    uint32_t *context, int **result, int *key_and_value)
{
  int *header = (int *)(uintptr_t)context[1];
  int *nil_node = (int *)(uintptr_t)(uint32_t)
      sound_option_tree_nil_node_address;
  int *parent = header;
  int *node = (int *)(uintptr_t)(uint32_t)header[1];
  int *candidate;
  int *inserted_node = key_and_value;
  bool insert_left = true;
  int was_inserted;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  if (node != nil_node) {
    do {
      parent = node;
      insert_left = key_and_value[0] < node[3];
      node = (int *)(uintptr_t)(uint32_t)
          (insert_left ? node[0] : node[2]);
    } while (node != nil_node);
  }
  destroy_runtime_lockit(&lock_storage);

  if (context[2])
    goto insert_node;

  candidate = parent;
  if (insert_left) {
    if (parent == *(int **)(void *)header)
      goto insert_node;
    move_to_previous_sound_option_tree_node((int *)&candidate);
  }

  if (candidate[3] >= key_and_value[0]) {
    result[0] = candidate;
    was_inserted = 0;
  } else {
insert_node:
    result[0] = (int *)(uintptr_t)*insert_sound_option_tree_node(
        context, &inserted_node, (int)(uintptr_t)node, parent,
        key_and_value);
    was_inserted = 1;
  }

  result[1] = (int *)(uintptr_t)was_inserted;
  return result;
}

static uint32_t *__thiscall find_sound_option_tree_lower_bound(
    uint32_t *tree, uint32_t *key)
{
  SoundOptionTreeNode *header =
      (SoundOptionTreeNode *)(uintptr_t)tree[1];
  SoundOptionTreeNode *candidate = header;
  SoundOptionTreeNode *node =
      (SoundOptionTreeNode *)(uintptr_t)header->parent;
  const uint32_t nil_node = (uint32_t)sound_option_tree_nil_node_address;
  uint32_t lock_storage = 0;

  construct_runtime_lockit(&lock_storage);
  while ((uint32_t)(uintptr_t)node != nil_node) {
    if ((int32_t)node->value.key >= (int32_t)*key) {
      candidate = node;
      node = (SoundOptionTreeNode *)(uintptr_t)node->left;
    } else {
      node = (SoundOptionTreeNode *)(uintptr_t)node->right;
    }
  }
  destroy_runtime_lockit(&lock_storage);
  return (uint32_t *)(void *)candidate;
}

uint32_t *__thiscall find_sound_option_tree_node(
    uint32_t *tree, uint32_t *result, uint32_t *key)
{
  SoundOptionTreeNode *header =
      (SoundOptionTreeNode *)(uintptr_t)tree[1];
  SoundOptionTreeNode *candidate =
      (SoundOptionTreeNode *)(void *)find_sound_option_tree_lower_bound(
          tree, key);

  if ((uint32_t)(uintptr_t)candidate == (uint32_t)(uintptr_t)header ||
      (int32_t)*key < (int32_t)candidate->value.key)
    *result = (uint32_t)(uintptr_t)header;
  else
    *result = (uint32_t)(uintptr_t)candidate;
  return result;
}

char *__thiscall initialize_sound_manager_core(char *manager)
{
  char *settings = manager + 56;
  char *allocated_memory;
  char *sound_object;
  int *setting;
  const uint32_t *zero_vector = shared_zero_vector;
  int enabled = 1;

  manager[64] = 0;
  settings[0] = 0;
  settings[1] = 0;
  construct_sound_setting_map((uint32_t *)settings);
  *(uint32_t *)manager = (uint32_t)(uintptr_t)sound_manager_purecall_vtable;
  active_sound_manager_address = (int)(intptr_t)manager;
  manager[4] = 0;
  ((uint32_t *)manager)[2] = 0;
  ((uint32_t *)manager)[3] = 44100;
  ((uint32_t *)manager)[4] = 1077936128;
  ((uint32_t *)manager)[5] = zero_vector[0];
  ((uint32_t *)manager)[6] = zero_vector[1];
  ((uint32_t *)manager)[7] = zero_vector[2];
  ((float *)manager)[8] = 0.0f;
  ((float *)manager)[9] = 0.0f;
  manager[48] = 0;
  ((uint32_t *)manager)[10] = 16;
  ((uint32_t *)manager)[11] = 0;
  manager[49] = 1;
  ((uint32_t *)manager)[13] = 1120403456;

  allocated_memory = (char *)allocate_tracked_memory(72);
  sound_object = allocated_memory
      ? construct_sound_collection(allocated_memory) : 0;
  allocated_memory = 0;
  ((uint32_t *)manager)[18] = (uint32_t)(uintptr_t)sound_object;
  setting = find_or_create_sound_option(settings,
                                         (int *)&allocated_memory);
  setting[0] = enabled;
  setting[1] = 1120403456;
  initialize_sound_resource_cache();
  return manager;
}

char *__thiscall initialize_sound_worker_queue(char *queue)
{
  char *critical_section = queue + 12;

  InitializeCriticalSection((LPCRITICAL_SECTION)critical_section);
  ((uint32_t *)critical_section)[6] = 1;
  *(uint32_t *)queue = UINT32_MAX;
  memset(queue + 4, 0, 8);
  queue[57] = 0;
  ((uint32_t *)queue)[10] = 0;
  ((uint32_t *)queue)[11] = 0;
  ((uint32_t *)queue)[12] = 1;
  ((uint32_t *)queue)[13] = 1;
  queue[56] = 1;
  return queue;
}

char __thiscall ensure_sound_system_initialized(uint32_t *audio_settings)
{
  typedef int (__thiscall *InitializeSoundSystemMethod)(uint32_t *settings);
  typedef void (__thiscall *SetSoundOptionMethod)(uint32_t *settings,
                                                   uint32_t value);
  typedef void (__thiscall *ConfigureSoundMethod)(uint32_t *settings,
                                                   uint32_t *values,
                                                   uint32_t first_option,
                                                   uint32_t second_option);
  typedef void (__thiscall *LogEngineMessageMethod)(int engine,
                                                    const char *message,
                                                    uint32_t flags,
                                                    int severity);

  uint8_t *settings_bytes = (uint8_t *)(void *)audio_settings;
  if (settings_bytes[4] == 0) {
    uint32_t *settings_words = audio_settings;
    uint32_t attempts = settings_words[2];

    if (attempts >= 25) {
      if (attempts == 25) {
        settings_words[2] = 26;
        uint32_t *engine = (uint32_t *)(uintptr_t)(uint32_t)game_engine_address;
        uint32_t *engine_methods = *(uint32_t **)(void *)engine;
        LogEngineMessageMethod log_message =
            (LogEngineMessageMethod)(uintptr_t)engine_methods[144 / 4];
        log_message(game_engine_address,
                    "Sound system failed to initialize after multiple attempts, sound disabled.",
                    0, 16);
      }
    } else {
      settings_words[2] = attempts + 1;
      uint32_t *sound_methods = *(uint32_t **)(void *)audio_settings;
      InitializeSoundSystemMethod initialize =
          (InitializeSoundSystemMethod)(uintptr_t)sound_methods[0];
      settings_bytes[4] = (uint8_t)initialize(audio_settings);

      if (settings_bytes[4] != 0) {
        SetSoundOptionMethod set_option =
            (SetSoundOptionMethod)(uintptr_t)sound_methods[60 / 4];
        set_option(audio_settings, settings_words[4]);

        ConfigureSoundMethod configure =
            (ConfigureSoundMethod)(uintptr_t)sound_methods[64 / 4];
        configure(audio_settings, &settings_words[5], settings_words[8],
                  settings_words[9]);
      }
    }
  }

  return (char)settings_bytes[4];
}

int __thiscall resume_sound_by_id(int *manager, int sound_id)
{
  uint32_t *sound = 0;

  find_sound_by_id(manager, sound_id, (uint32_t *)&sound);
  if (sound)
    clear_sound_state(sound, 16);
  return release_sound_reference((uint32_t *)(void *)&sound);
}

char *__thiscall construct_sound_collection(char *collection)
{
  uint32_t *list_header = allocate_tracked_memory(sizeof(SoundListNode));
  const uint32_t header_address = (uint32_t)(uintptr_t)list_header;
  uint32_t *fields = (uint32_t *)(void *)collection;

  list_header[0] = header_address;
  list_header[1] = header_address;
  fields[2] = header_address;
  fields[3] = 0;
  fields[5] = 0;
  fields[6] = 0;
  fields[7] = 0;
  initialize_synchronization_context(collection + 32);
  fields[0] = (uint32_t)(uintptr_t)sound_collection_vtable;
  return collection;
}

uint32_t *__cdecl initialize_sound_resource_cache(void)
{
  uint32_t *cache = allocate_tracked_memory(12);
  uint32_t *list_header = 0;

  if (cache) {
    list_header = allocate_tracked_memory(sizeof(SoundListNode));
    const uint32_t header_address = (uint32_t)(uintptr_t)list_header;
    list_header[0] = header_address;
    list_header[1] = header_address;
    cache[1] = header_address;
    cache[2] = 0;
  }

  sound_resource_cache_address = (int)(uintptr_t)cache;
  return list_header;
}

void __thiscall pause_sounds_matching(
    char **manager, uint8_t (__cdecl *predicate)(uint32_t), int context)
{
  char *collection = (char *)(uintptr_t)(uint32_t)manager[18];
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;

  (void)context;
  begin_synchronization_context_activity(
      (int)(uintptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    if (predicate(((uint32_t *)(uintptr_t)sound_reference)[1]))
      set_sound_state((uint32_t *)(uintptr_t)sound_reference, 16);
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);
}

int __thiscall remove_sound_from_collection(int collection_address,
                                            uint32_t sound_address,
                                            char notify)
{
  char *collection = (char *)(uintptr_t)(uint32_t)collection_address;
  HANDLE *synchronization_context = (HANDLE *)(void *)(collection + 32);
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;
  DeferredSoundRelease deferred_release = {
      sound_address, (uint8_t)notify, {0, 0, 0}};

  lock_synchronization_context(synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;

    if (node->sound_address == sound_address) {
      SoundListNode *previous = (SoundListNode *)(uintptr_t)node->previous;
      SoundListNode *next = (SoundListNode *)(uintptr_t)node->next;
      uint32_t *pending_entry;
      uint32_t *pending_end;

      previous->next = node->next;
      next->previous = node->previous;
      free_tracked_memory((int)(uintptr_t)node);
      --*(uint32_t *)(void *)(collection + 12);

      pending_entry = *(uint32_t **)(void *)(collection + 20);
      pending_end = *(uint32_t **)(void *)(collection + 24);
      while (pending_entry != pending_end) {
        if (*pending_entry == sound_address)
          goto unlock_collection;
        pending_entry += 2;
      }
      append_dynamic_array_pair((int *)(void *)(collection + 16),
                                (const uint32_t *)(void *)&deferred_release);
      break;
    }
    node_address = node->next;
  }

unlock_collection:
  return unlock_synchronization_context(synchronization_context);
}

int __thiscall remove_collection_sounds_matching(
    int collection_address, uint8_t (__cdecl *predicate)(uint32_t),
    int context, char notify)
{
  char *collection = (char *)(uintptr_t)(uint32_t)collection_address;
  char *synchronization_context = collection + 32;
  uint32_t header_address = *(uint32_t *)(void *)(collection + 8);
  uint32_t node_address;
  SoundRemovalList matches = {
      (uint8_t)((uint32_t)context >> 8), {0, 0, 0}, 0, 0, 0};

  begin_synchronization_context_activity((int)(intptr_t)synchronization_context);
  node_address = *(uint32_t *)(uintptr_t)header_address;
  while (node_address != header_address) {
    SoundListNode *node = (SoundListNode *)(uintptr_t)node_address;
    uint32_t sound_reference = 0;

    initialize_sound_reference(&sound_reference,
                                (void *)(uintptr_t)node->sound_address);
    if (predicate(((uint32_t *)(uintptr_t)sound_reference)[1]))
      insert_repeated_array_value(
          (int *)(void *)&matches,
          (uint32_t *)(uintptr_t)matches.end_address, 1, &sound_reference);
    release_sound_reference(&sound_reference);
    node_address = node->next;
  }
  end_synchronization_context_activity(synchronization_context);

  for (uint32_t address = matches.begin_address;
       address != matches.end_address; address += sizeof(uint32_t))
    remove_sound_from_collection(
        collection_address, *(uint32_t *)(uintptr_t)address, notify);
  return free_vector_storage((int *)(void *)&matches);
}

int __thiscall remove_sounds_matching(
    int *manager, uint8_t (__cdecl *predicate)(uint32_t), int context,
    char flag)
{
  return remove_collection_sounds_matching(manager[18], predicate, context,
                                           flag);
}

int __thiscall construct_sound_manager(int address)
{
  char *manager = (char *)(intptr_t)address;
  initialize_sound_manager_core(manager);
  initialize_sound_worker_queue(manager + 88);
  *(uint32_t *)(manager + 76) = 0;
  *(uint32_t *)(manager + 80) = 0;
  *(uint32_t *)(manager + 84) = 0;
  *(uint32_t *)manager = (uint32_t)(uintptr_t)sound_manager_vtable;
  return address;
}

char *__stdcall normalize_sound_filename(char *source, char *buffer)
{
  char *result;

  strcpy(buffer, source);
  result = strchr(buffer, '.');
  if (!result)
    return strcat(buffer, ".wav");
  return result;
}

BOOL __thiscall add_sound_to_collection(int collection, int sound_address)
{
  HANDLE *context = (HANDLE *)(uintptr_t)(collection + 32);
  uint32_t insert_args[2];
  int count;

  insert_args[1] = (uint32_t)(collection + 32);
  lock_synchronization_context(context);
  count = *(int *)(uintptr_t)(collection + 8);
  insert_sound_list_node((uint32_t *)(uintptr_t)(collection + 4), insert_args,
                         count, (uint32_t *)(void *)&sound_address);
  return unlock_synchronization_context(context);
}

int __thiscall set_sound_volume(
    int (__thiscall ***sound)(void *),
    int (__thiscall **volume_bits)(void *))
{
  sound[12] = volume_bits;
  return (**sound)(sound);
}

int __thiscall set_sound_position(int *sound, int *position)
{
  int vtable_address = *sound;

  sound[16] = *position;
  sound[17] = position[1];
  sound[18] = position[2];
  return (*(int (__stdcall **)(int *))(vtable_address + 48))(sound + 16);
}

int __thiscall set_sound_distance_range(float *sound,
                                        int min_distance_bits,
                                        float max_distance)
{
  *((uint32_t *)sound + 19) = (uint32_t)min_distance_bits;
  sound[20] = max_distance;
  return (*(int (__stdcall **)(int, uint32_t))(*(uint32_t *)sound + 56))(
      min_distance_bits, *(uint32_t *)(void *)&max_distance);
}

int __thiscall play_sound(
    int manager_address, float sound_category, char *sound_name, float volume,
    char looping, int sound_flags, int *event, int spatial,
    int *position, int min_distance_bits, float max_distance)
{
  uint8_t *manager = (uint8_t *)(uintptr_t)(uint32_t)manager_address;
  float requested_sound_category = sound_category;
  float requested_volume = volume;
  int sound_address;
  char normalized_filename[260];
  uint32_t category_key;
  uint32_t option_node;

  memcpy(&category_key, &sound_category, sizeof(category_key));
  if (!manager[49] ||
      !(*(uint8_t *)(uintptr_t)(find_sound_option_tree_node(
            (uint32_t *)(void *)(manager + 56), &option_node,
            &category_key)[0] + 16)) ||
      (!*(uint8_t *)(uintptr_t)(manager + 4) &&
       !ensure_sound_system_initialized((uint32_t *)(void *)manager))) {
    if (event)
      queue_engine_event((uint32_t *)(uintptr_t)(uint32_t)game_engine_address,
                         event);
    return 0;
  }

  normalize_sound_volume(volume);
  normalize_sound_filename(sound_name, normalized_filename);
  sound_address = (*(int (__thiscall **)(int, float, char *, int))
      (*(uint32_t *)(void *)manager + 4))(
          manager_address, requested_sound_category, normalized_filename,
          spatial);
  if (!sound_address) {
    if (event)
      queue_engine_event((uint32_t *)(uintptr_t)(uint32_t)game_engine_address,
                         event);
    return 0;
  }

  uint32_t volume_bits;
  memcpy(&volume_bits, &requested_volume, sizeof(volume_bits));
  if (looping)
    *(uint32_t *)(uintptr_t)(sound_address + 44) |= 1u;
  else
    *(uint32_t *)(uintptr_t)(sound_address + 44) &= ~1u;
  *(uint32_t *)(uintptr_t)(sound_address + 84) = (uint32_t)sound_flags;
  set_sound_volume((int (__thiscall ***)(void *))(uintptr_t)sound_address, 0);
  if (spatial) {
    set_sound_position((int *)(uintptr_t)sound_address, position);
    set_sound_distance_range((float *)(uintptr_t)sound_address,
                             min_distance_bits, max_distance);
  }
  start_sound_with_manager_pause_check(sound_address, event);
  set_sound_volume((int (__thiscall ***)(void *))(uintptr_t)sound_address,
                   (int (__thiscall **)(void *))(uintptr_t)volume_bits);
  if ((*(uint8_t *)(uintptr_t)(sound_address + 44) & 4u) != 0)
    stop_sound_and_clear_flag_0x40(
        (int (__thiscall ***)(void *))(uintptr_t)sound_address);
  release_object_reference((void *)(uintptr_t)sound_address);
  add_sound_to_collection(*(int *)(void *)(manager + 72), sound_address);
  return *(int *)(uintptr_t)(sound_address + 4);
}

int __thiscall play_2d_sound(
    void *manager, float sound_category, char *sound_name, float volume,
    char looping, int sound_flags, int *event)
{
  return play_sound((int)(uintptr_t)manager, sound_category, sound_name,
                    volume, looping, sound_flags, event, 0,
                    (int *)(void *)shared_zero_vector, 0, 0.0f);
}

int __thiscall play_3d_sound(
    void *manager, float sound_category, char *sound_name, float volume,
    char looping, int sound_flags, int *position, int min_distance_bits,
    float max_distance, int *event)
{
  return play_sound((int)(uintptr_t)manager, sound_category, sound_name,
                    volume, looping, sound_flags, event, 1, position,
                    min_distance_bits, max_distance);
}

int __thiscall process_soundtrack_node(int soundtrack_address)
{
  uint8_t *soundtrack =
      (uint8_t *)(uintptr_t)(uint32_t)soundtrack_address;
  int result;
  int current_node_address;
  int node_type;
  int random_value;
  int random_percent;
  int min_wait_ms;
  int max_wait_ms;
  uint32_t event_context_storage[2];
  uint32_t *event_context;

  uint32_t vtable_address = *(uint32_t *)(void *)soundtrack;
  *(int *)(void *)(soundtrack + 52) = -1;
  ((void (__stdcall *)(int))(uintptr_t)(vtable_address + 24))(1);
  current_node_address =
      advance_soundtrack_queue((uint32_t *)(void *)soundtrack);
  if (!current_node_address) {
    *(int *)(void *)(soundtrack + 52) = 1;
    return 0;
  }

  *(int *)(void *)(soundtrack + 88) = 0;
  node_type = *(int *)(uintptr_t)(current_node_address + 4) - 1;
  if (node_type) {
    node_type -= 1;
    if (node_type) {
      if (node_type - 1 == 0) {
        uint8_t *selected_entry =
            select_random_soundtrack_entry(
                (uint32_t *)(uintptr_t)current_node_address);
        *(uint32_t *)(void *)(soundtrack + 88) =
            (uint32_t)(uintptr_t)selected_entry;
        if (selected_entry) {
          event_context = initialize_event_context(event_context_storage,
                                                   soundtrack_address, 3);
          result = (int)play_or_update_soundtrack_sound(
              *(int *)(void *)(soundtrack + 88) + 12,
              *(float *)(void *)(soundtrack + 80), (int)event_context[0],
              (char *)(uintptr_t)event_context[1], 1);
          *(int *)(void *)(soundtrack + 52) = 0;
          return result;
        }
      }
    } else {
      int repeats_remaining = *(int *)(uintptr_t)(current_node_address + 20);
      if (repeats_remaining <= 1) {
        if (repeats_remaining == 1)
          *(uint8_t *)(uintptr_t)(current_node_address + 8) = 1;
      } else {
        *(int *)(uintptr_t)(current_node_address + 20) = repeats_remaining - 1;
      }

      if (*(int *)(uintptr_t)(current_node_address + 24) == 100 ||
          ((random_value = rand(), random_percent = random_value % 100,
            result = random_value / 100,
            random_percent <= *(int *)(uintptr_t)(current_node_address + 24)))) {
        min_wait_ms = *(int *)(uintptr_t)(current_node_address + 12);
        max_wait_ms = *(int *)(uintptr_t)(current_node_address + 16);
        if (max_wait_ms) {
          int wait_range_ms = max_wait_ms - min_wait_ms;
          if (wait_range_ms > 0)
            min_wait_ms += rand() % wait_range_ms;
        }
        vtable_address = *(uint32_t *)(void *)soundtrack;
        return ((int (__thiscall *)(int, int))
            (uintptr_t)(vtable_address + 24))(soundtrack_address, min_wait_ms);
      }
    }
  } else {
    int repeats_remaining = *(int *)(uintptr_t)(current_node_address + 36);
    if (repeats_remaining <= 1) {
      if (repeats_remaining == 1)
        *(uint8_t *)(uintptr_t)(current_node_address + 8) = 1;
    } else {
      *(int *)(uintptr_t)(current_node_address + 36) = repeats_remaining - 1;
    }

    uint8_t random_threshold =
        *(uint8_t *)(uintptr_t)(current_node_address + 40);
    if (random_threshold == 100 || rand() % 100 <= random_threshold) {
      *(int *)(void *)(soundtrack + 88) = current_node_address;
      event_context = initialize_event_context(event_context_storage,
                                               soundtrack_address, 3);
      result = (int)play_or_update_soundtrack_sound(
          *(int *)(void *)(soundtrack + 88) + 12,
          *(float *)(void *)(soundtrack + 80), (int)event_context[0],
          (char *)(uintptr_t)event_context[1], 1);
      *(int *)(void *)(soundtrack + 52) = 0;
      return result;
    }
  }

  return result;
}
