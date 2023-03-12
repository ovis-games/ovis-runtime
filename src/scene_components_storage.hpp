#pragma once

#include "ovis/runtime/resource.h"
#include "ovis/runtime/type.h"
#include <unordered_map>
#include <string>

class ComponentStorage {
  public:
    ComponentStorage(const Resource* resource) : m_resource(resource) {}
    virtual ~ComponentStorage() = default;

    const Resource* resource() const { return m_resource; }

  private:
    const Resource* m_resource;
};

class SceneComponentStorage final : public ComponentStorage {
  public:
    SceneComponentStorage(const Resource* resource);
    ~SceneComponentStorage() override;

    const void* get() const { return m_component_ptr; }
    void* get() { return m_component_ptr; }

    void* emplace();
    void reset();

  private:
    void* m_component_ptr;
};
