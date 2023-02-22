#include "ovis/runtime/basic_types.h"

#include <string.h>
#include <stdalign.h>

void mod__ovis__runtime__Bool_initialize(const struct TypeInfo* type_info, void* ptr) { *((mod__ovis__runtime__Bool*)ptr) = false; }
void mod__ovis__runtime__Bool_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool mod__ovis__runtime__Bool_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(mod__ovis__runtime__Bool)); return true; }
const struct TypeInfo mod__ovis__runtime__Bool_type = { sizeof(mod__ovis__runtime__Bool), alignof(mod__ovis__runtime__Bool), mod__ovis__runtime__Bool_initialize, mod__ovis__runtime__Bool_destroy, mod__ovis__runtime__Bool_clone };

void mod__ovis__runtime__Int_initialize(const struct TypeInfo* type_info, void* ptr) { *((mod__ovis__runtime__Int*)ptr) = 0; }
void mod__ovis__runtime__Int_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool mod__ovis__runtime__Int_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(mod__ovis__runtime__Int)); return true; }
const struct TypeInfo mod__ovis__runtime__Int_type = { sizeof(mod__ovis__runtime__Int), alignof(mod__ovis__runtime__Int), mod__ovis__runtime__Int_initialize, mod__ovis__runtime__Int_destroy, mod__ovis__runtime__Int_clone};

void mod__ovis__runtime__Float_initialize(const struct TypeInfo* type_info, void* ptr) { *((mod__ovis__runtime__Float*)ptr) = 0; }
void mod__ovis__runtime__Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool mod__ovis__runtime__Float_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(mod__ovis__runtime__Float)); return true; }
const struct TypeInfo mod__ovis__runtime__Float_type = { sizeof(mod__ovis__runtime__Float), alignof(mod__ovis__runtime__Float), mod__ovis__runtime__Float_initialize, mod__ovis__runtime__Float_destroy, mod__ovis__runtime__Float_clone };

void Vector3_Float_initialize(const struct TypeInfo* type_info, void* ptr) { memset(ptr, 0, sizeof(mod__ovis__runtime__Vector3_Float)); }
void Vector3_Float_destroy(const struct TypeInfo* type_info, void* ptr) {}
bool Vector3_Float_clone(const struct TypeInfo* type_info, const void* src, void* dst) { memcpy(dst, src, sizeof(mod__ovis__runtime__Vector3_Float)); return true; }
static const struct TypeInfo* Vector3_Float_generics[] = { &mod__ovis__runtime__Float_type };
const struct TypeInfo mod__ovis__runtime__Vector3_Float_type = { sizeof(mod__ovis__runtime__Vector3_Float), 16, Vector3_Float_initialize, Vector3_Float_destroy, Vector3_Float_clone, 1, Vector3_Float_generics };
