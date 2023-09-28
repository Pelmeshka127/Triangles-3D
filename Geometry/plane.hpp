#ifndef PLANE_HPP_
#define PLANE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"
#include "vector.hpp"

// Ax + By + Cz + D = 0 //

//-------------------------------------------------------------------------------//

class Plane
{
    private:
        const double A_;
        const double B_;
        const double C_;
        const double D_;

        const Point  plane_point_; // рандомная точка, лежащая в плоскости

        const Vector normal_vector_;

    public:
        Plane(const Point& p1, const Point& p2, const Point& p3) :
            A_{(p2.Y() - p1.Y()) * (p3.Z() - p1.Z()) - (p3.Y() - p1.Y()) * (p2.Z() - p1.Z())},
            B_{(p2.Z() - p1.Z()) * (p3.X() - p1.X()) - (p3.Z() - p1.Z()) * (p2.X() - p1.X())},
            C_{(p2.X() - p1.X()) * (p3.Y() - p1.Y()) - (p3.X() - p1.X()) * (p2.Y() - p1.Y())},
            D_{-1 * (p1.X() * A_ + p1.Y() * B_ + p1.Z() * C_)},
            plane_point_{p1},
            normal_vector_{A_, B_, C_}
            {}

        ~Plane() {}

        double  A()  const;

        double  B()  const;
        
        double  C()  const;

        double  D()  const;

        Vector  n()  const;

        bool    ArePlanesParallel(const Plane& plane)           const;

        bool    ArePlanesEqual(const Plane& plane)              const;

        void    PlaneDump()                                     const;
}; 

//-------------------------------------------------------------------------------//

#endif