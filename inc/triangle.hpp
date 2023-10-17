#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <iostream>

#include "point.hpp"
#include "plane.hpp"
#include "line.hpp"
#include "vector.hpp"

static const int NonInitialized = -1;

enum TriangleState
{
    NonIntersect = false,
    Intersect    = true,
};

enum TriangleType
{
    Point_t,
    Segment_t,
    Trinagle_t,
};

//-------------------------------------------------------------------------------//

class Triangle 
{
    private:
        const Point p1_;
        const Point p2_;
        const Point p3_;

        const Segment l1_;
        const Segment l2_;
        const Segment l3_;

        const Vector v1_;
        const Vector v2_;
        const Vector v3_;

        const Plane triangle_plane_;

    public:

        int number  = NonInitialized;

        bool status = NonIntersect;

        Triangle(const Point &p1, const Point &p2, const Point &p3) : 
            p1_{p1}, p2_{p2}, p3_{p3}, 
            l1_{Segment(p1, p2)}, l2_{Segment(p2, p3)}, l3_{Segment(p3, p1)},
            v1_{Vector(p1_, p2_)}, v2_{Vector(p2_, p3_)}, v3_{Vector(p3_, p1_)},
            triangle_plane_{Plane(p1, p2, p3)} {}

        ~Triangle() {}

        Point   P1()    const;

        Point   P2()    const;

        Point   P3()    const;

        Segment Line1()     const;

        Segment Line2()     const;

        Segment Line3()     const;

        Vector  Vector1()   const;

        Vector  Vector2()   const;

        Vector  Vector3()   const;

        Plane   GetPlane()  const;

        TriangleType GetType() const;

        bool    IsPointInTriangle(const Point& point) const;

        void    TriangleDump() const;
};

//-------------------------------------------------------------------------------//

#endif