#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include <set>

#include "double_intersection.hpp"
#include "../Octree/octree.hpp"

//-------------------------------------------------------------------------------//

int TriangleIntersection(std::set<size_t>& intersects, Node* const root);

//-------------------------------------------------------------------------------//

int FindIntersectsInNode(std::set<size_t>& intersects, Node* const node);

//-------------------------------------------------------------------------------//

int FindIntersectionWithChildren(std::set<size_t>& intersects, const Triangle& triangle, Node* child);

//-------------------------------------------------------------------------------//

#endif