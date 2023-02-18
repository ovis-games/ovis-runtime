#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime.hpp"

#include <cstdint>

TEST_CASE("Variable declaration", "[script]" ) {
  Variable<ovis_runtime_Int> int_var(&ovis_runtime_Int_type);
  int_var.initialize();

  REQUIRE(*int_var.get() == 0);

  ovis_runtime_Int val = 9;
  int_var.set(&val);

  REQUIRE(*int_var.get() == 9);

  int_var.destroy();
}
