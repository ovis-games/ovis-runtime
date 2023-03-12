#include "ovis/runtime/frame.h"
#include "ovis/runtime/resource.h"

#include <stdalign.h>

DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Frame));

SCENE_COMPONENT_IMPL(ovis, runtime, Frame);

TYPE_PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Frame), deltaTime) {
  *(float*)_output = ((mod__ovis__runtime__Frame*)object)->delta_time;
  return true;
}
