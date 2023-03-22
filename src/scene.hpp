#pragma once

#include <cassert>

#include "event_storage.hpp"
#include "id_list.hpp"
#include "indexed_component_storage.hpp"
#include "ovis/runtime/scene.h"
#include "resource.hpp"
#include "scene_component_storage.hpp"
#include "scheduler.hpp"

class Scene {
  public:
    Scene();

    IdList::Id::Type add_viewport() { return m_viewports.emplace(); }

    void tick(float delta_time);

    bool iterate(
        int32_t input_component_ids_count, const int32_t* input_component_ids,
        int32_t output_component_ids_count, const int32_t* output_component_ids,
        IterateCallback callback
    );

    ResourceStorage* get_resource_storage(ResourceId id) {
        assert(ResourceIdType::index(id) < m_resource_storages.size());
        return m_resource_storages[ResourceIdType::index(id)].get();
    }

    SceneComponentStorage* get_scene_component_storage(ResourceId id) {
        assert(ResourceIdType::index(id) < m_resource_storages.size());
        assert(m_resource_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_SCENE_COMPONENT);
        return static_cast<SceneComponentStorage*>(m_resource_storages[ResourceIdType::index(id)].get());
    }

    EventStorage* get_event_storage(ResourceId id) {
        assert(ResourceIdType::index(id) < m_resource_storages.size());
        assert(m_resource_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_EVENT);
        return static_cast<EventStorage*>(m_resource_storages[ResourceIdType::index(id)].get());
    }

    IndexedComponentStorage* get_indexed_component_storage(ResourceId id) {
        assert(ResourceIdType::index(id) < m_resource_storages.size());
        assert(m_resource_storages[ResourceIdType::index(id)].get()->resource()->kind == RESOURCE_KIND_VIEWPORT_COMPONENT);
        return static_cast<IndexedComponentStorage*>(m_resource_storages[ResourceIdType::index(id)].get());
    }

  private:
    float m_game_time = 0.0f;
    Scheduler m_scheduler;
    std::vector<std::unique_ptr<ResourceStorage>> m_resource_storages;
    IdList m_viewports;
    IdList m_entities;
};
