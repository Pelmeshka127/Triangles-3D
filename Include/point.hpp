#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

#include "double_numbers.hpp"

class Point 
{
    private:
        const double x_;
        const double y_;
        const double z_;

    public:
        Point(double x = NAN, double y = NAN, double z = NAN) : x_{x}, y_{y}, z_{z} {}

        ~Point() {}

        Point operator=(const Point p)
        {
            return Point(p.GetX(), p.GetY(), p.GetZ());
        }

        double GetX() const
        {
            return x_;
        }

        double GetY() const
        {
            return y_;
        }

        double GetZ() const
        {
            return z_;
        }

        double GetDistance(const Point &p1, const Point &p2) const
        {
            return (std::sqrt(  (p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
                                (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()) +
                                (p1.GetZ() - p2.GetZ()) * (p1.GetZ() - p2.GetZ())   ));
        }

        void PrintPoint() const
        {
            std::cout << "Point " << "(" << x_ << ";" << y_ << ";" << z_ << ")" << std::endl;
        }

        bool IsEqual(const Point &point) const
        {
            return (double_numbers::IsEqual(x_, point.x_) &&
                    double_numbers::IsEqual(y_, point.y_) &&
                    double_numbers::IsEqual(z_, point.z_));
        }
};

#endif