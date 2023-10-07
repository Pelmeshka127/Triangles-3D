#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

#include "../MathLibs/double_numbers.hpp"

//-------------------------------------------------------------------------------//

class Point 
{
    private:
        double x_;
        double y_;
        double z_;

    public:
        Point(double x = NAN, double y = NAN, double z = NAN) : x_{x}, y_{y}, z_{z} {}

        ~Point() {}

        double  X() const;
        
        double  Y() const;
        
        double  Z() const;

        bool    IsEqual(const Point &point) const;
        
        double  MinCoordinate(const Point& p1, const Point& p2, const int coordinate) const;

        double  MaxCoordinate(const Point& p1, const Point& p2, const int coordinate) const;


        Point   operator=(const Point p) const;

        Point   operator-(const Point& p) const;

        Point   operator+(const Point& p) const;

        Point&  operator*=(const Point& p);

        Point   operator*(const Point& p) const;

        Point   operator*(const double& n) const;


        void    PrintPoint() const;
};

//-------------------------------------------------------------------------------//

#endif