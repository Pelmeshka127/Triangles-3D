#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#include "triangle.hpp"

//-------------------------------------------------------------------------------//

bool IsTriangleInBoundingBox(const Triangle& triangle, const Point& middle, const double& radius);

//-------------------------------------------------------------------------------//

bool IsTrianglePartInBoundingBox(const Triangle& triangle, const Point& middle, const double& radius);

//-------------------------------------------------------------------------------//

bool IsPointInBox(const Point& point, const Point& middle, const double& radius);

//-------------------------------------------------------------------------------//

enum SpacePart {
    First,
    Second,
    Third,
    Forth,
    Fifth,
    Sixth,
    Seventh,
    Eighth,
    Multy = -1,
};

//-------------------------------------------------------------------------------//

class OctNode
{
    public:

        std::list<Triangle> src_triangles_{};

        OctNode* parent_ = nullptr;

        OctNode* child_[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

        const Point middle_ = {NAN, NAN, NAN};

        const double radius_ = 0;

        bool is_leaf_ = true;

        size_t active_node_mask_ = 0;

    public:

        OctNode(const Point& middle, const double& radius = NAN) : middle_{middle}, radius_{radius} {}
};

//-------------------------------------------------------------------------------//

class OctreeNew
{
    public:
        OctNode* root_ = nullptr;

    public:
        OctreeNew(const std::list<Triangle>& triangles, const Point& bounding_box);

        ~OctreeNew()
        {
            DeleteNode(root_);

            delete root_;
        }

        void DeleteNode(OctNode* node);
};

//-------------------------------------------------------------------------------//

void DivideSpaces(OctNode* node);

//-------------------------------------------------------------------------------//


#endif