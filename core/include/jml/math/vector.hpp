/**
 * This specifies the data type that the neural network actually processes.
 * Author: Adam Hutchings
 * Date: 09-19-23
 */

#pragma once

#include <memory>

#include <jml/math/activation_functions.hpp>

namespace jml {

class Vector {

    int length; // The number of entries in the vector

    double * entries;

public:

     Vector(int length);
    ~Vector();

    // This applies a given function to every component in the vector.
    void apply(std::shared_ptr<ActivationFunction> fn);

    // This adds every entry in v to this vector.
    void add(Vector& v);

    int get_size();

    double get_entry(int pos);
    void set_entry(int pos, double val);
    void add_entry(int pos, double val); // Adds val to the current value in pos.

};

}
