#ifndef LINE_HPP_
#define LINE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"
#include "../Intersection/intersection.hpp"

// (x - x1) / (x1 - x2) = (y - y1) / (y1 - y2) = (z - z1) / (z - z2)

// (x - x1) / p = (y - y1) / q = (z - z1) / s

//-------------------------------------------------------------------------------//

class LineSegment
{
    private:
        const Point FirstPoint_;
        
        const Point SecondPoint_;

    public:

        LineSegment(const Point &p1, const Point &p2) : FirstPoint_{p1}, SecondPoint_{p2} {}

        ~LineSegment() {}

        bool DoesLineSegmentIntersect(const LineSegment &l1, const LineSegment &l2) const;

        // void PrintLineSegment() const;
};

//-------------------------------------------------------------------------------//

#endif