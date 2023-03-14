#include "ovis/runtime/input_events.h"
#include "ovis/runtime/resource.h"
#include "ovis/runtime/symbols.h"
#include <stdalign.h>

DEFINE_BASIC_TYPE(TYPE(ovis, runtime, MouseMoveEvent));

RESOURCE_IMPL(ovis, runtime, MouseMoveEvent, RESOURCE_KIND_EVENT);

TYPE_PROPERTY_GETTER_DECL(TYPE(ovis, runtime, MouseMoveEvent), screenSpacePosition, TYPE(ovis, runtime, Vec2F)) {
  return CLONE(TYPE(ovis, runtime, Vec2F), object->screen_space_position, _output);
}

TYPE_PROPERTY_GETTER_DECL(TYPE(ovis, runtime, MouseMoveEvent), relativeScreenSpacePosition, TYPE(ovis, runtime, Vec2F)) {
  return CLONE(TYPE(ovis, runtime, Vec2F), object->relative_screen_space_position, _output);
}
