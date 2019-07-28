#pragma once

#include <atomic>
#include <type_traits>

#include <boost/hana.hpp>

#include "idg/detail/common.hpp"
#include "idg/detail/registration.hpp"
#include "idg/detail/type_sorter.hpp"
#include "idg/detail/util.hpp"

namespace idg
{
template<typename Integral = std::size_t,
         typename Tag      = idg::detail::global_tag>
class combination_registry
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral is not an integral type");

    template<typename T>
    struct combination_registry_tag
    {};

public:
    using value_type = Integral;
    using tag_type   = combination_registry_tag<Tag>;

private:
    static std::atomic<value_type> next_id_;

public:
    template<typename... Ts>
    static value_type register_types()
    {
        auto type_list = ::idg::detail::sort_types(
            boost::hana::type_c<detail::remove_cvref_t<Ts>>...);
        value_type id = next_id_++;

        boost::hana::unpack(type_list, [&](auto... types) {
            detail::registration<value_type,
                                 tag_type,
                                 typename decltype(
                                     types)::type...>::assign_id(id);
        });

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
        auto type_list = ::idg::detail::sort_types(
            boost::hana::type_c<detail::remove_cvref_t<Ts>>...);

        return boost::hana::unpack(type_list, [&](auto... types) {
            return detail::registration<value_type,
                                        tag_type,
                                        typename decltype(
                                            types)::type...>::is_registered();
        });
    }

    template<typename... Ts>
    static value_type id() noexcept
    {
        auto type_list = ::idg::detail::sort_types(
            boost::hana::type_c<detail::remove_cvref_t<Ts>>...);

        return boost::hana::unpack(type_list, [&](auto... types) {
            return detail::registration<value_type,
                                        tag_type,
                                        typename decltype(
                                            types)::type...>::id();
        });
    }
};

template<typename Integral, typename Tag>
std::atomic<Integral> combination_registry<Integral, Tag>::next_id_{0};
} // namespace idg
