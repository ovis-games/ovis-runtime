#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  mod__ovis__runtime__Float delta_time;
} mod__ovis__runtime__Frame;

extern const struct TypeInfo mod__ovis__runtime__Frame_type;
void mod__ovis__runtime__Frame_initialize(const struct TypeInfo* string_type, void* ptr);
void mod__ovis__runtime__Frame_destroy(const struct TypeInfo* string_type, void* ptr);
bool mod__ovis__runtime__Frame_clone(const struct TypeInfo* string_type, const void* src, void* dst);

bool mod__ovis__runtime__Frame_p_get_deltaTime(const struct TypeInfo* string_type, const void* frame, void* delta_time);

#ifdef __cplusplus
}
#endif
