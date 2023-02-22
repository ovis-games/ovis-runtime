#pragma once

#include "ovis/runtime/scene.h"
#include "scene_components_storage.hpp"
#include "scheduler.hpp"


extern std::unordered_map<std::string, const TypeInfo*> SCENE_COMPONENTS;

class Scene {
  public:
    void tick(float delta_time);

    SceneComponentsStorage* scene_components_storage() {
      return &m_scene_components;
    }

  private:
    SceneComponentsStorage m_scene_components;
    Scheduler m_scheduler;
};

