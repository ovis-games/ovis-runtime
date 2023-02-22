#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"

#include <cstdint>

TEST_CASE("Bool type exists and is property sized / aligned", "[ovis][runtime][Bool]" ) {
    REQUIRE(mod__ovis__runtime__Bool_type.size == 1);
    REQUIRE(mod__ovis__runtime__Bool_type.align == 1);
}

TEST_CASE("Int type exists and is property sized / aligned", "[ovis][runtime][Int]" ) {
    REQUIRE(mod__ovis__runtime__Int_type.size == 4);
    REQUIRE(mod__ovis__runtime__Int_type.align == 4);
}

TEST_CASE("Float type exists and is property sized / aligned", "[ovis][runtime][Float]" ) {
    REQUIRE(mod__ovis__runtime__Float_type.size == 4);
    REQUIRE(mod__ovis__runtime__Float_type.align == 4);
}

TEST_CASE("Vector3<Float> type exists and is property sized / aligned", "[ovis][runtime][Vector3<Float>]" ) {
    REQUIRE(mod__ovis__runtime__Vector3_Float_type.size == 12);
    REQUIRE(mod__ovis__runtime__Vector3_Float_type.align == 16);
}
