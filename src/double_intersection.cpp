#include "double_intersection.hpp"

#include <vector>

//-------------------------------------------------------------------------------//

bool TriangleIntersection(const Triangle& t1, const Triangle& t2)
{
    TriangleType t1_type = t1.GetType();

    TriangleType t2_type = t2.GetType();

    switch (t1_type)
    {
        case Point_t:
        {
            switch (t2_type)
            {
                case Point_t:
                    // std::cout << "PointPoint for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.P1().PointPointIntersection(t1.P1());
                
                case Segment_t:
                // std::cout << "PointSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return t2.GetNotZeroLine().PointSegmentIntersection(t1.P1());

                case Triangle_t:
                // std::cout << "PointTrinagle for " << t1.number << " and " << t2.number<< std::endl;
                    return t2.TrianglePointIntersection(t1.P1());
            }
        }
        
        break;

        case Segment_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "SegmentPoint for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.GetNotZeroLine().PointSegmentIntersection(t2.P1());

                case Segment_t:
                // std::cout << "SegmentSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.GetNotZeroLine().SegmentSegmentIntersection(t2.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "SegmentTriangle for " << t1.number << " and " << t2.number<< std::endl;
                    return t2.TriangleSegmentIntersection(t1.GetNotZeroLine());
            }
        }

        break;

        case Triangle_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "TrianglePoint for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.TrianglePointIntersection(t2.P1());

                case Segment_t:
                // std::cout << "TriangleSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.TriangleSegmentIntersection(t2.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "TriangleTriangle for " << t1.number << " and " << t2.number<< std::endl;
                    return t1.TriangleTriangleIntersection(t2);
            }
        }

        break;
    }

    return false;
}

//-------------------------------------------------------------------------------//

bool DistancesFromPointsToPlaneHaveOneSign(const Plane& plane, const Point&p1, const Point& p2, const Point& p3)
{
    if (DistanceFromPointToPlane(plane, p1) > 0 && DistanceFromPointToPlane(plane, p2) > 0 &&
        DistanceFromPointToPlane(plane, p3) > 0 || DistanceFromPointToPlane(plane, p1) < 0 &&
        DistanceFromPointToPlane(plane, p2) < 0 && DistanceFromPointToPlane(plane, p3) < 0)
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------//

double DistanceFromPointToTriangle(const Triangle& t, const Point& p)
{
    return (t.GetPlane().n() * p + t.GetPlane().D());
}

//-------------------------------------------------------------------------------//

double DistanceFromPointToPlane(const Plane& plane, const Point& point)
{
    using namespace double_numbers;

    if (IsEqual(plane.A() * plane.A() + plane.B() * plane.B() + plane.C() * plane.C(), 0))
        return -1;

    if (IsEqual(point.X() * plane.A() + point.Y() * plane.B() + point.Z() * plane.C() + plane.D(), 0))
    {
        // point is in the plane
        return 0;
    }

    double distance = (plane.A() * point.X() + plane.B() * point.Y() + plane.C() * point.Z() + plane.D());

    return distance;
}

//-------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------//

Segment SegmentOfPlanesIntersection(const Plane& p1, const Plane& p2)
{
    Vector direct_vector = p1.n().CrossProductVector(p1.n(), p2.n());

    if (direct_vector.IsNullVector(direct_vector))
    {
        std::cerr << "Zero vector in " << __PRETTY_FUNCTION__ << std::endl;
    }

    double s1 = -p1.D();
    
    double s2 = -p2.D();

    double n1_n2_dot = p1.n().DotProduct(p1.n(), p2.n());

    double n1_sqr    = p1.n().DotProduct(p1.n(), p1.n());

    double n2_sqr    = p2.n().DotProduct(p2.n(), p2.n());

    double a = (s2 * n1_n2_dot - s1 * n2_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    double b = (s1 * n1_n2_dot - s2 * n1_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    Point line_point1(a * p1.A() + b * p2.A(), a * p1.B() + b * p2.B(), a * p1.C() + b * p2.C());

    Segment intersection_line(line_point1, direct_vector);

    return intersection_line;
}

//-------------------------------------------------------------------------------//

std::vector<double> GetLineOptions(const Triangle& t, const std::vector<double>& dis, const Segment& int_line)
{
    double p0 = int_line.DirVector() * t.P1()  - int_line.DirVector() * int_line.Point1();

    double p1 = int_line.DirVector() * t.P2() - int_line.DirVector() * int_line.Point1();

    double p2 = int_line.DirVector() * t.P3()  - int_line.DirVector() * int_line.Point1();

    std::vector<double> t_options(2);

    if (dis[0] * dis[1] >= 0 && DistancesAreNotZero(dis[1], dis[2]) && DistancesAreNotZero(dis[0], dis[2]))
    {
        t_options[0] = p0 + (p2 - p0) * (dis[0] / (dis[0] - dis[2]));

        t_options[1] = p1 + (p2 - p1) * (dis[1] / (dis[1] - dis[2]));

        if (t_options[0] > t_options[1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    if (dis[0] * dis[2] >= 0 && DistancesAreNotZero(dis[0], dis[1]) && DistancesAreNotZero(dis[2], dis[1]))
    {
        t_options[0] = p0 + (p1 - p0) * (dis[0] / (dis[0] - dis[1]));

        t_options[1] = p2 + (p1 - p2) * (dis[2] / (dis[2] - dis[1]));

        if (t_options[0] > t_options [1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    if (dis[1] * dis[2] >= 0 && DistancesAreNotZero(dis[1], dis[0]) && DistancesAreNotZero(dis[2], dis[0]))
    {
        t_options[0] = p1 + (p0 - p1) * (dis[1] / (dis[1] - dis[0]));

        t_options[1] = p2 + (p0 - p2) * (dis[2] / (dis[2] - dis[0]));

        if (t_options[0] > t_options[1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    return t_options;
}

//-------------------------------------------------------------------------------//

bool DistancesAreNotZero(double d1, double d2)
{
    using namespace double_numbers;

    return (!IsEqual(d1 - d2, 0));
}

//-------------------------------------------------------------------------------//

bool IntervalOverlap(std::vector<double>& t1, std::vector<double>& t2)
{
    if (t1[0] <= t2[0] && t2[0] <= t1[1])
        return true;

    if (t2[0] <= t1[0] && t1[0] <= t2[1])
        return true;

    return false;
}

//-------------------------------------------------------------------------------//