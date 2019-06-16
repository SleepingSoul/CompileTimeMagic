[![Build status](https://ci.appveyor.com/api/projects/status/oq545onv20jxg9rw?svg=true)](https://ci.appveyor.com/project/SleepingSoul/extra-std)
## extra_std

The things missing in STL

### 1. Compile time magic
You can check if some class has typedef or method with parameters in compile time using one of methods:
```
estl::has_value_type<>
estl::has_size_type<>
estl::has_key_type<>
estl::has_method_cbegin<>
```
and others.

You can define your own checks with __ESTL_HAS_TYPEDEF(_typedef_name_), ESTL_HAS_METHOD(_method_name_)__

```
template <TContainer>
...
if constexpr(estl::has_key_type_v<TContainer> &&
    estl::has_method_find_v<TContainer, typename TContainer::key_type>)
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

### 2. Extra algorithms
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
