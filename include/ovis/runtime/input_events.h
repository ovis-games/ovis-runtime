#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  TYPE(ovis, runtime, Vec2F) screen_space_position;
  TYPE(ovis, runtime, Vec2F) relative_screen_space_position;
} MouseMoveEvent;

DECLARE_TYPE(ovis, runtime, MouseMoveEvent);
TYPEDEF(MouseMoveEvent, TYPE(ovis, runtime, MouseMoveEvent));
EVENT(TYPE(ovis, runtime, MouseMoveEvent));

DECLARE_PROPERTY_TYPE_GETTER(TYPE(ovis, runtime, MouseMoveEvent), screenSpacePosition, TYPE(ovis, runtime, Vec2F));
DECLARE_PROPERTY_TYPE_GETTER(TYPE(ovis, runtime, MouseMoveEvent), relativeScreenSpacePosition, TYPE(ovis, runtime, Vec2F));

#ifdef __cplusplus
}
#endif
