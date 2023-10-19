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
                    return PointPointIntersection(t1.P1(), t2.P1());
                
                case Segment_t:
                // std::cout << "PointSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return PointSegmentIntersection(t1.P1(), t2.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "PointTrinagle for " << t1.number << " and " << t2.number<< std::endl;
                    return TrianglePointIntersection(t1.P1(), t2);
            }
        }
        
        break;

        case Segment_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "SegmentPoint for " << t1.number << " and " << t2.number<< std::endl;
                    return PointSegmentIntersection(t2.P1(), t1.GetNotZeroLine());

                case Segment_t:
                // std::cout << "SegmentSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return SegmentSegmentIntersection(t1.GetNotZeroLine(), t2.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "SegmentTriangle for " << t1.number << " and " << t2.number<< std::endl;
                    return TriangleSegmentIntersection(t2, t1.GetNotZeroLine());
            }
        }

        break;

        case Triangle_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "TrianglePoint for " << t1.number << " and " << t2.number<< std::endl;
                    return TrianglePointIntersection(t2.P1(), t1);

                case Segment_t:
                // std::cout << "TriangleSegment for " << t1.number << " and " << t2.number<< std::endl;
                    return TriangleSegmentIntersection(t1, t2.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "TriangleTriangle for " << t1.number << " and " << t2.number<< std::endl;
                    return TriangleTriangleIntersection(t1, t2);
            }
        }

        break;
    }

    return false;
}

//-------------------------------------------------------------------------------//

bool PointPointIntersection(const Point& p1, const Point& p2)
{
    return (p1 == p2);
}

//-------------------------------------------------------------------------------//

bool PointSegmentIntersection(const Point& p, const Segment& l)
{
    return IsOnSegment(l.Point1(), l.Point2(), p);
}

//-------------------------------------------------------------------------------//

bool TriangleSegmentIntersection(const Triangle& t, const Segment& l)
{
    if (TrianglePointIntersection(l.Point1(), t) || TrianglePointIntersection(l.Point2(), t))
    {
        // std::cout << "here" << std::endl;
        return true;
    }

    // if (SegmentSegmentIntersection(t.Line1(), l) ||
    //     SegmentSegmentIntersection(t.Line2(), l) ||
    //     SegmentSegmentIntersection(t.Line3(), l))
    // {
    //     t.Line1().PrintSegment();
    //     // t.Line2().PrintSegment();
    //     // t.Line3().PrintSegment();
    //     // l.PrintSegment();
    //     std::cout << "here" << std::endl;
    //     return true;
    // }

    Point plane_point = PlaneSegmentIntersection(t.GetPlane(), l);

    if (!plane_point.IsValid())
        return false;

    if (PointSegmentIntersection(plane_point, l) && TrianglePointIntersection(plane_point, t))
        return true;

    return false;
}

//-------------------------------------------------------------------------------//

bool TriangleTriangleIntersection(const Triangle& t1, const Triangle& t2)
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

Point PlaneSegmentIntersection(const Plane& p, const Segment& l)
{
    using namespace double_numbers;

    double denominator = l.DirVector().DotProduct(p.n(), l.DirVector());

    double t = 0;

    if (IsEqual(denominator, 0))
    {
        if (IsEqual(p.A() * l.Point1().X() + p.B() * l.Point1().Y() + p.C() * l.Point1().Z() + p.D(), 0))
        {
            t = 0;
            return l.Point1();   
        }
        
        else
            return Point();
    }

    else
    {
        t = p.A() * l.Point1().X() + p.B() * l.Point1().Y() + p.C() * l.Point1().Z() + p.D();

        t = -1 * t / denominator;

        return Point(l.Point1().X() + t * l.DirVector().X() +
                     l.Point1().Y() + t * l.DirVector().Y() +
                     l.Point1().Z() + t * l.DirVector().Z());
    }
}

//-------------------------------------------------------------------------------//

bool CoplanarTrianglesIntersection(const Triangle& t1, const Triangle& t2)
{
    // Проверка всех отрезков одного треугольника на пересечние
    // Со всеми отрезками другого треугольника

    if (SegmentSegmentIntersection (t1.Line1(),  t2.Line1())  || 
        SegmentSegmentIntersection (t1.Line1(),  t2.Line2())  || 
        SegmentSegmentIntersection (t1.Line1(),  t2.Line3())  ||
        SegmentSegmentIntersection (t1.Line2(),  t2.Line1())  || 
        SegmentSegmentIntersection (t1.Line2(),  t2.Line2())  || 
        SegmentSegmentIntersection (t1.Line2(),  t2.Line3())  ||
        SegmentSegmentIntersection (t1.Line3(),  t2.Line1())  || 
        SegmentSegmentIntersection (t1.Line3(),  t2.Line2())  || 
        SegmentSegmentIntersection (t1.Line3(),  t2.Line3())  ) 
    {
        // std::cout << "Segments intersect" << std::endl;
        return true;
    }

    // Достаточно проверить одну точку каждого треугольника 
    // Чтобы понять не находится ли один треугольник внутри другого

    else if (TrianglePointIntersection(t2.P1(), t1) || TrianglePointIntersection(t1.P1(), t2))
    {
        // std::cout << "One is in another" << std::endl;
        return true;
    }


    return false;
}

//-------------------------------------------------------------------------------//

bool SegmentSegmentIntersection(const Segment& l1, const Segment& l2)
{
    // l1.PrintSegment();
    // l2.PrintSegment();
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

bool TrianglePointIntersection(const Point& p, const Triangle& t)
{
    using namespace double_numbers;

    if (!IsEqual(t.GetPlane().A() * p.X() + t.GetPlane().B() * p.Y() + t.GetPlane().C() * p.Z() + t.GetPlane().D(), 0))
        return false;

    if (!t.IsPointInTriangle(p))
        return false;

    return true;
    // // Vector AB(t.P1(), t.P2());
    // Vector AP(t.P1(), p);

    // // Vector BC(t.P2(), t.P3());
    // Vector BP(t.P2(), p);

    // // Vector CA(t.P3(), t.P1());
    // Vector CP(t.P3(), p);

    // AP.PrintVector();
    // BP.PrintVector();
    // CP.PrintVector();

    // double d1 = t.Vector1().CrossProductValue(t.Vector1(), AP);
    // double d2 = t.Vector2().CrossProductValue(t.Vector2(), BP);
    // double d3 = t.Vector3().CrossProductValue(t.Vector3(), CP);

    // std::cout << d1 << " " << d2 << " " << d3 << std::endl;

    // t.TriangleDump();

    // p.PrintPoint();

    // // std::cout << (d1 * d2 >= 0 && d1 * d3 >=0 && d2 * d3 >= 0) <<std::endl;

    // return (d1 * d2 > 0 && d1 * d3 > 0 && d2 * d3 > 0);
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