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

        const Vector DirectionVector_;

    public:
        Segment(const Point &p1, const Point &p2) : 
        FirstPoint_{p1}, SecondPoint_{p2},
        DirectionVector_{p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z()} {}

        Segment(const Point& p, const Vector& v) : 
        FirstPoint_{p}, DirectionVector_{v},
        SecondPoint_{p.X() + v.X(), p.Y() + v.Y(), p.Z() + v.Z()} {}

        Segment(const Point& p1, const Point& p2, const Vector& v) :
        FirstPoint_{p1}, SecondPoint_{p2}, DirectionVector_{v} {}

        ~Segment() {}

        Point   Point1() const;

        Point   Point2() const;

        Vector  DirVector() const;

        void PrintSegment() const;
};

//-------------------------------------------------------------------------------//

#endif