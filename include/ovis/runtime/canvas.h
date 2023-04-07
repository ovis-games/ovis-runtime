#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/scene.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Canvas;

struct Canvas* ovis_canvas_create(struct Scene* scene, const char* canvas_id);
void ovis_canvas_destroy(struct Canvas* canvas);

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ClearColor), TYPE(ovis, runtime, Color));
DECLARE_RESOURCE(ViewportComponent, TYPE(ovis, runtime, ClearColor));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ViewportDimensions), TYPE(ovis, runtime, Vec2F));
DECLARE_RESOURCE(ViewportComponent, TYPE(ovis, runtime, ViewportDimensions));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ProjectionMatrix), TYPE(ovis, runtime, Mat4x4F));
DECLARE_RESOURCE(ViewportComponent, TYPE(ovis, runtime, ProjectionMatrix));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ViewMatrix), TYPE(ovis, runtime, Mat3x4F));
DECLARE_RESOURCE(ViewportComponent, TYPE(ovis, runtime, ViewMatrix));

typedef struct Framebuffer {
    int dummy;
} Framebuffer;
TYPEDEF(Framebuffer, TYPE(ovis, runtime, Framebuffer));

// The framebuffer that contains the content of a viewport.
DECLARE_TYPE(ovis, runtime, Framebuffer);
DECLARE_RESOURCE(ViewportComponent, TYPE(ovis, runtime, Framebuffer));

#ifdef __cplusplus
}
#endif
