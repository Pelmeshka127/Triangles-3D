#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"

//-------------------------------------------------------------------------------//

class Vector
{
    private:
        double x_;
        double y_;
        double z_;

    public:
        Vector(const double x = 0, const double y = 0, const double z = 0) : 
            x_{x}, y_{y}, z_{z} {}

        Vector(const Point &p) :
            x_{p.X()}, y_{p.Y()}, z_{p.Z()} {}

        Vector(const Point &p1, const Point &p2) : 
            x_{p2.X() - p1.X()}, y_{p2.Y() - p1.Y()}, z_{p2.Z() - p1.Z()} {}

        double  X() const
        {
            return x_;
        }
        
        double  Y() const
        {
            return y_;
        }

        double  Z() const
        {
            return z_;
        }

        Point   GetVectorCoordinates() const
        {
            Point p(x_, y_, z_);

            return p;
        }

        double  SqrtLength() const
        {
            return (x_ * x_ + y_ * y_ + z_ * z_);
        }
        
        bool    IsNullVector(const Vector &v1) const;
        

        Vector  operator=(const Vector &v);

        Vector  &operator+=(const Vector &v);

        Vector  operator+(const Vector &v) const;

        Vector  &operator-=(const Vector &v);

        Vector  operator-(const Vector &v) const;

        Vector  &operator*=(const float &number);

        Vector  operator*(const float &number) const;

        Point   operator+(const Point& p) const;

        double  operator*(const Point& point) const;

        bool    operator==(const Vector &v) const;


        double  DotProduct(const Vector &v1, const Vector &v2) const;

        double  CrossProductValue(const Vector &v1, const Vector &v2) const;

        Vector  CrossProductVector(const Vector &v1, const Vector &v2) const;

        void    PrintVector() const;
};

const Vector NullVec = Vector{0, 0, 0};

//-------------------------------------------------------------------------------//

#endif