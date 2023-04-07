#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/type.h"

#ifdef __cplusplus
extern "C" {
#endif

// A continous storage manages
typedef struct {
    void* data;
    int32_t capacity;
} ContinuousStorage;

#ifdef __cplusplus
}
#endif
