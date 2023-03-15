#include "event_storage.hpp"
#include "ovis/runtime/list.h"
#include "ovis/runtime/symbols.h"
#include <cassert>

EventStorage::EventStorage(const Resource* resource) : ResourceStorage(resource) {
  assert(resource);
  assert(resource->kind == RESOURCE_KIND_EVENT);
  m_list_type = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), resource->type);
  m_list_type->initialize(m_list_type, &m_events);
}

EventStorage::~EventStorage() {
  m_list_type->destroy(m_list_type, &m_events);
  RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), m_list_type);
}

void EventStorage::emit(const void* event) {
  TYPE_FUNCTION(TYPE(ovis, runtime, List), add)(m_list_type, &m_events, event);
}

int32_t EventStorage::count() const {
  return m_events.size;
}

void* EventStorage::event_ptr(int32_t index) {
  assert(index < m_events.size);
  return offset_mutable_ptr(m_events.data, index * resource()->type->size);
}


void EventStorage::clear() {
  // TODO: actually clear the list
  m_events.size = 0;
}
