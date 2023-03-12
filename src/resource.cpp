#include "resource.hpp"

std::unordered_map<std::string, Resource> RESOURCES;

bool ovis_runtime_register_resource(const char* resource_name, ResourceKind resource_kind, const struct TypeInfo* resource_type) {
  return RESOURCES.insert(std::make_pair(resource_name, Resource{ resource_kind, resource_type })).second;
}

bool ovis_runtime_deregister_resource(const char* resource_name) {
  return RESOURCES.erase(resource_name) == 1;
}
