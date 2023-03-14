#pragma once

#include <cassert>

#include "event_storage.hpp"
#include "ovis/runtime/scene.h"
#include "scene_components_storage.hpp"
#include "resource.hpp"
#include "scheduler.hpp"

class Scene {
  public:
    Scene();

    void tick(float delta_time);

    ResourceStorage* get_resource_storage(ResourceId id) {
      assert(ResourceIdType::index(id) < m_resource_storages.size());
      return m_resource_storages[ResourceIdType::index(id)].get();
    }

    SceneComponentStorage* get_scene_component_storage(ResourceId id) {
      assert(ResourceIdType::index(id) < m_resource_storages.size());
      assert(m_resource_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_SCENE_COMPONENT);
      return static_cast<SceneComponentStorage*>(m_resource_storages[ResourceIdType::index(id)].get());
    }

    EventStorage* get_event_storage(ResourceId id) {
      assert(ResourceIdType::index(id) < m_resource_storages.size());
      assert(m_resource_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_EVENT);
      return static_cast<EventStorage*>(m_resource_storages[ResourceIdType::index(id)].get());
    }

  private:
    float m_game_time = 0.0f;
    Scheduler m_scheduler;
    std::vector<std::unique_ptr<ResourceStorage>> m_resource_storages;
};

