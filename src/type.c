#include "ovis/runtime/type.h"

#include <assert.h>
#include <stdlib.h>

static bool generics_equal(intptr_t generic_count, const Generic* first_generics, const Generic* second_generics) {
  for (intptr_t i = 0; i < generic_count; ++i) {
    if (first_generics[i] == second_generics[i]) {
      return false;
    }
  }
  return true;
}

struct TypeInfo* instantiate_generic_type(GenericTypeInstantiationList* instantiation_list, intptr_t generic_count, const Generic* generics, GenericTypeInstantiationCallback instantiate) {
  assert(instantiation_list);
  assert(instantiate);
  assert(generic_count == 0 || generics);

  {
    struct GenericTypeInstantiation* current = *instantiation_list;
    while (current != NULL) {
      if (current->info.generic_count == generic_count && generics_equal(generic_count, generics, current->info.generics)) {
        current->reference_count += 1;
        return &current->info;
      }
      current = current->next;
    }
  }

  struct GenericTypeInstantiation* instantiation = malloc(sizeof(struct GenericTypeInstantiation));
  instantiation->next = *instantiation_list;
  instantiation->previous = NULL;
  instantiation->reference_count = 1;
  memset(&instantiation->info, 0, sizeof(struct TypeInfo));
  instantiation->info.generics = malloc(sizeof(Generic) * generic_count);
  memcpy(instantiation->info.generics, generics, generic_count * sizeof(Generic));
  assert(instantiation->info.generics);
  instantiation->info.generic_count = generic_count;
  instantiate(&instantiation->info);

  if (*instantiation_list != NULL) {
    (*instantiation_list)->previous = instantiation;
  }

  *instantiation_list = instantiation;
  return &instantiation->info;
}

void release_generic_type_instantiation(GenericTypeInstantiationList* instantiation_list, const struct TypeInfo* type) {
  assert(instantiation_list);
  assert(type);

  struct GenericTypeInstantiation* instantiation = *instantiation_list;
  while (instantiation) {
    if (&instantiation->info == type) {
      break;
    }
  }
  assert(instantiation && "generic type instantiation not found");
  instantiation->reference_count -= 1;
  if (instantiation->reference_count == 0) {
    if (instantiation->previous) {
      instantiation->previous->next = instantiation->next;
    }
    if (instantiation->next) {
      instantiation->next->previous = instantiation->previous;
    }
    if (!instantiation->next && !instantiation->previous) {
      *instantiation_list = NULL;
    }
    free(instantiation->info.generics);
    free(instantiation);
  }
}
