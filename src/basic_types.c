#include "ovis/runtime/basic_types.h"

#include <math.h>
#include <stdalign.h>
#include <stdlib.h>
#include <string.h>

#include "ovis/runtime/error.h"

DEFINE_BASIC_TYPE(ovis, runtime, Bool);
DEFINE_BASIC_TYPE(ovis, runtime, Int);
DEFINE_BASIC_TYPE(ovis, runtime, Float);
DEFINE_BASIC_TYPE(ovis, runtime, Vec2I);
DEFINE_BASIC_TYPE(ovis, runtime, Vec2F);
DEFINE_BASIC_TYPE(ovis, runtime, Vec3I);
DEFINE_BASIC_TYPE(ovis, runtime, Vec3F);
DEFINE_BASIC_TYPE(ovis, runtime, Vec4I);
DEFINE_BASIC_TYPE(ovis, runtime, Vec4F);
DEFINE_BASIC_TYPE(ovis, runtime, Mat2x2F);
DEFINE_BASIC_TYPE(ovis, runtime, Mat3x3F);
DEFINE_BASIC_TYPE(ovis, runtime, Mat3x4F);
DEFINE_BASIC_TYPE(ovis, runtime, Mat4x4F);

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Bool), not,
    PARAMETER(value, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
) {
    *_output = !*value;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Bool), and,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
) {
    *_output = *lhs && *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Bool), or,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
) {
    *_output = *lhs || *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Bool), xor,
    PARAMETER(lhs, TYPE(ovis, runtime, Bool)),
    PARAMETER(rhs, TYPE(ovis, runtime, Bool)),
    RESULT(TYPE(ovis, runtime, Bool))
) {
    *_output = *lhs ^ *rhs;
    return true;
}

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

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Int), add,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
) {
    *_output = *lhs + *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Int), sub,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
) {
    *_output = *lhs - *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Int), mul,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
) {
    *_output = *lhs * *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Int), div,
    PARAMETER(lhs, TYPE(ovis, runtime, Int)),
    PARAMETER(rhs, TYPE(ovis, runtime, Int)),
    RESULT(TYPE(ovis, runtime, Int))
) {
    if (*rhs == 0) {
        RETURN_ERROR("cannot divide by 0");
    }
    *_output = *lhs / *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), add,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = *lhs + *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), sub,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = *lhs - *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), mul,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = *lhs * *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), div,
    PARAMETER(lhs, TYPE(ovis, runtime, Float)),
    PARAMETER(rhs, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = *lhs / *rhs;
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), sin,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = sinf(*value);
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), cos,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = cosf(*value);
    return true;
}

TYPE_FUNCTION_IMPL(
    TYPE(ovis, runtime, Float), abs,
    PARAMETER(value, TYPE(ovis, runtime, Float)),
    RESULT(TYPE(ovis, runtime, Float))
) {
    *_output = fabs(*value);
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec2I), x, TYPE(ovis, runtime, Int)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec2I), x, TYPE(ovis, runtime, Int)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec2I), y, TYPE(ovis, runtime, Int)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec2I), y, TYPE(ovis, runtime, Int)) {
    object[1] = *value;
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec2F), x, TYPE(ovis, runtime, Float)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec2F), x, TYPE(ovis, runtime, Float)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec2F), y, TYPE(ovis, runtime, Float)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec2F), y, TYPE(ovis, runtime, Float)) {
    object[1] = *value;
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3I), x, TYPE(ovis, runtime, Int)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3I), x, TYPE(ovis, runtime, Int)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3I), y, TYPE(ovis, runtime, Int)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3I), y, TYPE(ovis, runtime, Int)) {
    object[1] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3I), z, TYPE(ovis, runtime, Int)) {
    *_output = object[2];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3I), z, TYPE(ovis, runtime, Int)) {
    object[2] = *value;
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3F), x, TYPE(ovis, runtime, Float)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3F), x, TYPE(ovis, runtime, Float)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3F), y, TYPE(ovis, runtime, Float)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3F), y, TYPE(ovis, runtime, Float)) {
    object[1] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec3F), z, TYPE(ovis, runtime, Float)) {
    *_output = object[2];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec3F), z, TYPE(ovis, runtime, Float)) {
    object[2] = *value;
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4I), x, TYPE(ovis, runtime, Int)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4I), x, TYPE(ovis, runtime, Int)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4I), y, TYPE(ovis, runtime, Int)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4I), y, TYPE(ovis, runtime, Int)) {
    object[1] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4I), z, TYPE(ovis, runtime, Int)) {
    *_output = object[2];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4I), z, TYPE(ovis, runtime, Int)) {
    object[2] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4I), w, TYPE(ovis, runtime, Int)) {
    *_output = object[3];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4I), w, TYPE(ovis, runtime, Int)) {
    object[3] = *value;
    return true;
}

PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4F), x, TYPE(ovis, runtime, Float)) {
    *_output = object[0];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4F), x, TYPE(ovis, runtime, Float)) {
    object[0] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4F), y, TYPE(ovis, runtime, Float)) {
    *_output = object[1];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4F), y, TYPE(ovis, runtime, Float)) {
    object[1] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4F), z, TYPE(ovis, runtime, Float)) {
    *_output = object[2];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4F), z, TYPE(ovis, runtime, Float)) {
    object[2] = *value;
    return true;
}
PROPERTY_GETTER_DECL(TYPE(ovis, runtime, Vec4F), w, TYPE(ovis, runtime, Float)) {
    *_output = object[3];
    return true;
}
PROPERTY_SETTER_DECL(TYPE(ovis, runtime, Vec4F), w, TYPE(ovis, runtime, Float)) {
    object[3] = *value;
    return true;
}

// PROPERTY_GETTER_DECL(
