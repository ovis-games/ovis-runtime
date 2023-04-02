#pragma once

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define CONCAT3(a, b, c) CONCAT(a, CONCAT(b, c))
#define CONCAT4(a, b, c, d) CONCAT(CONCAT(a, b), CONCAT(c, d))

#define MODULE(owner, project) mod__ ## owner ## __ ## project

#define FUNCTION(owner, project, function) CONCAT3(MODULE(owner, project), __, function)
#define GENERIC(name) const struct TypeInfo* name
#define PARAMETER(name, type) TYPE_CONST_PTR(type) name
#define MUTABLE_PARAMETER(name, type) type* name
#define GENERIC_PARAMETER(name, type) const void* name
#define MUTABLE_GENERIC_PARAMETER(name, type) void* name
#define RESULT(type) type* _output
#define GENERIC_RESULT(type) void* _output
#define DECLARE_FUNCTION(func, ...) bool func(__VA_ARGS__)
#define FUNCTION_IMPL(func, ...) bool func(__VA_ARGS__)

#define TYPE(owner, project, type, ...) CONCAT3(MODULE(owner, project), __, type)
#define TYPE_PTR(type) CONCAT(type, _ptr)
#define TYPE_CONST_PTR(type) CONCAT(type, _cptr)
#define TYPE_FROZEN(type) CONCAT(type, _frozen)
#define TYPE_IS_FROZEN(type) defined(type ## _frozen)

#define TYPE_INITIALIZE(type) CONCAT(type, _initialize)
#define TYPE_INITIALIZE_DECL(type) void TYPE_INITIALIZE(type) (const struct TypeInfo* type_info, void* ptr)
#define TYPE_INITIALIZE_IMPL(type) TYPE_INITIALIZE_DECL(type) { memset(ptr, 0, sizeof(type)); }
#define INITIALIZE(type, ptr) TYPE_INITIALIZE(type)(&TYPE_INFO(type), (ptr))

#define TYPE_DESTROY(type) CONCAT(type, _destroy)
#define TYPE_DESTROY_DECL(type_) void TYPE_DESTROY(type_) (const struct TypeInfo* type, void* ptr)
#define TYPE_DESTROY_IMPL(type) TYPE_DESTROY_DECL(type) {}
#define DESTROY(type, ptr) TYPE_DESTROY(type)(&TYPE_INFO(type), (ptr))

#define TYPE_CLONE(type) CONCAT(type, _clone)
#define TYPE_CLONE_DECL(type) bool TYPE_CLONE(type) (const struct TypeInfo* type_info, const void* src, void* dst)
#define TYPE_CLONE_IMPL(type) TYPE_CLONE_DECL(type) { memcpy(dst, src, sizeof(type)); return true; }
#define CLONE(type, src, dst) TYPE_CLONE(type)(&TYPE_INFO(type), (src), (dst))

#define TYPE_INFO(type) CONCAT(type, _type)
#define SIZE_OF(type) TYPE_INFO(type).size
#define ALIGN_OF(type) TYPE_INFO(type).align
#define STRIDE_OF(type) TYPE_INFO(type).stride
#define TYPE_INFO_DECL(type) extern const struct TypeInfo TYPE_INFO(type)
#define TYPE_INFO_IMPL(owner, project, type) \
  const struct TypeInfo TYPE_INFO(TYPE(owner, project, type)) = { \
    sizeof(TYPE(owner, project, type)), \
    alignof(TYPE(owner, project, type)), \
    sizeof(TYPE(owner, project, type)) + (alignof(TYPE(owner, project, type)) - (sizeof(TYPE(owner, project, type)) & (alignof(TYPE(owner, project, type)) - 1))), \
    TYPE_INITIALIZE(TYPE(owner, project, type)), \
    TYPE_DESTROY(TYPE(owner, project, type)), \
    TYPE_CLONE(TYPE(owner, project, type)), \
    0, \
    NULL, \
    #owner "/" #project "/" #type \
  }

#define DECLARE_TYPE(owner, project, type) \
  TYPE_INITIALIZE_DECL(TYPE(owner, project, type)); \
  TYPE_DESTROY_DECL(TYPE(owner, project, type)); \
  TYPE_CLONE_DECL(TYPE(owner, project, type)); \
  TYPE_INFO_DECL(TYPE(owner, project, type))

#define GENERIC_INSTANTIATION_LIST(type) CONCAT(type, _instantiations)
#define GENERIC_INSTANTIATION_CALLBACK(type) CONCAT(type, _instantiation_callback)
#define GENERIC_INSTANTIATION_IMPL(type_) \
  GenericTypeInstantiationList GENERIC_INSTANTIATION_LIST(type_) = NULL; \
  void GENERIC_INSTANTIATION_CALLBACK(type_)(struct TypeInfo* type)

#define GENERIC_COUNT(...) (sizeof((Generic[]){__VA_ARGS__})/sizeof(Generic))
#define INSTANTIATE_GENERIC_TYPE(type, ...) \
  instantiate_generic_type(&GENERIC_INSTANTIATION_LIST(type), GENERIC_COUNT(__VA_ARGS__), (Generic[]){__VA_ARGS__}, GENERIC_INSTANTIATION_CALLBACK(type))

#define RELEASE_GENERIC_TYPE(type, instance) \
  release_generic_type_instantiation(&GENERIC_INSTANTIATION_LIST(type), instance)

#define GENERIC_TYPE(name) const struct TypeInfo* name
#define DECLARE_GENERIC_TYPE(owner, project, type, ...) \
  TYPE_INITIALIZE_DECL(TYPE(owner, project, type)); \
  TYPE_DESTROY_DECL(TYPE(owner, project, type)); \
  TYPE_CLONE_DECL(TYPE(owner, project, type)); \
  extern GenericTypeInstantiationList GENERIC_INSTANTIATION_LIST(TYPE(owner, project, type)); \
  void GENERIC_INSTANTIATION_CALLBACK(TYPE(owner, project, type))(struct TypeInfo* type)

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
  typedef const ctype* TYPE_CONST_PTR(type); \
  typedef ctype* TYPE_PTR(type)
#endif

#define DEFINE_BASIC_TYPE(owner, project, type) \
  TYPE_INITIALIZE_IMPL(TYPE(owner, project, type)); \
  TYPE_DESTROY_IMPL(TYPE(owner, project, type)); \
  TYPE_CLONE_IMPL(TYPE(owner, project, type)); \
  TYPE_INFO_IMPL(owner, project, type)

#define DECLARE_TYPE_ALIAS(alias, type) \
  typedef type alias; \
  typedef TYPE_PTR(type) TYPE_PTR(alias); \
  typedef TYPE_CONST_PTR(type) TYPE_CONST_PTR(alias)

#define RESOURCE_ID(type) CONCAT(type, _resource_id)
#define DECLARE_RESOURCE(resource_type, type) extern int32_t RESOURCE_ID(type)

#define RESOURCE_IMPL(owner, project, type, kind) \
  RESOURCE_IMPL_WITH_INFO(owner, project, type, kind, &TYPE_INFO(TYPE(owner, project, type))) \

 // TODO: what if register_resource() fails?
#define RESOURCE_IMPL_WITH_INFO(owner, project, type, kind, info) \
  int32_t RESOURCE_ID(TYPE(owner, project, type)); \
  __attribute__((constructor)) void CONCAT(TYPE(owner, project, type), _resource_registration)() { \
    CONCAT(TYPE(owner, project, type), _resource_id) = register_resource(#owner "/" #project "/" #type, kind, info)->id; \
  }


#define PROPERTY_GETTER_PREFIX(type, property_name) CONCAT3(type, _p_get_, property_name)
#define PROPERTY_GETTER_DECL(type, property_name, property_type) bool PROPERTY_GETTER_PREFIX(type, property_name)(const struct TypeInfo* type_info, TYPE_CONST_PTR(type) object, TYPE_PTR(property_type) _output)
#define DECLARE_PROPERTY_GETTER(type, property_name, property_type) PROPERTY_GETTER_DECL(type, property_name, property_type)
#define PROPERTY_GETTER_IMPL(type, property_name, property_type) PROPERTY_GETTER_DECL(type, property_name, property_type) { \
  return CONCAT(property_type, _clone)(&CONCAT(property_type, _type), &object->property_name, _output); \
}

#define PROPERTY_SETTER_PREFIX(type, property_name) CONCAT3(type, _p_set_, property_name)
#define PROPERTY_SETTER_DECL(type, property_name, property_type) bool PROPERTY_SETTER_PREFIX(type, property_name)(const struct TypeInfo* type_info, TYPE_PTR(type) object, TYPE_CONST_PTR(property_type) value)
#define DECLARE_PROPERTY_SETTER(type, property_name, property_type) PROPERTY_SETTER_DECL(type, property_name, property_type)
#define PROPERTY_SETTER_IMPL(type, property_name, property_type) PROPERTY_SETTER_DECL(type, property_name, property_type) { \
  DESTROY(property_type, &object->property_name); \
  return CLONE(property_type, value, &object->property_name); \
}

// #define GET_PROPERTY(type, property_name, output) PROPERTY_SETTER_PREFIX(
// #define GET_PROPERTY_FROM_GENERIC(type, property_name, output) PROPERTY_SETTER_PREFIX(

#define PROPERTY_IMPL(type, property_name, property_type) \
  PROPERTY_GETTER_IMPL(type, property_name, property_type) \
  PROPERTY_SETTER_IMPL(type, property_name, property_type) \

#define DECLARE_PROPERTY(type, property_name, property_type) \
  DECLARE_PROPERTY_GETTER(type, property_name, property_type); \
  DECLARE_PROPERTY_SETTER(type, property_name, property_type)

#define TYPE_FUNCTION(type, method_name) CONCAT3(type, _s_, method_name)
#define SELF(type) TYPE_CONST_PTR(type) self
#define MUTABLE_SELF(type) TYPE_PTR(type) self
#define DECLARE_TYPE_FUNCTION(type, method_name, ...) bool TYPE_FUNCTION(type, method_name)(const struct TypeInfo* type_info, __VA_ARGS__)
#define DECLARE_MEMBER_FUNCTION(type, method_name, ...) DECLARE_TYPE_FUNCTION(type, method_name, SELF(type), __VA_ARGS__)
#define DECLARE_MUTABLE_MEMBER_FUNCTION(type, method_name, ...) DECLARE_TYPE_FUNCTION(type, method_name, MUTABLE_SELF(type) __VA_OPT__(,) __VA_ARGS__)
#define TYPE_FUNCTION_IMPL(type, method_name, ...) DECLARE_TYPE_FUNCTION(type, method_name, __VA_ARGS__)

#define VARIABLE_STORAGE(type, identifier) alignas(16) char identifier[SIZE_OF(type)]
