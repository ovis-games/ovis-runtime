#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

TYPEDEF(bool, TYPE(ovis, runtime, Bool));

// A type that can only have the values true or false.
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
// A 32 bit signed integer.
DECLARE_TYPE(ovis, runtime, Int);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), random,
    PARAMETER(min, TYPE(ovis, runtime, Int)),
    PARAMETER(max, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Int), equals,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Bool))
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
// A 32 bit IEEE 754 floating point number.
DECLARE_TYPE(ovis, runtime, Float);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), equals,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Bool))
);

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

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), sin,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), cos,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

DECLARE_TYPE_FUNCTION(
    TYPE(ovis, runtime, Float), abs,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
);

TYPEDEF_ALIGNED_ARRAY(int32_t, 8, 2, TYPE(ovis, runtime, Vec2I));
// A two-dimensional integer vector.
DECLARE_TYPE(ovis, runtime, Vec2I);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec2I), x, TYPE(ovis, runtime, Int));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec2I), y, TYPE(ovis, runtime, Int));

TYPEDEF_ALIGNED_ARRAY(float, 8, 2, TYPE(ovis, runtime, Vec2F));
// A two-dimensional floating point vector.
DECLARE_TYPE(ovis, runtime, Vec2F);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec2F), x, TYPE(ovis, runtime, Float));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec2F), y, TYPE(ovis, runtime, Float));

TYPEDEF_ALIGNED_ARRAY(int32_t, 16, 3, TYPE(ovis, runtime, Vec3I));
// A three-dimensional integer vector.
DECLARE_TYPE(ovis, runtime, Vec3I);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3I), x, TYPE(ovis, runtime, Int));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3I), y, TYPE(ovis, runtime, Int));
// The z component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3I), z, TYPE(ovis, runtime, Int));

TYPEDEF_ALIGNED_ARRAY(float, 16, 3, TYPE(ovis, runtime, Vec3F));
// A three-dimensional floating point vector.
DECLARE_TYPE(ovis, runtime, Vec3F);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3F), x, TYPE(ovis, runtime, Float));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3F), y, TYPE(ovis, runtime, Float));
// The z component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec3F), z, TYPE(ovis, runtime, Float));

TYPEDEF_ALIGNED_ARRAY(int32_t, 16, 4, TYPE(ovis, runtime, Vec4I));
// A four-dimensional integer vector.
DECLARE_TYPE(ovis, runtime, Vec4I);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4I), x, TYPE(ovis, runtime, Int));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4I), y, TYPE(ovis, runtime, Int));
// The z component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4I), z, TYPE(ovis, runtime, Int));
// The w component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4I), w, TYPE(ovis, runtime, Int));

TYPEDEF_ALIGNED_ARRAY(float, 16, 4, TYPE(ovis, runtime, Vec4F));
// A four-dimensional floating point vector.
DECLARE_TYPE(ovis, runtime, Vec4F);

// The x component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4F), x, TYPE(ovis, runtime, Float));
// The y component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4F), y, TYPE(ovis, runtime, Float));
// The z component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4F), z, TYPE(ovis, runtime, Float));
// The w component of the vector.
DECLARE_PROPERTY(TYPE(ovis, runtime, Vec4F), w, TYPE(ovis, runtime, Float));

TYPEDEF_ARRAY(TYPE(ovis, runtime, Vec2F), 2, TYPE(ovis, runtime, Mat2x2F));
DECLARE_TYPE(ovis, runtime, Mat2x2F);

TYPEDEF_ARRAY(TYPE(ovis, runtime, Vec3F), 3, TYPE(ovis, runtime, Mat3x3F));
DECLARE_TYPE(ovis, runtime, Mat3x3F);

TYPEDEF_ARRAY(TYPE(ovis, runtime, Vec4F), 3, TYPE(ovis, runtime, Mat3x4F));
DECLARE_TYPE(ovis, runtime, Mat3x4F);

TYPEDEF_ARRAY(TYPE(ovis, runtime, Vec4F), 4, TYPE(ovis, runtime, Mat4x4F));
DECLARE_TYPE(ovis, runtime, Mat4x4F);

#ifdef __cplusplus
}
#endif
