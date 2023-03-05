#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

TYPEDEF(bool, TYPE(ovis, runtime, Bool));
DECLARE_TYPE(ovis, runtime, Bool);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Bool), not,
    PARAMETER(value, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Bool), and,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Bool), or,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Bool), xor,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
);

TYPEDEF(int32_t, TYPE(ovis, runtime, Int));
DECLARE_TYPE(ovis, runtime, Int);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), random,
    PARAMETER(min, TYPE(ovis, runtime, Int)),
    PARAMETER(max, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), add,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), sub,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), mul,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), div,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

TYPEDEF(float, TYPE(ovis, runtime, Float));
DECLARE_TYPE(ovis, runtime, Float);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), add,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), sub,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), mul,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), div,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

TYPEDEF_ALIGNED_ARRAY(int32_t, 8, 2, TYPE(ovis, runtime, Vec2I));
DECLARE_TYPE(ovis, runtime, Vec2I);

TYPEDEF_ALIGNED_ARRAY(float, 8, 2, TYPE(ovis, runtime, Vec2F));
DECLARE_TYPE(ovis, runtime, Vec2F);

TYPEDEF_ALIGNED_ARRAY(int32_t, 16, 3, TYPE(ovis, runtime, Vec3I));
DECLARE_TYPE(ovis, runtime, Vec3I);

TYPEDEF_ALIGNED_ARRAY(float, 16, 3, TYPE(ovis, runtime, Vec3F));
DECLARE_TYPE(ovis, runtime, Vec3F);

TYPEDEF_ALIGNED_ARRAY(int32_t, 16, 4, TYPE(ovis, runtime, Vec4I));
DECLARE_TYPE(ovis, runtime, Vec4I);

TYPEDEF_ALIGNED_ARRAY(float, 16, 4, TYPE(ovis, runtime, Vec4F));
DECLARE_TYPE(ovis, runtime, Vec4F);

typedef TYPE(ovis, runtime, Vec2F) TYPE(ovis, runtime, Mat2x2F)[2];
DECLARE_TYPE(ovis, runtime, Mat2x2F);

typedef TYPE(ovis, runtime, Vec3F) TYPE(ovis, runtime, Mat3x3F)[3];
DECLARE_TYPE(ovis, runtime, Mat3x3F);

typedef TYPE(ovis, runtime, Vec4F) TYPE(ovis, runtime, Mat3x4F)[3];
DECLARE_TYPE(ovis, runtime, Mat3x4F);

typedef TYPE(ovis, runtime, Vec4F) TYPE(ovis, runtime, Mat4x4F)[4];
DECLARE_TYPE(ovis, runtime, Mat4x4F);

#ifdef __cplusplus
}
#endif
