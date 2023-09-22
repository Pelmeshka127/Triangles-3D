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
            x_{p.GetX()}, y_{p.GetY()}, z_{p.GetZ()} {}

        Vector(const Point &p1, const Point &p2) : 
            x_{p2.GetX() - p1.GetX()}, y_{p2.GetY() - p1.GetY()}, z_{p2.GetZ() - p1.GetZ()} {}

        ~Vector() {}

        bool    IsNullVector(const Vector &v1) const;

        Point   GetVectorCoordinates(const Vector &v1) const;
        

        Vector  operator=(const Vector &v);

        Vector  &operator+=(const Vector &v);

        Vector  operator+(const Vector &v) const;

        Vector  &operator-=(const Vector &v);

        Vector  operator-(const Vector &v) const;

        Vector  &operator*=(const int &number);

        Vector  operator*(const int &number) const;

        bool    operator==(const Vector &v) const;


        double  Length() const;

        double  ScalarProduct(const Vector &v1, const Vector &v2) const;

        bool    IsOrthogonal(const Vector &v1, const Vector &v2) const;

        double  CrossProductValue(const Vector &v1, const Vector &v2) const;

        Vector  CrossProductVector(const Vector &v1, const Vector &v2) const;

        bool    IsCollinear(const Vector &v1, const Vector &v2) const;

        double  MixedProduct(const Vector &v1, const Vector &v2, const Vector &v3) const;

        bool    AreCoplanar(const Vector &v1, const Vector &v2, const Vector &v3) const;

        void    PrintVector() const;
};

//-------------------------------------------------------------------------------//

#endif