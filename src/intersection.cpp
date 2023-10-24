#include "intersection.hpp"

//-------------------------------------------------------------------------------//

int FindIntersectionsInNode(OctNode* const node, bool* FlagArray)
{
    auto start = node->src_triangles_.begin();

    auto end = node->src_triangles_.end();

    auto prev_end = std::prev(node->src_triangles_.end());

    for (auto t1 = start; t1 != prev_end; ++t1)
    {
        for (auto t2 = std::next(t1); t2 != end; ++t2)
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
        if (!(node->active_node_mask_ & (1 << i)))
            continue;
        
        FindIntersectionsInNode(node->child_[i], FlagArray);
    }

    return 0;
}

//-------------------------------------------------------------------------------//

int FindIntersectionsWithChildren(OctNode* const node, const Triangle& tr, bool* FlagArray)
{
    if (node->is_leaf_ || node->active_node_mask_ == 0)
        return 0;

    for (size_t i = 0; i < 8; i++)
    {
        if (!(node->active_node_mask_ & (1 << i)))
            continue;

        if (!IsTrianglePartInBoundingBox(tr, node->child_[i]->middle_, node->child_[i]->radius_))
            continue;

        std::list<Triangle> ChildList = node->child_[i]->src_triangles_;

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

// //-------------------------------------------------------------------------------//


// //-------------------------------------------------------------------------------//

// int FindIntersectionsInNode(Node* const node, bool* FlagArray)
// {
//     // std::cout << node->node_triangles_.size() << std::endl;

//     auto prev_end = std::prev(node->node_triangles_.end());

//     auto end      = node->node_triangles_.end();

//     auto begin    = node->node_triangles_.begin();

//     for (auto t1 = begin; t1 != prev_end; ++t1)
//     {
//         for (auto t2 = std::next(t1); t2 != end; t2++)
//         {
//             if (TriangleIntersection(*t1, *t2))
//             {
//                 FlagArray[t1->number] = Intersect;
//                 FlagArray[t2->number] = Intersect;
//             }
//         }

//         FindIntersectionsWithChildren(node, *t1, FlagArray);
//     }

//     // for (size_t i = 0; i < 8; i++)
//     // {
//     //     if (node->child_[i])
//     //         std::cout << node->child_[i]->node_triangles_.size() << std::endl;;
//     // }

//     for (size_t i = 0; i < 8; i++)
//     {
//         if (node->child_[i])
//         {
//             if (!(node->active_node_mask_ & (1 << i)))
//                 continue;
//             FindIntersectionsInNode(node->child_[i], FlagArray);
//         }
//     }

//     return 0;
// }

// //-------------------------------------------------------------------------------//

// int FindIntersectionsWithChildren(Node* const node, const Triangle& tr, bool* FlagArray)
// {
//     for (size_t i = 0; i < 8; i++)
//     {
//         if (!node->child_[i])
//             continue;

//         if (!(node->active_node_mask_ & (1 << i)))
//             continue;

//         if (!IsTrianglePartInBoundingBox(tr, node->child_[i]->Middle_, node->child_[i]->Radius_))
//             continue;

//         std::list<Triangle> ChildList = node->child_[i]->node_triangles_;

//         auto begin  = ChildList.begin();

//         auto end    = ChildList.end();

//         for (auto t1 = begin; t1 != end; ++t1)
//         {
//             if (TriangleIntersection(*t1, tr))
//             {
//                 FlagArray[t1->number] = Intersect;
//                 FlagArray[tr.number]  = Intersect;
//             }
//         }

//         FindIntersectionsWithChildren(node->child_[i], tr, FlagArray);
//     }

//     return 0;
// }

// //-------------------------------------------------------------------------------//