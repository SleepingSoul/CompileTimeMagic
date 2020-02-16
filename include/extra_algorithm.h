#pragma once

#include <vector>
#include <algorithm>
#include "compile_time_magic.h"

namespace estd
{

template <class TContainer, class TValue>
static bool contains(const TContainer& container, const TValue& value)
{
    const auto cend = container.cend();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, TValue>)
    {
        return container.find(static_cast<const typename TContainer::key_type&>(value)) != cend;
    }
    else
    {
        return std::find(container.cbegin(), cend, value) != cend;
    }
}

template <class TContainer, class TPred>
static bool contains_if(const TContainer& container, TPred&& pred)
{
    const auto cend = container.cend();
    return std::find_if(container.cbegin(), cend, std::forward<TPred>(pred)) != cend;
}

template <class TContainer, class TValue>
static std::pair<bool, typename TContainer::const_iterator> find(const TContainer& container, const TValue& value)
{
    const auto cend = container.cend();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, TValue>)
    {
        const auto it = container.find(value);
        return { it != cend, it };
    }
    else
    {
        const auto it = std::find(container.cbegin(), cend, value);
        return { it != cend, it };
    }
}

template <class TContainer, class TValue>
static std::pair<bool, typename TContainer::iterator> find(TContainer& container, const TValue& value)
{
    const auto end = container.end();

    if constexpr (has_key_type_v<TContainer> && has_mapped_type_v<TContainer> &&
        has_method_find_v<TContainer, TValue>)
    {
        const auto it = container.find(value);
        return { it != end, it };
    }
    else
    {
        const auto it = std::find(container.begin(), end, value);
        return { it != end, it };
    }
}

template <class TContainer, class TPred>
static std::pair<bool, typename TContainer::const_iterator> find_if(const TContainer& container, TPred&& pred)
{
    auto const cend = container.cend();
    auto const it = std::find_if(container.cbegin(), cend, std::forward<TPred>(pred));
    return { it != cend, it };
}

template <class TContainer, class TPred>
static std::pair<bool, typename TContainer::iterator> find_if(TContainer& container, TPred&& pred)
{
    auto const end = container.end();
    auto const it = std::find_if(container.begin(), end, std::forward<TPred>(pred));
    return { it != end, it };
}

template <class TContainer, class TPred>
static bool all(const TContainer& container, TPred&& pred)
{
    return std::all_of(container.cbegin(), container.cend(), std::forward<TPred>(pred));
}

template <class TContainer>
static bool are_unique(TContainer container)
{
    const auto oldEnd = container.end();
    const auto it = std::unique(container.begin(), container.end());
    return it == oldEnd;
}

template <class TContainer, class TContainerToAppend>
static void append(TContainer& base, const TContainerToAppend& toAppend)
{
    std::copy(toAppend.cbegin(), toAppend.cend(), std::back_inserter(base));
}

template <class TContainer, class TContainerToAppend, class TPred>
static void append_if(TContainer& base, const TContainerToAppend& toAppend, TPred&& pred)
{
    std::copy_if(toAppend.cbegin(), toAppend.cend(), std::back_inserter(base), std::forward<TPred>(pred));
}

template <class TContainer, class TPred>
static void remove_if(TContainer& container, TPred&& pred)
{
    const auto it = std::remove_if(container.begin(), container.end(), std::forward<TPred>(pred));
    container.erase(it, container.cend());
}

template <class TContainer, class TFilter>
static TContainer filter(TContainer const& orig, TFilter&& filter)
{
    TContainer filtered;
    std::copy_if(orig.cbegin(), orig.cend(), std::back_inserter(filtered), std::forward<TFilter>(filter));
    return filtered;
}

}