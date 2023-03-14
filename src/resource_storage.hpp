#pragma once

#include "ovis/runtime/resource.h"

class ResourceStorage {
  public:
    ResourceStorage(const Resource* resource) : m_resource(resource) {}
    virtual ~ResourceStorage() = default;

    const Resource* resource() const { return m_resource; }

  private:
    const Resource* m_resource;
};

