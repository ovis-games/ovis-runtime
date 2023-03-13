#pragma once

#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Canvas;

struct Canvas* ovis_canvas_create(struct Scene* scene, const char* canvas_id);
void ovis_canvas_destroy(struct Canvas* canvas);

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, ClearColor), TYPE(ovis, runtime, Vec4F));
SCENE_COMPONENT(TYPE(ovis, runtime, ClearColor));


#ifdef __cplusplus
}
#endif
