#include "ovis/runtime/list.h"

#include <assert.h> // assert
#include <string.h> // memmove
#include <stdlib.h> // malloc, realloc, free
#include <stdalign.h> // alignof

#include "ovis/runtime/type.h" // type_stride, is_ptr_aligned, DestroyFunction
#include "ovis/runtime/basic_types.h" // Int
#include "ovis/runtime/error.h" // RETURN_ERROR

static const struct TypeInfo* mod__ovis__runtime__List_element_type(const struct TypeInfo* list_type) {
  assert(list_type);
  assert(list_type->generic_count == 1);
  assert(list_type->generics);
  assert(list_type->generics[0]);
  return list_type->generics[0];
}

static bool mod__ovis__runtime__List_grow(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list) {
  // Use a growth rate of 1.5.
  const int32_t new_capacity = list->capacity > 1 ? list->capacity + list->capacity / 2 : 2;
  void* new_data = realloc(list->data, new_capacity * type_stride(mod__ovis__runtime__List_element_type(list_type)));
  if (new_data == NULL) {
    RETURN_ERROR("out of memory");
  }
  list->data = new_data;
  list->capacity = new_capacity;
  return true;
}

static void* list_element_ptr(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, int32_t index) {
  return offset_mutable_ptr(list->data, index * type_stride(mod__ovis__runtime__List_element_type(list_type)));
}

static void* list_end(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list) {
  return list_element_ptr(list_type, list, list->size);
}

static void mod__ovis__runtime__List_instantiate_callback(struct TypeInfo* list_type) {
  list_type->initialize = mod__ovis__runtime__List_initialize;
  list_type->clone = mod__ovis__runtime__List_clone;
  list_type->destroy = mod__ovis__runtime__List_destroy;
  list_type->size = sizeof(struct mod__ovis__runtime__List);
  list_type->align = alignof(struct mod__ovis__runtime__List);
}

GenericTypeInstantiationList mod__ovis__runtime__List_instantiations;

const struct TypeInfo* mod__ovis__runtime__List_instantiate(const struct TypeInfo* T) {
  Generic generic[] = { T };
  return instantiate_generic_type(&mod__ovis__runtime__List_instantiations, 1, generic, mod__ovis__runtime__List_instantiate_callback);
}

void mod__ovis__runtime__List_release(const struct TypeInfo* list_type) {
  release_generic_type_instantiation(&mod__ovis__runtime__List_instantiations, list_type);
}

void mod__ovis__runtime__List_initialize(const struct TypeInfo* list_type, void* ptr) {
  struct mod__ovis__runtime__List* list = ptr;
  list->data = NULL;
  list->capacity = 0;
  list->size = 0;
}

bool mod__ovis__runtime__List_clone(const struct TypeInfo* list_type, const void* src, void* dst) {
  const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  const intptr_t element_stride = type_stride(element_type);
  const struct mod__ovis__runtime__List* src_list = src;

  void* data = malloc(src_list->capacity * element_stride);
  if (!data) {
    RETURN_ERROR("out of memory");
  }

  if (!clone_n(element_type, src_list->data, data, src_list->size)) {
    return false;
  }

  struct mod__ovis__runtime__List* dst_list = dst;
  dst_list->data = data;
  dst_list->size = src_list->size;
  dst_list->capacity = src_list->capacity;
  return true;
}

void mod__ovis__runtime__List_destroy(const struct TypeInfo* list_type, void* ptr) {
  assert(ptr);
  assert(list_type);
  assert(is_ptr_aligned(ptr, list_type->align));

  struct mod__ovis__runtime__List* list = ptr;

  assert(list_type->generics != NULL);
  const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  // assert(is_ptr_aligned(list->data, element_type->align));

  // destroy_n(element_type, list->data, list->size);
  // free(list->data);
}

bool mod__ovis__runtime__List_m_add(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const void* value) {
  if (list->size == list->capacity) {
    if (!mod__ovis__runtime__List_grow(list_type, list)) {
      return false;
    }
  }

  const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  if (!element_type->clone(element_type, value, list_end(list_type, list))) {
    RETURN_ERROR("failed to copy element");
  }

  list->size += 1;
  return true;
}

bool mod__ovis__runtime__List_m_remove(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int32_t* index) {
  void* element_to_remove = list_element_ptr(list_type, list, *index);
  const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  element_type->destroy(element_type, element_to_remove);

  const int32_t elements_after_removed = list->size - *index - 1;
  const int32_t stride = type_stride(element_type);

  memmove(element_to_remove, offset_ptr(element_to_remove, stride), elements_after_removed * stride);
  list->size -= 1;

  return true;
}

bool mod__ovis__runtime__List_m_swap(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int32_t* first_index, const int32_t* second_index) {
  const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  uint8_t temp[element_type->size];
  void* first_element = list_element_ptr(list_type, list, *first_index);
  void* second_element = list_element_ptr(list_type, list, *second_index);
  memcpy(temp, first_element, element_type->size);
  memcpy(first_element, second_element, element_type->size);
  memcpy(second_element, temp, element_type->size);
  return true;
}
