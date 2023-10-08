#include "catch2/catch_test_macros.hpp"
#include "jml/math/vector.hpp"
#include <jml/math/matrix.hpp>
#include <memory>

SCENARIO("A matrix is multiplied with a vector", "[matrix][vector]") {
    GIVEN("a matrix and vector with some values") {
        jml::Matrix m(2, 3);
        jml::Vector V(3);

        // TODO: check row and col
        
        // Initialize matrix to some values
        // TODO: add fuzzing?
        // TODO: it would also be nice to test the setters (no getters defined yet)
        m.set_entry(0, 0, 1);
        m.set_entry(1, 0, 2);
        m.set_entry(0, 1, 3);
        m.set_entry(1, 1, 4);
        m.set_entry(0, 2, 5);
        m.set_entry(1, 2, 6);

        // Initialize vector to some values
        V.set_entry(0, 7);
        V.set_entry(1, 8);
        V.set_entry(2, 9);

        WHEN("matrix and vector are multiplied") {
            jml::Vector ret = *m.multiply(std::make_unique<jml::Vector>(V)).get();

            THEN("vector has length equal to number of rows") {
                REQUIRE(ret.get_size() == 2);
            }

            THEN("vector values are correct") {
                REQUIRE(ret.get_entry(0) == 76);
                REQUIRE(ret.get_entry(1) == 100);
            }
        }
    }
}