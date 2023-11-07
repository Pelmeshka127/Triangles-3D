#ifndef LINE_HPP_
#define LINE_HPP_

#include <iostream>
#include <cmath>

#include "point.hpp"
#include "vector.hpp"

//-------------------------------------------------------------------------------//

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

class Segment
{
    private:
        Point FirstPoint_;
        
        Point SecondPoint_;

        Vector DirectionVector_;

    public:
        Segment(const Point &p1, const Point &p2) : 
        FirstPoint_{p1}, SecondPoint_{p2},
        DirectionVector_{p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z()} {}

        Segment(const Point& p, const Vector& v) : 
        FirstPoint_{p}, DirectionVector_{v},
        SecondPoint_{p.X() + v.X(), p.Y() + v.Y(), p.Z() + v.Z()} {}

        Segment(const Point& p1, const Point& p2, const Vector& v) :
        FirstPoint_{p1}, SecondPoint_{p2}, DirectionVector_{v} {}

        Point   Point1() const { return FirstPoint_; }

        Point   Point2() const { return SecondPoint_; }

        Vector  DirVector() const { return DirectionVector_; }

        bool    PointSegmentIntersection(const Point& p) const
        {
            return IsOnSegment(Point1(), Point2(), p);
        }

        Point   LineIntersection(const Segment& l) const;

        bool    SegmentSegmentIntersection(const Segment& l) const;

        void PrintSegment() const;
};

//-------------------------------------------------------------------------------//

#endif