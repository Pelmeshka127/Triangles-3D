#include "triangle.hpp"
#include "../MathLibs/coordinates.hpp"
#include "../Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

bool Triangle::TrianglesIntersect(const Triangle& triangle) const
{
    if (triangle_plane_.ArePlanesEqual(triangle.triangle_plane_))
    {
        std::cout << "Triangles are coplanar" << std::endl;
        return CoplanarTrianglesIntersect(triangle);
    }

    if (DistancesFromPointsToPlaneHaveOneSign(triangle.triangle_plane_, p1_, p2_, p3_) ||
        DistancesFromPointsToPlaneHaveOneSign(triangle_plane_, triangle.p1_, triangle.p2_, triangle.p3_))
    {
        std::cout << "All distances from T1 points to P2 have one sign" << std::endl;
        return false;
    }

    SegmentOfPlanesIntersection(triangle_plane_, triangle.triangle_plane_);

    std::cout << "Variant that haven't been done" << std::endl;
    return false;
}

//-------------------------------------------------------------------------------//

bool Triangle::CoplanarTrianglesIntersect(const Triangle& triangle) const
{
    // Проверка всех отрезков одного треугольника на пересечние
    // Со всеми отрезками другого треугольника

    if (l1_.IsSegmentIntersect(triangle.l1_) || 
        l1_.IsSegmentIntersect(triangle.l2_) || 
        l1_.IsSegmentIntersect(triangle.l3_) ||
        l2_.IsSegmentIntersect(triangle.l1_) || 
        l2_.IsSegmentIntersect(triangle.l2_) || 
        l2_.IsSegmentIntersect(triangle.l3_) ||
        l3_.IsSegmentIntersect(triangle.l1_) || 
        l3_.IsSegmentIntersect(triangle.l2_) || 
        l3_.IsSegmentIntersect(triangle.l3_)  ) 
    {
        return true;
    }

    // Достаточно проверить одну точку каждого треугольника 
    // Чтобы понять не находится ли один треугольник внутри другого

    else if (IsPointInTriangle(triangle.p1_) || triangle.IsPointInTriangle(p1_))
        return true;


    return false;
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

    std::cout << "The line segments of triangle are:" << std::endl;

    l1_.PrintSegment();

    l2_.PrintSegment();

    l3_.PrintSegment();

    std::cout << "Plane equation of the triangle" << std::endl;
    
    triangle_plane_.PlaneDump();

    std::cout << "//----------------------------------//\n\n";
}

//-------------------------------------------------------------------------------//