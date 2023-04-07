#pragma once

#include "ovis/runtime/resource.h"
#include <unordered_map>

struct EntityDescriptor {
  public:
    EntityDescriptor() {
    }

    ~EntityDescriptor() {
    }

    std::unordered_map<ResourceId, void*> m_components;
};

