#include <ctime>

#include "Geometry/point.hpp"
#include "Geometry/line.hpp"
#include "Geometry/triangle.hpp"

int main()
{
    std::clock_t start = clock();

    Point p1(0,0,0);

    Point p2(2,0,0);

    Point p3(0,-1,0);

    Point a1(3,3,0);

    Point a2(5,1,0);

    Point a3(2,0,0);

    // Segment l1(p1, p2);

    // Segment l2(a1, a3);

    // bool res = l1.IsSegmentIntersect(l2);

    // std::cout << "Lines intersection " << res << std::endl;
    
    Triangle Triangle1(p1, p2, p3);

    Triangle Triangle2(a1, a2, a3);

    Triangle1.TriangleDump();

    Triangle2.TriangleDump();

    std::cout << Triangle1.TrianglesIntersect(Triangle2) << std::endl;

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}