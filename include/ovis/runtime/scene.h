#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

void ovis_register_entity_component_type(struct TypeInfo* component_type);
void ovis_deregister_entity_component_type(struct TypeInfo* component_type);

struct Scene;

struct Scene* ovis_scene_create();
void ovis_scene_tick(struct Scene* scene, float delta_time);
void ovis_scene_destroy(struct Scene* scene);

#ifdef __cplusplus
}
#endif
