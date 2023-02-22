#include "ovis/runtime/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

const struct TypeInfo ovis_runtime_String_type = {
  sizeof(ovis_runtime_String),
  alignof(ovis_runtime_String),
  ovis_runtime_String_initialize,
  ovis_runtime_String_destroy,
  ovis_runtime_String_clone,
  0, NULL,
};

void ovis_runtime_String_initialize(const struct TypeInfo* type_info, void* ptr) {
  memset(ptr, 0, sizeof(ovis_runtime_String));
}

void ovis_runtime_String_destroy(const struct TypeInfo* type_info, void* ptr) {
  free(((ovis_runtime_String*)ptr)->data);
}

bool ovis_runtime_String_clone(const struct TypeInfo* type_info, const void* src, void* dst) {
  const ovis_runtime_String* src_string = src;
  ovis_runtime_String* dst_string = dst;

  // We only allocated the necessary amount (TODO: should we?)
  dst_string->data = malloc(src_string->size);
  dst_string->capacity = src_string->size;
  dst_string->size = src_string->size;
  memcpy(dst_string->data, src_string->data, src_string->size);

  return true;
}

void ovis_runtime_String_initialize_from_literal(const struct TypeInfo* string_type, void* ptr, const char* literal, int32_t length) {
  ovis_runtime_String* string = ptr;
  string->data = malloc(length);
  string->size = length;
  string->capacity = length;
  memcpy(string->data, literal, length);
}

bool ovis_runtime_String_p_get_size(const struct TypeInfo* string_type, const void* string, void* size) {
  return ovis_runtime_Int_clone(&ovis_runtime_Int_type, &((const ovis_runtime_String*)string)->size, size);
}

bool ovis_runtime_int2Str(const void* input, void* str) {
  const int* integer = input;
  int string_length = snprintf(NULL, 0, "%d", *integer);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%d", *integer);
  ovis_runtime_String_initialize_from_literal(&ovis_runtime_String_type, str, string, string_length);
  return true;
}

bool ovis_runtime_float2Str(const void* number, void* str) {
  const float* num = number;
  int string_length = snprintf(NULL, 0, "%f", *num);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%f", *num);
  ovis_runtime_String_initialize_from_literal(&ovis_runtime_String_type, str, string, string_length);
  return true;
}
