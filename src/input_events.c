#include "ovis/runtime/input_events.h"
#include "ovis/runtime/resource.h"
#include "ovis/runtime/symbols.h"
#include <stdalign.h>

DEFINE_BASIC_TYPE(ovis, runtime, MouseMoveEvent);
RESOURCE_IMPL(ovis, runtime, MouseMoveEvent, RESOURCE_KIND_EVENT);

PROPERTY_IMPL(TYPE(ovis, runtime, MouseMoveEvent), position, TYPE(ovis, runtime, Vec2F));
PROPERTY_IMPL(TYPE(ovis, runtime, MouseMoveEvent), delta, TYPE(ovis, runtime, Vec2F));

DEFINE_BASIC_TYPE(ovis, runtime, MouseButtonEvent);
RESOURCE_IMPL(ovis, runtime, MouseButtonEvent, RESOURCE_KIND_EVENT);

PROPERTY_IMPL(TYPE(ovis, runtime, MouseButtonEvent), position, TYPE(ovis, runtime, Vec2F));
PROPERTY_IMPL(TYPE(ovis, runtime, MouseButtonEvent), button, TYPE(ovis, runtime, Int));
PROPERTY_IMPL(TYPE(ovis, runtime, MouseButtonEvent), pressed, TYPE(ovis, runtime, Bool));
