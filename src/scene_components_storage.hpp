#pragma once

#include "ovis/runtime/type.h"
#include <unordered_map>
#include <string>

class SceneComponentsStorage final {
  public:
    SceneComponentsStorage();
    ~SceneComponentsStorage();

    void* add(const char* component_id);
    void* get(const char* component_id);

  private:
    std::unordered_map<std::string, void*> m_scene_components;
};
