#pragma once

#include "ovis/runtime/list.h"
#include "resource_storage.hpp"

class EventStorage : public ResourceStorage {
  public:
    EventStorage(const Resource* resource);
    ~EventStorage() override;

    void emit(const void* event);
    int32_t count() const;
    void* event_ptr(int32_t index);
    void clear();

  private:
    const TypeInfo* m_list_type;
    List m_events;
};
