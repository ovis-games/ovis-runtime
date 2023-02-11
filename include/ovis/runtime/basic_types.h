#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef bool ovis_runtime_Bool;
void ovis_runtime_Bool_initialize(const struct TypeInfo* type_info, void* ptr);
void ovis_runtime_Bool_destroy(const struct TypeInfo* type_info, void* ptr);
bool ovis_runtime_Bool_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo ovis_runtime_Bool_type;

typedef int32_t ovis_runtime_Int;
void ovis_runtime_Int_initialize(const struct TypeInfo* type_info, void* ptr);
void ovis_runtime_Int_destroy(const struct TypeInfo* type_info, void* ptr);
bool ovis_runtime_Int_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo ovis_runtime_Int_type;

typedef float ovis_runtime_Float;
void ovis_runtime_Float_initialize(const struct TypeInfo* type_info, void* ptr);
void ovis_runtime_Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool ovis_runtime_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo ovis_runtime_Float_type;

typedef ovis_runtime_Float ovis_runtime_Vector3_Float[3];
void ovis_runtime_Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr);
void ovis_runtime_Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr);
bool ovis_runtime_Vector3_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst);
extern const struct TypeInfo ovis_runtime_Vector3_Float_type;

#ifdef __cplusplus
}
#endif
