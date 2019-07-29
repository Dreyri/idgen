#pragma once

#include <atomic>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

namespace idg
{
namespace detail
{
template<typename Integral, typename Tag, typename... Ts>
class registration
{
public:
    using value_type = Integral;
    using tag_type   = Tag;

private:
    static value_type id_;

public:
    static value_type do_registration(std::atomic<value_type>& counter)
    {
        if (is_registered())
        {
            return id_;
        }

        id_ = counter++;
        return id_;
    }

    static bool is_registered() noexcept
    {
        return id_ != std::numeric_limits<Integral>::max();
    }

    static value_type id() noexcept
    {
        assert(is_registered());
        return id_;
    }
};

template<typename Integral, typename Tag, typename... Ts>
Integral registration<Integral, Tag, Ts...>::id_{
    std::numeric_limits<Integral>::max()};
} // namespace detail
} // namespace idg
