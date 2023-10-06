#include "octree.hpp"

//-------------------------------------------------------------------------------//

void Octree::OctreeDump() const
{
    std::cout << "//======Octree Dump=======//" << std::endl;
    std::cout << "Our space has dimensions::\n";
    std::cout << "From " << min_size_.X() << " to " << max_size_.X() << std::endl;
    std::cout << "From " << min_size_.Y() << " to " << max_size_.Y() << std::endl;
    std::cout << "From " << min_size_.Z() << " to " << max_size_.Z() << std::endl;
    std::cout << "//========End Dump========//" << std::endl;
}

//-------------------------------------------------------------------------------//

size_t Octree::GetTriangleCount() const
{
    return triangles_.size();
}

//-------------------------------------------------------------------------------//

Point Octree::GetMaxSize() const
{
    return max_size_;
}

//-------------------------------------------------------------------------------//

Point Octree::GetMinSize() const
{
    return min_size_;
}

//-------------------------------------------------------------------------------//

std::vector<Triangle> Octree::GetTriangles() const
{
    return triangles_;
}

//-------------------------------------------------------------------------------//

int GetPartOfSpace(const Octree& octree, const Triangle& triangle)
{
    Point mid = (octree.GetMaxSize() + octree.GetMinSize()) * 0.5;

    // mid.PrintPoint();

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 0;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 1;
    }

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 2;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 3;
    }
    

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 4;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 5;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 6;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 7;
    }

    return -1;
}

//-------------------------------------------------------------------------------//

int DivideSpace(const Octree& octree, const Triangle& triangles)
{
    if (octree.GetTriangleCount() <= 8)
        return 0;

    for (auto triangle: octree.GetTriangle())
    {
        switch()
    }

    return 0;
}

//-------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------//