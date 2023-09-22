#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "../Geometry/point.hpp"

double  Direction(const Point& p1, const Point& p2, const Point& p3);

bool    IsOnSegment(const Point& p1, const Point& p2, const Point& p3);

#endif