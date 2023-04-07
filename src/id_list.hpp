#pragma once

#include "versioned_index_id.hpp"

#include <cassert>
#include <vector>

class IdList {
  public:
    using Id = VersionedIndexId<>;

    Id::Type emplace();
    void remove(Id::Type id);
    bool contains(Id::Type id);

    // TODO: count is actually wrong, as it does not take into account the number "freed" indices
    int32_t count() const { return m_ids.size() - m_free_list_size; }
    Id::Type operator[](std::size_t i) { return m_ids[i]; }

    struct Iterator;
    Iterator begin() const;
    Iterator end() const;

  private:
    std::vector<Id::Type> m_ids;

    static constexpr uint32_t FREE_LIST_END = (1 << Id::INDEX_BITS) - 1;
    uint32_t m_free_list_head = Id::create(FREE_LIST_END);
    int32_t m_free_list_size = 0;
};

struct IdList::Iterator {
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = IdList::Id::Type;
  using pointer = const IdList::Id::Type*;
  using reference = const IdList::Id::Type&;

  reference operator*() const { return list->m_ids[index]; }
  pointer operator->() { return &list->m_ids[index]; }
  Iterator& operator++() {
    Increment();
    return *this;
  }
  Iterator operator++(int) {
    auto current = *this;
    Increment();
    return current;
  }

  const IdList* list;
  size_t index;

  void Increment() {
    do {
      ++index;
    } while (index < list->m_ids.size() && IdList::Id::index(list->m_ids[index]) != index);
  }
};

inline bool operator==(const IdList::Iterator& lhs, const IdList::Iterator& rhs) {
  assert(lhs.list == rhs.list);
  return lhs.index == rhs.index;
}

inline bool operator!=(const IdList::Iterator& lhs, const IdList::Iterator& rhs) {
  assert(lhs.list == rhs.list);
  return lhs.index != rhs.index;
}
