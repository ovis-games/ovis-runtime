#include "ovis/runtime/list.h"

#include <assert.h>   // assert
#include <stdalign.h> // alignof
#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // memmove

#include "ovis/runtime/basic_types.h" // Int
#include "ovis/runtime/error.h"       // RETURN_ERROR
#include "ovis/runtime/type.h"        // type_stride, is_ptr_aligned, DestroyFunction
                                      //
static const struct TypeInfo* list_element_type(const struct TypeInfo* list_type) {
    assert(list_type);
    assert(list_type->generic_count == 1);
    assert(list_type->generics);
    assert(list_type->generics[0]);
    return list_type->generics[0];
}

static bool grow_list_to(const struct TypeInfo* list_type, List* list, int32_t new_capacity) {
    assert(list->capacity <= new_capacity);
    const struct TypeInfo* element_type = list_element_type(list_type);
    void* new_data = aligned_alloc(element_type->align, element_type->stride * new_capacity);
    assert(is_ptr_aligned(new_data, element_type->align));
    if (new_data == NULL) {
        RETURN_ERROR("out of memory");
    } else {
        // It's UB to pass NULL to memcpy (even if count == 0)
        if (list->data != NULL) {
            memcpy(new_data, list->data, element_type->stride * list->capacity);
        }
        free(list->data);
        list->data = new_data;
        list->capacity = new_capacity;
        return true;
    }
}

static bool grow_list(const struct TypeInfo* list_type, List* list) {
    // Use a growth rate of 1.5.
    const int32_t new_capacity = list->capacity > 1 ? list->capacity + list->capacity / 2 : 2;
    return grow_list_to(list_type, list, new_capacity);
}

static void* list_element_ptr(const struct TypeInfo* list_type, const List* list, int32_t index) {
    return offset_mutable_ptr(list->data, index * type_stride(list_element_type(list_type)));
}

// static void* list_element_mutable_ptr(const struct TypeInfo* list_type, List* list, int32_t index) {
//     return offset_mutable_ptr(list->data, index * type_stride(list_element_type(list_type)));
// }

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
    const struct TypeInfo* element_type = list_element_type(type_info);
    const intptr_t element_stride = type_stride(element_type);
    const List* src_list = src;

    void* data = malloc(src_list->size * element_stride);
    if (!data) {
      RETURN_ERROR("out of memory");
    }

    if (!clone_n(element_type, src_list->data, data, src_list->size)) {
      return false;
    }

    List* dst_list = dst;
    dst_list->data = data;
    dst_list->size = src_list->size;
    dst_list->capacity = src_list->size;
    return true;
}

GENERIC_INSTANTIATION_IMPL(TYPE(ovis, runtime, List)) {
    type->initialize = TYPE_INITIALIZE(TYPE(ovis, runtime, List));
    type->destroy = TYPE_DESTROY(TYPE(ovis, runtime, List));
    type->clone = TYPE_CLONE(TYPE(ovis, runtime, List));
    type->size = sizeof(List);
    type->align = alignof(List);
}

DECLARE_PROPERTY_GETTER(
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

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    get,
    PARAMETER(index, TYPE(ovis, runtime, Int)),
    GENERIC_RESULT(T)
) {
    if (*index < 0 || *index >= self->size) {
        RETURN_ERROR("index out of bounds");
    }

    const struct TypeInfo* element_type = list_element_type(type_info);
    void* element_ptr = list_element_ptr(type_info, self, *index);
    return element_type->clone(element_type, element_ptr, _output);
}

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    remove,
    PARAMETER(index, TYPE(ovis, runtime, Int))
) {
    void* element_to_remove = list_element_ptr(type_info, self, *index);
    const struct TypeInfo* element_type = list_element_type(type_info);
    element_type->destroy(element_type, element_to_remove);

    const int32_t elements_after_removed = self->size - *index - 1;
    const int32_t stride = type_stride(element_type);

    memmove(element_to_remove, offset_ptr(element_to_remove, stride), elements_after_removed * stride);
    self->size -= 1;

    return true;
}

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    clear
) {
    destroy_n(list_element_type(type_info), self->data, self->size);
    self->size = 0;
    return true;
}

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    append,
    PARAMETER(other, TYPE(ovis, runtime, List, GENERIC(T)))
) {
    const int32_t required_capacity = self->size + other->size;
    if (self->capacity < required_capacity) {
        if (!grow_list_to(type_info, self, required_capacity)) {
            return false;
        }
    }

    const struct TypeInfo* element_type = list_element_type(type_info);
    if (!clone_n(element_type, list_element_ptr(type_info, other, 0), list_end(type_info, self), other->size)) {
        return false;
    }
    self->size += other->size;

    return true;
}
