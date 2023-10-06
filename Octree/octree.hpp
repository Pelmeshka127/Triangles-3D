#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <iostream>
#include <algorithm>
#include <vector>

#include "../Geometry/triangle.hpp"

//-------------------------------------------------------------------------------//

class Octree
{
    private:
        const Point max_size_;

        const Point min_size_;

        const std::vector<Triangle> triangles_;

        Octree *node_triangles_[8];  // pointer to the array of 8 elements;

        Octree *parent_;

        char Mask = 0; // shows how many nodes are in actively used

    public:
        Octree() {};

        Octree(const Point& max_size, const Point& min_size, const std::vector<Triangle> t) :
            max_size_{max_size}, min_size_{min_size}, triangles_{t} {}

        ~Octree() {};

        size_t GetTriangleCount() const;

        Point GetMaxSize() const;

        Point GetMinSize() const;

        std::vector<Triangle> GetTriangles() const;

        void OctreeDump() const;
};

//-------------------------------------------------------------------------------//

int GetPartOfSpace(const Octree& octree, const Triangle& triangle);

//-------------------------------------------------------------------------------//

int DivideSpace(const Octree&octree, const Triangle& triangle);

//-------------------------------------------------------------------------------//

#endif