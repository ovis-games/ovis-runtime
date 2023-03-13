#pragma once

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define CONCAT3(a, b, c) CONCAT(a, CONCAT(b, c))
#define CONCAT4(a, b, c, d) CONCAT(CONCAT(a, b), CONCAT(c, d))

#define MODULE(owner, project) mod__ ## owner ## __ ## project

#define FUNCTION(owner, project, function) CONCAT3(MODULE(owner, project), __, function)
#define PARAMETER(name, type) TYPE_CONST_PTR(type) name
#define MUTABLE_PARAMETER(name, type) type* name
#define RESULT(type) type* _output
#define DECLARE_FUNCTION(func, ...) bool func(__VA_ARGS__)
#define FUNCTION_IMPL(func, ...) bool func(__VA_ARGS__)

#define TYPE(owner, project, type) CONCAT3(MODULE(owner, project), __, type)
#define TYPE_PTR(type) CONCAT(type, _ptr)
#define TYPE_CONST_PTR(type) CONCAT(type, _cptr)
#define TYPE_FROZEN(type) CONCAT(type, _frozen)
#define TYPE_IS_FROZEN(type) defined(type ## _frozen)

#define TYPE_INITIALIZE(type) type ## _initialize
#define TYPE_INITIALIZE_DECL(type) void TYPE_INITIALIZE(type) (const struct TypeInfo* type_info, void* ptr)
#define TYPE_INITIALIZE_IMPL(type) TYPE_INITIALIZE_DECL(type) { memset(ptr, 0, sizeof(type)); }
#define INITIALIZE(type, ptr) TYPE_INITIALIZE(type)(&TYPE_INFO(type), (ptr))

#define TYPE_DESTROY(type) type ## _destroy
#define TYPE_DESTROY_DECL(type) void TYPE_DESTROY(type) (const struct TypeInfo* type_info, void* ptr)
#define TYPE_DESTROY_IMPL(type) TYPE_DESTROY_DECL(type) {}
#define DESTROY(type, ptr) TYPE_DESTROY(type)(&TYPE_INFO(type), (ptr))

#define TYPE_CLONE(type) type ## _clone
#define TYPE_CLONE_DECL(type) bool TYPE_CLONE(type) (const struct TypeInfo* type_info, const void* src, void* dst)
#define TYPE_CLONE_IMPL(type) TYPE_CLONE_DECL(type) { memcpy(dst, src, sizeof(type)); return true; }
#define CLONE(type, src, dst) TYPE_CLONE(type)(&TYPE_INFO(type), (src), (dst))

#define TYPE_INFO(type) CONCAT(type, _type)
#define SIZE_OF(type) TYPE_INFO(type).size
#define ALIGN_OF(type) TYPE_INFO(type).align
#define TYPE_INFO_DECL(type) extern const struct TypeInfo TYPE_INFO(type)
#define TYPE_INFO_IMPL(type) const struct TypeInfo TYPE_INFO(type) = { sizeof(type), alignof(type), TYPE_INITIALIZE(type), TYPE_DESTROY(type), TYPE_CLONE(type), 0, NULL }

#define DECLARE_TYPE(owner, project, type) \
  TYPE_INITIALIZE_DECL(TYPE(owner, project, type)); \
  TYPE_DESTROY_DECL(TYPE(owner, project, type)); \
  TYPE_CLONE_DECL(TYPE(owner, project, type)); \
  TYPE_INFO_DECL(TYPE(owner, project, type))

#define TYPEDEF(ctype, type) \
  typedef ctype type; \
  typedef const type* TYPE_CONST_PTR(type); \
  typedef type* TYPE_PTR(type)

#define TYPEDEF_ARRAY(ctype, size, type) \
  typedef ctype type[size]; \
  typedef const type TYPE_CONST_PTR(type); \
  typedef type TYPE_PTR(type)

#ifdef _MSC_VER
#define TYPEDEF_ALIGNED_ARRAY(ctype, alignment, size, type) \
  typedef __declspec(align(alignment)) ctype type[size]; \
  typedef const type TYPE_CONST_PTR(type); \
  typedef type TYPE_PTR(type)
#else
#define TYPEDEF_ALIGNED_ARRAY(ctype, alignment, size, type) \
  typedef ctype type[size] __attribute__((aligned(alignment))); \
  typedef const type TYPE_CONST_PTR(type); \
  typedef type TYPE_PTR(type)
#endif

#define DEFINE_BASIC_TYPE(type) \
  TYPE_INITIALIZE_IMPL(type); \
  TYPE_DESTROY_IMPL(type); \
  TYPE_CLONE_IMPL(type); \
  TYPE_INFO_IMPL(type)

#define RESOURCE_ID(type) CONCAT(type, _resource_id)
#define SCENE_COMPONENT(type) \
  extern int32_t RESOURCE_ID(type)


#define SCENE_COMPONENT_IMPL(owner, project, type) \
  SCENE_COMPONENT_IMPL_WITH_INFO(owner, project, type, TYPE_INFO(TYPE(owner, project, type))) \

 // TODO: what if register_job() fails?
#define SCENE_COMPONENT_IMPL_WITH_INFO(owner, project, type, info) \
  int32_t RESOURCE_ID(TYPE(owner, project, type)); \
  __attribute__((constructor)) void CONCAT(TYPE(owner, project, type), _resource_registration)() { \
    CONCAT(TYPE(owner, project, type), _resource_id) = register_resource(#owner "/" #project "/" #type, RESOURCE_KIND_SCENE_COMPONENT, &info)->id; \
  }

#define TYPE_PROPERTY_GETTER_PREFIX(type, property_name) CONCAT3(type, _p_get_, property_name)
#define TYPE_PROPERTY_GETTER_DECL(type, property_name) bool TYPE_PROPERTY_GETTER_PREFIX(type, property_name)(const struct TypeInfo* type_info, const void* object, void* _output)
#define DECLARE_PROPERTY_TYPE_GETTER(type, property_name, property_type) TYPE_PROPERTY_GETTER_DECL(type, property_name)
#define TYPE_PROPERTY_GETTER_IMPL(type, property_name, projecty_type) bool TYPE_PROPERTY_GETTER_PREFIX(type, property_name)(const struct TypeInfo* type_info, const void* object, void* _output) { \
  return CONCAT(projecty_type, _clone)(&CONCAT(projecty_type, _type), &((const type*)object)->property_name, _output); \
}

#define TYPE_FUNCTION(type, method_name) CONCAT3(type, _s_, method_name)
#define DECLARE_TYPE_FUNCTION(type, method_name, ...) bool TYPE_FUNCTION(type, method_name)(__VA_ARGS__)
#define TYPE_FUNCTION_IMPL(type, method_name, ...) DECLARE_TYPE_FUNCTION(type, method_name, __VA_ARGS__)

#define VARIABLE_STORAGE(type, identifier) alignas(16) char identifier[SIZE_OF(type)]
