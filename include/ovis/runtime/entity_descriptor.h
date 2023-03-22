#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/resource.h"
#include "ovis/runtime/symbols.h"
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EntityDescriptor EntityDescriptor;

TYPEDEF(EntityDescriptor, TYPE(ovis, runtime, EntityDescriptor));
DECLARE_TYPE(ovis, runtime, EntityDescriptor);

DECLARE_MUTABLE_MEMBER_FUNCTION(
    TYPE(ovis, runtime, EntityDescriptor),
    addComponent,
    GENERIC(C),
    GENERIC_PARAMETER(component, C)
);

#ifdef __cplusplus
}
#endif
