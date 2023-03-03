#include "ovis/runtime/basic_types.h"

#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Bool));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Int));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Float));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec2I));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec2F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec3I));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec3F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec4I));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Vec4F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Mat2x2F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Mat3x3F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Mat3x4F));
DEFINE_BASIC_TYPE(TYPE(ovis, runtime, Mat4x4F));

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Int), random,
    PARAMETER(min, TYPE(ovis, runtime, Int)),
    PARAMETER(max, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
) {
  int32_t n = *max - *min;
  *_output = *min + rand() % n;
  return true;
}
