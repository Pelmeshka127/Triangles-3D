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

    Triangle Triangle1(p1, p2, p3);

    Point a1(3,3,0);

    Point a2(5,1,0);

    Point a3(-1,-1,0);

    Triangle Triangle2(a1, a2, a3);

    Triangle1.TriangleDump();

    Triangle2.TriangleDump();

    std::cout << Triangle1.TrianglesIntersect(Triangle2) << std::endl;

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}