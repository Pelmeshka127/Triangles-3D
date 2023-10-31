#include "octree.hpp"

//-------------------------------------------------------------------------------//

OctreeNew::OctreeNew(const std::list<Triangle>& triangles, const Point& bounding_box)
{
    double radius = std::max(bounding_box.X(), std::max(bounding_box.Y(), bounding_box.Z()));

    Point middle(0,0,0);

    root_ = new OctNode(middle, radius);

    if (root_ == nullptr)
    {
        // std::cout << "Bad Alloc in " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }

    auto start = triangles.begin();

    auto end = triangles.end();

    while (start != end)
    {
        root_->src_triangles_.push_back(*start);

        start++;
    }

    DivideSpaces(root_);
}

//-------------------------------------------------------------------------------//

bool IsTriangleInBoundingBox(const Triangle& triangle, const Point& middle, const double& radius)
{
    return (IsPointInBox(triangle.P1(), middle, radius) &&
            IsPointInBox(triangle.P2(), middle, radius) &&
            IsPointInBox(triangle.P3(), middle, radius));
}

//-------------------------------------------------------------------------------//

bool IsTrianglePartInBoundingBox(const Triangle& triangle, const Point& middle, const double& radius)
{
    return (IsPointInBox(triangle.P1(), middle, radius) ||
            IsPointInBox(triangle.P2(), middle, radius) ||
            IsPointInBox(triangle.P3(), middle, radius));
}

//-------------------------------------------------------------------------------//

bool IsPointInBox(const Point& point, const Point& middle, const double& radius)
{
    double  min_x = middle.X() - radius,
            max_x = middle.X() + radius,
            min_y = middle.Y() - radius,
            max_y = middle.Y() + radius,
            min_z = middle.Z() - radius,
            max_z = middle.Z() + radius;

    return (min_x < point.X() && point.X() < max_x &&
            min_y < point.Y() && point.Y() < max_y &&
            min_z < point.Z() && point.Z() < max_z);
}

//-------------------------------------------------------------------------------//

void DivideSpaces(OctNode* node)
{
    if (node->src_triangles_.size() < 8)
        return;

    double new_radius = node->radius_ / 2;

    for (size_t i = 0; i < 8; i++)
    {
        double middle_x = node->middle_.X() + ((i & 1) ? new_radius : -new_radius);

        double middle_y = node->middle_.Y() + ((i & 2) ? new_radius : -new_radius);

        double middle_z = node->middle_.Z() + ((i & 4) ? new_radius : -new_radius);

        node->child_[i] = new OctNode(Point{middle_x, middle_y, middle_z}, new_radius);
    }

    size_t old_size = node->src_triangles_.size();

    auto it  = node->src_triangles_.begin();

    auto end = node->src_triangles_.end();

    while (it != end)
    {
        bool is_exist = true;

        for (size_t i = 0; i < 8; i++)
        {
            if (IsTriangleInBoundingBox(*it, node->child_[i]->middle_, node->child_[i]->radius_))
            {
                node->child_[i]->src_triangles_.push_back(*it);

                node->src_triangles_.erase(it++);

                is_exist = false;

                break;
            }
        }

        if (is_exist)
            it++;
    }

    if (old_size - node->src_triangles_.size())
        node->is_leaf_ = false;

    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i]->src_triangles_.size())
        {
            node->active_node_mask_ |= (1 << i);

            DivideSpaces(node->child_[i]);
        }
    }
}

//-------------------------------------------------------------------------------//

void OctreeNew::DeleteNode(OctNode* node)
{
    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i])
            DeleteNode(node->child_[i]);
    }

    for (size_t i = 0; i < 8; i++)
        delete node->child_[i];
}

//-------------------------------------------------------------------------------//