#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

bool ovis_runtime_register_scene_component_type(const char* scene_component_id, const struct TypeInfo* component_type);
bool ovis_runtime_deregister_scene_component_type(const char* scene_component_id);

struct Scene;

struct Scene* ovis_scene_create();
void ovis_scene_destroy(struct Scene* scene);

void ovis_scene_tick(struct Scene* scene, float delta_time);

typedef bool(*IterateCallback)(void**);
bool ovis_scene_iterate(struct Scene* scene, const char** component_ids, int component_ids_count, IterateCallback callback);

#ifdef __cplusplus
}
#endif
