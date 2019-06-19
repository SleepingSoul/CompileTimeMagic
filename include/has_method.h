#pragma once

#include <utility>

#define ESTD_HAS_METHOD(method_name)\
template <typename T, class ...Args>\
class has_method_##method_name\
{\
    template <typename C, typename = decltype(std::declval<C>().method_name(std::declval<Args>()...))>\
    static std::true_type test(int);\
    template <typename C>\
    static std::false_type test(...);\
\
public:\
    static constexpr bool value = decltype(test<T>(0))::value;\
};\
\
template <class T, class ...Args>\
static constexpr bool has_method_##method_name##_v = has_method_##method_name<T, Args...>::value;\

