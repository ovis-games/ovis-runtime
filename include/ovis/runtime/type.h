#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "symbols.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct TypeInfo;
typedef void (*InitializeFunction)(const struct TypeInfo*, void*);
typedef void (*DestroyFunction)(const struct TypeInfo*, void*);
typedef bool (*CloneFunction)(const struct TypeInfo*, const void*, void*);

typedef const struct TypeInfo* Generic;

struct TypeInfo {
  intptr_t size;
  intptr_t align;
  intptr_t stride;
  InitializeFunction initialize;
  DestroyFunction destroy;
  CloneFunction clone;
  intptr_t generic_count;
  Generic* generics;
  const char* name;
};

struct GenericTypeInstantiation {
  struct GenericTypeInstantiation* next;
  struct GenericTypeInstantiation* previous;
  intptr_t reference_count;
  struct TypeInfo info;
};

typedef struct GenericTypeInstantiation* GenericTypeInstantiationList;
typedef void(*GenericTypeInstantiationCallback)(struct TypeInfo* out);
struct TypeInfo* instantiate_generic_type(GenericTypeInstantiationList* instantiation_list, intptr_t generic_count, const Generic* generics, GenericTypeInstantiationCallback instantiate);
void release_generic_type_instantiation(GenericTypeInstantiationList* instantiation_list, const struct TypeInfo* type);

static inline intptr_t round_up_to_alignment(uintptr_t value, uintptr_t align) {
  return value + (align - (value & (align - 1)));
}

static inline intptr_t type_stride(const struct TypeInfo* type_info) {
  return round_up_to_alignment(type_info->size, type_info->align);
}

static inline bool is_ptr_aligned(const void* ptr, intptr_t align) {
  return (((intptr_t)ptr) & (align - 1)) == 0;
}

static inline const void* offset_ptr(const void* ptr, intptr_t offset) {
  return (const void*)(((intptr_t)ptr) + offset);
}

static inline void* offset_mutable_ptr(void* ptr, intptr_t offset) {
  return (void*)(((intptr_t)ptr) + offset);
}

static inline void initialize_n(const struct TypeInfo* type, void* dst, intptr_t count) {
  const intptr_t stride = type_stride(type);
  const InitializeFunction initialize = type->initialize;
  for (intptr_t i = 0; i < count; ++i) {
    initialize(type, offset_mutable_ptr(dst, i * stride));
  }
}

static inline void destroy_n(const struct TypeInfo* type, void* dst, intptr_t count) {
  const intptr_t stride = type_stride(type);
  const DestroyFunction destroy = type->destroy;
  for (intptr_t i = 0; i < count; ++i) {
    destroy(type, offset_mutable_ptr(dst, i * stride));
  }
}

static inline bool clone_n(const struct TypeInfo* type, const void* src, void* dst, intptr_t count) {
  const intptr_t stride = type_stride(type);
  const CloneFunction clone = type->clone;
  for (intptr_t i = 0; i < count; ++i) {
    if (!clone(type, offset_ptr(src, i * stride), offset_mutable_ptr(dst, i * stride))) {
      // Destroy every element that has already been cloned
      destroy_n(type, dst, i);
      return false;
    }
  }

  return true;
}

// static inline intptr_t max_align(const struct TypeInfo** types) {
//   const struct TypeInfo** type = types;

//   intptr_t max_align = 1;
//   while (*type) {
//     if ((*type)->align > max_align) {
//       max_align = (*type)->align;
//     }
//     ++type;
//   }

//   return max_align;
// }

static inline intptr_t size(const struct TypeInfo** types) {
  const struct TypeInfo** type = types;

  intptr_t size = 0;
  intptr_t max_align = 1;
  while (*type) {
    if ((*type)->align > max_align) {
      max_align = (*type)->align;
    }
    size = round_up_to_alignment(size, (*type)->align);
    size += (*type)->size;
    ++type;
  }
  size = round_up_to_alignment(size, max_align);

  return size;
}

// TODO: figure out alignment
#define push_stack_var(type_ptr, name, type)                                   \
  {                                                                            \
    uint8_t var_##name##_buffer[type_ptr->size];                               \
    type *name = (type*)var_##name##_buffer;                                   \
    type_ptr->initialize(type_ptr, name)

#define pop_stack_var(name, type_ptr)                                          \
    type_ptr->destroy(type_ptr, name);                                         \
  }

#ifdef __cplusplus
}
#endif
