#include "plane.hpp"
#include "line.hpp"

//-------------------------------------------------------------------------------//

bool Plane::ArePlanesParallel(const Plane& plane) const
{
    return double_numbers::IsEqual(B_ * plane.C_ - C_ * plane.B_ +
                                   C_ * plane.A_ - A_ * plane.C_ +
                                   A_ * plane.B_ - B_ * plane.A_, 0);
}

//-------------------------------------------------------------------------------//

bool Plane::ArePlanesEqual(const Plane& plane) const
{
    using namespace double_numbers;

    return (ArePlanesParallel(plane) && IsEqual(A_ * plane.plane_point_.X() + 
                                                B_ * plane.plane_point_.Y() + 
                                                C_ * plane.plane_point_.Z() + D_, 0));
}

//-------------------------------------------------------------------------------//

Point Plane::PlaneSegmentIntersection(const Segment& l) const
{
    using namespace double_numbers;

    double denominator = l.DirVector().DotProduct(n(), l.DirVector());

    double t = 0;

    if (IsEqual(denominator, 0))
    {
        if (IsEqual(A() * l.Point1().X() + B() * l.Point1().Y() + C() * l.Point1().Z() + D(), 0))
        {
            t = 0;
            return l.Point1();   
        }
        
        else
            return Point();
    }

    else
    {
        t = A() * l.Point1().X() + B() * l.Point1().Y() + C() * l.Point1().Z() + D();

        t = -1 * t / denominator;

        return Point(l.Point1().X() + t * l.DirVector().X() +
                     l.Point1().Y() + t * l.DirVector().Y() +
                     l.Point1().Z() + t * l.DirVector().Z());
    }
}

//-------------------------------------------------------------------------------//

Segment Plane::SegmentOfPlanesIntersection(const Plane& p) const
{
    Vector direct_vector = n().CrossProductVector(n(), p.n());

    if (direct_vector.IsNullVector(direct_vector))
    {
        std::cerr << "Zero vector in " << __PRETTY_FUNCTION__ << std::endl;
    }

    double s1 = -D();
    
    double s2 = -p.D();

    double n1_n2_dot = n().DotProduct(n(), p.n());

    double n1_sqr    = n().DotProduct(n(), n());

    double n2_sqr    = p.n().DotProduct(p.n(), p.n());

    double a = (s2 * n1_n2_dot - s1 * n2_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    double b = (s1 * n1_n2_dot - s2 * n1_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    Point line_point1(a * A() + b * p.A(), a * B() + b * p.B(), a * C() + b * p.C());

    Segment intersection_line(line_point1, direct_vector);

    return intersection_line;
}

//-------------------------------------------------------------------------------//

double Plane::DistanceFromPointToPlane(const Point& point) const
{
    using namespace double_numbers;

    if (IsEqual(A() * A() + B() * B() + C() * C(), 0))
        return -1;

    if (IsEqual(point.X() * A() + point.Y() * B() + point.Z() * C() + D(), 0))
    {
        // point is in the plane
        return 0;
    }

    double distance = (A() * point.X() + B() * point.Y() + C() * point.Z() + D());

    return distance;
}

//-------------------------------------------------------------------------------//

bool Plane::DistancesFromPointsToPlaneHaveOneSign(const Point&p1, const Point& p2, const Point& p3) const
{
    if (DistanceFromPointToPlane(p1) > 0 && DistanceFromPointToPlane(p2) > 0 &&
        DistanceFromPointToPlane(p3) > 0 || DistanceFromPointToPlane(p1) < 0 &&
        DistanceFromPointToPlane(p2) < 0 && DistanceFromPointToPlane(p3) < 0)
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------//

void Plane::PlaneDump() const
{
    std::cout << "//=====Plane Equation=====//\n"
              << A_ << "x + " << B_ << "y + " << C_ << "z + " << D_ << std::endl
              << "//========================//\n";
}

//-------------------------------------------------------------------------------//