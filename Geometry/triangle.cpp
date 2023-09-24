#include "triangle.hpp"
#include "../MathLibs/coordinates.hpp"

//-------------------------------------------------------------------------------//

bool Triangle::TrianglesIntersect(const Triangle& triangle) const
{
    if (triangle_plane_.ArePlanesEqual(triangle.triangle_plane_))
        return CoplanarTrianglesIntersect(triangle);

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
        l3_.IsSegmentIntersect(triangle.l3_)   ) 
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
    // std::cout << "MAX and MIN\n";
    // std::cout << p1_.MinCoordinate(p2_, p3_, cords::X) << std::endl;
    // std::cout << point.GetX() << std::endl;
    // std::cout << p1_.MaxCoordinate(p2_, p3_, cords::X) << std::endl;
    // std::cout <<std::endl;
    // std::cout << p1_.MinCoordinate(p2_, p3_, cords::Y) << std::endl;
    // std::cout << point.GetY() << std::endl;
    // std::cout << p1_.MaxCoordinate(p2_, p3_, cords::Y) << std::endl;
    // std::cout << std::endl;
    // std::cout << p1_.MinCoordinate(p2_, p3_, cords::Z) << std::endl;
    // std::cout << point.GetZ() << std::endl;
    // std::cout << p1_.MaxCoordinate(p2_, p3_, cords::Z) << std::endl;
    // std::cout << "END MAX AND MIN\n";

    // std::cout << (p1_.MinCoordinate(p2_, p3_, cords::X) < point.GetX() < p1_.MaxCoordinate(p2_, p3_, cords::X) &&
    //             p1_.MinCoordinate(p2_, p3_, cords::Y) < point.GetY() < p1_.MaxCoordinate(p2_, p3_, cords::Y) &&
    //             p1_.MinCoordinate(p2_, p3_, cords::Z) < point.GetZ() < p1_.MaxCoordinate(p2_, p3_, cords::Z)) << std::endl;
    
    return (p1_.MinCoordinate(p2_, p3_, cords::X) <= point.GetX() && point.GetX() <= p1_.MaxCoordinate(p2_, p3_, cords::X) &&
            p1_.MinCoordinate(p2_, p3_, cords::Y) <= point.GetY() && point.GetY() <= p1_.MaxCoordinate(p2_, p3_, cords::Y) &&
            p1_.MinCoordinate(p2_, p3_, cords::Z) <= point.GetZ() && point.GetZ() <= p1_.MaxCoordinate(p2_, p3_, cords::Z));
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