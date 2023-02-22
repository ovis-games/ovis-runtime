#pragma once

#include "ovis/runtime/type.h"
#include "ovis/runtime/basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mod__ovis__runtime__List {
  void* data;
  int32_t capacity;
  int32_t size;
};
extern GenericTypeInstantiationList mod__ovis__runtime__List_instantiations;
const struct TypeInfo* mod__ovis__runtime__List_instantiate(const struct TypeInfo* T);
void mod__ovis__runtime__List_release(const struct TypeInfo* list_type);

void mod__ovis__runtime__List_initialize(const struct TypeInfo* list_type, void* ptr);
void mod__ovis__runtime__List_destroy(const struct TypeInfo* list_type, void* ptr);
bool mod__ovis__runtime__List_clone(const struct TypeInfo* list_type, const void* src, void* dst);

bool mod__ovis__runtime__List_m_add(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const void* value);
bool mod__ovis__runtime__List_m_remove(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const mod__ovis__runtime__Int* index);
bool mod__ovis__runtime__List_m_swap(const struct TypeInfo* list_type, struct mod__ovis__runtime__List* list, const mod__ovis__runtime__Int* first_index, const mod__ovis__runtime__Int* second_index);

#ifdef __cplusplus
}
#endif
