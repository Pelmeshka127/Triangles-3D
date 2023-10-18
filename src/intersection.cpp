#include "intersection.hpp"

//-------------------------------------------------------------------------------//

int FindIntersectionsInNode(Node* const node, bool* FlagArray)
{
    auto prev_end = std::prev(node->node_triangles_.end());

    auto end      = node->node_triangles_.end();

    auto begin    = node->node_triangles_.begin();

    for (auto t1 = begin; t1 != prev_end; ++t1)
    {
        for (auto t2 = std::next(t1); t2 != end; t2++)
        {
            if (TriangleIntersection(*t1, *t2))
            {
                FlagArray[t1->number] = Intersect;
                FlagArray[t2->number] = Intersect;
            }
        }

        FindIntersectionsWithChildren(node, *t1, FlagArray);
    }

    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i])
            FindIntersectionsInNode(node->child_[i], FlagArray);
    }

    return 0;
}

//-------------------------------------------------------------------------------//

int FindIntersectionsWithChildren(Node* const node, const Triangle& tr, bool* FlagArray)
{
    for (size_t i = 0; i < 8; i++)
    {
        if (!node->child_[i])
            continue;

        std::list<Triangle> ChildList = node->child_[i]->node_triangles_;

        auto begin  = ChildList.begin();

        auto end    = ChildList.end();

        for (auto t1 = begin; t1 != end; ++t1)
        {
            if (TriangleIntersection(*t1, tr))
            {
                FlagArray[t1->number] = Intersect;
                FlagArray[tr.number]  = Intersect;
            }
        }

        FindIntersectionsWithChildren(node->child_[i], tr, FlagArray);
    }

    return 0;
}

//-------------------------------------------------------------------------------//