#include "Vec.h"

#include <limits>
#include <stdexcept>
#include <cmath>

double Vec::fisq(double a) {
    if (!std::numeric_limits<double>::is_iec559) return 1 / std::sqrt(a);
    double y = a;
    double x2 = y * 0.5;
    std::int64_t i = *(std::int64_t *) &y;
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double *) &i;
    y = y * (1.5 - (x2 * y * y));
    y = y * ( 1.5 - ( x2 * y * y ) );
    return y;
}

Vec::Vec() noexcept {
}

Vec::Vec(double x, double y, double z) noexcept {
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

Vec::Vec(Vec& src) noexcept {
    this->_data[0] = src._data[0];
    this->_data[1] = src._data[1];
    this->_data[2] = src._data[2];
}

Vec::Vec(Vec&& src) noexcept {
    this->_data[0] = src._data[0];
    this->_data[1] = src._data[1];
    this->_data[2] = src._data[2];
}

Vec::~Vec() noexcept {
    // Everything on the stack
}

double Vec::operator [] (size_t idx) {
    if (idx > 2) throw std::out_of_range(
        "[Vec::operator[]] Index out of range.");
    return _data[idx];
}

double Vec::norm() const noexcept{
    return std::sqrt(dot(*this, *this));
}

Vec& Vec::operator += (const Vec& other) noexcept {
    this->_data[0] += other._data[0];
    this->_data[1] += other._data[1];
    this->_data[2] += other._data[2];
    return *this;
}

Vec& Vec::operator -= (const Vec& other) noexcept {
    this->_data[0] -= other._data[0];
    this->_data[1] -= other._data[1];
    this->_data[2] -= other._data[2];
    return *this;
}

Vec& Vec::operator *= (const double other) noexcept {
    this->_data[0] *= other;
    this->_data[1] *= other;
    this->_data[2] *= other;
    return *this;
}

Vec& Vec::operator /= (const double other) noexcept {
    this->_data[0] /= other;
    this->_data[1] /= other;
    this->_data[2] /= other;
    return *this;
}

Vec operator + (Vec lhs, const Vec& rhs) noexcept {
    lhs += rhs;
    return lhs;
}

Vec operator - (Vec lhs, const Vec& rhs) noexcept {
    lhs -= rhs;
    return lhs;
}

Vec operator * (Vec lhs, const double scaler) noexcept {
    lhs *= scaler;
    return lhs;
}

Vec operator / (Vec lhs, const double scaler) noexcept {
    lhs /= scaler;
    return lhs;
}

Vec operator * (const double scaler, Vec rhs) noexcept {
    rhs *= scaler;
    return rhs;
}

double dot(const Vec& a, const Vec& b) {
    return  a._data[0] * b._data[0] +
            a._data[1] * b._data[1] +
            a._data[2] * b._data[2];
}

Vec cross(const Vec& a, const Vec& b) {
    Vec ret(
        a._data[1] * b._data[2] - a._data[2] * b._data[1],
        a._data[2] * b._data[0] - a._data[0] * b._data[2],
        a._data[0] * b._data[1] - a._data[1] * b._data[0]
    );
    return ret;
}

Vec unit(Vec a) {
    return a.unify();
}

std::ostream& operator << (std::ostream& os, const Vec& rhs) {
    os << '[' << rhs._data[0] << ", " << rhs._data[1] << ", " << rhs._data[2] << ']';
    return os;
}

Vec& Vec::unify() {
    if (_data[0] == 0 && _data[1] == 0 && _data[2] == 0) {
        throw std::domain_error("[Vec::unify / unit] Attempting to find the unit vector of [0, 0, 0].");
    }
    double n = fisq(dot(*this, *this));
    _data[0] *= n;
    _data[1] *= n;
    _data[2] *= n;
    return *this;
}