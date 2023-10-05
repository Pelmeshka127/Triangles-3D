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

    else if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 1;
    }

    else if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 2;
    }

    else if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return 3;
    }
    

    else if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 4;
    }

    else if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 5;
    }

    else if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 6;
    }

    else if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return 7;
    }

    return -1;
}

//-------------------------------------------------------------------------------//