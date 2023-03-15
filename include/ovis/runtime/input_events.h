#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  TYPE(ovis, runtime, Vec2F) position;
  TYPE(ovis, runtime, Vec2F) delta;
} MouseMoveEvent;

DECLARE_TYPE(ovis, runtime, MouseMoveEvent);
TYPEDEF(MouseMoveEvent, TYPE(ovis, runtime, MouseMoveEvent));
EVENT(TYPE(ovis, runtime, MouseMoveEvent));

DECLARE_PROPERTY(TYPE(ovis, runtime, MouseMoveEvent), position, TYPE(ovis, runtime, Vec2F));
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseMoveEvent), delta, TYPE(ovis, runtime, Vec2F));

typedef struct {
  TYPE(ovis, runtime, Vec2F) position;
  TYPE(ovis, runtime, Int) button;
  TYPE(ovis, runtime, Bool) pressed;
} MouseButtonEvent;

DECLARE_TYPE(ovis, runtime, MouseButtonEvent);
TYPEDEF(MouseButtonEvent, TYPE(ovis, runtime, MouseButtonEvent));
EVENT(TYPE(ovis, runtime, MouseButtonEvent));

DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), position, TYPE(ovis, runtime, Vec2F));
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), button, TYPE(ovis, runtime, Int));
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), pressed, TYPE(ovis, runtime, Bool));

#ifdef __cplusplus
}
#endif
