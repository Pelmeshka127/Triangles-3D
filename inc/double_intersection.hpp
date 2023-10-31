#ifndef DOUBLE_INTERSECTION_HPP_
#define DOUBLE_INTERSECTION_HPP_

#include "point.hpp"
#include "plane.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "triangle.hpp"

#include <vector>

//-------------------------------------------------------------------------------//

bool    TriangleIntersection(const Triangle& t1, const Triangle& t2);

//-------------------------------------------------------------------------------//

double  DistanceFromPointToPlane(const Plane& plane, const Point& point);

//-------------------------------------------------------------------------------//

double  DistanceFromPointToTriangle(const Triangle& t, const Point& p);

//-------------------------------------------------------------------------------//

bool    DistancesFromPointsToPlaneHaveOneSign(const Plane& plane, const Point&p1, const Point& p2, const Point& p3);

//-------------------------------------------------------------------------------//

Segment SegmentOfPlanesIntersection(const Plane& p1, const Plane& p2);

//-------------------------------------------------------------------------------//

bool    DistancesAreNotZero(double d1, double d2);

//-------------------------------------------------------------------------------//

std::vector<double> GetLineOptions(const Triangle& t, const std::vector<double>& dis, const Segment& int_line);

//-------------------------------------------------------------------------------//

bool    IntervalOverlap(std::vector<double>& t1, std::vector<double>& t2);

//-------------------------------------------------------------------------------//

#endif