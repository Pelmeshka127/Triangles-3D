#ifndef LINE_HPP_
#define LINE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"
#include "vector.hpp"

// (x - x1) / (x1 - x2) = (y - y1) / (y1 - y2) = (z - z1) / (z - z2)

// (x - x1) / p = (y - y1) / q = (z - z1) / s

//-------------------------------------------------------------------------------//

class Segment
{
    private:
        const Point FirstPoint_;
        
        const Point SecondPoint_;

    public:
        // Segment() {}

        Segment(const Point &p1, const Point &p2) : FirstPoint_{p1}, SecondPoint_{p2} {}

        // Segment(const Point &point, const Vector& direct_vector) : FirstPoint_{point}, 
        // SecondPoint_{
        //     Point(point.GetX() + direct_vector.)
        // } {}

        ~Segment() {}

        bool IsSegmentIntersect(const Segment &line) const;

        void PrintSegment() const;
};

//-------------------------------------------------------------------------------//

#endif