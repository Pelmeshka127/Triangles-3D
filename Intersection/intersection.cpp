#include "intersection.hpp"

//-------------------------------------------------------------------------------//

int TriangleIntersection(std::set<size_t>& intersects, Node* const root)
{
    FindIntersectsInNode(intersects, root);

    return 0;
}

//-------------------------------------------------------------------------------//

int FindIntersectsInNode(std::set<size_t>& intersects, Node* const node)
{
    // node->Dump();
    for (auto t1 = node->node_triangles_.begin(); t1 != std::prev(node->node_triangles_.end()); t1++)
    {
        for (auto t2 = std::next(t1); t2 != node->node_triangles_.end(); t2++)
        {
            if (TwoTriangleIntersection(*t1, *t2))
            {
                intersects.insert(t1->number);
                intersects.insert(t2->number);
            }
        }
    }

    for (auto triangle = node->node_triangles_.begin(); triangle != node->node_triangles_.end(); triangle++)
    {
        for (size_t i = 0; i < 8; i++)
        {
            if (node->child_[i])
                FindIntersectionWithChildren(intersects, *triangle, node->child_[i]);
        }
    }

    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i])
            FindIntersectsInNode(intersects, node->child_[i]);
    }

    return 0;
}

//-------------------------------------------------------------------------------//

int FindIntersectionWithChildren(std::set<size_t>& intersects, const Triangle& triangle, Node* child)
{
    for (auto t1 = child->src_triangles_.begin(); t1 != child->src_triangles_.end(); t1++)
    {
        if (TwoTriangleIntersection(triangle, *t1))
        {
            intersects.insert(t1->number);
            intersects.insert(triangle.number);
        }
    }

    for (size_t i = 0; i < 8; i++)
    {
        if (child->child_[i])
            FindIntersectionWithChildren(intersects, triangle, child->child_[i]);
    }

    return 0;
}

//-------------------------------------------------------------------------------//