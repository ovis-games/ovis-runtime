#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/frame.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"

bool foo_ran = false;
bool foo(struct Scene*) {
  foo_ran = true;
  return true;
}

bool iterated = false;
bool iterate_me(void** components) {
  void* x = components[0];
  auto frame = (mod__ovis__runtime__Frame*)components[0];
  REQUIRE(frame->delta_time == 1337);
  iterated = true;
  return true;
}

bool iteration_test_called = false;
bool iteration_test(struct Scene* scene) {
  iteration_test_called = true;
  const char* components[] = { "ovis/runtime/Frame" };
  return ovis_scene_iterate(scene, components, 1, iterate_me);
}

TEST_CASE("Scheduler", "[ovis][runtime][scheduler]" ) {
  ovis_runtime_register_scene_component_type("ovis/runtime/Frame", &mod__ovis__runtime__Float_type);

  SECTION("registering basic job") {
    REQUIRE(register_job("foo", &foo));
    REQUIRE(get_job("foo") == &foo);
    REQUIRE(!register_job("foo", &foo));
    Scene* scene = ovis_scene_create();
    REQUIRE(scene != nullptr);

    REQUIRE(!foo_ran);
    ovis_scene_tick(scene, 0.0f);
    REQUIRE(foo_ran);

    ovis_scene_destroy(scene);
    REQUIRE(deregister_job("foo"));
  }

  SECTION("test scene iteration") {
    REQUIRE(register_job("iteration_test", &iteration_test));
    REQUIRE(get_job("iteration_test") == &iteration_test);
    Scene* scene = ovis_scene_create();
    REQUIRE(scene != nullptr);

    REQUIRE(!iteration_test_called);
    REQUIRE(!iterated);
    ovis_scene_tick(scene, 1337.0f);
    ovis_scene_tick(scene, 1337.0f);
    REQUIRE(iteration_test_called);
    REQUIRE(iterated);

    ovis_scene_destroy(scene);
    REQUIRE(deregister_job("iteration_test"));
  }
}

// bool foo2_ran = false;
// bool foo2(struct Scene*) {
//   REQUIRE(false);
//   foo_ran = true;
//   return true;
// }

// TEST_CASE("Scheduler", "[ovis][runtime][scheduler]" ) {
//   REQUIRE(register_job("foo", &foo));
//   REQUIRE(get_job("foo") == &foo);
//   REQUIRE(!register_job("foo", &foo));
//   Scene* scene = ovis_scene_create();
//   REQUIRE(scene != nullptr);

//   REQUIRE(!foo_ran);
//   ovis_scene_tick(scene, 0.0f);
//   REQUIRE(foo_ran);

//   ovis_scene_destroy(scene);
// }
