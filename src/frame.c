#include "ovis/runtime/frame.h"

#include <stdalign.h>

const struct TypeInfo ovis_runtime_Frame_type = {
  sizeof(ovis_runtime_Frame),
  alignof(ovis_runtime_Frame),
  ovis_runtime_Frame_initialize,
  ovis_runtime_Frame_destroy,
  ovis_runtime_Frame_clone,
  0, NULL,
};

void ovis_runtime_Frame_initialize(const struct TypeInfo* type_info, void* ptr) {
  memset(ptr, 0, sizeof(ovis_runtime_Frame));
}

void ovis_runtime_Frame_destroy(const struct TypeInfo* type_info, void* ptr) {}

bool ovis_runtime_Frame_clone(const struct TypeInfo* type_info, const void* src, void* dst) {
  memcpy(dst, src, sizeof(ovis_runtime_Frame));
  return true;
}

bool ovis_runtime_Frame_p_get_deltaTime(const struct TypeInfo* frame_type, const void* frame, void* delta_time) {
  *(ovis_runtime_Float*)delta_time = ((ovis_runtime_Frame*)frame)->delta_time;
  return true;
}
