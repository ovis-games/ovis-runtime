#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime.hpp"

#include <cstdint>

TEST_CASE("Variable declaration", "[script]" ) {
  Variable<int32_t> int_var(&mod__ovis__runtime__Int_type);
  int_var.initialize();

  REQUIRE(*int_var.get() == 0);

  int32_t val = 9;
  int_var.set(&val);

  REQUIRE(*int_var.get() == 9);

  int_var.destroy();
}
