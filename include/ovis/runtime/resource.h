#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ResourceAccessKind {
    RESOURCE_ACCESS_READ = 1,
    RESOURCE_ACCESS_WRITE = 2,
    RESOURCE_ACCESS_READ_WRITE = RESOURCE_ACCESS_READ | RESOURCE_ACCESS_WRITE,
} ResourceAccessKind;

typedef int32_t ResourceId;

typedef struct ResourceAccess {
    ResourceId resource_id;
    ResourceAccessKind access;
} ResourceAccess;

typedef enum ResourceKind {
    RESOURCE_KIND_ENTITY_SPAWN_LIST,
    RESOURCE_KIND_ENTITY_DESPAWN_LIST,
    RESOURCE_KIND_EVENT,
    RESOURCE_KIND_SCENE_COMPONENT,
    RESOURCE_KIND_VIEWPORT_COMPONENT,
    RESOURCE_KIND_ENTITY_COMPONENT,
} ResourceKind;

typedef struct Resource {
    ResourceId id;
    const char* name;
    ResourceKind kind;
    const struct TypeInfo* type;
} Resource;

typedef ResourceId SceneComponent;
typedef ResourceId EntityComponent;
typedef ResourceId ViewportComponent;
typedef ResourceId Event;

Resource* register_resource(const char* name, ResourceKind kind, const struct TypeInfo* type);
bool deregister_resource(ResourceId id);
const Resource* get_resource(ResourceId id);
const Resource* get_resource_by_name(const char* name);

#ifdef __cplusplus
}
#endif
