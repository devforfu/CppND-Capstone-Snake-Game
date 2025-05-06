#include <catch2/catch_test_macros.hpp>

int RandomDice4() {
    return 4;
}

TEST_CASE("Random dice cast", "[dice]") {
    REQUIRE(RandomDice4() == 4);
}
