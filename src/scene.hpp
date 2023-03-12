#pragma once

#include <cassert>

#include "ovis/runtime/scene.h"
#include "scene_components_storage.hpp"
#include "resource.hpp"
#include "scheduler.hpp"

class Scene {
  public:
    Scene();

    void tick(float delta_time);

    ComponentStorage* get_component_storage(ResourceId id) {
      assert(ResourceIdType::index(id) < m_component_storages.size());
      return m_component_storages[ResourceIdType::index(id)].get();
    }

    SceneComponentStorage* get_scene_component_storage(ResourceId id) {
      assert(ResourceIdType::index(id) < m_component_storages.size());
      assert(m_component_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_SCENE_COMPONENT);
      return static_cast<SceneComponentStorage*>(m_component_storages[ResourceIdType::index(id)].get());
    }

  private:
    Scheduler m_scheduler;
    std::vector<std::unique_ptr<ComponentStorage>> m_component_storages;
};

