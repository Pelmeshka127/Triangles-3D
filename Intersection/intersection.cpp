#include "intersection.hpp"
#include "../Geometry/vector.hpp"

double Direction(const Point& p1, const Point& p2, const Point& p3)
{
    Vector v1(p1, p2);
    
    Vector v2(p1, p3);

    return v1.CrossProductValue(v1, v2);
}

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3)
{
    // bool res = (std::min(p1.GetX(), p2.GetX()) <= p3.GetX() && p3.GetX() <= std::max(p1.GetX(), p2.GetX()) &&
    //         std::min(p1.GetY(), p2.GetY()) <= p3.GetY() && p3.GetY() <= std::max(p1.GetY(), p2.GetY()) &&
    //         std::min(p1.GetZ(), p2.GetZ()) <= p3.GetZ() && p3.GetZ() <= std::max(p1.GetZ(), p2.GetZ()) );

    // std::cout << res << std::endl;

    // std::cout <<(std::min(p1.GetX(), p2.GetX()) <= p3.GetX() && p3.GetX() <= std::max(p1.GetX(), p2.GetX())) <<std::endl;
    // std::cout <<(std::min(p1.GetY(), p2.GetY()) <= p3.GetY() && p3.GetY() <= std::max(p1.GetY(), p2.GetY())) <<std::endl;
    // std::cout <<(std::min(p1.GetZ(), p2.GetZ()) <= p3.GetZ() && p3.GetZ() <= std::max(p1.GetZ(), p2.GetZ())) <<std::endl;

    return (std::min(p1.GetX(), p2.GetX()) <= p3.GetX() && p3.GetX() <= std::max(p1.GetX(), p2.GetX()) &&
            std::min(p1.GetY(), p2.GetY()) <= p3.GetY() && p3.GetY() <= std::max(p1.GetY(), p2.GetY()) &&
            std::min(p1.GetZ(), p2.GetZ()) <= p3.GetZ() && p3.GetZ() <= std::max(p1.GetZ(), p2.GetZ()) );
}