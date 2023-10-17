#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include <set>

#include "double_intersection.hpp"
#include "octree.hpp"

//-------------------------------------------------------------------------------//

int FindIntersectionsInNode(Node* const node, bool* FlagArray);

//-------------------------------------------------------------------------------//

int FindIntersectionsWithChildren(Node* const node, const Triangle& tr, bool* FlagArray);

//-------------------------------------------------------------------------------//

#endif