#include "triangle.hpp"
#include "../MathLibs/coordinates.hpp"
#include "../Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

Point Triangle::FirstPoint() const
{
    return p1_;
}

//-------------------------------------------------------------------------------//

Point Triangle::SecondPoint() const
{
    return p2_;
}

//-------------------------------------------------------------------------------//

Point Triangle::ThirdPoint() const
{
    return p3_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::FirstLine() const
{
    return l1_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::SecondLine() const
{
    return l2_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::ThirdLine() const
{
    return l3_;
}

//-------------------------------------------------------------------------------//

Plane Triangle::TrianglePlane() const
{
    return triangle_plane_;
}

//-------------------------------------------------------------------------------//

bool Triangle::IsPointInTriangle(const Point& point) const
{
    return (p1_.MinCoordinate(p2_, p3_, cords::X) <= point.X() && point.X() <= p1_.MaxCoordinate(p2_, p3_, cords::X) &&
            p1_.MinCoordinate(p2_, p3_, cords::Y) <= point.Y() && point.Y() <= p1_.MaxCoordinate(p2_, p3_, cords::Y) &&
            p1_.MinCoordinate(p2_, p3_, cords::Z) <= point.Z() && point.Z() <= p1_.MaxCoordinate(p2_, p3_, cords::Z));
}

//-------------------------------------------------------------------------------//
        
void Triangle::TriangleDump() const
{
    std::cout << "\n\n//---------Triangle DUMP---------//\n";

    std::cout << "The triangle has coordinates:" << std::endl;
    
    p1_.PrintPoint();
    
    p2_.PrintPoint();
    
    p3_.PrintPoint();

    // std::cout << "The line segments of triangle are:" << std::endl;

    // l1_.PrintSegment();

    // l2_.PrintSegment();

    // l3_.PrintSegment();

    std::cout << "Plane equation of the triangle" << std::endl;
    
    triangle_plane_.PlaneDump();

    std::cout << "//----------------------------------//\n\n";
}

//-------------------------------------------------------------------------------//