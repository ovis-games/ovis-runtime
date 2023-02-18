#include "ovis/runtime/log.h"

#include <stdio.h>

bool ovis_runtime_log(const void* message) {
  const ovis_runtime_String* message_string = message;
  printf("%.*s\n", message_string->size, message_string->data);
  return true;
}
