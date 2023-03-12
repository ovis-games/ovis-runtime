#pragma once

#include <deque>
#include <string>

#include "ovis/runtime/resource.h"
#include "versioned_index_id.hpp"

extern std::deque<Resource> RESOURCES;
using ResourceIdType = VersionedIndexId<>;
