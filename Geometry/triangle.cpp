#include "triangle.hpp"

//-------------------------------------------------------------------------------//

bool Triangle::TrianglesIntersect(const Triangle& triangle) const
{
    if (triangle_plane_.ArePlanesEqual(triangle.triangle_plane_))
    {
        return CoplanarTrianglesIntersect(triangle);
    }

    return false;
}

//-------------------------------------------------------------------------------//

bool Triangle::CoplanarTrianglesIntersect(const Triangle& triangle) const
{
    // std::cout << l1_.IsSegmentIntersect(triangle.l1_) << std::endl; 
    // std::cout << l1_.IsSegmentIntersect(triangle.l2_) << std::endl; 
    // std::cout << l1_.IsSegmentIntersect(triangle.l3_) << std::endl;
    // std::cout << l2_.IsSegmentIntersect(triangle.l2_) << std::endl; 
    // std::cout << l2_.IsSegmentIntersect(triangle.l2_) << std::endl; 
    // std::cout << l2_.IsSegmentIntersect(triangle.l3_) << std::endl;
    // std::cout << l3_.IsSegmentIntersect(triangle.l1_) << std::endl; 
    // std::cout << l3_.IsSegmentIntersect(triangle.l2_) << std::endl; 
    // std::cout << l3_.IsSegmentIntersect(triangle.l3_) << std::endl;

    if (l1_.IsSegmentIntersect(triangle.l1_) || 
        l1_.IsSegmentIntersect(triangle.l2_) || 
        l1_.IsSegmentIntersect(triangle.l3_) ||
        l2_.IsSegmentIntersect(triangle.l1_) || 
        l2_.IsSegmentIntersect(triangle.l2_) || 
        l2_.IsSegmentIntersect(triangle.l3_) ||
        l3_.IsSegmentIntersect(triangle.l1_) || 
        l3_.IsSegmentIntersect(triangle.l2_) || 
        l3_.IsSegmentIntersect(triangle.l3_)
        )

        return true;

    return false;
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

    std::cout << "Plane equation of the triangle" << std::endl;
    
    triangle_plane_.PlaneDump();

    std::cout << "//----------------------------------//\n\n";
}

//-------------------------------------------------------------------------------//