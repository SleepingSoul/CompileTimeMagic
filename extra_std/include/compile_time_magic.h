#pragma once

#include "has_using.h"
#include "has_method.h"

namespace estd
{

ESTD_HAS_TYPEDEF(const_iterator)
ESTD_HAS_TYPEDEF(iterator)
ESTD_HAS_TYPEDEF(value_type)
ESTD_HAS_TYPEDEF(key_type)
ESTD_HAS_TYPEDEF(mapped_type)
ESTD_HAS_TYPEDEF(size_type)

ESTD_HAS_METHOD(begin)
ESTD_HAS_METHOD(end)
ESTD_HAS_METHOD(cbegin)
ESTD_HAS_METHOD(cend)
ESTD_HAS_METHOD(find)
ESTD_HAS_METHOD(size)

template <class T>
class is_container
{
    static constexpr bool value = has_method_begin_v<T> && has_method_end_v<T>;
};

template <class T>
static constexpr bool is_container_v = is_container<T>::value;

}
