#include <iostream>

#ifndef VEC_H
#define VEC_H

class Vec {
private:
    double _data[3]{0,};
    // Fast inverse sqrt
    static double fisq(double a);

public:
    Vec ()                              noexcept;
    Vec (double x, double y, double z)  noexcept;
    Vec (Vec& src)                      noexcept;
    Vec (Vec&& src)                     noexcept;
    ~Vec()                              noexcept;

    // Lookups
    double  operator [] (size_t idx);
    double  norm        () const noexcept;

    // Operations
    Vec& operator += (const Vec& other)     noexcept;
    Vec& operator -= (const Vec& other)     noexcept;
    Vec& operator *= (const double scaler)  noexcept;
    Vec& operator /= (const double scaler)  noexcept;

    friend Vec operator + (Vec lhs, const Vec& rhs) noexcept;
    friend Vec operator - (Vec lhs, const Vec& rhs) noexcept;
    friend Vec operator * (Vec lhs, const double scaler) noexcept;
    friend Vec operator / (Vec lhs, const double scaler) noexcept;
    friend Vec operator * (const double scaler, Vec rhs) noexcept;

    friend double   dot     (const Vec& a, const Vec& b);
    friend Vec      cross   (const Vec& a, const Vec& b);
    friend Vec      unit    (Vec a);

    // Print operation
    friend std::ostream& operator << (std::ostream& os, const Vec& rhs);

    // Mutations
    Vec& unify();

    // TODO Bulk operations with SIMD
};

double  dot     (const Vec& a, const Vec& b);
Vec     cross   (const Vec& a, const Vec& b);
Vec     unit    (Vec a);

#endif