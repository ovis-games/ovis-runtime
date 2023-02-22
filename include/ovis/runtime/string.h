#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char* data;
  int32_t capacity;
  int32_t size;
} mod__ovis__runtime__String;

extern const struct TypeInfo mod__ovis__runtime__String_type;
void mod__ovis__runtime__String_initialize(const struct TypeInfo* string_type, void* ptr);
void mod__ovis__runtime__String_destroy(const struct TypeInfo* string_type, void* ptr);
bool mod__ovis__runtime__String_clone(const struct TypeInfo* string_type, const void* src, void* dst);

// This is a special function called by the compiler when constructing a string from a literal
void mod__ovis__runtime__String_initialize_from_literal(const struct TypeInfo* string_type, void* ptr, const char* literal, int32_t length);

bool mod__ovis__runtime__String_p_get_size(const struct TypeInfo* string_type, const void* string, void* size);

bool mod__ovis__runtime__int2Str(const void* integer, void* str);
bool mod__ovis__runtime__float2Str(const void* number, void* str);

#ifdef __cplusplus
}
#endif
