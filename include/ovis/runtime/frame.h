#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Frame {
  float delta_time;
};
TYPEDEF(struct Frame, TYPE(ovis, runtime, Frame));

DECLARE_TYPE(ovis, runtime, Frame);
SCENE_COMPONENT(TYPE(ovis, runtime, Frame));

DECLARE_PROPERTY_TYPE_GETTER(TYPE(ovis, runtime, Frame), deltaTime, TYPE(ovis, runtime, Float));

#ifdef __cplusplus
}
#endif
