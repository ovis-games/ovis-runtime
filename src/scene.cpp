#include "scene.hpp"
#include "event_storage.hpp"
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
  m_resource_storages.resize(RESOURCES.size());

  for (const auto& resource : RESOURCES) {
    switch (resource.kind) {
    case RESOURCE_KIND_SCENE_COMPONENT:
      m_resource_storages[ResourceIdType::index(resource.id)] = std::make_unique<SceneComponentStorage>(&resource);
      break;

    case RESOURCE_KIND_EVENT:
      m_resource_storages[ResourceIdType::index(resource.id)] = std::make_unique<EventStorage>(&resource);
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

  for (auto& resource_storage : m_resource_storages) {
    if (resource_storage->resource()->kind == RESOURCE_KIND_EVENT) {
      static_cast<EventStorage*>(resource_storage.get())->clear();
    }
  }
}

bool ovis_scene_iterate(struct Scene* scene,
    int32_t input_component_ids_count, const int32_t* input_component_ids,
    int32_t output_component_ids_count, const int32_t* output_component_ids,
    IterateCallback callback
) {
  EventStorage* event_storage = nullptr;
  intptr_t event_input_index = 0;

  void* input_components[input_component_ids_count];
  for (int i = 0; i < input_component_ids_count; ++i) {
    switch (get_resource(input_component_ids[i])->kind) {
    case RESOURCE_KIND_SCENE_COMPONENT:
      input_components[i] = scene->get_scene_component_storage(input_component_ids[i])->get();
      if (!input_components[i]) {
        // The scene component does not exist so we can stop
        return true;
      }
      break;

    case RESOURCE_KIND_EVENT:
      event_storage = scene->get_event_storage(input_component_ids[i]);
      event_input_index = i;
      break;
    }
  }
  void* output_components[output_component_ids_count];
  for (int i = 0; i < output_component_ids_count; ++i) {
    output_components[i] = alloca(get_resource(output_component_ids[i])->type->size);
  }

  if (event_storage != nullptr) {
    for (int event_index = 0; event_index < event_storage->count(); ++event_index) {
      input_components[event_input_index] = event_storage->event_ptr(event_input_index);

      if (callback(input_components, output_components)) {
        for (int i = 0; i < output_component_ids_count; ++i) {
          auto scene_component_storage = scene->get_scene_component_storage(output_component_ids[i]);
          assert(scene_component_storage);
          // TODO: move the value into the storage instead of copying it
          scene_component_storage->emplace(output_components[i]);
          get_resource(output_component_ids[i])->type->destroy(get_resource(output_component_ids[i])->type, output_components[i]);
        }
      } else {
        return false;
      }
    }
    return true;
  } else {
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
}

RESOURCE_IMPL_WITH_INFO(ovis, runtime, DeltaTime, RESOURCE_KIND_SCENE_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Float)));
RESOURCE_IMPL_WITH_INFO(ovis, runtime, GameTime, RESOURCE_KIND_SCENE_COMPONENT, TYPE_INFO(TYPE(ovis, runtime, Float)));
