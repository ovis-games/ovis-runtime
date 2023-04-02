#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* data;
    int32_t capacity;
    int32_t size;
} List;
TYPEDEF(List, TYPE(ovis, runtime, List));

// A list stores a number of elements of a single type.
DECLARE_GENERIC_TYPE(
    ovis, runtime, List,
    GENERIC_TYPE(T)
);

// Reflects the number of items currently stored in the list.
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
    get,
    PARAMETER(index, TYPE(ovis, runtime, Int)),
    GENERIC_RESULT(T)
);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    remove,
    PARAMETER(index, TYPE(ovis, runtime, Int))
);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    clear
);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, List),
    append,
    PARAMETER(list, TYPE(ovis, runtime, List, GENERIC(T)))
);

#ifdef __cplusplus
}
#endif
