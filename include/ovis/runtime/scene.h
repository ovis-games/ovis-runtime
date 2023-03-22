#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/resource.h"
#include "ovis/runtime/symbols.h"
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Scene;

struct Scene* ovis_scene_create();
void ovis_scene_destroy(struct Scene* scene);

void ovis_scene_tick(struct Scene* scene, float delta_time);
void* ovis_scene_get_scene_component(struct Scene* scene, ResourceId resource_id);

typedef bool (*IterateCallback)(void**, void**);
bool ovis_scene_iterate(struct Scene* scene, int32_t input_component_ids_count, const int32_t* input_component_ids, int32_t output_component_ids_count, const int32_t* output_component_ids, IterateCallback callback);

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, DeltaTime), TYPE(ovis, runtime, Float));
SCENE_COMPONENT(TYPE(ovis, runtime, DeltaTime));

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, GameTime), TYPE(ovis, runtime, Float));
SCENE_COMPONENT(TYPE(ovis, runtime, GameTime));

#ifdef __cplusplus
}
#endif
