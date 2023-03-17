#pragma once

#include <unordered_map>
#include <string>
#include "ovis/runtime/type.h"
#include "resource_storage.hpp"

class SceneComponentStorage final : public ResourceStorage {
  public:
    SceneComponentStorage(const Resource* resource);
    ~SceneComponentStorage() override;

    const void* get() const { return m_component_ptr; }
    void* get() { return m_component_ptr; }

    void* emplace(const void* src = nullptr);
    void reset();

  private:
    void* m_component_ptr = nullptr;
};
