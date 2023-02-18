#include "ovis/runtime/basic_types.h"

#include <string.h>
#include <stdalign.h>

void ovis_runtime_Bool_initialize(const struct TypeInfo* type_info, void* ptr) { *((ovis_runtime_Bool*)ptr) = false; }
void ovis_runtime_Bool_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool ovis_runtime_Bool_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(ovis_runtime_Bool)); return true; }
const struct TypeInfo ovis_runtime_Bool_type = { sizeof(ovis_runtime_Bool), alignof(ovis_runtime_Bool), ovis_runtime_Bool_initialize, ovis_runtime_Bool_destroy, ovis_runtime_Bool_clone };

void ovis_runtime_Int_initialize(const struct TypeInfo* type_info, void* ptr) { *((ovis_runtime_Int*)ptr) = 0; }
void ovis_runtime_Int_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool ovis_runtime_Int_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(ovis_runtime_Int)); return true; }
const struct TypeInfo ovis_runtime_Int_type = { sizeof(ovis_runtime_Int), alignof(ovis_runtime_Int), ovis_runtime_Int_initialize, ovis_runtime_Int_destroy, ovis_runtime_Int_clone};

void ovis_runtime_Float_initialize(const struct TypeInfo* type_info, void* ptr) { *((ovis_runtime_Float*)ptr) = 0; }
void ovis_runtime_Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool ovis_runtime_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(ovis_runtime_Float)); return true; }
const struct TypeInfo ovis_runtime_Float_type = { sizeof(ovis_runtime_Float), alignof(ovis_runtime_Float), ovis_runtime_Float_initialize, ovis_runtime_Float_destroy, ovis_runtime_Float_clone };

void Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr) { memset(ptr, 0, sizeof(ovis_runtime_Vector3_Float)); }
void Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Vector3_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(ovis_runtime_Vector3_Float)); return true; }
static const struct TypeInfo* Vector3_Float_generics[] = { &ovis_runtime_Float_type };
const struct TypeInfo ovis_runtime_Vector3_Float_type = { sizeof(ovis_runtime_Vector3_Float), 16, Vector3_Float_initialize, Vector3_Float_destroy, Vector3_Float_clone, 1, Vector3_Float_generics };
