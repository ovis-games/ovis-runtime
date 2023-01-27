#include "ovis/runtime/basic_types.h"

#include <string.h>
#include <stdalign.h>

void Bool_initialize(const struct TypeInfo* type_info, void* ptr) { *((Bool*)ptr) = false; }
void Bool_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Bool_copy(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(Bool)); return true; }
const struct TypeInfo Bool_type = { sizeof(Bool), alignof(Bool), Bool_initialize, Bool_destroy, Bool_copy };

void Int_initialize(const struct TypeInfo* type_info, void* ptr) { *((Int*)ptr) = 0; }
void Int_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Int_copy(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(Int)); return true; }
const struct TypeInfo Int_type = { sizeof(Int), alignof(Int), Int_initialize, Int_destroy, Int_copy};

void Float_initialize(const struct TypeInfo* type_info, void* ptr) { *((Float*)ptr) = 0; }
void Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Float_copy(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(Float)); return true; }
const struct TypeInfo Float_type = { sizeof(Float), alignof(Float), Float_initialize, Float_destroy, Float_copy };

void Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr) { memset(ptr, 0, sizeof(Vector3_Float)); }
void Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Vector3_Float_copy(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(Bool)); return true; }
static const struct TypeInfo* Vector3_Float_generics[] = { &Float_type };
const struct TypeInfo Vector3_Float_type = { sizeof(Vector3_Float), 16, Vector3_Float_initialize, Vector3_Float_destroy, Vector3_Float_copy, 1, Vector3_Float_generics };
