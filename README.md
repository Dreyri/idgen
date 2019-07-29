# idgen

Identify types without using RTTI.

# Example

```cpp
#include <idg/type_registry.hpp>

struct some_erased_type
{
    // use size_t as id value_type and some_erased_type as the tag 
    // to separate it from other registries. You can use any tag you want.
    using reg = idg::type_registry<std::size_t, some_erased_type>;

    std::size_t id_;
    void* data_;
	
    template<typename T>
    some_erased_type(T* data)
      : id_{reg::register_type<T>()}, data_{data}
    {}
	
    template<typename T>
    bool is_type() {
        if (!reg::is_registered<T>())
        {
            return false;
        }

        return reg::id<T>() == id_;	
    }
};
```

We can now recognize whether the erased type is of a certain type.
All without requiring RTTI and most operations involving a single MOV instruction.

The same can be done with combinations (order doesn't matter) and permutations (order matters) of types.

# Warnings

All ids are defined as globals. Therefore when you destroy an object that used a registry and then construct a new one, all ids will still be defined. Luckily calling extra registers on an already registered type will not trigger an error. Just something to keep in mind if you run into strange behavior or expect a type to have a certain id.

# Dependencies

If you're using the `combination_registry` then you'll need [nameof](https://github.com/Neargye/nameof).
This library is used to get the names of types, these names are then used to sort the types and make sure that `<bool, char>` == `<char, bool>` when registering combinations.
