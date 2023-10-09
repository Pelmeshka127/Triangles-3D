#include "octree.hpp"

//-------------------------------------------------------------------------------//

Octree::Octree(const Point& max, const Point& min, const std::list<Triangle>& triangles)
{
    root = new Node(max, min, triangles);
    if (root == nullptr)
    {
        std::cerr << "Alocation error of tree root in " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }

    // std::cout << "Root was allocated" << std::endl;
}

//-------------------------------------------------------------------------------//

Octree::~Octree()
{
    DeleteTree(root);

    // std::cout << "Destroctor is succeeeded" << std::endl;
}

//-------------------------------------------------------------------------------//

Node* Octree::Root() const
{
    return root;
}

//-------------------------------------------------------------------------------//

void Node::Dump() const
{
    std::cout << "\nDump of node " << this << std::endl;
    // std::cout << "It's parent is " << parent_ << std::endl;
    std::cout << "The size of src triangles is " << src_triangles_.size() << std::endl;
    std::cout << "The size of node triangles is " << node_triangles_.size() << std::endl;
    // std::cout << "Src triangles:\n";
    // for (auto x: src_triangles_)
    // {
    //     std::cout << x.number << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "Node triangles:\n";
    // for (auto x: node_triangles_)
    // {
    //     std::cout << x.number << " ";
    // }
    std::cout << std::endl;
}   

//-------------------------------------------------------------------------------//

SpacePart::SpacePart PartOfSpace(const Node* node, const Triangle& triangle)
{
    Point mid = (node->MaxSize_ + node->MinSize_) * 0.5;

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return SpacePart::First;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return SpacePart::Second;
    }

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return SpacePart::Third;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() > mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() > mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() > mid.Z())
    {
        return SpacePart::Forth;
    }
    

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return SpacePart::Fifth;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() > mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() > mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() > mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return SpacePart::Sixth;
    }

    if (triangle.P1().X() > mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() > mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() > mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return SpacePart::Seventh;
    }

    if (triangle.P1().X() < mid.X() && triangle.P1().Y() < mid.Y() && triangle.P1().Z() < mid.Z() &&
        triangle.P2().X() < mid.X() && triangle.P2().Y() < mid.Y() && triangle.P2().Z() < mid.Z() &&
        triangle.P3().X() < mid.X() && triangle.P3().Y() < mid.Y() && triangle.P3().Z() < mid.Z())
    {
        return SpacePart::Eighth;
    }

    return SpacePart::Multy;
}

//-------------------------------------------------------------------------------//

int DivideSpace(Node* node)
{
    if (node->src_triangles_.size() <= 8)
    {
        for (auto t = node->src_triangles_.begin(); t != node->src_triangles_.end(); t++)
            node->node_triangles_.push_back(*t);
        // node->Dump();
        return 0;
    }

    // node->MaxSize_.PrintPoint();
    // node->MinSize_.PrintPoint();

    // std::cout << "The size of this main node "<< node << " is " << node->src_triangles_.size() << std::endl;
    for (auto triangle = node->src_triangles_.begin(); triangle != node->src_triangles_.end(); triangle++)
    {
        int space_part = PartOfSpace(node, *triangle);
        // std::cout << space_part << std::endl;

        if (space_part != SpacePart::Multy)
        {
            // std::cout << node->child_[space_part] << " and " << space_part << std::endl;
            if (node->child_[space_part] == nullptr)
            {
                // std::cout << space_part << std::endl;
                Point min = node->MinSize_;

                Point max = node->MaxSize_;
                switch(space_part)
                {
                    case SpacePart::First:
                    {
                        // x > 0, y > 0, z > 0
                        Point max_size = max;
                        Point min_size = (min + max) * 0.5;
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Second:
                    {
                        // x < 0, y > 0, z > 0
                        Point max_size = Point((min.X() + max.X()) * 0.5, max.Y(), max.Z());
                        Point min_size = Point(min.X(), (min.Y() + max.Y()) * 0.5, (min.Z() + max.Z()) * 0.5);
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Third:
                    {
                        // x > 0, y < 0, z > 0
                        Point max_size = Point(max.X(), (min.Y() + max.Y()) * 0.5, max.Z());
                        Point min_size = Point((min.X() + max.X()) * 0.5, min.Y(), (min.Z() + max.Z()) * 0.5);
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Forth:
                    {
                        // x < 0, y < 0, z > 0
                        Point max_size = Point((min.X() + max.X()) * 0.5, (min.Y() + max.Y()) * 0.5, max.Z());
                        Point min_size = Point(min.X(), min.Y(), (min.Z() + max.Z()) * 0.5);
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Fifth:
                    {
                        // x > 0, y > 0, z < 0
                        Point max_size = Point(max.X(), max.Y(), (min.Z() + max.Z()) * 0.5);
                        Point min_size = Point((min.X() + max.X()) * 0.5, (min.Y() + max.Y()) * 0.5, min.Z());
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Sixth:
                    {
                        // x < 0, y > 0, z > 0
                        Point max_size = Point((min.X() + max.X()) * 0.5, max.Y(), (min.Z() + max.Z()) * 0.5);
                        Point min_size = Point(min.X(), (min.Y() + max.Y()) * 0.5, min.Z());
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Seventh:
                    {
                        // x > 0, y < 0, z > 0
                        Point max_size = Point(max.X(), (min.Y() + max.Y()) * 0.5, (min.Z() + max.Z()) * 0.5);
                        Point min_size = Point((min.X() + max.X()) * 0.5, min.Y(), min.Z());
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    case SpacePart::Eighth:
                    {
                        // x < 0, y < 0, z < 0
                        Point max_size = (min + max) * 0.5;
                        Point min_size = Point(min.X(), min.Y(), min.Z());
                        node->child_[space_part] = new Node(max_size, min_size);
                        node->child_[space_part]->parent_ = node;
                        break;
                    }

                    default:
                    {
                        std::cerr << "Incorrect space part " << space_part << std::endl;
                        return -1;
                    }
                }
            }
            node->child_[space_part]->src_triangles_.push_back(*triangle);
            // triangle = node->src_triangles_.erase(triangle);
            // std::cout << "The " << space_part << " child node has size " << node->child_[space_part]->src_triangles_.size() << std::endl;
        }
        else
        {
            node->node_triangles_.push_back(*triangle);
        }
    }

    // node->Dump();

    // std::cout << "The size of this main node "<< node << " after function is " << node->node_triangles_.size() << std::endl;

    // for (size_t i = 0; i < 8; i++)
    // {
    //     if (node->child_[i])
    //     {
    //         std::cout << "The " << i << " child node "<< node->child_[i] <<" has size " << node->child_[i]->src_triangles_.size() << std::endl;
    //     }
    // }

    for (size_t i = 0; i < 8; i++)
    {
        if (node->child_[i])
        {
            // std::cout << "Working with " << node->child_[i] << " " << i << std::endl;
            DivideSpace(node->child_[i]);
        }
    }

    return 0;
}

//-------------------------------------------------------------------------------//