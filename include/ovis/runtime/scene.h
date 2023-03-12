#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Scene;

struct Scene* ovis_scene_create();
void ovis_scene_destroy(struct Scene* scene);

void ovis_scene_tick(struct Scene* scene, float delta_time);

typedef bool(*IterateCallback)(void**);
bool ovis_scene_iterate(struct Scene* scene, const int32_t* component_ids, int component_ids_count, IterateCallback callback);

#ifdef __cplusplus
}
#endif
