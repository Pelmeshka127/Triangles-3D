#include "intersection.hpp"

//-------------------------------------------------------------------------------//

int TriangleIntersection(std::set<size_t>& intersects, Node* const node)
{
    if (node->node_triangles_.size() < 1)
        return 0;

    // std::cout << "The size of this main node "<< node << " is " << node->node_triangles_.size() << std::endl;
    
    size_t number = 0;

    for (auto t1 = node->node_triangles_.begin(); t1 != node->node_triangles_.end(); t1++, number++)
    {
        for (auto t2 = std::next(t1); t2 != node->node_triangles_.end(); t2++)
        {
            if ((t1->status == NonIntersect || t2->status == NonIntersect) && TwoTriangleIntersection(*t1, *t2))
            {
                intersects.insert(t1->number);
                t1->status = Intersect;
                t2->status = Intersect;
            }
        }
    }

    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i])
            TriangleIntersection(intersects, node->child_[i]);
    }

    return 0;
}

//-------------------------------------------------------------------------------//