#include "ovis/runtime/shapes.h"
#include "ovis/runtime/canvas.h"
#include "ovis/runtime/job.h"
#include "ovis/runtime/resource.h"
#include "scene.hpp"

bool shape_renderer(Scene* scene) {
    const auto component_storage = scene->get_indexed_component_storage(RESOURCE_ID(TYPE(ovis, runtime, Cuboid)));
    for (auto entity_id : scene->entities()) {
        if (component_storage->contains(entity_id)) {
            printf("entity %d has Cuboid component\n", entity_id);
        }
    }
    return true;
}

DEFINE_BASIC_TYPE(ovis, runtime, Cuboid);
RESOURCE_IMPL(ovis, runtime, Cuboid, RESOURCE_KIND_ENTITY_COMPONENT);

__attribute__((constructor)) void setup_shape_renderer_job() {
    ResourceAccess resource_accesses[] = {
        {
            .resource_id = RESOURCE_ID(TYPE(ovis, runtime, Framebuffer)),
            .access = RESOURCE_ACCESS_READ_WRITE,
        },
        {
            .resource_id = RESOURCE_ID(TYPE(ovis, runtime, Cuboid)),
            .access = RESOURCE_ACCESS_READ,
        },
    };
    register_job("ovis/runtime/shapeRenderer", &shape_renderer, JOB_KIND_UPDATE, sizeof(resource_accesses) / sizeof(resource_accesses[0]), resource_accesses);
}
