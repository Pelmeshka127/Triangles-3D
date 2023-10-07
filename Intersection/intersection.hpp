#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include <set>

#include "double_intersection.hpp"
#include "../Octree/octree.hpp"

//-------------------------------------------------------------------------------//

int TriangleIntersection(std::set<size_t>& intersects, Node* const node);

//-------------------------------------------------------------------------------//

#endif