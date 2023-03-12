#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  RESOURCE_ACCESS_READ = 1,
  RESOURCE_ACCESS_WRITE = 2,
  RESOURCE_ACCESS_READ_WRITE = RESOURCE_ACCESS_READ | RESOURCE_ACCESS_WRITE,
} ResourceAccessKind;

typedef struct {
  const char* resource_name;
  ResourceAccessKind access;
} ResourceAccess;

typedef enum {
  RESOURCE_KIND_SCENE_COMPONENT,
  RESOURCE_KIND_VIEWPORT_COMPONENT,
} ResourceKind;

typedef int32_t ResourceId;

typedef struct {
  ResourceId id;
  const char* name;
  ResourceKind kind;
  const struct TypeInfo* type;
} Resource;

Resource* register_resource(const char* name, ResourceKind kind, const struct TypeInfo* type);
bool deregister_resource(ResourceId id);
const Resource* get_resource(ResourceId id);
const Resource* get_resource_by_name(const char* name);

#ifdef __cplusplus
}
#endif
