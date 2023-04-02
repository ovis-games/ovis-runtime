#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/resource.h"
#include "ovis/runtime/symbols.h"
#include "ovis/runtime/list.h"
#include "ovis/runtime/type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EntityDescriptor EntityDescriptor;

TYPEDEF(EntityDescriptor, TYPE(ovis, runtime, EntityDescriptor));
// Describes an entity with all its components and children.
// Usually used to spawn entities via the EntitySpawnList.
DECLARE_TYPE(ovis, runtime, EntityDescriptor);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, EntityDescriptor),
    addComponent,
    GENERIC(C),
    GENERIC_PARAMETER(component, C)
);

DECLARE_TYPE_ALIAS(TYPE(ovis, runtime, EntitySpawnList), TYPE(ovis, runtime, List, TYPE(ovis, runtime, EntityDescriptor)));
DECLARE_RESOURCE(EntitySpawnList, TYPE(ovis, runtime, EntitySpawnList));

extern const struct TypeInfo* EntitySpawnList;

#ifdef __cplusplus
}
#endif
