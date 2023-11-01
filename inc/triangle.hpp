#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <iostream>

#include "point.hpp"
#include "plane.hpp"
#include "line.hpp"
#include "vector.hpp"

#include <vector>

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
    Triangle_t,
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

        int number          = NonInitialized;

        bool status         = NonIntersect;

        TriangleType type_  = Triangle_t;

        Triangle(const Point &p1, const Point &p2, const Point &p3) : 
            p1_{p1}, p2_{p2}, p3_{p3}, 
            l1_{Segment(p1_, p2_)}, l2_{Segment(p2_, p3_)}, l3_{Segment(p3_, p1_)},
            v1_{Vector(p1_, p2_)}, v2_{Vector(p2_, p3_)}, v3_{Vector(p3_, p1_)},
            triangle_plane_{Plane(p1_, p2_, p3_)} 
        {
            type_ = GetType();
        }

        ~Triangle() {}

        Point   P1()    const { return p1_; }

        Point   P2()    const { return p2_; }

        Point   P3()    const { return p3_; }

        Segment Line1()     const { return l1_; }

        Segment Line2()     const { return l2_; }

        Segment Line3()     const { return l3_; }

        Vector  Vector1()   const { return v1_; }

        Vector  Vector2()   const { return v2_; }

        Vector  Vector3()   const { return v3_; }

        Plane   GetPlane()  const { return triangle_plane_; }

        TriangleType GetType() const;

        Segment GetNotZeroLine() const;

        bool    IsPointInTriangle(const Point& point) const;

        bool    TrianglePointIntersection(const Point& p) const;

        bool    TriangleSegmentIntersection(const Segment& l) const;

        bool    CoplanarTrianglesIntersection(const Triangle& t) const;

        double  DistanceFromPointToTriangle(const Point& p) const;

        bool    FindTrianglesIntersectionByLine(const Triangle& t) const;

        std::vector<double> GetLineOptions(const std::vector<double>& dis, const Segment& int_line) const;

        bool    TriangleTriangleIntersection(const Triangle& t) const;

        bool    TriangleIntersection(const Triangle& t) const;

        void    TriangleDump() const;
};

//-------------------------------------------------------------------------------//

bool    DistancesAreNotZero(double d1, double d2);

//-------------------------------------------------------------------------------//

bool    IntervalOverlap(std::vector<double>& t1, std::vector<double>& t2);

//-------------------------------------------------------------------------------//

#endif