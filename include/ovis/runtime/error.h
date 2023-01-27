#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

static inline bool error(const char* string) { return false; }
#define RETURN_ERROR(error_string) return false


#ifdef __cplusplus
}
#endif
