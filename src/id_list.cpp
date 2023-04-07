#include "id_list.hpp"
#include <cassert>

IdList::Id::Type IdList::emplace() {
    if (const auto insert_index = Id::index(m_free_list_head); insert_index != FREE_LIST_END) {
        m_free_list_head = Id::index(m_ids[insert_index]);
        m_ids[insert_index] = Id::create(insert_index, Id::version(m_ids[insert_index]) + 1);
        --m_free_list_size;
        return m_ids[insert_index];
    } else {
        m_ids.push_back(Id::create(m_ids.size()));
        return m_ids.back();
    }
}

void IdList::remove(Id::Type id) {
    assert(contains(id));
    m_ids[Id::index(id)] = Id::create(m_free_list_head, Id::version(id));
    m_free_list_head = Id::create(Id::index(id));
    ++m_free_list_size;
}

bool IdList::contains(Id::Type id) {
    return Id::index(id) < m_ids.size() && m_ids[Id::index(id)] == id;
}

IdList::Iterator IdList::begin() const {
    size_t index = 0;
    while (index < m_ids.size() && Id::index(m_ids[index]) != index) {
        ++index;
    }
    return {
        .list = this,
        .index = index,
    };
}

IdList::Iterator IdList::end() const {
    return {
        .list = this,
        .index = m_ids.size(),
    };
}
