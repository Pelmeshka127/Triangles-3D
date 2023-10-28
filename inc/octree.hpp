#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#include "triangle.hpp"

//New

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
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
// //Old//

// namespace SpacePart
// {

// enum SpacePart {
//     First,
//     Second,
//     Third,
//     Forth,
//     Fifth,
//     Sixth,
//     Seventh,
//     Eighth,
//     Multy   = -1,
// };

// }

// //-------------------------------------------------------------------------------//

// class Node
// {
//     public:
//         Point MaxSize_;

//         Point MinSize_;

//         Point Middle_;

//         double Radius_;

//         std::list<Triangle> src_triangles_{};

//         std::list<Triangle> node_triangles_{};

//         bool is_leaf_ = true;

//         size_t active_node_mask_ = 0;
        
//         Node *parent_ = nullptr;

//         Node *child_[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

//         Node() {}

//         Node(const Point& max_size, const Point& min_size) :
//             MaxSize_{max_size}, MinSize_{min_size} {}

//         Node(const Point& max_size, const Point& min_size, const std::list<Triangle> triangle) : 
//             src_triangles_{triangle}, 
//             MaxSize_{max_size}, 
//             MinSize_{min_size},
//             Middle_{(max_size.X() + min_size.X()) / 2,
//                     (max_size.Y() + min_size.Y()) / 2, 
//                     (max_size.Z() + min_size.Z()) / 2} ,
//             Radius_{std::max(max_size.X(), std::max(max_size.Y(), max_size.Z()))} {}

//         void Dump() const;
// };

// //-------------------------------------------------------------------------------//

// class Octree
// {
//     private:
//         Node *root;

//         void DeleteTree(Node* node)
//         {
//             for (int i = 0; i < 8; i++)
//             {
//                 if (node->child_[i])
//                     DeleteTree(node->child_[i]);
//                 // else
//                 //     std::cout << "Child is ex child" << std::endl;
//             }

//             for (int i = 0; i < 8; i++)
//             {
//                 delete node->child_[i];
//                 // std::cout << "deleting node " << node->child_[i] << std::endl;
//             }
//         }

//     public:
//         Octree(const Point& max, const Point& min, const std::list<Triangle>& triangles);

//         ~Octree();

//         Node* Root() const;
// };

// //-------------------------------------------------------------------------------//

// SpacePart::SpacePart PartOfSpace(const Node* node, const Triangle& triangle);

// //-------------------------------------------------------------------------------//

// int DivideSpace(Node* node);

// //-------------------------------------------------------------------------------//


#endif