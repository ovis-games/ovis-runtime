# Linking
The language has a special linking strategy that modules can be dynamically linked and no recompilation has to occur when any of the dependencies change in way that they remain compatible according to [semantic versioning](https://semver.org/lang/de/).
This means that, e.g., a module can add or reorder struct members and any other modules depending on it should remain binary compatible.
This is not a trivial task, especially when generic types are involved.
In C++ and Rust generic functions (or methods of generic types) essentially generate their own code for each instantiation.
This is not possible with the limitations described above, thus, we cannot rely on C++'s templating mechanism for generic types.
Instead, a system similar to Swift model is implemented.
Each generic function takes an additional `TypeInfo` parameter that describes the size, alignment, constructor, ... for the specific type.
When the generic type requires an interface to be implemented by the type, an additional `Interface` parameter is added that contains the function pointers for all required methods / properties.

Properties cannot generally be accessed via an offset to the base address of the object as this might change due to reordering of the properties.
Instead the module exports getter and setter functions for each property.
