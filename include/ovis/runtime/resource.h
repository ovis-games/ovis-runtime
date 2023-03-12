#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
  RESOURCE_ACCESS_READ = 1,
  RESOURCE_ACCESS_WRITE = 2,
  RESOURCE_ACCESS_READ_WRITE = RESOURCE_ACCESS_READ | RESOURCE_ACCESS_WRITE,
} ResourceAccess;

typedef enum {
  SCENE_COMPONENT,
  VIEWPORT_COMPONENT,
} ResourceKind;

bool ovis_runtime_register_resource(const char* resource_name, ResourceKind resource_kind, const struct TypeInfo* resource_type);
bool ovis_runtime_deregister_resource(const char* resource_name);

#ifdef __cplusplus
}
#endif
