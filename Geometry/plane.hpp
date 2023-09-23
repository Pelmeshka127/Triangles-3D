#ifndef PLANE_HPP_
#define PLANE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"

// Ax + By + Cz + D = 0 //

//-------------------------------------------------------------------------------//

class Plane
{
    private:
        const double A_;
        const double B_;
        const double C_;
        const double D_;

    public:
        Plane(const Point& p1, const Point& p2, const Point& p3) :
            A_{(p2.GetY() - p1.GetY()) * (p3.GetZ() - p1.GetZ()) - (p3.GetY() - p1.GetY()) * (p2.GetZ() - p1.GetZ())},
            B_{(p2.GetZ() - p1.GetZ()) * (p3.GetX() - p1.GetX()) - (p3.GetZ() - p1.GetZ()) * (p2.GetX() - p1.GetX())},
            C_{(p2.GetX() - p1.GetX()) * (p3.GetY() - p1.GetY()) - (p3.GetX() - p1.GetX()) * (p2.GetY() - p1.GetY())},
            D_{-1 * (p1.GetX() * A_ + p1.GetY() * B_ + p1.GetZ() * C_)}
            {}

        ~Plane() {}

        bool ArePlanesParallel(const Plane& plane) const;

        bool ArePlanesEqual(const Plane& plane) const;

        void PlaneDump() const;
}; 

//-------------------------------------------------------------------------------//

#endif