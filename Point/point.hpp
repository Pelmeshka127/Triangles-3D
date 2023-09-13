#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

const double Epsilon = 0.00001;

class Point 
{
    private:
        const double x_;
        const double y_;
        const double z_;

    public:
        Point(double x = 0, double y = 0, double z = 0) : x_{x}, y_{y}, z_{z} {}

        // Point() : x_{NAN}, y_{NAN}, z_{NAN} {}

        ~Point() {}

        void PrintPoint() const;

        bool IsEqual(const Point &point) const;
};

#endif