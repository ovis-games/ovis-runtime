#pragma once

#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/symbols.h"

typedef struct {
    TYPE(ovis, runtime, Vec3F) dimensions;
    TYPE(ovis, runtime, Color) color;
} Cuboid;
TYPEDEF(Cuboid, TYPE(ovis, runtime, Cuboid));

// A 3D cuboid.
DECLARE_TYPE(ovis, runtime, Cuboid);

DECLARE_RESOURCE(EntityComponent, TYPE(ovis, runtime, Cuboid));

// The dimensions of the cuboid.
DECLARE_PROPERTY(TYPE(ovis, runtime, Cuboid), dimensions, TYPE(ovis, runtime, Vec3F));

// Color of the cuboid.
DECLARE_PROPERTY(TYPE(ovis, runtime, Cuboid), color, TYPE(ovis, runtime, Color));
