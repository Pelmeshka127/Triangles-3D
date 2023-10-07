#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#include "../Geometry/triangle.hpp"

//-------------------------------------------------------------------------------//

namespace SpacePart
{

enum SpacePart {
    First   = 1,
    Second  = 2,
    Third   = 3,
    Forth   = 4,
    Fifth   = 5,
    Sixth   = 6,
    Seventh = 7,
    Eighth  = 8,
    Multy   = -1,
};

}

//-------------------------------------------------------------------------------//

class Node
{
    public:
        Point MaxSize_;

        Point MinSize_;

        std::list<Triangle> triangles_{};
        
        Node *parent_ = nullptr;

        Node *child_[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

        Node() {}

        Node(const Point& max_size, const Point& min_size) :
            MaxSize_{max_size}, MinSize_{min_size} {}

        Node(const Point& max_size, const Point& min_size, const std::list<Triangle> triangle) : 
            triangles_{triangle}, MaxSize_{max_size}, MinSize_{min_size} {}
};

//-------------------------------------------------------------------------------//

class Octree
{
    private:
        Node *root;

        void DeleteTree(Node* node)
        {
            for (int i = 0; i < 8; i++)
            {
                if (node->child_[i])
                    DeleteTree(node->child_[i]);
                // else
                //     std::cout << "Child is ex child" << std::endl;
            }

            for (int i = 0; i < 8; i++)
            {
                delete node->child_[i];
                // std::cout << "deleting node " << node->child_[i] << std::endl;
            }
        }

    public:
        Octree(const Point& max, const Point& min, const std::list<Triangle>& triangles);

        ~Octree();

        Node* Root() const;
};

//-------------------------------------------------------------------------------//

SpacePart::SpacePart PartOfSpace(const Node& node, const Triangle& triangle);

//-------------------------------------------------------------------------------//

int DivideSpace(Node& node);

//-------------------------------------------------------------------------------//

#endif