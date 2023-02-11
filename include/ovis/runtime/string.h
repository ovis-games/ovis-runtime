#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ovis_runtime_String {
  char* data;
  int32_t capacity;
  int32_t size;
};

extern const struct TypeInfo ovis_runtime_String_type;
void ovis_runtime_String_initialize(const struct TypeInfo* string_type, void* ptr);
void ovis_runtime_String_destroy(const struct TypeInfo* string_type, void* ptr);
bool ovis_runtime_String_clone(const struct TypeInfo* string_type, const void* src, void* dst);

// This is a special function called by the compiler when constructing a string from a literal
void ovis_runtime_String_initialize_from_literal(const struct TypeInfo* string_type, void* ptr, const char* literal, int32_t length);

bool ovis_runtime_String_p_get_size(const struct TypeInfo* string_type, const void* string, void* size);

#ifdef __cplusplus
}
#endif
