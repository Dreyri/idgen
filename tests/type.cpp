#include <catch2/catch.hpp>

#include "idg/type_registry.hpp"

TEST_CASE("type")
{
    using reg = idg::type_registry<std::size_t, idg::detail::global_tag>;

    auto id0 = reg::register_type<bool>();
    REQUIRE(id0 == 0);
    REQUIRE(reg::is_registered<bool>());
    REQUIRE(!reg::is_registered<char>());

    auto id1 = reg::register_type<char>();
    REQUIRE(id0 != id1);
    REQUIRE(reg::is_registered<char>());
}
