#include "scene.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/frame.h"
#include "ovis/runtime/resource.h"
#include "resource.hpp"

#include <unordered_map>
#include <string>
#include <cassert>

struct Scene* ovis_scene_create() {
  return new Scene();
}

void ovis_scene_tick(struct Scene* scene, float delta_time) {
  scene->tick(delta_time);
}

void ovis_scene_destroy(struct Scene* scene) {
  delete scene;
}

Scene::Scene() {
  m_component_storages.resize(RESOURCES.size());

  for (const auto& resource : RESOURCES) {
    switch (resource.kind) {
    case RESOURCE_KIND_SCENE_COMPONENT:
      m_component_storages[ResourceIdType::index(resource.id)] = std::make_unique<SceneComponentStorage>(&resource);
      break;

    case RESOURCE_KIND_VIEWPORT_COMPONENT:
      assert(false);
      break;
    }
  }
}

void Scene::tick(float delta_time) {
  assert(get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, Frame))));
  auto frame = (TYPE_PTR(TYPE(ovis, runtime, Frame)))get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, Frame)))->emplace();
  assert(frame);
  frame->delta_time = delta_time;
  m_scheduler.run_jobs(this);
}

bool ovis_scene_iterate(struct Scene* scene, const int32_t* component_ids, int component_ids_count, IterateCallback callback) {
  void* components[component_ids_count];
  for (int i = 0; i < component_ids_count; ++i) {
    assert(scene->get_scene_component_storage(component_ids[i]));
    components[i] = scene->get_scene_component_storage(component_ids[i])->get();
    // The scene component does not exist so we can stop
    if (!components[i]) {
      return true;
    }
  }
  return callback(components);
}
