#include "indexed_component_storage.hpp"
#include "ovis/runtime/list.h"
#include "ovis/runtime/symbols.h"
#include <cassert>
#include <cstdio>

IndexedComponentStorage::IndexedComponentStorage(const Resource* resource) : ResourceStorage(resource) {
    assert(resource);
    assert(resource->kind == RESOURCE_KIND_VIEWPORT_COMPONENT || resource->kind == RESOURCE_KIND_ENTITY_COMPONENT);
    m_list_type = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), resource->type);
    m_list_type->initialize(m_list_type, &m_components);
}

IndexedComponentStorage::~IndexedComponentStorage() {
    m_list_type->destroy(m_list_type, &m_components);
    RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), m_list_type);
}

void IndexedComponentStorage::emplace(Id::Type id, const void* src) {
    if (auto ptr = component_ptr(id); ptr != nullptr) {
        resource()->type->destroy(resource()->type, ptr);
        resource()->type->clone(resource()->type, src, ptr);
    } else {
        if (Id::index(id) >= m_reverse_array.size()) {
            m_reverse_array.resize(Id::index(id) + 1, ComponentIndex{.index = 0, .is_emplaced = 0});
        }

        if (auto insert_index = m_free_list_head; m_free_list_head != FREE_LIST_END) {
            m_free_list_head = m_forward_array[m_free_list_head];
            auto ptr = offset_mutable_ptr(m_components.data, insert_index * resource()->type->stride);
            resource()->type->destroy(resource()->type, ptr);
            resource()->type->clone(resource()->type, src, ptr);
            m_forward_array[insert_index] = id;
            m_reverse_array[Id::index(id)] = ComponentIndex{
                .index = insert_index,
                .is_emplaced = 1,
            };
        } else {
            m_reverse_array[Id::index(id)] = ComponentIndex{
                .index = static_cast<uint32_t>(m_components.size),
                .is_emplaced = 1,
            };
            TYPE_FUNCTION(TYPE(ovis, runtime, List), add)
            (m_list_type, &m_components, src);
            m_forward_array.push_back(id);
        }
    }
}

void IndexedComponentStorage::remove(Id::Type id) {
    assert(Id::index(id) < m_reverse_array.size());
    assert(m_reverse_array[Id::index(id)].is_emplaced);
    assert(m_forward_array[m_reverse_array[Id::index(id)].index] == id);
    auto& entry = m_reverse_array[Id::index(id)];
    m_forward_array[entry.index] = m_free_list_head;
    m_free_list_head = entry.index;
    entry.is_emplaced = 0;
}

bool IndexedComponentStorage::contains(Id::Type id) {
    assert(Id::index(id) >= m_reverse_array.size() || !m_reverse_array[Id::index(id)].is_emplaced || m_forward_array[m_reverse_array[Id::index(id)].index] == id);
    return Id::index(id) < m_reverse_array.size() && m_reverse_array[Id::index(id)].is_emplaced;
}

int32_t IndexedComponentStorage::count() const {
    return m_components.size;
}

void* IndexedComponentStorage::component_ptr(Id::Type id) {
    if (Id::index(id) < m_reverse_array.size() && m_reverse_array[Id::index(id)].is_emplaced) {
        const auto component_index = m_reverse_array[Id::index(id)].index;
        assert(m_forward_array[component_index] == id);
        return offset_mutable_ptr(m_components.data, component_index * resource()->type->stride);
    } else {
        return nullptr;
    }
}
