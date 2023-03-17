#pragma once

#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Canvas;

struct Canvas* ovis_canvas_create(struct Scene* scene, const char* canvas_id);
void ovis_canvas_destroy(struct Canvas* canvas);

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ClearColor), TYPE(ovis, runtime, Vec4F));
VIEWPORT_COMPONENT(TYPE(ovis, runtime, ClearColor));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ViewportDimensions), TYPE(ovis, runtime, Vec2F));
VIEWPORT_COMPONENT(TYPE(ovis, runtime, ViewportDimensions));

#ifdef __cplusplus
}
#endif
