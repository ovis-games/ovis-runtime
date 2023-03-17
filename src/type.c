#include "ovis/runtime/type.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static bool generics_equal(intptr_t generic_count, const Generic* first_generics, const Generic* second_generics) {
    for (intptr_t i = 0; i < generic_count; ++i) {
        if (first_generics[i] != second_generics[i]) {
            return false;
        }
    }
    return true;
}

void print_instantiation_list(GenericTypeInstantiationList* list) {
    printf("[");
    for (struct GenericTypeInstantiation* current = *list; current != NULL; current = current->next) {
        printf("%s%s", current->info.name, current->next != NULL ? ", " : "");
    }
    printf("]");
}

struct TypeInfo* instantiate_generic_type(GenericTypeInstantiationList* instantiation_list, intptr_t generic_count, const Generic* generics, GenericTypeInstantiationCallback instantiate) {
    assert(instantiation_list);
    assert(instantiate);
    assert(generic_count == 0 || generics);

    puts("instantiate generic\nbefore: ");
    print_instantiation_list(instantiation_list);
    putchar('\n');

    {
        struct GenericTypeInstantiation* current = *instantiation_list;
        while (current != NULL) {
            if (current->info.generic_count == generic_count && generics_equal(generic_count, generics, current->info.generics)) {
                puts("increase reference count\n");
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
    instantiation->info.name = generic_count > 0 ? generics[0]->name : NULL;
    instantiate(&instantiation->info);

    if (*instantiation_list != NULL) {
        (*instantiation_list)->previous = instantiation;
    }

    *instantiation_list = instantiation;

    puts("after: ");
    print_instantiation_list(instantiation_list);
    printf("\n");

    return &instantiation->info;
}

void release_generic_type_instantiation(GenericTypeInstantiationList* instantiation_list, const struct TypeInfo* type) {
    assert(instantiation_list);
    assert(type);

    struct GenericTypeInstantiation* instantiation = *instantiation_list;
    while (instantiation) {
        if (&instantiation->info == type) {
            break;
        } else {
            instantiation = instantiation->next;
        }
    }
    assert(instantiation && "generic type instantiation not found");
    instantiation->reference_count -= 1;
    printf("releasing instantiation for %s\nbefore: ", type->name);
    print_instantiation_list(instantiation_list);
    printf("\n");

    if (instantiation->reference_count == 0) {
        printf("reference count reached 0 for %s\n", type->name);
        if (instantiation->previous) {
            instantiation->previous->next = instantiation->next;
        } else {
            *instantiation_list = instantiation->next;
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

    printf("after: ");
    print_instantiation_list(instantiation_list);
    printf("\n");
}
