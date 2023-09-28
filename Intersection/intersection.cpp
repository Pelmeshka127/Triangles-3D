#include "intersection.hpp"

//-------------------------------------------------------------------------------//

double Direction(const Point& p1, const Point& p2, const Point& p3)
{
    Vector v1(p1, p2);
    
    Vector v2(p1, p3);

    return v1.CrossProductValue(v1, v2);
}

//-------------------------------------------------------------------------------//

bool IsOnSegment(const Point& p1, const Point& p2, const Point& p3)
{
    // bool res = (std::min(p1.GetX(), p2.GetX()) <= p3.GetX() && p3.GetX() <= std::max(p1.GetX(), p2.GetX()) &&
    //         std::min(p1.GetY(), p2.GetY()) <= p3.GetY() && p3.GetY() <= std::max(p1.GetY(), p2.GetY()) &&
    //         std::min(p1.GetZ(), p2.GetZ()) <= p3.GetZ() && p3.GetZ() <= std::max(p1.GetZ(), p2.GetZ()) );

    // std::cout << res << std::endl;

    // std::cout <<(std::min(p1.GetX(), p2.GetX()) <= p3.GetX() && p3.GetX() <= std::max(p1.GetX(), p2.GetX())) <<std::endl;
    // std::cout <<(std::min(p1.GetY(), p2.GetY()) <= p3.GetY() && p3.GetY() <= std::max(p1.GetY(), p2.GetY())) <<std::endl;
    // std::cout <<(std::min(p1.GetZ(), p2.GetZ()) <= p3.GetZ() && p3.GetZ() <= std::max(p1.GetZ(), p2.GetZ())) <<std::endl;

    return (std::min(p1.X(), p2.X()) <= p3.X() && p3.X() <= std::max(p1.X(), p2.X()) &&
            std::min(p1.Y(), p2.Y()) <= p3.Y() && p3.Y() <= std::max(p1.Y(), p2.Y()) &&
            std::min(p1.Z(), p2.Z()) <= p3.Z() && p3.Z() <= std::max(p1.Z(), p2.Z()) );
}

//-------------------------------------------------------------------------------//

double DistanceFromPointToPlane(const Plane& plane, const Point& point)
{
    using namespace double_numbers;

    if (IsEqual(plane.A() * plane.A() + plane.B() * plane.B() + plane.C() * plane.C(), 0))
    {
        std::cerr << "Plane has zero normal vector in " << __PRETTY_FUNCTION__ << std::endl;
        return -1;
    }

    if (IsEqual(point.X() * plane.A() + point.Y() * plane.B() + point.Z() * plane.C() + plane.D(), 0))
    {
        // point is in the plane
        return 0;
    }

    double normal_length = std::sqrt(plane.A() * plane.A() + plane.B() * plane.B() + plane.C() * plane.C());

    double distance = (plane.A() * point.X() + plane.B() * point.Y() + plane.C() * point.Z() + plane.D()) / normal_length;

    return distance;
}

//-------------------------------------------------------------------------------//
 
bool DistancesFromPointsToPlaneHaveOneSign(const Plane& plane, const Point&p1, const Point& p2, const Point& p3)
{
    std::cout << "\nThe distances from points to plane:" << std::endl;
    std::cout << DistanceFromPointToPlane(plane, p1) << std::endl;
    std::cout << DistanceFromPointToPlane(plane, p2) << std::endl;
    std::cout << DistanceFromPointToPlane(plane, p3) << std::endl;
    std::cout << "End of distances\n\n";

    if (DistanceFromPointToPlane(plane, p1) > 0 && DistanceFromPointToPlane(plane, p2) > 0 &&
        DistanceFromPointToPlane(plane, p3) > 0 || DistanceFromPointToPlane(plane, p1) < 0 &&
        DistanceFromPointToPlane(plane, p2) < 0 && DistanceFromPointToPlane(plane, p3) < 0)
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------//

Segment SegmentOfPlanesIntersection(const Plane& p1, const Plane& p2)
{
    Vector direct_vector = p1.n().CrossProductVector(p1.n(), p2.n());

    if (direct_vector.IsNullVector(direct_vector))
    {
        std::cerr << "Zero vector in " << __PRETTY_FUNCTION__ << std::endl;
    }

    std::cout << "Direct ";
    direct_vector.PrintVector();

    double s1 = p1.D();
    
    double s2 = p2.D();

    double n1_n2_dot = p1.n().DotProduct(p1.n(), p2.n());

    double n1_sqr = p1.n().DotProduct(p1.n(), p1.n());

    double n2_sqr = p2.n().DotProduct(p2.n(), p2.n());

    double a = (s2 * n1_n2_dot - s1 * n2_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    double b = (s1 * n1_n2_dot - s2 * n1_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    Point line_point1(a * p1.A() + b * p2.A(), a * p1.B() + b * p2.B(), a * p1.C() + b * p2.C());

    Point line_point2(  line_point1.X() + direct_vector.X(),
                        line_point1.Y() + direct_vector.Y(),
                        line_point1.Z() + direct_vector.Z() );

    Segment intersection_line(line_point1, line_point2);

    intersection_line.PrintSegment();

    return intersection_line;
}

//-------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------//