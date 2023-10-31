#include "line.hpp"

//-------------------------------------------------------------------------------//

Point Segment::Point1() const
{
    return FirstPoint_;
}

//-------------------------------------------------------------------------------//

Point Segment::Point2() const
{
    return SecondPoint_;
}

//-------------------------------------------------------------------------------//

Vector Segment::DirVector() const
{
    return DirectionVector_;
}

//-------------------------------------------------------------------------------//

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3)
{
    return (std::min(p1.X(), p2.X()) <= p3.X() && p3.X() <= std::max(p1.X(), p2.X()) &&
            std::min(p1.Y(), p2.Y()) <= p3.Y() && p3.Y() <= std::max(p1.Y(), p2.Y()) &&
            std::min(p1.Z(), p2.Z()) <= p3.Z() && p3.Z() <= std::max(p1.Z(), p2.Z()) );
}

//-------------------------------------------------------------------------------//

bool Segment::PointSegmentIntersection(const Point& p) const
{
    return IsOnSegment(Point1(), Point2(), p);
}

//-------------------------------------------------------------------------------//

Point Segment::LineIntersection(const Segment& l) const
{
    double param = (l.Point1().X() - Point1().X()) / (DirVector().X() - l.DirVector().X());

    Point p1 = Point(Point1().X() + param * DirVector().X(), Point1().Y() + param * DirVector().Y(), Point1().Z() + param * DirVector().Z());

    if (p1.IsValid())
        return p1;

    param = (l.Point1().Y() - Point1().Y()) / (DirVector().Y() - l.DirVector().Y());

    Point p2 = Point(Point1().X() + param * DirVector().X(), Point1().Y() + param * DirVector().Y(), Point1().Z() + param * DirVector().Z());

    if (p2.IsValid())
        return p2;

    param = (l.Point1().Z() - Point1().Z()) / (DirVector().Z() - l.DirVector().Z());

    Point p3 = Point(Point1().X() + param * DirVector().X(), Point1().Y() + param * DirVector().Y(), Point1().Z() + param * DirVector().Z());

    return p3;
}

//-------------------------------------------------------------------------------//

bool Segment::SegmentSegmentIntersection(const Segment& l) const
{
    Point p = LineIntersection(l);

    if (IsOnSegment(Point1(), Point2(), p) && IsOnSegment(l.Point1(), l.Point2(), p))
        return true;

    return false;
}

//-------------------------------------------------------------------------------//

void Segment::PrintSegment() const
{
    std::cout << "//----line----//" << std::endl;
    
    FirstPoint_.PrintPoint();
    
    SecondPoint_.PrintPoint();

    DirectionVector_.PrintVector();
    
    std::cout << "//------------//" << std::endl;
}

//-------------------------------------------------------------------------------//