#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"

#include <cstdint>

TEST_CASE("Bool type exists and is property sized / aligned", "[ovis][runtime][Bool]" ) {
    REQUIRE(ovis_runtime_Bool_type.size == 1);
    REQUIRE(ovis_runtime_Bool_type.align == 1);
}

TEST_CASE("Int type exists and is property sized / aligned", "[ovis][runtime][Int]" ) {
    REQUIRE(ovis_runtime_Int_type.size == 4);
    REQUIRE(ovis_runtime_Int_type.align == 4);
}

TEST_CASE("Float type exists and is property sized / aligned", "[ovis][runtime][Float]" ) {
    REQUIRE(ovis_runtime_Float_type.size == 4);
    REQUIRE(ovis_runtime_Float_type.align == 4);
}

TEST_CASE("Vector3<Float> type exists and is property sized / aligned", "[ovis][runtime][Vector3<Float>]" ) {
    REQUIRE(ovis_runtime_Vector3_Float_type.size == 12);
    REQUIRE(ovis_runtime_Vector3_Float_type.align == 16);
}
