#pragma once

#include <unordered_map>
#include <string_view>
#include <gmock/gmock.h>
#include <compile_time_magic.h>

template <class TKey, class TValue>
class MapWithExtraInfo : public std::unordered_map<TKey, TValue>
{
public:
    using base = std::unordered_map<TKey, TValue>;

    using key_type = typename base::key_type;
    using mapped_type = typename base::mapped_type;
    using value_type = typename base::value_type;

    unsigned countCallsOf(const std::string_view& methodName) const
    {
        return m_calls[methodName];
    }

    auto begin()
    {
        ++m_calls["begin"];
        return base::begin();
    }

    auto end()
    {
        ++m_calls["end"];
        return base::end();
    }

    auto cbegin() const
    {
        ++m_calls["cbegin"];
        return base::cbegin();
    }

    auto cend() const
    {
        ++m_calls["cend"];
        return base::cend();
    }

    auto find(const key_type& key)
    {
        ++m_calls["find"];
        return base::find(key);
    }

    auto find(const key_type& key) const
    {
        ++m_calls["cfind"];
        return base::find(key);
    }

private:
    mutable std::unordered_map<std::string_view, unsigned> m_calls;
};
