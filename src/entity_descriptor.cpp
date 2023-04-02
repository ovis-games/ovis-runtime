#include "ovis/runtime/entity_descriptor.h"
#include "ovis/runtime/error.h"
#include "entity_descriptor.hpp"
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
    GENERIC(C),
    GENERIC_PARAMETER(component, C)
) {
    if (self->m_components.contains(C)) {
        RETURN_ERROR("Component already added");
    }

    void* component_ptr = aligned_alloc(C->align, C->size);
    if (!C->clone(C, component, component_ptr)) {
        free(component_ptr);
        return false;
    }

    self->m_components.insert(std::make_pair(C, component_ptr));
    return true;
}

const struct TypeInfo* EntityDescriptorList = instantiate_generic_type(
    &GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)),
    1,
    (Generic[]){ &TYPE_INFO(TYPE(ovis, runtime, EntityDescriptor)) }, 
    GENERIC_INSTANTIATION_CALLBACK(TYPE(ovis, runtime, List))
);

int32_t EntityDescriptorList_resource_id = register_resource("EntityDescriptorList", RESOURCE_KIND_ENTITY_SPAWN_LIST, EntityDescriptorList)->id;
