#include <ctime>

#include "Geometry/point.hpp"
#include "Geometry/line.hpp"
#include "Geometry/triangle.hpp"
#include "Intersection/intersection.hpp"

#include <vector>

int main()
{
    std::clock_t start = clock();

    Point p1(0,-1,-1);

    Point p2(1,-1,-1);

    Point p3(0,1,2);

    Point a1(0,-2,0);

    Point a2(3,-2,0);

    Point a3(1,2,1);
    
    Triangle Triangle1(p1, p2, p3);

    Triangle Triangle2(a1, a2, a3);

    Triangle1.TriangleDump();

    Triangle2.TriangleDump();

    std::cout << TriangleIntersection(Triangle1, Triangle2) << std::endl;

    // std::vector<int> v1{1,2,3};

    // std::vector<int> v2{3,4,5};

    // int d = v1 * v2;

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}