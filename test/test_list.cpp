#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/list.h"
#include "ovis/runtime/type.h"

#include <cstdint>

TEST_CASE("list ...", "[ovis][runtime][list]") {
    SECTION("... can be instantiated") {
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) == nullptr);

        const struct TypeInfo* int_list = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), &TYPE_INFO(TYPE(ovis, runtime, Int)));
        REQUIRE(int_list->size == sizeof(List));
        REQUIRE(int_list->align == alignof(List));
        REQUIRE(int_list->initialize);
        REQUIRE(int_list->clone);
        REQUIRE(int_list->destroy);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) != nullptr);
        REQUIRE(&GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->info == int_list);
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->next == nullptr);

        const struct TypeInfo* bool_list = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), &TYPE_INFO(TYPE(ovis, runtime, Bool)));
        REQUIRE(bool_list->size == sizeof(List));
        REQUIRE(bool_list->align == alignof(List));
        REQUIRE(bool_list->initialize);
        REQUIRE(bool_list->clone);
        REQUIRE(bool_list->destroy);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) != nullptr);
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->next != nullptr);

        RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), int_list);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) != nullptr);
        REQUIRE(&GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->info == bool_list);
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->next == nullptr);

        RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), bool_list);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) == nullptr);
    }

    SECTION("... can be instantiated twice with same type") {
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) == nullptr);

        const struct TypeInfo* int_list = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), &TYPE_INFO(TYPE(ovis, runtime, Int)));
        REQUIRE(int_list->size == sizeof(List));
        REQUIRE(int_list->align == alignof(List));
        REQUIRE(int_list->initialize);
        REQUIRE(int_list->clone);
        REQUIRE(int_list->destroy);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) != nullptr);
        REQUIRE(&GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->info == int_list);
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->next == nullptr);

        const struct TypeInfo* second_int_list = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), &TYPE_INFO(TYPE(ovis, runtime, Int)));
        REQUIRE(second_int_list->size == sizeof(List));
        REQUIRE(second_int_list->align == alignof(List));
        REQUIRE(second_int_list->initialize);
        REQUIRE(second_int_list->clone);
        REQUIRE(second_int_list->destroy);

        REQUIRE(int_list == second_int_list);
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->reference_count == 2);

        RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), int_list);

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) != nullptr);
        REQUIRE(&GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->info == second_int_list );
        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List))->next == nullptr);

        RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), second_int_list );

        REQUIRE(GENERIC_INSTANTIATION_LIST(TYPE(ovis, runtime, List)) == nullptr);
    }

    SECTION("... can be initialized") {
        const struct TypeInfo* int_list = INSTANTIATE_GENERIC_TYPE(TYPE(ovis, runtime, List), &TYPE_INFO(TYPE(ovis, runtime, Int)));

        List list;
        int_list->initialize(int_list, &list);

        REQUIRE(list.size == 0);
        REQUIRE(list.capacity == 0);
        REQUIRE(list.data == NULL);

        const int32_t value = 100;
        TYPE_FUNCTION(TYPE(ovis, runtime, List), add)(int_list, &list, &value);

        REQUIRE(list.size == 1);
        REQUIRE(list.capacity >= 1);
        REQUIRE(list.data != nullptr);

        const int32_t index_to_remove = 0;
        TYPE_FUNCTION(TYPE(ovis, runtime, List), remove)(int_list, &list, &index_to_remove);

        REQUIRE(list.size == 0);
        REQUIRE(list.capacity >= 1);
        REQUIRE(list.data != nullptr);

        int_list->destroy(int_list, &list);

        RELEASE_GENERIC_TYPE(TYPE(ovis, runtime, List), int_list);
    }
}

// TEST_CASE("value can be added and removed to list", "[ovis][runtime][mod__ovis__runtime__List]" ) {
//   const struct TypeInfo* int_list_type = mod__ovis__runtime__List_instantiate(&mod__ovis__runtime__Int_type);

//   push_stack_var(int_list_type, list, mod__ovis__runtime__List);

//   REQUIRE(list->size == 0);
//   REQUIRE(list->capacity == 0);
//   REQUIRE(list->data == NULL);

//   int32_t val = 42;
//   REQUIRE(mod__ovis__runtime__List_m_add(int_list_type, list, &val));

//   REQUIRE(list->size == 1);
//   REQUIRE(list->capacity > 0);
//   REQUIRE(list->data != NULL);

//   int32_t remove_index = 0;
//   REQUIRE(mod__ovis__runtime__List_m_remove(int_list_type, list, &remove_index));

//   REQUIRE(list->size == 0);
//   REQUIRE(list->capacity > 0);
//   REQUIRE(list->data != NULL);

//   pop_stack_var(list, int_list_type);

//   mod__ovis__runtime__List_release(int_list_type);
// }
