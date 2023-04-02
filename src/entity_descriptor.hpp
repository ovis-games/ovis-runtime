#pragma once

#include <unordered_map>

struct EntityDescriptor {
  public:
    EntityDescriptor() {
    }

    ~EntityDescriptor() {
    }

    std::unordered_map<const struct TypeInfo*, void*> m_components;
};

