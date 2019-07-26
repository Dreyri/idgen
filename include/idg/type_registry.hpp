#pragma once

#include <atomic>
#include <cassert>
#include <limits>
#include <type_traits>

#include "idg/detail/common.hpp"
#include "idg/detail/registration.hpp"
#include "idg/detail/util.hpp"

namespace idg
{
template<typename Integral = std::size_t,
         typename Tag      = idg::detail::global_tag>
class type_registry
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral is not an integral type");

    template<typename T>
    struct type_registry_tag
    {};

public:
    using value_type = Integral;
    using tag_type   = type_registry_tag<Tag>;

private:
    static std::atomic<value_type> next_id_;

public:
    template<typename T>
    static value_type register_type()
    {
        using type    = detail::remove_cvref_t<T>;
        value_type id = next_id_++;
        detail::registration<value_type, tag_type, type>::assign_id(id);
        return id;
    }

    template<typename T>
    static bool is_registered() noexcept
    {
        using type = detail::remove_cvref_t<T>;
        return detail::registration<value_type, tag_type, type>::
            is_registered();
    }

    template<typename T>
    static value_type id() noexcept
    {
        using type = detail::remove_cvref_t<T>;
        return detail::registration<value_type, tag_type, type>::id();
    }
};

template<typename Integral, typename Tag>
std::atomic<Integral> type_registry<Integral, Tag>::next_id_{0};
} // namespace idg
