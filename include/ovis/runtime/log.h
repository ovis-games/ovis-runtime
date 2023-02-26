#pragma once

#include <stdbool.h>

#include "ovis/runtime/string.h"
#include "ovis/runtime/symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTION(FUNCTION(ovis, runtime, log), PARAMETER(message, TYPE(ovis, runtime, String)));

#ifdef __cplusplus
}
#endif
