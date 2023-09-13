#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <cmath>

class Vector
{
    private:
        const double x_;
        const double y_;
        const double z_;

    public:
        Vector(double x = 0, double y = 0, double z = 0) : x_{x}, y_{y}, z_{z} {}

        ~Vector() {}

        double Length() const;
};

#endif