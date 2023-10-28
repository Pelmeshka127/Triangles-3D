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

Segment Triangle::GetNotZeroLine() const
{
    double v1_length  = v1_.SqrtLength();

    double v2_length  = v2_.SqrtLength();

    double v3_length  = v3_.SqrtLength();

    double max_length = std::max(v1_length, std::max(v2_length, v3_length));

    using namespace double_numbers;

    if (IsEqual(v1_length, max_length))
        return l1_;

    if (IsEqual(v2_length, max_length))
        return l2_;

    if (IsEqual(v3_length, max_length))
        return l3_;

    return l1_;
}

//-------------------------------------------------------------------------------//

bool Triangle::IsPointInTriangle(const Point& point) const
{
    Vector AP(p1_, point);
    Vector BP(p2_, point);
    Vector CP(p3_, point);

    double d1 = AP.CrossProductValue(v1_, AP);

    double d2 = BP.CrossProductValue(v2_, BP);

    double d3 = CP.CrossProductValue(v3_, CP);

    if (d1 * d2 < 0 || d1 * d3 < 0 || d2 * d3 < 0)
        return false;
    
    return true;

    // return (p1_.MinCoordinate(p2_, p3_, cords::X) <= point.X() && point.X() <= p1_.MaxCoordinate(p2_, p3_, cords::X) &&
    //         p1_.MinCoordinate(p2_, p3_, cords::Y) <= point.Y() && point.Y() <= p1_.MaxCoordinate(p2_, p3_, cords::Y) &&
    //         p1_.MinCoordinate(p2_, p3_, cords::Z) <= point.Z() && point.Z() <= p1_.MaxCoordinate(p2_, p3_, cords::Z));
}

//-------------------------------------------------------------------------------//

TriangleType Triangle::GetType() const
{
    using namespace double_numbers;

    if (p1_ == p2_ && p1_ == p3_)
        return Point_t;

    else if (v1_.CrossProductVector(v1_, v2_) ==  NullVec ||
             v2_.CrossProductVector(v2_, v3_) ==  NullVec ||
             v3_.CrossProductVector(v3_, v1_) ==  NullVec)
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