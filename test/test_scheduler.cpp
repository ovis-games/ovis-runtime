#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"

bool foo_ran = false;
bool foo(struct Scene*) {
  foo_ran = true;
  return true;
}

bool iterated = false;
bool iterate_me(void** input_components, void**) {
  void* x = input_components[0];
  auto delta_time = (float*)input_components[0];
  REQUIRE(*delta_time == 1337);
  iterated = true;
  return true;
}

bool iteration_test_called = false;
bool iteration_test(struct Scene* scene) {
  iteration_test_called = true;
  const int32_t components[] = { RESOURCE_ID(TYPE(ovis, runtime, DeltaTime)) };
  return ovis_scene_iterate(scene, 1, components, 0, nullptr, iterate_me);
}

struct Test {
  int32_t value;
};
TYPEDEF(Test, TYPE(ovis, test, Test));
DECLARE_TYPE(ovis, test, Test);
DEFINE_BASIC_TYPE(ovis, test, Test);

bool output_iterated = false;
bool output_iterator(void**, void** outputs) {
  REQUIRE(outputs[0] != nullptr);
  static_cast<Test*>(outputs[0])->value = 1337;
  output_iterated = true;
  return true;
}

int32_t Test_resource_id;
bool output_test_called = false;
bool output_test(struct Scene* scene) {
  output_test_called = true;
  const int32_t output_components[] = { Test_resource_id };
  return ovis_scene_iterate(scene, 0, nullptr, 1, output_components, output_iterator);
}

TEST_CASE("Scheduler", "[ovis][runtime][scheduler]" ) {
  SECTION("registering basic job") {
    REQUIRE(register_job("foo", &foo, JOB_KIND_UPDATE, 0, nullptr));
    REQUIRE(get_job("foo")->function == &foo);
    REQUIRE(!register_job("foo", &foo, JOB_KIND_UPDATE, 0, nullptr));
    Scene* scene = ovis_scene_create();
    REQUIRE(scene != nullptr);

    REQUIRE(!foo_ran);
    ovis_scene_tick(scene, 0.0f);
    REQUIRE(foo_ran);

    ovis_scene_destroy(scene);
    REQUIRE(deregister_job("foo"));
    REQUIRE(get_job("foo") == nullptr);
  }

  SECTION("test scene iteration") {
    REQUIRE(register_job("iteration_test", &iteration_test, JOB_KIND_UPDATE, 0, nullptr));
    REQUIRE(get_job("iteration_test")->function == &iteration_test);
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

  SECTION("test scene iteration with output") {
    const auto test_component = register_resource("Test", RESOURCE_KIND_SCENE_COMPONENT, &TYPE_INFO(TYPE(ovis, test, Test)));
    REQUIRE(test_component != nullptr);
    Test_resource_id = test_component->id;

    REQUIRE(register_job("output_test", &output_test, JOB_KIND_UPDATE, 0, nullptr));
    REQUIRE(get_job("output_test")->function == &output_test);
    Scene* scene = ovis_scene_create();
    REQUIRE(scene != nullptr);


    REQUIRE(ovis_scene_get_scene_component(scene, test_component->id) == nullptr);
    REQUIRE(!output_test_called);
    REQUIRE(!output_iterated);
    ovis_scene_tick(scene, 1337.0f);
    REQUIRE(output_test_called);
    REQUIRE(output_iterated);

    Test* test_component_instance = static_cast<Test*>(ovis_scene_get_scene_component(scene, test_component->id));
    REQUIRE(test_component_instance);
    REQUIRE(test_component_instance->value == 1337);

    ovis_scene_destroy(scene);
    REQUIRE(deregister_job("output_test"));
    REQUIRE(deregister_resource(Test_resource_id));
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
