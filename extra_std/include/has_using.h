#pragma once

#include <type_traits>

#define ESTD_HAS_TYPEDEF(typedef_name)\
template <class T>\
class has_##typedef_name\
{\
    template <class C>\
    static std::true_type test(typename C::##typedef_name*);\
\
    template <class C>\
    static std::false_type test(...);\
\
public:\
    using type = T;\
    static bool constexpr value = decltype(test<T>(nullptr))::value;\
};\
\
template <class T>\
static constexpr bool has_##typedef_name##_v = has_##typedef_name<T>::value;\

