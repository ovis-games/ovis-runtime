#include "scene.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/frame.h"

#include <unordered_map>
#include <string>
#include <cassert>

std::unordered_map<std::string, const TypeInfo*> SCENE_COMPONENTS;

bool ovis_runtime_register_scene_component_type(const char* component_id, const struct TypeInfo* component_type) {
    return SCENE_COMPONENTS.insert(std::make_pair(component_id, component_type)).second;
}

bool ovis_runtime_deregister_scene_component_type(const char* component_id) {
  return SCENE_COMPONENTS.erase(component_id) == 1;
}

struct Scene* ovis_scene_create() {
  ovis_runtime_register_scene_component_type("ovis/runtime/Frame", &mod__ovis__runtime__Frame_type);
  return new Scene();
}

void ovis_scene_tick(struct Scene* scene, float delta_time) {
  mod__ovis__runtime__Frame* frame = (mod__ovis__runtime__Frame*)scene->scene_components_storage()->add("ovis/runtime/Frame");
  assert(frame);
  frame->delta_time = delta_time;
  scene->tick(delta_time);
}

void ovis_scene_destroy(struct Scene* scene) {
  delete scene;
}

void Scene::tick(float delta_time) {
  m_scheduler.run_jobs(this);
}

bool ovis_scene_iterate(struct Scene* scene, const char** component_ids, int component_ids_count, IterateCallback callback) {
  void* components[component_ids_count];
  for (int i = 0; i < component_ids_count; ++i) {
    components[i] = scene->scene_components_storage()->get(component_ids[i]);
    // The scene component does not exist so we can stop
    if (!components[i]) {
      return true;
    }
  }
  return callback(components);
}
