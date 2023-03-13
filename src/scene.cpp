#include "scene.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/resource.h"
#include "resource.hpp"

#include <alloca.h>
#include <unordered_map>
#include <string>
#include <cassert>

struct Scene* ovis_scene_create() {
  return new Scene();
}

void ovis_scene_tick(struct Scene* scene, float delta_time) {
  scene->tick(delta_time);
}

void* ovis_scene_get_scene_component(struct Scene* scene, ResourceId resource_id) {
  auto storage = scene->get_scene_component_storage(resource_id);
  return storage != nullptr ? storage->get() : nullptr;
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
  assert(get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, DeltaTime))));
  get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, DeltaTime)))->emplace(&delta_time);

  m_game_time += delta_time * (1 / 1000.0f);
  assert(get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, GameTime))));
  get_scene_component_storage(RESOURCE_ID(TYPE(ovis, runtime, GameTime)))->emplace(&m_game_time);

  m_scheduler.run_jobs(this);
}

bool ovis_scene_iterate(struct Scene* scene,
    int32_t input_component_ids_count, const int32_t* input_component_ids,
    int32_t output_component_ids_count, const int32_t* output_component_ids,
    IterateCallback callback
) {
  void* input_components[input_component_ids_count];
  for (int i = 0; i < input_component_ids_count; ++i) {
    assert(scene->get_scene_component_storage(input_component_ids[i]));
    input_components[i] = scene->get_scene_component_storage(input_component_ids[i])->get();
    // The scene component does not exist so we can stop
    if (!input_components[i]) {
      return true;
    }
  }
  void* output_components[output_component_ids_count];
  for (int i = 0; i < output_component_ids_count; ++i) {
    output_components[i] = alloca(get_resource(output_component_ids[i])->type->size);
  }

  if (callback(input_components, output_components)) {
    for (int i = 0; i < output_component_ids_count; ++i) {
      auto scene_component_storage = scene->get_scene_component_storage(output_component_ids[i]);
      assert(scene_component_storage);
      // TODO: move the value into the storage instead of copying it
      scene_component_storage->emplace(output_components[i]);
      get_resource(output_component_ids[i])->type->destroy(get_resource(output_component_ids[i])->type, output_components[i]);
    }
    return true;
  } else {
    return false;
  }
}

SCENE_COMPONENT_IMPL_WITH_INFO(ovis, runtime, DeltaTime, TYPE_INFO(TYPE(ovis, runtime, Float)));
SCENE_COMPONENT_IMPL_WITH_INFO(ovis, runtime, GameTime, TYPE_INFO(TYPE(ovis, runtime, Float)));
