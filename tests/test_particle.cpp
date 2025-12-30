#include <catch2/catch_test_macros.hpp>

#include "Particle.hpp"

TEST_CASE("Particle pt calculation") {
    csc2026::Particle p(3.0, 4.0, 0.0, 0.0);
    REQUIRE(p.pt() == Approx(5.0));
}

TEST_CASE("Particle energy calculation") {
    csc2026::Particle p(0.0, 0.0, 0.0, 1.0);
    REQUIRE(p.energy() == Approx(1.0));
}
