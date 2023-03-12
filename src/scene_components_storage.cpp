#include "scene_components_storage.hpp"

#include "scene.hpp"
#include <cstdlib>

SceneComponentStorage::SceneComponentStorage(const Resource* resource) : ComponentStorage(resource), m_component_ptr(nullptr) {}

SceneComponentStorage::~SceneComponentStorage() {
  reset();
}

void* SceneComponentStorage::emplace() {
  if (m_component_ptr == nullptr) {
    m_component_ptr = aligned_alloc(resource()->type->align, resource()->type->size);
    resource()->type->initialize(resource()->type, m_component_ptr);
  }
  return m_component_ptr;
}

void SceneComponentStorage::reset() {
  if (m_component_ptr == nullptr) {
    return;
  }

  resource()->type->destroy(resource()->type, m_component_ptr);
  free(m_component_ptr); // free_sized() is only available in C
}
