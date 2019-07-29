#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "idg/combination_registry.hpp"

TEST_CASE("combination")
{
    using reg = idg::combination_registry<std::size_t, idg::detail::global_tag>;

    auto id0 = reg::register_combination<int, bool, char>();
    auto id1 = reg::register_combination<char, int, bool>();
    REQUIRE(id0 == id1);

    REQUIRE(reg::id<int, bool, char>() == 0);
    REQUIRE(reg::is_registered<bool, int, char>());

    REQUIRE(reg::register_combination<int, bool>() == 1);
}
