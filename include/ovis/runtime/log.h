#pragma once

#include <stdbool.h>

#include "ovis/runtime/string.h"

#ifdef __cplusplus
extern "C" {
#endif

bool ovis_runtime_log(const void* message);

#ifdef __cplusplus
}
#endif
