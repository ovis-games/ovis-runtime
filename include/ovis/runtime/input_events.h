#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    TYPE(ovis, runtime, Vec2F)
    position;

    TYPE(ovis, runtime, Vec2F)
    delta;
} MouseMoveEvent;

// An event that is emitted whenever the mouse moves.
DECLARE_TYPE(ovis, runtime, MouseMoveEvent);
TYPEDEF(MouseMoveEvent, TYPE(ovis, runtime, MouseMoveEvent));
EVENT(TYPE(ovis, runtime, MouseMoveEvent));

// The current mouse position in screen space coordinates.
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseMoveEvent), position, TYPE(ovis, runtime, Vec2F));
// The delta to the previous mouse position in screen space coordinates.
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseMoveEvent), delta, TYPE(ovis, runtime, Vec2F));

typedef struct {
    TYPE(ovis, runtime, Vec2F)
    position;

    TYPE(ovis, runtime, Int)
    button;

    TYPE(ovis, runtime, Bool)
    pressed;
} MouseButtonEvent;

// An event that is emitted whenever a mouse button is pressed or released.
DECLARE_TYPE(ovis, runtime, MouseButtonEvent);
TYPEDEF(MouseButtonEvent, TYPE(ovis, runtime, MouseButtonEvent));
EVENT(TYPE(ovis, runtime, MouseButtonEvent));

// The current mouse position in screen space coordinates.
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), position, TYPE(ovis, runtime, Vec2F));
// The button that was pressed/release.
// 0: main button (usually left).
// 1: auxiliary button (usually middle/mouse wheel).
// 2: secondary button (usually right).
// 3: forth button (usually browser back).
// 4: fifth button (usually browser forward).
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), button, TYPE(ovis, runtime, Int));
// True if the button was pressed, false if it was released.
DECLARE_PROPERTY(TYPE(ovis, runtime, MouseButtonEvent), pressed, TYPE(ovis, runtime, Bool));

#ifdef __cplusplus
}
#endif
