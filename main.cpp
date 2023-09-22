#include "Geometry/point.hpp"
#include "Geometry/line.hpp"

int main()
{
    Point p1(0,0,0);

    Point p2(2,0,0);

    Point p3(0,-1,0);

    Point p4(0,1,0);

    LineSegment line1(p1, p2);
    
    LineSegment line2(p3, p4);

    std::cout << line1.DoesLineSegmentIntersect(line1, line2) << std::endl;

    // std::cout << std::endl;

    // std::cout <<(std::min(0, 0) <= 0 && 0 <= std::max(0,0)) <<std::endl;

    return 0;
}