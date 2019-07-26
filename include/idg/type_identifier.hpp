#pragma once

#include <atomic>
#include <cassert>
#include <limits>
#include <type_traits>

#include "idg/detail/identity.hpp"

namespace idg
{
namespace detail
{
struct global_tag
{};
} // namespace detail

template<typename Integral, typename Tag = idg::detail::global_tag>
class type_identifier
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral is not an integral type");

    template<typename T>
    struct type_identifier_tag
    {};

public:
    using value_type = Integral;
    using tag_type   = type_identifier_tag<Tag>;

private:
    static std::atomic<value_type> next_id_;

public:
    template<typename T>
    static value_type register_type() noexcept
    {
        value_type id = next_id_++;
        detail::identity<value_type, tag_type, T>::assign_id(id);
        return id;
    }

    template<typename T>
    static bool is_registered() noexcept
    {
        return detail::identity<value_type, tag_type, T>::is_registered();
    }

    template<typename T>
    static value_type get_id() noexcept
    {
        return detail::identity<value_type, tag_type, T>::get_id();
    }
};

template<typename Integral, typename Tag>
std::atomic<Integral> type_identifier<Integral, Tag>::next_id_{0};
} // namespace idg
