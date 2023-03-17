#pragma once

#include "versioned_index_id.hpp"

#include <vector>

class IdList {
  public:
    using Id = VersionedIndexId<>;

    Id::Type emplace();
    void remove(Id::Type id);
    bool containts(Id::Type id);

    // TODO: count is actually wrong, as it does not take into account the number "freed" indices
    int count() const { return m_ids.size(); }
    Id::Type operator[](std::size_t i) { return m_ids[i]; }

  private:
    std::vector<Id::Type> m_ids;

    static constexpr uint32_t FREE_LIST_END = (1 << Id::INDEX_BITS) - 1;
    uint32_t m_free_list_head = Id::create(FREE_LIST_END);
};
