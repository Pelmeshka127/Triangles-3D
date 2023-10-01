#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <iostream>

#include "point.hpp"
#include "plane.hpp"
#include "line.hpp"

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

        const Plane triangle_plane_;

    public:
        Triangle(const Point &p1, const Point &p2, const Point &p3) : p1_{p1}, p2_{p2}, p3_{p3}, 
            l1_{Segment(p1, p2)}, l2_{Segment(p2, p3)}, l3_{Segment(p3, p1)},
            triangle_plane_{Plane(p1, p2, p3)} {}

        ~Triangle() {}

        Point   FirstPoint() const;

        Point   SecondPoint() const;

        Point   ThirdPoint() const;

        Segment FirstLine()  const;

        Segment SecondLine() const;

        Segment ThirdLine()  const;

        Plane   TrianglePlane()  const;

        bool    IsPointInTriangle(const Point& point) const;

        void    TriangleDump() const;
};

//-------------------------------------------------------------------------------//

#endif