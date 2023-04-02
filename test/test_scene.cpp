#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/entity_descriptor.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/scene.h"

bool foo_iterator(void**, void** outputs) {
    EntitySpawnList->initialize(EntitySpawnList, outputs[0]);
    List* spawn_list = (List*)outputs[0];

    const auto entity_descriptor_type = &TYPE_INFO(TYPE(ovis, runtime, EntityDescriptor));
    char entity_desc_storage[entity_descriptor_type->size];
    entity_descriptor_type->initialize(entity_descriptor_type, entity_desc_storage);
    TYPE_FUNCTION(TYPE(ovis, runtime, List), add)(EntitySpawnList, spawn_list, &entity_desc_storage);
    entity_descriptor_type->destroy(entity_descriptor_type, entity_desc_storage);

    return true;
}

bool foo1(struct Scene* scene) {
    const int32_t components[] = {RESOURCE_ID(TYPE(ovis, runtime, EntitySpawnList))};
    return ovis_scene_iterate(scene, 0, nullptr, 1, components, foo_iterator);
}

bool foo2(struct Scene* scene) {
    const int32_t components[] = {RESOURCE_ID(TYPE(ovis, runtime, EntitySpawnList))};
    return ovis_scene_iterate(scene, 0, nullptr, 1, components, foo_iterator);
}

TEST_CASE("scene ...", "[ovis][runtime][scene]") {
    SECTION("... can spawn entitites") {
        REQUIRE(register_job("foo1", &foo1, JOB_KIND_SETUP, 0, nullptr));
        REQUIRE(register_job("foo2", &foo2, JOB_KIND_SETUP, 0, nullptr));
        Scene* scene = ovis_scene_create();
        REQUIRE(scene != nullptr);

        ovis_scene_tick(scene, 0.0f);
        REQUIRE(ovis_scene_get_entity_count(scene) == 2);

        ovis_scene_destroy(scene);
        REQUIRE(deregister_job("foo1"));
        REQUIRE(get_job("foo1") == nullptr);
        REQUIRE(deregister_job("foo2"));
        REQUIRE(get_job("foo2") == nullptr);
    }
}
