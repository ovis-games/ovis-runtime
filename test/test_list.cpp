#include "catch2/catch_test_macros.hpp"
#include "ovis/runtime/basic_types.h"
#include "ovis/runtime/list.h"
#include "ovis/runtime/type.h"

#include <cstdint>

TEST_CASE("List can be instantiated", "[ovis][runtime][List]" ) {
  const struct TypeInfo* int_list = List_instantiate(&ovis_runtime_Int_type);
  REQUIRE(int_list->size == sizeof(List));
  REQUIRE(int_list->align == alignof(List));
  REQUIRE(int_list->initialize);
  REQUIRE(int_list->clone);
  REQUIRE(int_list->destroy);

  const struct TypeInfo* bool_list = List_instantiate(&ovis_runtime_Bool_type);
  REQUIRE(bool_list->size == sizeof(List));
  REQUIRE(bool_list->align == alignof(List));
  REQUIRE(bool_list->initialize);
  REQUIRE(bool_list->clone);
  REQUIRE(bool_list->destroy);

  List_release(int_list);
  List_release(bool_list);
}

TEST_CASE("List can be initialized", "[ovis][runtime][List]" ) {
  const struct TypeInfo* int_list_type = List_instantiate(&ovis_runtime_Int_type);

  push_stack_var(int_list_type, list, List);
  REQUIRE(list->size == 0);
  REQUIRE(list->capacity == 0);
  REQUIRE(list->data == NULL);
  pop_stack_var(list, int_list_type);

  List_release(int_list_type);
}

TEST_CASE("value can be added and removed to list", "[ovis][runtime][List]" ) {
  const struct TypeInfo* int_list_type = List_instantiate(&ovis_runtime_Int_type);

  push_stack_var(int_list_type, list, List);

  REQUIRE(list->size == 0);
  REQUIRE(list->capacity == 0);
  REQUIRE(list->data == NULL);

  ovis_runtime_Int val = 42;
  REQUIRE(List_m_add(int_list_type, list, &val));

  REQUIRE(list->size == 1);
  REQUIRE(list->capacity > 0);
  REQUIRE(list->data != NULL);

  ovis_runtime_Int remove_index = 0;
  REQUIRE(List_m_remove(int_list_type, list, &remove_index));

  REQUIRE(list->size == 0);
  REQUIRE(list->capacity > 0);
  REQUIRE(list->data != NULL);

  pop_stack_var(list, int_list_type);

  List_release(int_list_type);
}
