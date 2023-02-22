#include "scene_components_storage.hpp"

#include "scene.hpp"
#include <cstdlib>

SceneComponentsStorage::SceneComponentsStorage() {
}

SceneComponentsStorage::~SceneComponentsStorage() {
}

void* SceneComponentsStorage::add(const char* component_id) {
  auto component = m_scene_components.find(component_id);
  if (component == m_scene_components.end()) {
    auto scene_component = SCENE_COMPONENTS.find(component_id);
    if (scene_component == SCENE_COMPONENTS.end()) {
      return nullptr;
    } else {
      auto component = std::malloc(scene_component->second->size);
      scene_component->second->initialize(scene_component->second, component);
      m_scene_components.insert(std::make_pair(component_id, component));
      return component;
    }
  } else {
    return component->second;
  }
}

void* SceneComponentsStorage::get(const char* component_id) {
  auto component = m_scene_components.find(component_id);
  if (component == m_scene_components.end()) {
    return nullptr;
  } else {
    return component->second;
  }
}
