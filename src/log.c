#include "ovis/runtime/log.h"

#include <stdio.h>

bool mod__ovis__runtime__log(const void* message) {
  const mod__ovis__runtime__String* message_string = message;
  printf("%.*s\n", message_string->size, message_string->data);
  return true;
}
