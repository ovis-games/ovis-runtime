#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  void* data;
  int32_t capacity;
  int32_t size;
} List;
TYPEDEF(List, TYPE(ovis, runtime, List));

DECLARE_GENERIC_TYPE(
    ovis, runtime, List,
    GENERIC_TYPE(T)
);

DECLARE_PROPERTY_GETTER(
    TYPE(ovis, runtime, List),
    length,
    TYPE(ovis, runtime, Int)
);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    add,
    GENERIC_PARAMETER(value, T)
);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    remove,
    PARAMETER(index, TYPE(ovis, runtime, Int))
);

// DECLARE_MUTABLE_MEMBER_FUNCTION(
//     TYPE(ovis, runtime, List),
//     clear
// );


// void mod__ovis__runtime__List_initialize(const struct TypeInfo* list_type, void* ptr);
// void mod__ovis__runtime__List_destroy(const struct TypeInfo* list_type, void* ptr);
// bool mod__ovis__runtime__List_clone(const struct TypeInfo* list_type, const void* src, void* dst);

// bool mod__ovis__runtime__List_m_add(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const void* value);
// bool mod__ovis__runtime__List_m_remove(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int* index);
// bool mod__ovis__runtime__List_m_swap(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const int* first_index, const int* second_index);

#ifdef __cplusplus
}
#endif
