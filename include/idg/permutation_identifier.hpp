#pragma once

#include <atomic>
#include <type_traits>

#include "idg/detail/common.hpp"
#include "idg/detail/identity.hpp"
#include "idg/detail/util.hpp"

namespace idg
{
template<typename Integral = std::size_t,
         typename Tag      = idg::detail::global_tag>
class permutation_identifier
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral is not an integral type");

    template<typename T>
    struct permutation_identifier_tag
    {};

public:
    using value_type = Integral;
    using tag_type   = permutation_identifier_tag<Tag>;

private:
    static std::atomic<value_type> next_id_;

public:
    template<typename... Ts>
    static value_type register_types()
    {
        value_type id = next_id_++;
        detail::identity<value_type, tag_type, detail::remove_cvref_t<Ts>...>::
            assign_id(id);
        return id;
    }

    template<typename T>
    static value_type register_type()
    {
        return register_types<T>();
    }

    template<typename... Ts>
    static bool is_registered() noexcept
    {
        return detail::identity<value_type,
                                tag_type,
                                detail::remove_cvref_t<Ts>...>::is_registered();
    }

    template<typename... Ts>
    static value_type id() noexcept
    {
        return detail::
            identity<value_type, tag_type, detail::remove_cvref_t<Ts>...>::id();
    }
};
} // namespace idg
