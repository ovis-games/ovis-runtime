#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime.hpp"

#include <cstdint>

TEST_CASE("Variable declaration", "[script]" ) {
  Variable<mod__ovis__runtime__Int> int_var(&mod__ovis__runtime__Int_type);
  int_var.initialize();

  REQUIRE(*int_var.get() == 0);

  mod__ovis__runtime__Int val = 9;
  int_var.set(&val);

  REQUIRE(*int_var.get() == 9);

  int_var.destroy();
}
