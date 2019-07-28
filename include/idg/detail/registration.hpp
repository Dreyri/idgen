#pragma once

#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

namespace idg
{
class registration_error : public std::logic_error
{
public:
    template<typename... Ts>
    registration_error(std::in_place_type_t<Ts>...) noexcept
        : std::logic_error{"TODO was already registered"}
    {}
};

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
    static void assign_id(value_type id)
    {
        if (is_registered())
        {
            throw idg::registration_error{std::in_place_type<Ts>...};
        }
        id_ = id;
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
