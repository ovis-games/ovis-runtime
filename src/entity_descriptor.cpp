#include "ovis/runtime/entity_descriptor.h"
#include "entity_descriptor.hpp"
#include "ovis/runtime/error.h"
#include "ovis/runtime/symbols.h"
#include <cstdlib>

TYPE_INFO_IMPL(ovis, runtime, EntityDescriptor);

TYPE_INITIALIZE_DECL(TYPE(ovis, runtime, EntityDescriptor)) {
    new (ptr) EntityDescriptor();
}

TYPE_DESTROY_DECL(TYPE(ovis, runtime, EntityDescriptor)) {
    reinterpret_cast<EntityDescriptor*>(ptr)->~EntityDescriptor();
}

TYPE_CLONE_DECL(TYPE(ovis, runtime, EntityDescriptor)) {
    new (dst) EntityDescriptor(*reinterpret_cast<const EntityDescriptor*>(src));
    return true;
}

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, EntityDescriptor),
    addComponent,
    GENERIC(C, INTERFACE(EntityComponent, C_EntityComponent)),
    GENERIC_PARAMETER(component, C)
) {
    if (self->m_components.contains(*C_EntityComponent)) {
        RETURN_ERROR("Component already added");
    }

    void* component_ptr = aligned_alloc(C->align, C->size);
    if (!C->clone(C, component, component_ptr)) {
        free(component_ptr);
        return false;
    }

    self->m_components.insert(std::make_pair(*C_EntityComponent, component_ptr));
    return true;
}

const struct TypeInfo* EntitySpawnList = nullptr;
int32_t RESOURCE_ID(TYPE(ovis, runtime, EntitySpawnList));
__attribute__((constructor)) void CONCAT(TYPE(ovis, runtime, EntitySpawnList), _resource_registration)() {
    EntitySpawnList = instantiate_generic_type(
        &GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)),
        1,
        (Generic[]){&TYPE_INFO(TYPE(ovis, runtime, EntityDescriptor))},
        GENERIC_INSTANTIATION_CALLBACK(TYPE(ovis, runtime, List))
    );

    RESOURCE_ID(TYPE(ovis, runtime, EntitySpawnList)) = register_resource("ovis/runtime/EntitySpawnList", RESOURCE_KIND_ENTITY_SPAWN_LIST, EntitySpawnList)->id;
}
