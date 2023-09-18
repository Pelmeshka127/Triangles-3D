#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <iostream>

#include "point.hpp"

class Triangle 
{
    private:
        const Point p1_;
        const Point p2_;
        const Point p3_;

    public:
        Triangle(const Point &p1, const Point &p2, const Point &p3) : p1_{p1}, p2_{p2}, p3_{p3} {}

        ~Triangle() {}
};

#endif