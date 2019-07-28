#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "idg/combination_registry.hpp"

TEST_CASE("combination")
{
    using reg = idg::combination_registry<std::size_t, idg::detail::global_tag>;

    auto id0 = reg::register_types<int, bool, char>();
    REQUIRE(reg::id<int, bool, char>() == 0);
    REQUIRE(reg::is_registered<bool, int, char>());
}
