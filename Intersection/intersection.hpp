#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "../Geometry/point.hpp"
#include "../Geometry/plane.hpp"
#include "../Geometry/vector.hpp"
#include "../Geometry/line.hpp"


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

bool CoplanarTriangleIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------//

#endif