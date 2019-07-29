#include <catch2/catch.hpp>

#include "idg/permutation_registry.hpp"

TEST_CASE("permutation")
{
    using reg = idg::permutation_registry<std::size_t, idg::detail::global_tag>;

    auto id0 = reg::register_permutation<int, bool, char>();
    REQUIRE(!reg::is_registered<bool, int, char>());
    auto id1 = reg::register_permutation<bool, int, char>();
    REQUIRE(reg::is_registered<bool, int, char>());
    REQUIRE(id0 != id1);
}
