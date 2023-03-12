#pragma once

#include <unordered_map>
#include <string>

#include "ovis/runtime/resource.h"

struct Resource {
  ResourceKind kind;
  const TypeInfo* type;
};

extern std::unordered_map<std::string, Resource> RESOURCES;
