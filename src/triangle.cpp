#include "triangle.hpp"
#include "coordinates.hpp"
#include "double_intersection.hpp"

//-------------------------------------------------------------------------------//

Point Triangle::P1() const
{
    return p1_;
}

//-------------------------------------------------------------------------------//

Point Triangle::P2() const
{
    return p2_;
}

//-------------------------------------------------------------------------------//

Point Triangle::P3() const
{
    return p3_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::Line1() const
{
    return l1_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::Line2() const
{
    return l2_;
}

//-------------------------------------------------------------------------------//

Segment Triangle::Line3() const
{
    return l3_;
}

//-------------------------------------------------------------------------------//

Vector Triangle::Vector1() const
{
    return v1_;
}

//-------------------------------------------------------------------------------//

Vector Triangle::Vector2() const
{
    return v2_;
}

//-------------------------------------------------------------------------------//

Vector Triangle::Vector3() const
{
    return v3_;
}

//-------------------------------------------------------------------------------//

Plane Triangle::GetPlane() const
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

TriangleType Triangle::GetType() const
{
    using namespace double_numbers;

    if (p1_ == p2_ && p1_ == p3_)
        return Point_t;

    else if (IsEqual(v1_.CrossProductValue(v1_, v2_), 0) ||
             IsEqual(v2_.CrossProductValue(v2_, v3_), 0) ||
             IsEqual(v3_.CrossProductValue(v3_, v1_), 0))
    {
        return Segment_t;
    }

    return Triangle_t;
}

//-------------------------------------------------------------------------------//
        
void Triangle::TriangleDump() const
{
    std::cout << "\n\n//---------Triangle DUMP---------//\n";

    std::cout << "The triangle has coordinates:" << std::endl;
    
    p1_.PrintPoint();
    
    p2_.PrintPoint();
    
    p3_.PrintPoint();

    std::cout << "The line segments of triangle are:" << std::endl;

    l1_.PrintSegment();

    l2_.PrintSegment();

    l3_.PrintSegment();

    std::cout << "The vectors of triangle are:" << std::endl;

    v1_.PrintVector();

    v2_.PrintVector();

    v3_.PrintVector();

    std::cout << "Triangle has number " << number << std::endl;

    std::cout << "Triangle has type " << type_ << std::endl;

    std::cout << "Plane equation of the triangle" << std::endl;
    
    triangle_plane_.PlaneDump();

    std::cout << "//----------------------------------//\n\n";
}

//-------------------------------------------------------------------------------//