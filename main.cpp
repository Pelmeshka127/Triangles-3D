#include <ctime>
#include <vector>
#include <fstream>
#include <set>

#include "Geometry/triangle.hpp"
#include "Intersection/double_intersection.hpp"
#include "Octree/octree.hpp"
#include "MathLibs/coordinates.hpp"
#include "Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

// int main()
// {
//     std::clock_t start = clock();

//     Point p1(1,1,0);

//     Point p2(3,1,0);

//     Point p3(1,1,2);

//     Point a1(2,2,2);

//     Point a2(1,1,2);

//     Point a3(2,1,2);
    
//     Triangle Triangle1(p1, p2, p3);

//     Triangle Triangle2(a1, a2, a3);

//     Triangle1.TriangleDump();

//     Triangle2.TriangleDump();

//     std::cout << TriangleIntersection(Triangle1, Triangle2) << std::endl;

//     // std::vector<int> v1{1,2,3};

//     // std::vector<int> v2{3,4,5};

//     // int d = v1 * v2;

//     std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

//     return 0;
// }

//-------------------------------------------------------------------------------//

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

//     std::list<Triangle> triangles;

//     // triangles.reserve(tr_numbers);

//     double BoundingBoxX = 0, BoundingBoxY = 0, BoundingBoxZ = 0;

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

//         if (BoundingBoxX < p1.MaxCoordinate(p2, p3, cords::X))
//             BoundingBoxX = p1.MaxCoordinate(p2, p3, cords::X);

//         if (BoundingBoxY < p1.MaxCoordinate(p2, p3, cords::Y))
//             BoundingBoxY = p1.MaxCoordinate(p2, p3, cords::Y);

//         if (BoundingBoxZ < p1.MaxCoordinate(p1, p2, cords::Z))
//             BoundingBoxZ = p1.MaxCoordinate(p1, p2, cords::Z);
//     }

//     double CubeDimension = std::max(std::max(BoundingBoxX, BoundingBoxY), BoundingBoxZ);

//     Point MaxSize{CubeDimension, CubeDimension, CubeDimension};
//     Point MinSize{-1 * CubeDimension, -1 * CubeDimension, -1 * CubeDimension};

//     Octree oct(MaxSize, MinSize, triangles);

//     DivideSpace(oct.Root());

//     // triangles.erase(triangles.begin());

//     // std::set<size_t> intersecting_triangles;

//     // for (size_t i = 0; i < tr_numbers; i++)
//     // {
//     //     for (size_t j = 0; j < tr_numbers; j++)
//     //     {
//     //         if (i == j)
//     //             continue;
//     //         if (TriangleIntersection(triangles[i], triangles[j]))
//     //         {
//     //             std::cout << "Triangle " << i << " is in " << PartOfSpace(*(oct.Root()), triangles[i]) << std::endl;
//     //             intersecting_triangles.insert(i);
//     //         }
//     //     }
//     // }

//     // for (auto x: intersecting_triangles)
//     // {
//     //     std::cout << x << std::endl;
//     // }

//     std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

//     return 0;
// }

//-------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Incorrect value of args" << std::endl;
        return -1;
    }

    std::ifstream test_file;

    test_file.open(argv[1]);

    size_t tr_numbers = 0;

    test_file >> tr_numbers;

    const std::clock_t start = clock();

    std::list<Triangle> triangles;

    double BoundingBoxX = 0, BoundingBoxY = 0, BoundingBoxZ = 0;

    for (int i = 0; i < tr_numbers; i++)
    {
        double p1x = 0, p1y = 0, p1z = 0, p2x = 0, p2y = 0, p2z = 0, p3x = 0, p3y = 0, p3z = 0;

        test_file >> p1x >> p1y >> p1z;
        Point p1(p1x, p1y, p1z);

        test_file >> p2x >> p2y >> p2z;
        Point p2(p2x, p2y, p2z);

        test_file >> p3x >> p3y >> p3z;
        Point p3(p3x, p3y, p3z);

        Triangle t(p1, p2, p3);

        triangles.push_back(t);

        if (BoundingBoxX < p1.MaxCoordinate(p2, p3, cords::X))
            BoundingBoxX = p1.MaxCoordinate(p2, p3, cords::X);

        if (BoundingBoxY < p1.MaxCoordinate(p2, p3, cords::Y))
            BoundingBoxY = p1.MaxCoordinate(p2, p3, cords::Y);

        if (BoundingBoxZ < p1.MaxCoordinate(p1, p2, cords::Z))
            BoundingBoxZ = p1.MaxCoordinate(p1, p2, cords::Z);
    }

    double CubeDimension = std::max(std::max(BoundingBoxX, BoundingBoxY), BoundingBoxZ);

    Point MaxSize{CubeDimension, CubeDimension, CubeDimension};
    Point MinSize{-1 * CubeDimension, -1 * CubeDimension, -1 * CubeDimension};

    Octree oct(MaxSize, MinSize, triangles);

    DivideSpace(oct.Root());

    std::cout << oct.Root()->node_triangles_.size() << std::endl;

    std::set<size_t> intersecting_triangles;

    TriangleIntersection(intersecting_triangles, oct.Root());

    // int num = 0;

    // for (auto i = triangles.begin(); i != triangles.end(); i++, num++)
    // {
    //     for (auto j = triangles.begin(); j != triangles.end(); j++)
    //     {
    //         if (i == j)
    //             continue;
    //         if (TwoTriangleIntersection(*i, *j))
    //         {
    //             // std::cout << "Triangle " << i << " intersects triangle " << j << std::endl;
    //             intersecting_triangles.insert(num);
    //         }
    //     }
    // }

    // for (auto x: intersecting_triangles)
    // {
    //     std::cout << x << std::endl;
    // }

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}

//-------------------------------------------------------------------------------//