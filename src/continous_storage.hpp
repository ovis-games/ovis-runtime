#pragma once

#include "ovis/runtime/continous_storage.h"
#include <cstdlib>

// Creates a continous storage for `capacity` elements of `type`. The memory is not initialized!
inline ContinuousStorage continous_storage_create(const TypeInfo* type, int32_t capacity) {
    return {
        .data = aligned_alloc(type->align, capacity * type->stride),
        .capacity = capacity,
    };
}

inline void continous_storage_destroy(ContinuousStorage* storage) {
    free(storage->data);
}
