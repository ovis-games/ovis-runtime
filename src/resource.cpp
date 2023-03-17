#include "resource.hpp"

std::deque<Resource> RESOURCES;

Resource* register_resource(const char* name, ResourceKind kind, const struct TypeInfo* type) {
    if (get_resource_by_name(name) != nullptr) {
        return nullptr;
    }

    for (auto& resource : RESOURCES) {
        if (resource.name == nullptr) {
            resource.name = name;
            resource.kind = kind;
            resource.type = type;
            return &resource;
        }
    }

    printf("registering resource: %s [%d]\n", name, kind);
    RESOURCES.push_back(Resource{
        .id = static_cast<ResourceId>(ResourceIdType::create(RESOURCES.size())), // TODO: int vs unsigned
        .name = name,
        .kind = kind,
        .type = type,
    });

    return &RESOURCES.back();
}

bool deregister_resource(ResourceId id) {
    const auto index = ResourceIdType::index(id);
    if (index >= RESOURCES.size() || RESOURCES[index].id != id) {
        return false;
    }

    RESOURCES[index].name = nullptr;
    RESOURCES[index].type = nullptr;
    RESOURCES[index].id = ResourceIdType::increase_version(RESOURCES[index].id);
    return true;
}

const Resource* get_resource(ResourceId id) {
    const auto index = ResourceIdType::index(id);
    if (index >= RESOURCES.size() || RESOURCES[index].id != id) {
        return nullptr;
    } else {
        return &RESOURCES[index];
    }
}

const Resource* get_resource_by_name(const char* name) {
    for (const auto& resource : RESOURCES) {
        if (resource.name == name) {
            return &resource;
        }
    }
    return nullptr;
}
