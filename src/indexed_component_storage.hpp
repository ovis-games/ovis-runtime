#pragma once

#include "ovis/runtime/list.h"
#include "resource_storage.hpp"
#include "versioned_index_id.hpp"
#include <optional>
#include <vector>

class IndexedComponentStorage : public ResourceStorage {
  public:
    IndexedComponentStorage(const Resource* resource);
    ~IndexedComponentStorage() override;

    using Id = VersionedIndexId<>;

    void emplace(Id::Type id, const void* src);
    void remove(Id::Type id);
    bool contains(Id::Type id);

    int32_t count() const;
    void* component_ptr(Id::Type id);

  private:
    const TypeInfo* m_list_type;

    // Stores all the components. Note: not all slots contain valid components for indices.
    // If a component is removed, it just gets marked as "free", so the list may contain holes.
    // The locations of these holes are stored in a linked list. The first item in the list is
    // stored in m_free_list_head which points to the first free slot. The next slot can be then
    // looked up by indexing the m_forward_array with the first item index.
    //
    // Example:
    //
    //                  0 1 2 3 4 5 6 7 8 9
    //
    // component:      [C C X C X X C]
    // forward_array:  [0 5 5 3 X 4 8]
    // reverse_array:  [0 X X 3 X 1 X X 5 X]
    // free_list_head: 2
    //
    // reverse array stores the component index for each id. The vector is indexed by index(id)
    // and returns a component index. If is_emplaced of the component index is 1, the index
    // provides information at which position in the component array we have to look. if is_emplaced
    // is 0 there is no associated component for that id (indicated as an X). The components not
    // associated with any id are also indicated by an X in the component array. This can be caused
    // by removing a component. The free spots in the component array can be found by traversing
    // a linked list. The first free index of the list is stored in free_list_head. The next free slot
    // index can be found by looking up the value at the position of the previous free index in the
    // forward_array. If the array contains 0xffffffff we are at the end of the list. For each slot
    // that is not free, the forward_array stores the associated id of the component.
    List m_components; // TODO: use continous storage!
    std::vector<Id::Type> m_forward_array;

    struct ComponentIndex {
        uint32_t index : Id::INDEX_BITS;
        // Id::VERSION_BITS for additional per-id information
        uint32_t is_emplaced : 1;
    };
    static_assert(sizeof(ComponentIndex) == 4);
    std::vector<ComponentIndex> m_reverse_array;

    static constexpr uint32_t FREE_LIST_END = 0xffffffff;
    uint32_t m_free_list_head = FREE_LIST_END;
};
