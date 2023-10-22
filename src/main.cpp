#include <ctime>
#include <vector>
#include <fstream>
#include <set>

#include "triangle.hpp"
#include "double_intersection.hpp"
#include "octree.hpp"
#include "coordinates.hpp"
#include "intersection.hpp"

//-------------------------------------------------------------------------------//

int main()
{
    size_t tr_numbers = 0;

    std::cin >> tr_numbers;

    std::list<Triangle> triangles;

    double BoundingBoxX = 0, BoundingBoxY = 0, BoundingBoxZ = 0;

    for (int i = 0; i < tr_numbers; i++)
    {
        double p1x = 0, p1y = 0, p1z = 0, p2x = 0, p2y = 0, p2z = 0, p3x = 0, p3y = 0, p3z = 0;

        std::cin >> p1x >> p1y >> p1z;
        Point p1(p1x, p1y, p1z);

        std::cin >> p2x >> p2y >> p2z;
        Point p2(p2x, p2y, p2z);

        std::cin >> p3x >> p3y >> p3z;
        Point p3(p3x, p3y, p3z);

        Triangle t(p1, p2, p3);

        t.number = i;

        triangles.push_back(t);

        // t.TriangleDump();

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

    std::clock_t start = clock();

    DivideSpace(oct.Root());

    bool *FlagArray = new bool [tr_numbers]{};

    FindIntersectionsInNode(oct.Root(), FlagArray);

    for (size_t i = 0; i < tr_numbers; i++)
    {
        if (FlagArray[i])
            std::cout << i << std::endl;
    }

    std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}

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

//     std::vector<Triangle> triangles;

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

//         // t.TriangleDump();

//         triangles.push_back(t);

//         if (BoundingBoxX < p1.MaxCoordinate(p2, p3, cords::X))
//             BoundingBoxX = p1.MaxCoordinate(p2, p3, cords::X);

//         if (BoundingBoxY < p1.MaxCoordinate(p2, p3, cords::Y))
//             BoundingBoxY = p1.MaxCoordinate(p2, p3, cords::Y);

//         if (BoundingBoxZ < p1.MaxCoordinate(p1, p2, cords::Z))
//             BoundingBoxZ = p1.MaxCoordinate(p1, p2, cords::Z);
//     }

//     // double CubeDimension = std::max(std::max(BoundingBoxX, BoundingBoxY), BoundingBoxZ);

//     // Point MaxSize{CubeDimension, CubeDimension, CubeDimension};
//     // Point MinSize{-1 * CubeDimension, -1 * CubeDimension, -1 * CubeDimension};

//     // Octree oct(MaxSize, MinSize, triangles);

//     // DivideSpace(oct.Root());

//     // triangles.erase(triangles.begin());

//     std::set<size_t> intersecting_triangles;

//     for (size_t i = 0; i < tr_numbers; i++)
//     {
//         for (size_t j = 0; j < tr_numbers; j++)
//         {
//             if (i == j)
//                 continue;
//             if (TwoTriangleIntersection(triangles[i], triangles[j]))
//             {
//                 // std::cout << "Triangle " << i << " is in " << PartOfSpace(*(oct.Root()), triangles[i]) << std::endl;
//                 intersecting_triangles.insert(i);
//             }
//         }
//     }

//     for (auto x: intersecting_triangles)
//     {
//         std::cout << x << std::endl;
//     }

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

//         t.number = i;

//         triangles.push_back(t);

//         // t.TriangleDump();

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

//     std::set<size_t> intersecting_triangles;

//     bool *FlagArray = new bool [tr_numbers]{};

//     FindIntersectionsInNode(oct.Root(), FlagArray);

//     for (size_t i = 0; i < tr_numbers; i++)
//     {
//         if (FlagArray[i])
//             std::cout << i << std::endl;
//     }

//     std::cout << "Total time is " << (clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

//     return 0;
// }

// //-------------------------------------------------------------------------------//