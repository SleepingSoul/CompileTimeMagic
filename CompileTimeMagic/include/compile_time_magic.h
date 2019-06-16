#pragma once

#include "has_using.h"
#include "has_method.h"

namespace ctm
{

CTM_HAS_TYPEDEF(const_iterator)
CTM_HAS_TYPEDEF(iterator)
CTM_HAS_TYPEDEF(value_type)
CTM_HAS_TYPEDEF(key_type)
CTM_HAS_TYPEDEF(mapped_type)
CTM_HAS_TYPEDEF(size_type)

CTM_HAS_METHOD(begin)
CTM_HAS_METHOD(end)
CTM_HAS_METHOD(cbegin)
CTM_HAS_METHOD(cend)
CTM_HAS_METHOD(find)
CTM_HAS_METHOD(size)

template <class T>
class is_container
{
    static constexpr bool value = has_method_begin_v<T> && ctm::has_method_end_v<T>;
};

template <class T>
static constexpr bool is_container_v = is_container<T>::value;

}
