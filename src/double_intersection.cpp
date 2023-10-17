#include "double_intersection.hpp"

#include <vector>

//-------------------------------------------------------------------------------//

bool TwoTriangleIntersection(const Triangle& t1, const Triangle& t2)
{
    // сначала рассмотрим случай треугольников, лежащих в параллельных
    // или совпадающих плоскостях

    if (t1.GetPlane().ArePlanesEqual(t2.GetPlane()))
    {
        // std::cout << "Coplanar triangles" << std::endl;
        return CoplanarTrianglesIntersection(t1, t2);
    }

    // если все точки одного треугольника лежат по одну сторону от плоскости
    // другого тругольника, то пересечение невозможно

    if (DistancesFromPointsToPlaneHaveOneSign(t1.GetPlane(), t2.P1(), t2.P2(), t2.P3()) ||
        DistancesFromPointsToPlaneHaveOneSign(t2.GetPlane(), t1.P1(), t1.P2(), t1.P3()) )
    {
        // std::cout << "All distances from T1 points to P2 have one sign" << std::endl;
        return false;        
    }

    // рассматриваем случай пересечния тругольников по линии
    // пересечения их плоскостей

    else
    {
        // std::cout << "Triangles segment" << std::endl;
        return FindTrianglesIntersectionByLine(t1, t2);
    }

    return false;
}

//-------------------------------------------------------------------------------//

// bool IsExceptionCase(const Triangle& t1, const Triangle& t2)
// {
//     return t1.IsPoint() || t2.IsPoint() || t1.IsSegment() || t2.IsSegment();
// }

//-------------------------------------------------------------------------------//

bool CoplanarTrianglesIntersection(const Triangle& t1, const Triangle& t2)
{
    // Проверка всех отрезков одного треугольника на пересечние
    // Со всеми отрезками другого треугольника

    if (AreSegmentsIntersect (t1.Line1(),  t2.Line1())  || 
        AreSegmentsIntersect (t1.Line1(),  t2.Line2())  || 
        AreSegmentsIntersect (t1.Line1(),  t2.Line3())  ||
        AreSegmentsIntersect (t1.Line2(),  t2.Line1())  || 
        AreSegmentsIntersect (t1.Line2(),  t2.Line2())  || 
        AreSegmentsIntersect (t1.Line2(),  t2.Line3())  ||
        AreSegmentsIntersect (t1.Line3(),  t2.Line1())  || 
        AreSegmentsIntersect (t1.Line3(),  t2.Line2())  || 
        AreSegmentsIntersect (t1.Line3(),  t2.Line3())  ) 
    {
        // std::cout << "Segments intersect" << std::endl;
        return true;
    }

    // Достаточно проверить одну точку каждого треугольника 
    // Чтобы понять не находится ли один треугольник внутри другого

    else if (IsPointInTriangle(t2.P1(), t1) || IsPointInTriangle(t1.P1(), t2))
    {
        // std::cout << "One is in another" << std::endl;
        return true;
    }


    return false;
}

//-------------------------------------------------------------------------------//

bool AreSegmentsIntersect(const Segment& l1, const Segment& l2)
{
    double drc1 = Direction(l2.Point1(), l2.Point2(), l1.Point1() );
    // std::cout << drc1 << std::endl;
    
    double drc2 = Direction(l2.Point1(), l2.Point2(), l1.Point2());
    // std::cout << drc2 << std::endl;
    
    double drc3 = Direction(l1.Point1(), l1.Point2(), l2.Point1() );
    // std::cout << drc3 << std::endl;
    
    double drc4 = Direction(l1.Point1(), l1.Point2(), l2.Point2());
    // std::cout << drc4 << std::endl;

    if ((drc1 * drc2 < 0) && (drc3 * drc4 < 0))
        return true;

    else if (drc1 == 0 && IsOnSegment(l2.Point1(), l2.Point2(), l1.Point1()))
        return true;

    else if (drc2 == 0 && IsOnSegment(l2.Point1(), l2.Point2(), l1.Point2()))
        return true;

    else if (drc3 == 0 && IsOnSegment(l1.Point1(), l1.Point2(), l2.Point1()))
        return true;

    else if (drc4 == 0 && IsOnSegment(l1.Point1(), l1.Point2(), l2.Point2()))
        return true;

    return false;
}

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
    return (std::min(p1.X(), p2.X()) <= p3.X() && p3.X() <= std::max(p1.X(), p2.X()) &&
            std::min(p1.Y(), p2.Y()) <= p3.Y() && p3.Y() <= std::max(p1.Y(), p2.Y()) &&
            std::min(p1.Z(), p2.Z()) <= p3.Z() && p3.Z() <= std::max(p1.Z(), p2.Z()) );
}

//-------------------------------------------------------------------------------//

bool IsPointInTriangle(const Point& p, const Triangle& t)
{
    Vector AB(t.P1(), t.P2());
    Vector AP(t.P1(), p);

    Vector BC(t.P2(), t.P3());
    Vector BP(t.P2(), p);

    Vector CA(t.P3(), t.P1());
    Vector CP(t.P3(), p);

    double d1 = AB.CrossProductValue(AB, AP);
    double d2 = BC.CrossProductValue(BC, BP);
    double d3 = CA.CrossProductValue(CA, CP);

    return (d1 * d2 >= 0 && d1 * d3 >=0 && d2 * d3 >= 0);
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
    {
        std::cerr << "Plane has zero normal vector in " << __PRETTY_FUNCTION__ << std::endl;
        return -1;
    }

    if (IsEqual(point.X() * plane.A() + point.Y() * plane.B() + point.Z() * plane.C() + plane.D(), 0))
    {
        // point is in the plane
        return 0;
    }

    double distance = (plane.A() * point.X() + plane.B() * point.Y() + plane.C() * point.Z() + plane.D());

    return distance;
}

//-------------------------------------------------------------------------------//

bool FindTrianglesIntersectionByLine(const Triangle& t1, const Triangle& t2)
{
    Segment int_line = SegmentOfPlanesIntersection(t1.GetPlane(), t2.GetPlane());

    std::vector<double> dist_from_t1_to_points(3), dist_from_t2_to_points(3);

    dist_from_t1_to_points[0] = DistanceFromPointToTriangle(t1, t2.P1());

    dist_from_t1_to_points[1] = DistanceFromPointToTriangle(t1, t2.P2());

    dist_from_t1_to_points[2] = DistanceFromPointToTriangle(t1, t2.P3());

    dist_from_t2_to_points[0] = DistanceFromPointToTriangle(t2, t1.P1());

    dist_from_t2_to_points[1] = DistanceFromPointToTriangle(t2, t1.P2());

    dist_from_t2_to_points[2] = DistanceFromPointToTriangle(t2, t1.P3());

    std::vector<double> t_options_1 = GetLineOptions(t1, dist_from_t2_to_points, int_line);

    std::vector<double> t_options_2 = GetLineOptions(t2, dist_from_t1_to_points, int_line);

    return IntervalOverlap(t_options_1, t_options_2);
}

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