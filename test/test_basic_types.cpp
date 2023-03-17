#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"

#include <cstdint>

TEST_CASE("Basic types exists and are property sized / aligned", "[ovis][runtime]" ) {
    // Size and alignment should match the WGSL types (https://www.w3.org/TR/WGSL/#alignment-and-size)
    SECTION("Bool") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Bool)) == 1);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Bool)) == 1);
      // REQUIRE(STRIDE_OF(TYPE(ovis, runtime, Bool)) == 1);
    }
    SECTION("Int") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Int)) == 4);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Int)) == 4);
    }
    SECTION("Float") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Float)) == 4);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Float)) == 4);
    }
    SECTION("Vec2I") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec2I)) == 8);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec2I)) == 8);
    }
    SECTION("Vec2F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec2F)) == 8);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec2F)) == 8);
    }
    SECTION("Vec3I") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec3I)) == 12);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec3I)) == 16);
    }
    SECTION("Vec3F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec3F)) == 12);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec3F)) == 16);
    }
    SECTION("Vec4I") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec4I)) == 16);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec4I)) == 16);
    }
    SECTION("Vec4F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Vec4F)) == 16);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Vec4F)) == 16);
    }
    SECTION("Mat2x2F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Mat2x2F)) == 16);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Mat2x2F)) == 8);
    }
    SECTION("Mat3x3F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Mat3x3F)) == 48);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Mat3x3F)) == 16);
    }
    SECTION("Mat3x4F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Mat3x4F)) == 48);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Mat3x4F)) == 16);
    }
    SECTION("Mat4x4F") {
      REQUIRE(SIZE_OF(TYPE(ovis, runtime, Mat4x4F)) == 64);
      REQUIRE(ALIGN_OF(TYPE(ovis, runtime, Mat4x4F)) == 16);
    }
}
