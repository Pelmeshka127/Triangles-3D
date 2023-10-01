#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "../Geometry/point.hpp"
#include "../Geometry/plane.hpp"
#include "../Geometry/vector.hpp"
#include "../Geometry/line.hpp"
#include "../Geometry/triangle.hpp"

//-------------------------------------------------------------------------------//

bool AreSegmentsIntersect(const Segment& l1, const Segment& l2);

//-------------------------------------------------------------------------------//

double Direction(const Point& p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

bool TriangleIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

bool CoplanarTrianglesIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

double DistanceFromPointToPlane(const Plane& plane, const Point& point);

//-------------------------------------------------------------------------------//

double DistanceFromPointToTriangle(const Triangle& t, const Point& p);

//-------------------------------------------------------------------------------//

bool DistancesFromPointsToPlaneHaveOneSign(const Plane& plane, const Point&p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

bool FindTrianglesIntersectionByLine(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

Segment SegmentOfPlanesIntersection(const Plane& p1, const Plane& p2);

//-------------------------------------------------------------------------------//

std::vector<double> GetOptionsOfLine(const Triangle& t, const Segment& int_line, std::vector<double>& distance);

//-------------------------------------------------------------------------------//

bool OverlapIntervals(const std::vector<double>& t1, const std::vector<double>& t2);

#endif