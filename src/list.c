#include "ovis/runtime/list.h"

#include <assert.h> // assert
#include <string.h> // memmove
#include <stdlib.h> // malloc, realloc, free
#include <stdalign.h> // alignof

#include "ovis/runtime/type.h" // type_stride, is_ptr_aligned, DestroyFunction
#include "ovis/runtime/basic_types.h" // Int
#include "ovis/runtime/error.h" // RETURN_ERROR
                                //
static const struct TypeInfo* list_element_type(const struct TypeInfo* list_type) {
  assert(list_type);
  assert(list_type->generic_count == 1);
  assert(list_type->generics);
  assert(list_type->generics[0]);
  return list_type->generics[0];
}

static bool grow_list(const struct TypeInfo* list_type, List* list) {
  // Use a growth rate of 1.5.
  const int32_t new_capacity = list->capacity > 1 ? list->capacity + list->capacity / 2 : 2;
  void* new_data = realloc(list->data, new_capacity * type_stride(list_element_type(list_type)));
  if (new_data == NULL) {
    RETURN_ERROR("out of memory");
  }
  list->data = new_data;
  list->capacity = new_capacity;
  return true;
}

static void* list_element_ptr(const struct TypeInfo* list_type, List* list, int32_t index) {
  return offset_mutable_ptr(list->data, index * type_stride(list_element_type(list_type)));
}

static void* list_end(const struct TypeInfo* list_type, List* list) {
  return list_element_ptr(list_type, list, list->size);
}

TYPE_INITIALIZE_DECL(TYPE(ovis, runtime, List)) {
  List* list = ptr;
  list->data = NULL;
  list->capacity = 0;
  list->size = 0;
}

TYPE_DESTROY_DECL(TYPE(ovis, runtime, List)) {
  assert(ptr);
  assert(type);
  assert(is_ptr_aligned(ptr, type->align));

  List* list = ptr;
  assert(type->generics != NULL);
  const struct TypeInfo* element_type = list_element_type(type);
  assert(is_ptr_aligned(list->data, element_type->align));

  destroy_n(element_type, list->data, list->size);
  free(list->data);
}

TYPE_CLONE_DECL(TYPE(ovis, runtime, List)) {
  // const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
  // const intptr_t element_stride = type_stride(element_type);
  // const struct mod__ovis__runtime__List* src_list = src;

  // void* data = malloc(src_list->capacity * element_stride);
  // if (!data) {
  //   RETURN_ERROR("out of memory");
  // }

  // if (!clone_n(element_type, src_list->data, data, src_list->size)) {
  //   return false;
  // }

  // struct mod__ovis__runtime__List* dst_list = dst;
  // dst_list->data = data;
  // dst_list->size = src_list->size;
  // dst_list->capacity = src_list->capacity;
  // return true;
  return false;
}

GENERIC_INSTANTIATION_IMPL(TYPE(ovis, runtime, List)) {
  type->initialize = TYPE_INITIALIZE(TYPE(ovis, runtime, List));
  type->destroy = TYPE_DESTROY(TYPE(ovis, runtime, List));
  type->clone = TYPE_CLONE(TYPE(ovis, runtime, List));
  type->size = sizeof(List);
  type->align = alignof(List);
}


DECLARE_PROPERTY_TYPE_GETTER(
    TYPE(ovis, runtime, List),
    length,
    TYPE(ovis, runtime, Int)
) {
  *_output = object->size;
  return true;
}

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    add,
    GENERIC_PARAMETER(value, T)
) {
  if (self->size == self->capacity) {
    if (!grow_list(type_info, self)) {
      return false;
    }
  }

  const struct TypeInfo* element_type = list_element_type(type_info);
  if (!element_type->clone(element_type, value, list_end(type_info, self))) {
    RETURN_ERROR("failed to copy element");
  }

  self->size += 1;
  return true;
}


// bool mod__ovis__runtime__List_m_add(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const void* value) {
// }

// bool mod__ovis__runtime__List_m_remove(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int32_t* index) {
//   void* element_to_remove = list_element_ptr(list_type, list, *index);
//   const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
//   element_type->destroy(element_type, element_to_remove);

//   const int32_t elements_after_removed = list->size - *index - 1;
//   const int32_t stride = type_stride(element_type);

//   memmove(element_to_remove, offset_ptr(element_to_remove, stride), elements_after_removed * stride);
//   list->size -= 1;

//   return true;
// }

// bool mod__ovis__runtime__List_m_swap(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int32_t* first_index, const int32_t* second_index) {
//   const struct TypeInfo* element_type = mod__ovis__runtime__List_element_type(list_type);
//   uint8_t temp[element_type->size];
//   void* first_element = list_element_ptr(list_type, list, *first_index);
//   void* second_element = list_element_ptr(list_type, list, *second_index);
//   memcpy(temp, first_element, element_type->size);
//   memcpy(first_element, second_element, element_type->size);
//   memcpy(second_element, temp, element_type->size);
//   return true;
// }
