#pragma once

#include <vector>
#include "compile_time_magic.h"

namespace estd
{

template <class TContainer, class TValue>
inline bool contains(TContainer const& container, TValue const& value)
{
    auto const cend = container.cend();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, typename TContainer::key_type>)
    {
        return container.find(static_cast<typename TContainer::key_type const&>(value)) != cend;
    }
    else
    {
        return std::find(container.cbegin(), cend, value) != cend;
    }
}

template <class TContainer, class TPred>
inline bool contains_if(TContainer const& container, TPred const& pred)
{
    auto const cend = container.cend();
    return std::find_if(container.cbegin(), cend, pred) != cend;
}

template <class TContainer, class TValue>
inline std::pair<bool, typename TContainer::const_iterator> find(TContainer const& container, TValue const& value)
{
    auto const cend = container.cend();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, typename TContainer::key_type>)
    {
        auto const it = container.find(value);
        return { it != cend, it };
    }
    else
    {
        auto const it = std::find(container.cbegin(), cend, value);
        return { it != cend, it };
    }
}

template <class TContainer, class TValue>
inline std::pair<bool, typename TContainer::iterator> find(TContainer& container, TValue const& value)
{
    auto const end = container.end();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, typename TContainer::key_type>)
    {
        auto const it = container.find(value);
        return { it != end, it };
    }
    else
    {
        auto const it = std::find(container.begin(), end, value);
        return { it != end, it };
    }
}

template <class TContainer, class TPred>
inline std::pair<bool, typename TContainer::const_iterator> find_if(TContainer const& container, TPred const& pred)
{
    auto const cend = container.cend();
    auto const it = std::find_if(container.cbegin(), cend, pred);
    return { it != cend, it };
}

template <class TContainer, class TPred>
inline std::pair<bool, typename TContainer::iterator> find_if(TContainer& container, TPred const& pred)
{
    auto const end = container.end();
    auto const it = std::find_if(container.begin(), end, pred);
    return { it != end, it };
}

template <class TContainer, class TPred>
inline bool all(TContainer const& container, TPred const& pred)
{
    return std::all_of(container.cbegin(), container.cend(), pred);
}

template <class TContainer>
inline bool are_unique(TContainer container)
{
    auto oldEnd = container.cend();
    auto it = std::unique(container.cbegin(), container.cend());
    return it == oldEnd;
}

template <class TContainer, class TContainerToAppend>
inline void append(TContainer& base, TContainerToAppend const& toAppend)
{
    std::copy(toAppend.cbegin(), toAppend.cend(), std::back_inserter(base));
}

template <class TContainer, class TContainerToAppend, class TPred>
inline void append_if(TContainer& base, TContainerToAppend const& toAppend, TPred const& pred)
{
    std::copy_if(toAppend.cbegin(), toAppend.cend(), std::back_inserter(base), pred);
}

template <class TContainer, class TPred>
inline void remove_if(TContainer& container, TPred const& pred)
{
    auto it = std::remove_if(container.begin(), container.end(), pred);
    container.erase(it, container.cend());
}

template <class TContainer, class TFilter>
TContainer filter(TContainer const& orig, TFilter const& filter)
{
    TContainer filtered;
    std::copy_if(orig.cbegin(), orig.cend(), std::back_inserter(filtered), filter);
    return filtered;
}

}