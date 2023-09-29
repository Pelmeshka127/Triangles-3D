#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "../Geometry/point.hpp"
#include "../Geometry/plane.hpp"
#include "../Geometry/vector.hpp"
#include "../Geometry/line.hpp"
#include "../Geometry/triangle.hpp"


//-------------------------------------------------------------------------------//

double Direction(const Point& p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

double DistanceFromPointToPlane(const Plane& plane, const Point& point);

//-------------------------------------------------------------------------------//

bool DistancesFromPointsToPlaneHaveOneSign(const Plane& plane, const Point&p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

Segment SegmentOfPlanesIntersection(const Plane& p1, const Plane& p2);

//-------------------------------------------------------------------------------//

bool TriangleIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

bool CoplanarTrianglesIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

bool AreSegmentsIntersect(const Segment& l1, const Segment& l2);

//-------------------------------------------------------------------------------//

#endif