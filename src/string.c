#include "ovis/runtime/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

const struct TypeInfo mod__ovis__runtime__String_type = {
  sizeof(mod__ovis__runtime__String),
  alignof(mod__ovis__runtime__String),
  mod__ovis__runtime__String_initialize,
  mod__ovis__runtime__String_destroy,
  mod__ovis__runtime__String_clone,
  0, NULL,
};

void mod__ovis__runtime__String_initialize(const struct TypeInfo* type_info, void* ptr) {
  memset(ptr, 0, sizeof(mod__ovis__runtime__String));
}

void mod__ovis__runtime__String_destroy(const struct TypeInfo* type_info, void* ptr) {
  free(((mod__ovis__runtime__String*)ptr)->data);
}

bool mod__ovis__runtime__String_clone(const struct TypeInfo* type_info, const void* src, void* dst) {
  const mod__ovis__runtime__String* src_string = src;
  mod__ovis__runtime__String* dst_string = dst;

  // We only allocated the necessary amount (TODO: should we?)
  dst_string->data = malloc(src_string->size);
  dst_string->capacity = src_string->size;
  dst_string->size = src_string->size;
  memcpy(dst_string->data, src_string->data, src_string->size);

  return true;
}

void mod__ovis__runtime__String_initialize_from_literal(const struct TypeInfo* string_type, void* ptr, const char* literal, int32_t length) {
  mod__ovis__runtime__String* string = ptr;
  string->data = malloc(length);
  string->size = length;
  string->capacity = length;
  memcpy(string->data, literal, length);
}

bool mod__ovis__runtime__String_p_get_size(const struct TypeInfo* string_type, const void* string, void* size) {
  return mod__ovis__runtime__Int_clone(&mod__ovis__runtime__Int_type, &((const mod__ovis__runtime__String*)string)->size, size);
}

bool mod__ovis__runtime__int2Str(const void* input, void* str) {
  const int* integer = input;
  int string_length = snprintf(NULL, 0, "%d", *integer);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%d", *integer);
  mod__ovis__runtime__String_initialize_from_literal(&mod__ovis__runtime__String_type, str, string, string_length);
  return true;
}

bool mod__ovis__runtime__float2Str(const void* number, void* str) {
  const float* num = number;
  int string_length = snprintf(NULL, 0, "%f", *num);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%f", *num);
  mod__ovis__runtime__String_initialize_from_literal(&mod__ovis__runtime__String_type, str, string, string_length);
  return true;
}
