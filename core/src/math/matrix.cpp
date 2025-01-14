#include <jml/math/matrix.hpp>
#include <jml/internal/logger.hpp>

#include <iostream>
#include <stdexcept>

namespace jml {

Matrix::Matrix(int m, int n): m(m), n(n) { this->entries = new double[m * n]; }

Matrix::~Matrix() { delete[] this->entries; }

int Matrix::get_position(int i, int j) const { return i * this->n + j; }

int Matrix::get_n_rows() const { return m; }

int Matrix::get_n_cols() const { return n; }

void Matrix::set_entry(int i, int j, double value) {

    if (i < 0 || i >= this->m) {
        LOGGER->log(Log() << ERR << "Row number " << i << " out of bounds.\n");
        throw std::out_of_range("row out of bounds");
    }
    if (j < 0 || j >= this->n) {
        LOGGER->log(Log() << ERR << "Column number " << i
                          << " out of bounds.\n");
        throw std::out_of_range("column out of bounds");
    }

    this->entries[get_position(i, j)] = value;
}

double Matrix::get_entry(const int i, const int j) const {
    if (i < 0 || i >= this->m) {
        LOGGER->log(Log() << ERR << "Row number " << i << " out of bounds.\n");
        throw std::out_of_range("row out of bounds");
    }
    if (j < 0 || j >= this->n) {
        LOGGER->log(Log() << ERR << "Column number " << i
                          << " out of bounds.\n");
        throw std::out_of_range("column out of bounds");
    }

    return this->entries[get_position(i, j)];
}

std::unique_ptr<Vector> Matrix::multiply(const Vector& in) const {

    if (in.get_size() != this->n) {
        LOGGER->log(Log(WARN) << "Tried to multiply a vector of size "
                              << in.get_size() << " with a matrix containing "
                              << this->n << " columns.\n");
    }

    std::unique_ptr<Vector> ret = std::make_unique<Vector>(this->m);

    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j)
            ret->add_entry(i, in.get_entry(j) *
                                  this->entries[get_position(i, j)]);
    }

    return ret;
}

} // namespace jml
