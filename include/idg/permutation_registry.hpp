#pragma once

#include <atomic>
#include <type_traits>

#include "idg/detail/common.hpp"
#include "idg/detail/registration.hpp"
#include "idg/detail/util.hpp"

namespace idg
{
template<typename Integral = std::size_t,
         typename Tag      = idg::detail::global_tag>
class permutation_registry
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral is not an integral type");

    template<typename T>
    struct permutation_registry_tag
    {};

public:
    using value_type = Integral;
    using tag_type   = permutation_registry_tag<Tag>;

private:
    static std::atomic<value_type> next_id_;

public:
    template<typename... Ts>
    static value_type register_permutation()
    {
        return detail::registration<
            value_type,
            tag_type,
            detail::remove_cvref_t<Ts>...>::do_registration(next_id_);
    }

    template<typename... Ts>
    static bool is_registered() noexcept
    {
        return detail::registration<
            value_type,
            tag_type,
            detail::remove_cvref_t<Ts>...>::is_registered();
    }

    template<typename... Ts>
    static value_type id() noexcept
    {
        return detail::registration<value_type,
                                    tag_type,
                                    detail::remove_cvref_t<Ts>...>::id();
    }
};

template<typename Integral, typename Tag>
std::atomic<Integral> permutation_registry<Integral, Tag>::next_id_{0};
} // namespace idg
