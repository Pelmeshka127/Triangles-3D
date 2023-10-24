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
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//


// Octree::Octree(const Point& max, const Point& min, const std::list<Triangle>& triangles)
// {
//     root = new Node(max, min, triangles);
//     if (root == nullptr)
//     {
//         std::cerr << "Alocation error of tree root in " << __PRETTY_FUNCTION__ << std::endl;
//         return;
//     }

//     // root->Middle_.PrintPoint();

//     // std::cout << root->Radius_ << std::endl;

//     // std::cout << "Root was allocated" << std::endl;
// }

// //-------------------------------------------------------------------------------//

// Octree::~Octree()
// {
//     DeleteTree(root);

//     // std::cout << "Destroctor is succeeeded" << std::endl;
// }

// //-------------------------------------------------------------------------------//

// Node* Octree::Root() const
// {
//     return root;
// }

// //-------------------------------------------------------------------------------//

// void Node::Dump() const
// {
//     std::cout << "\nDump of node " << this << std::endl;
//     // std::cout << "It's parent is " << parent_ << std::endl;
//     std::cout << "The size of src triangles is " << src_triangles_.size() << std::endl;
//     std::cout << "The size of node triangles is " << node_triangles_.size() << std::endl;
//     // std::cout << "Src triangles:\n";
//     // for (auto x: src_triangles_)
//     // {
//     //     std::cout << x.number << " ";
//     // }
//     // std::cout << std::endl;
//     // std::cout << "Node triangles:\n";
//     // for (auto x: node_triangles_)
//     // {
//     //     std::cout << x.number << " ";
//     // }
//     std::cout << std::endl;
// }   

// //-------------------------------------------------------------------------------//

// SpacePart::SpacePart PartOfSpace(const Node* node, const Triangle& triangle)
// {
//     Point mid = (node->MaxSize_ + node->MinSize_) * 0.5;

//     if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
//         triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
//         triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
//     {
//         return SpacePart::First;
//     }

//     if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
//         triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
//         triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
//     {
//         return SpacePart::Second;
//     }

//     if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
//         triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
//         triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
//     {
//         return SpacePart::Third;
//     }

//     if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
//         triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
//         triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
//     {
//         return SpacePart::Forth;
//     }
    

//     if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
//         triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
//         triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
//     {
//         return SpacePart::Fifth;
//     }

//     if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
//         triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
//         triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
//     {
//         return SpacePart::Sixth;
//     }

//     if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
//         triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
//         triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
//     {
//         return SpacePart::Seventh;
//     }

//     if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
//         triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
//         triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
//     {
//         return SpacePart::Eighth;
//     }

//     return SpacePart::Multy;
// }

// //-------------------------------------------------------------------------------//

// int DivideSpace(Node* node)
// {
//     if (node->src_triangles_.size() <= 32)
//     {
//         for (auto t = node->src_triangles_.begin(); t != node->src_triangles_.end(); t++)
//             node->node_triangles_.push_back(*t);
//         return 0;
//     }

//     auto it = node->src_triangles_.begin();

//     auto end   = node->src_triangles_.end();

//     while(it != end)
//     {
//         int space_part = PartOfSpace(node, *it);

//         if (space_part != SpacePart::Multy)
//         {
//             if (node->child_[space_part] == nullptr)
//             {
//                 Point min = node->MinSize_;

//                 Point max = node->MaxSize_;

//                 switch(space_part)
//                 {
//                     case SpacePart::First:
//                     {
//                         // x > 0, y > 0, z > 0
//                         Point max_size = max;
//                         Point min_size = (min + max) * 0.5;
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Second:
//                     {
//                         // x < 0, y > 0, z > 0
//                         Point max_size = Point((min.X() + max.X()) * 0.5, max.Y(), max.Z());
//                         Point min_size = Point(min.X(), (min.Y() + max.Y()) * 0.5, (min.Z() + max.Z()) * 0.5);
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Third:
//                     {
//                         // x > 0, y < 0, z > 0
//                         Point max_size = Point(max.X(), (min.Y() + max.Y()) * 0.5, max.Z());
//                         Point min_size = Point((min.X() + max.X()) * 0.5, min.Y(), (min.Z() + max.Z()) * 0.5);
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Forth:
//                     {
//                         // x < 0, y < 0, z > 0
//                         Point max_size = Point((min.X() + max.X()) * 0.5, (min.Y() + max.Y()) * 0.5, max.Z());
//                         Point min_size = Point(min.X(), min.Y(), (min.Z() + max.Z()) * 0.5);
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Fifth:
//                     {
//                         // x > 0, y > 0, z < 0
//                         Point max_size = Point(max.X(), max.Y(), (min.Z() + max.Z()) * 0.5);
//                         Point min_size = Point((min.X() + max.X()) * 0.5, (min.Y() + max.Y()) * 0.5, min.Z());
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Sixth:
//                     {
//                         // x < 0, y > 0, z > 0
//                         Point max_size = Point((min.X() + max.X()) * 0.5, max.Y(), (min.Z() + max.Z()) * 0.5);
//                         Point min_size = Point(min.X(), (min.Y() + max.Y()) * 0.5, min.Z());
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Seventh:
//                     {
//                         // x > 0, y < 0, z > 0
//                         Point max_size = Point(max.X(), (min.Y() + max.Y()) * 0.5, (min.Z() + max.Z()) * 0.5);
//                         Point min_size = Point((min.X() + max.X()) * 0.5, min.Y(), min.Z());
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     case SpacePart::Eighth:
//                     {
//                         // x < 0, y < 0, z < 0
//                         Point max_size = (min + max) * 0.5;
//                         Point min_size = Point(min.X(), min.Y(), min.Z());
//                         node->child_[space_part] = new Node(max_size, min_size);
//                         node->child_[space_part]->parent_ = node;
//                         break;
//                     }

//                     default:
//                     {
//                         std::cerr << "Incorrect space part " << space_part << std::endl;
//                         return -1;
//                     }
//                 }
//             }
//             node->child_[space_part]->src_triangles_.push_back(*it);

//             it++;
            
//         }

//         else
//         {
//             node->node_triangles_.push_back(*it);

//             it++;
//         }
//     }

//     for (size_t i = 0; i < 8; i++)
//     {
//         if (node->child_[i])
//         {
//             node->active_node_mask_ |= (1 << i);

//             DivideSpace(node->child_[i]);
//         }
//     }

//     return 0;
// }
