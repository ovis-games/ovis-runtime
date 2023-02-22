#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef bool mod__ovis__runtime__Bool;
void mod__ovis__runtime__Bool_initialize(const struct TypeInfo* type_info, void* ptr);
void mod__ovis__runtime__Bool_destroy(const struct TypeInfo* type_info, void* ptr);
bool mod__ovis__runtime__Bool_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo mod__ovis__runtime__Bool_type;

typedef int32_t mod__ovis__runtime__Int;
void mod__ovis__runtime__Int_initialize(const struct TypeInfo* type_info, void* ptr);
void mod__ovis__runtime__Int_destroy(const struct TypeInfo* type_info, void* ptr);
bool mod__ovis__runtime__Int_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo mod__ovis__runtime__Int_type;

typedef float mod__ovis__runtime__Float;
void mod__ovis__runtime__Float_initialize(const struct TypeInfo* type_info, void* ptr);
void mod__ovis__runtime__Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool mod__ovis__runtime__Float_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo mod__ovis__runtime__Float_type;

typedef mod__ovis__runtime__Float mod__ovis__runtime__Vector3_Float[3];
void mod__ovis__runtime__Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr);
void mod__ovis__runtime__Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool mod__ovis__runtime__Vector3_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo mod__ovis__runtime__Vector3_Float_type;

#ifdef __cplusplus
}
#endif
