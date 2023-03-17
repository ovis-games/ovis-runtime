#include "ovis/runtime/log.h"

#include <stdio.h>

FUNCTION_IMPL(FUNCTION(ovis, runtime, log), PARAMETER(message, TYPE(ovis, runtime, String))) {
    printf("%.*s\n", message->size, message->data);
    return true;
}
