#include <ctime>
#include <vector>
#include <fstream>
#include <set>

#include "Geometry/point.hpp"
#include "Geometry/line.hpp"
#include "Geometry/triangle.hpp"
#include "Intersection/intersection.hpp"

int main()
{
    std::clock_t start = clock();

    Point p1(0,0,0);

    Point p2(1,0,0);

    Point p3(-1,1,0);

    Point a1(-1,0,0);

    Point a2(-2,0,0);

    Point a3(0,-2,0);
    
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

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         std::cerr << "Incorrect value of args" << std::endl;
//         return -1;
//     }

//     std::ifstream test_file;

//     test_file.open(argv[1]);

//     size_t tr_numbers = 0;

//     test_file >> tr_numbers;

//     const std::clock_t start = clock();

//     std::vector<Triangle> triangles;

//     for (int i = 0; i < tr_numbers; i++)
//     {
//         double p1x = 0, p1y = 0, p1z = 0, p2x = 0, p2y = 0, p2z = 0, p3x = 0, p3y = 0, p3z = 0;

//         test_file >> p1x >> p1y >> p1z;
//         Point p1(p1x, p1y, p1z);

//         test_file >> p2x >> p2y >> p2z;
//         Point p2(p2x, p2y, p2z);

//         test_file >> p3x >> p3y >> p3z;
//         Point p3(p3x, p3y, p3z);

//         Triangle t(p1, p2, p3);

//         triangles.push_back(t);
//     }

//     for (auto x: triangles)
//     {
//         // x.TriangleDump();
//     }

//     std::set<size_t> intersecting_triangles;

//     for (size_t i = 0; i < tr_numbers; i++)
//     {
//         for (size_t j = 0; j < tr_numbers; j++)
//         {
//             if (i != j)
//             {
//                 if (TriangleIntersection(triangles[i], triangles[j]))
//                 {
//                     // std::cout << "Triangle " << i << " intersects triangle " << j << std::endl;
//                     intersecting_triangles.insert(i);
//                 }
//             }
//         }
//     }

//     for (auto x: intersecting_triangles)
//     {
//         std::cout << x << " ";
//     }

//     std::cout << std::endl;

//     std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

//     return 0;
// }