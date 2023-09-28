#include <ctime>

#include "Geometry/point.hpp"
#include "Geometry/line.hpp"
#include "Geometry/triangle.hpp"

int main()
{
    std::clock_t start = clock();

    Point p1(0,1, 1);

    Point p2(-1,2,1);

    Point p3(-1, 1, 1);

    Point a1(0,0,2);

    Point a2(1,0,0);

    Point a3(-2,0,0);
    
    Triangle Triangle1(p1, p2, p3);

    Triangle Triangle2(a1, a2, a3);

    Triangle1.TriangleDump();

    Triangle2.TriangleDump();

    std::cout << Triangle1.TrianglesIntersect(Triangle2) << std::endl;

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}