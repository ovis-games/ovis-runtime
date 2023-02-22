#include "ovis/runtime/frame.h"

#include <stdalign.h>

const struct TypeInfo mod__ovis__runtime__Frame_type = {
  sizeof(mod__ovis__runtime__Frame),
  alignof(mod__ovis__runtime__Frame),
  mod__ovis__runtime__Frame_initialize,
  mod__ovis__runtime__Frame_destroy,
  mod__ovis__runtime__Frame_clone,
  0, NULL,
};

void mod__ovis__runtime__Frame_initialize(const struct TypeInfo* type_info, void* ptr) {
  memset(ptr, 0, sizeof(mod__ovis__runtime__Frame));
}

void mod__ovis__runtime__Frame_destroy(const struct TypeInfo* type_info, void* ptr) {}

bool mod__ovis__runtime__Frame_clone(const struct TypeInfo* type_info, const void* src, void* dst) {
  memcpy(dst, src, sizeof(mod__ovis__runtime__Frame));
  return true;
}

bool mod__ovis__runtime__Frame_p_get_deltaTime(const struct TypeInfo* frame_type, const void* frame, void* delta_time) {
  *(mod__ovis__runtime__Float*)delta_time = ((mod__ovis__runtime__Frame*)frame)->delta_time;
  return true;
}
