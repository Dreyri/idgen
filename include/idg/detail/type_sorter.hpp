#pragma once

#include <array>
#include <string_view>
#include <utility>

#include <boost/hana.hpp>
#include <nameof.hpp>

namespace idg
{
namespace detail
{
struct index_name_pair
{
public:
    std::size_t      index;
    std::string_view name;

public:
    constexpr index_name_pair(std::size_t i, std::string_view n) noexcept
        : index{i}, name{n}
    {}

    // implicitly defined copy operators
};

template<typename T>
constexpr void swap(T& lhs, T& rhs) noexcept
{
    T tmp = std::move(lhs);
    lhs   = std::move(rhs);
    rhs   = std::move(tmp);
}

template<typename It, typename Compare>
constexpr void insertion_sort(It first, It last, Compare comp)
{
    for (auto it = first + 1; it != last; ++it)
    {
        auto j = it;
        for (auto j = it; j != first; --j)
        {
            if (comp(*j, *(j - 1)))
            {
                ::idg::detail::swap(*j, *(j - 1));
            }
        }
    }
}

template<typename T, std::size_t N>
constexpr auto sort_array(const std::array<T, N>& arr) noexcept
{
    auto sorted = arr;
    ::idg::detail::insertion_sort(
        arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.name < rhs.name;
        });

    return sorted;
}

template<typename... Ts, std::size_t... Is>
constexpr auto sort_types_impl(std::index_sequence<Is...>,
                               boost::hana::basic_type<Ts>... types) noexcept
{
    using boost::hana::make_tuple;
    using boost::hana::size_c;

    auto types_tuple = make_tuple(types...);

    constexpr std::array<index_name_pair, sizeof...(Ts)> indexed_typenames{
        index_name_pair{Is, nameof::nameof_type<Ts>()}...};

    constexpr auto sorted_names = sort_array(indexed_typenames);

    return make_tuple(types_tuple[size_c<sorted_names[Is].index>]...);
}

template<typename... Ts>
constexpr auto sort_types(boost::hana::basic_type<Ts>... types) noexcept
{
    return ::idg::detail::sort_types_impl(
        std::make_index_sequence<sizeof...(Ts)>(), types...);
}
} // namespace detail
} // namespace idg
