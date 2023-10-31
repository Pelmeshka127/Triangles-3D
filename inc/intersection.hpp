#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include <set>

#include "double_intersection.hpp"
#include "octree.hpp"

//-------------------------------------------------------------------------------//

int FindIntersectionsInNode(OctNode* const node, bool* FlagArray);

//-------------------------------------------------------------------------------//

int FindIntersectionsWithChildren(OctNode* const node, const Triangle& tr, bool* FlagArray);

//-------------------------------------------------------------------------------//

#endif