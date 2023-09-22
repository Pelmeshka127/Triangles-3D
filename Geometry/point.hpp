#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

#include "../MathLibs/double_numbers.hpp"

//-------------------------------------------------------------------------------//

class Point 
{
    private:
        const double x_;
        const double y_;
        const double z_;

    public:
        Point(double x = NAN, double y = NAN, double z = NAN) : x_{x}, y_{y}, z_{z} {}

        ~Point() {}

        double  GetX() const;
        
        double  GetY() const;
        
        double  GetZ() const;

        bool    IsEqual(const Point &point) const;
        
        double  GetDistance(const Point &p1, const Point &p2) const;

        double  CrossProductValue(const Point &p1, const Point &p2) const;


        Point   operator=(const Point p) const;

        Point   operator-(const Point &p) const;

        Point   operator+(const Point &p) const;


        void    PrintPoint() const;
};

//-------------------------------------------------------------------------------//

#endif