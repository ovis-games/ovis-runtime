#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"

bool foo_ran = false;
bool foo() {
  foo_ran = true;
  return true;
}

TEST_CASE("Scheduler", "[ovis][runtime][scheduler]" ) {
  REQUIRE(register_job("foo", &foo));
  REQUIRE(get_job("foo") == &foo);
  REQUIRE(!register_job("foo", &foo));
  Scene* scene = ovis_scene_create();
  REQUIRE(scene != nullptr);

  REQUIRE(!foo_ran);
  ovis_scene_tick(scene, 0.0f);
  REQUIRE(foo_ran);

  ovis_scene_destroy(scene);
}
