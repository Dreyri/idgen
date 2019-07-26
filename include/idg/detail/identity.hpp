#pragma once

#include <cassert>
#include <limits>

namespace idg
{
namespace detail
{
template<typename Integral, typename Tag, typename... Ts>
class identity
{
public:
    using value_type = Integral;
    using tag_type   = Tag;

private:
    static value_type id_;

    static void assign_id(value_type id) noexcept
    {
        assert(!is_registered());
        id_ = id;
    }

    static bool is_registered() noexcept
    {
        return id_ != std::numeric_limits<Integral>::max();
    }

    static value_type get_id() noexcept
    {
        return id_;
    }
};

template<typename Integral, typename Tag, typename... Ts>
Integral identity<Integral, Tag, Ts...>::id_{0};
} // namespace detail
} // namespace idg
