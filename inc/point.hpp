#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

#include "coordinates.hpp"
#include "double_numbers.hpp"

//-------------------------------------------------------------------------------//

class Point 
{
    private:
        double x_;
        double y_;
        double z_;

    public:
        Point(double x = NAN, double y = NAN, double z = NAN) : x_{x}, y_{y}, z_{z} {}

        bool    IsValid() const
        {
            return (std::isfinite(x_) && std::isfinite(y_) && std::isfinite(z_));
        }

        double  X() const { return x_; }
        
        double  Y() const { return y_; }
        
        double  Z() const { return z_;}

        bool    IsEqual(const Point &point) const;
        
        double  MinCoordinate(const Point& p1, const Point& p2, const int coordinate) const;

        double  MaxCoordinate(const Point& p1, const Point& p2, const int coordinate) const;


        bool    operator==(const Point p) const;

        Point   operator=(const Point p) const;

        Point   operator-(const Point& p) const;

        Point   operator+(const Point& p) const;

        Point&  operator*=(const Point& p);

        Point   operator*(const Point& p) const;

        Point   operator*(const double& n) const;

        bool    PointPointIntersection(const Point& p) const { return (*this == p); }

        void    PrintPoint() const;
};

//-------------------------------------------------------------------------------//

#endif