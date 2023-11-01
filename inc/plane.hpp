#ifndef PLANE_HPP_
#define PLANE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"

//-------------------------------------------------------------------------------//

class Plane
{
    private:
        const double A_;
        const double B_;
        const double C_;
        const double D_;

        const Point  plane_point_;

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

        double  A()  const { return A_; }

        double  B()  const { return B_; }
        
        double  C()  const { return C_; }

        double  D()  const { return D_; }

        Vector  n()  const { return normal_vector_; }

        bool    ArePlanesParallel(const Plane& plane)           const;

        bool    ArePlanesEqual(const Plane& plane)              const;

        Point   PlaneSegmentIntersection(const Segment& l)      const;

        Segment SegmentOfPlanesIntersection(const Plane& p1)    const;

        double  DistanceFromPointToPlane(const Point& point)    const;

        bool    DistancesFromPointsToPlaneHaveOneSign(const Point&p1, const Point& p2, const Point& p3) const;

        void    PlaneDump()                                     const;
}; 

//-------------------------------------------------------------------------------//

#endif