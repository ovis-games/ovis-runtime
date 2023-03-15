#pragma once

#include "ovis/runtime/symbols.h"
#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct String {
  char* data;
  int32_t capacity;
  int32_t size;
};
TYPEDEF(struct String, TYPE(ovis, runtime, String));

DECLARE_TYPE(ovis, runtime, String);

// This is a special function called by the compiler when constructing a string from a literal
void mod__ovis__runtime__String_initialize_from_literal(const struct TypeInfo* string_type, void* ptr, const char* literal, int32_t length);

DECLARE_PROPERTY_GETTER(TYPE(ovis, runtime, String), size, TYPE(ovis, runtime, Int));

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, String), fromBool,
    PARAMETER(number, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, String))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, String), fromInt,
    PARAMETER(number, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, String))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, String), fromFloat,
    PARAMETER(number, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, String))
);

#ifdef __cplusplus
}
#endif
