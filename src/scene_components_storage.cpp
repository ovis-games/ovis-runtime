#include "scene_components_storage.hpp"

#include "scene.hpp"
#include <cstdlib>

SceneComponentStorage::SceneComponentStorage(const Resource* resource) : ComponentStorage(resource), m_component_ptr(nullptr) {}

SceneComponentStorage::~SceneComponentStorage() {
  reset();
}

void* SceneComponentStorage::emplace(const void* src) {
  if (m_component_ptr == nullptr) {
    m_component_ptr = aligned_alloc(resource()->type->align, resource()->type->size);
    
    if (src) {
      if (!resource()->type->clone(resource()->type, src, m_component_ptr)) {
        free(m_component_ptr);
        m_component_ptr = nullptr;
      }
    } else {
      resource()->type->initialize(resource()->type, m_component_ptr);
    }
  } else if (src) {
    resource()->type->destroy(resource()->type, m_component_ptr);
    if (!resource()->type->clone(resource()->type, src, m_component_ptr)) {
      free(m_component_ptr);
      m_component_ptr = nullptr;
    }
  }
  return m_component_ptr;
}

void SceneComponentStorage::reset() {
  if (m_component_ptr == nullptr) {
    return;
  }

  resource()->type->destroy(resource()->type, m_component_ptr);
  free(m_component_ptr); // free_sized() is only available in C
  m_component_ptr = nullptr;
}
