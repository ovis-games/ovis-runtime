#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef bool Bool;
void Bool_initialize(const struct TypeInfo* type_info, void* ptr);
void Bool_destroy(const struct TypeInfo* type_info, void* ptr);
bool Bool_copy(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo Bool_type;

typedef int32_t Int;
void Int_initialize(const struct TypeInfo* type_info, void* ptr);
void Int_destroy(const struct TypeInfo* type_info, void* ptr);
bool Int_copy(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo Int_type;

typedef float Float;
void Float_initialize(const struct TypeInfo* type_info, void* ptr);
void Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool Float_copy(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo Float_type;

typedef Float Vector3_Float[3];
void Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr);
void Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool Vector3_Float_copy(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo Vector3_Float_type;

#ifdef __cplusplus
}
#endif
