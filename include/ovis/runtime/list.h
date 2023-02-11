#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct List {
  void* data;
  int32_t capacity;
  int32_t size;
};
extern GenericTypeInstantiationList List_instantiations;
const struct TypeInfo* List_instantiate(const struct TypeInfo* T);
void List_release(const struct TypeInfo* list_type);

void List_initialize(const struct TypeInfo* list_type, void* ptr);
void List_destroy(const struct TypeInfo* list_type, void* ptr);
bool List_clone(const struct TypeInfo* list_type, const void* src, void* dst);

bool List_m_add(const struct TypeInfo* list_type, struct List* list, const void* value);
bool List_m_remove(const struct TypeInfo* list_type, struct List* list, const ovis_runtime_Int* index);
bool List_m_swap(const struct TypeInfo* list_type, struct List* list, const ovis_runtime_Int* first_index, const ovis_runtime_Int* second_index);

#ifdef __cplusplus
}
#endif
