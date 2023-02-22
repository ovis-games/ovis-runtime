#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  ovis_runtime_Float delta_time;
} ovis_runtime_Frame;

extern const struct TypeInfo ovis_runtime_Frame_type;
void ovis_runtime_Frame_initialize(const struct TypeInfo* string_type, void* ptr);
void ovis_runtime_Frame_destroy(const struct TypeInfo* string_type, void* ptr);
bool ovis_runtime_Frame_clone(const struct TypeInfo* string_type, const void* src, void* dst);

bool ovis_runtime_Frame_p_get_deltaTime(const struct TypeInfo* string_type, const void* frame, void* delta_time);

#ifdef __cplusplus
}
#endif
