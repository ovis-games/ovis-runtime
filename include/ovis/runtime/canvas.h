#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/scene.h"

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

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ProjectionMatrix), TYPE(ovis, runtime, Mat4x4F));
VIEWPORT_COMPONENT(TYPE(ovis, runtime, ProjectionMatrix));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ViewMatrix), TYPE(ovis, runtime, Mat4x4F));
VIEWPORT_COMPONENT(TYPE(ovis, runtime, ViewMatrix));


#ifdef __cplusplus
}
#endif
