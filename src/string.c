#include "ovis/runtime/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

TYPE_INFO_IMPL(TYPE(ovis, runtime, String));

TYPE_INITIALIZE_IMPL(TYPE(ovis, runtime, String));

TYPE_DESTROY_DECL(TYPE(ovis, runtime, String)) {
  free(((mod__ovis__runtime__String*)ptr)->data);
}

TYPE_CLONE_DECL(TYPE(ovis, runtime, String)) {
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


PROPERTY_GETTER_IMPL(TYPE(ovis, runtime, String), size, TYPE(ovis, runtime, Int))

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, String), fromBool,
    PARAMETER(boolean, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, String))
) {
  mod__ovis__runtime__String_initialize_from_literal(&mod__ovis__runtime__String_type, _output, *boolean ? "true" : "false", *boolean ? 4 : 5);
  return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, String), fromInt,
    PARAMETER(number, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, String))
) {
  int string_length = snprintf(NULL, 0, "%d", *number);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%d", *number);
  mod__ovis__runtime__String_initialize_from_literal(&mod__ovis__runtime__String_type, _output, string, string_length);
  return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, String), fromFloat,
    PARAMETER(number, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, String))
) {
  int string_length = snprintf(NULL, 0, "%f", *number);
  char string[string_length + 1];
  snprintf(string, string_length + 1, "%f", *number);
  mod__ovis__runtime__String_initialize_from_literal(&mod__ovis__runtime__String_type, _output, string, string_length);
  return true;
}
