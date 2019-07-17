# extra_std
The things missing in STL

#### Build status
| Compiler      | Build status (master) |
|-------------------------------|-----------------------|
|   Visual Compiler (VS 2019)   |     [![Build status](https://ci.appveyor.com/api/projects/status/oq545onv20jxg9rw/branch/master?svg=true)](https://ci.appveyor.com/project/SleepingSoul/extra-std/branch/master)    |
|              g++              |     [![Build status](https://ci.appveyor.com/api/projects/status/k8599s60qtp9rp49/branch/master?svg=true)](https://ci.appveyor.com/project/SleepingSoul/extra-std-9haqf/branch/master)


#### 1. Compile time magic
You can check if some class has typedef or method with parameters in compile time using one of methods:
```
estd::has_value_type<>
estd::has_size_type<>
estd::has_key_type<>
estd::has_method_cbegin<>
```
and others.

You can define your own checks with __ESTL_HAS_TYPEDEF(_typedef_name_), ESTL_HAS_METHOD(_method_name_)__

```
template <class TContainer>
...
if constexpr(estd::has_key_type_v<TContainer> &&
    estd::has_method_find_v<TContainer, typename TContainer::key_type>)
{
    auto it = container.find(value);
    ...
}
else
{
    auto it = std::find(container.begin(), container.end(), value);
    ...
}
```

#### 2. Extra algorithms
Useful algorithms such as estd::contains, estd::are_unique and others. Full list:
```
estd::contains
estd::contains_if
estd::find
estd::find_if
estd::all
estd::are_unique
estd::append
estd::append_if
estd::remove_if
estd::filter
```
Example:
```
auto const[found, it] = estd::find(vec, 255);

if (found)
{
    return *it;
}
```
