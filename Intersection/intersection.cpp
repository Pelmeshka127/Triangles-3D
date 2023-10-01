#include "intersection.hpp"

#include <vector>

//-------------------------------------------------------------------------------//

bool TriangleIntersection(const Triangle& t1, const Triangle& t2)
{
    // сначала рассмотрим случай треугольников, лежащих в параллельных
    // или совпадающих плоскостях

    if (t1.TrianglePlane().ArePlanesEqual(t2.TrianglePlane()))
    {
        std::cout << "Coplanar triangles" << std::endl;
        return CoplanarTrianglesIntersection(t1, t2);
    }

    // если все точки одного треугольника лежат по одну сторону от плоскости
    // другого тругольника, то пересечение невозможно

    if (DistancesFromPointsToPlaneHaveOneSign(
        t1.TrianglePlane(), t2.FirstPoint(), t2.SecondPoint(), t2.ThirdPoint()) ||
        DistancesFromPointsToPlaneHaveOneSign(
        t2.TrianglePlane(), t1.FirstPoint(), t1.SecondPoint(), t1.ThirdPoint()
        ))
    {
        std::cout << "All distances from T1 points to P2 have one sign" << std::endl;
        return false;        
    }

    // рассматриваем случай пересечния тругольников по линии
    // пересечения их плоскостей

    else
    {
        std::cout << "Triangles segment" << std::endl;
        return FindTrianglesIntersectionByLine(t1, t2);
    }

    return false;
}

//-------------------------------------------------------------------------------//

bool CoplanarTrianglesIntersection(const Triangle& t1, const Triangle& t2)
{
    // Проверка всех отрезков одного треугольника на пересечние
    // Со всеми отрезками другого треугольника

    if (AreSegmentsIntersect (t1.FirstLine(),  t2.FirstLine() )  || 
        AreSegmentsIntersect (t1.FirstLine(),  t2.SecondLine())  || 
        AreSegmentsIntersect (t1.FirstLine(),  t2.ThirdLine() )  ||
        AreSegmentsIntersect (t1.SecondLine(), t2.FirstLine() )  || 
        AreSegmentsIntersect (t1.SecondLine(), t2.SecondLine())  || 
        AreSegmentsIntersect (t1.SecondLine(), t2.ThirdLine() )  ||
        AreSegmentsIntersect (t1.ThirdLine(),  t2.FirstLine() )  || 
        AreSegmentsIntersect (t1.ThirdLine(),  t2.SecondLine())  || 
        AreSegmentsIntersect (t1.ThirdLine(),  t2.ThirdLine() )  ) 
    {
        return true;
    }

    // Достаточно проверить одну точку каждого треугольника 
    // Чтобы понять не находится ли один треугольник внутри другого

    else if (t1.IsPointInTriangle(t2.FirstPoint()) || t2.IsPointInTriangle(t1.FirstPoint()))
        return true;


    return false;
}

//-------------------------------------------------------------------------------//

bool AreSegmentsIntersect(const Segment& l1, const Segment& l2)
{
    double drc1 = Direction(l2.FirstPoint(), l2.SecondPoint(), l1.FirstPoint() );
    // std::cout << drc1 << std::endl;
    
    double drc2 = Direction(l2.FirstPoint(), l2.SecondPoint(), l1.SecondPoint());
    // std::cout << drc2 << std::endl;
    
    double drc3 = Direction(l1.FirstPoint(), l1.SecondPoint(), l2.FirstPoint() );
    // std::cout << drc3 << std::endl;
    
    double drc4 = Direction(l1.FirstPoint(), l1.SecondPoint(), l2.SecondPoint());
    // std::cout << drc4 << std::endl;

    if ((drc1 * drc2 < 0) && (drc3 * drc4 < 0))
        return true;

    else if (drc1 == 0 && IsOnSegment(l2.FirstPoint(), l2.SecondPoint(), l1.FirstPoint()))
        return true;

    else if (drc2 == 0 && IsOnSegment(l2.FirstPoint(), l2.SecondPoint(), l1.SecondPoint()))
        return true;

    else if (drc3 == 0 && IsOnSegment(l1.FirstPoint(), l1.SecondPoint(), l2.FirstPoint()))
        return true;

    else if (drc4 == 0 && IsOnSegment(l1.FirstPoint(), l1.SecondPoint(), l2.SecondPoint()))
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

double DistanceFromPointToTriangle(const Triangle& t, const Point& p)
{
    return (t.TrianglePlane().n() * p + t.TrianglePlane().D());
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

    // double normal_length = std::sqrt(plane.A() * plane.A() + plane.B() * plane.B() + plane.C() * plane.C());

    // std::cout << "Normal length is " << normal_length << std::endl;

    double distance = (plane.A() * point.X() + plane.B() * point.Y() + plane.C() * point.Z() + plane.D());

    return distance;
}

//-------------------------------------------------------------------------------//

bool FindTrianglesIntersectionByLine(const Triangle& t1, const Triangle& t2)
{
    Segment int_line = SegmentOfPlanesIntersection(t1.TrianglePlane(), t2.TrianglePlane());

    // Point project_p1_t1 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t1.GetFirstPoint()  - int_line.GetFirstPoint());

    // Point project_p2_t1 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t1.GetSecondPoint() - int_line.GetFirstPoint());

    // Point project_p3_t1 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t1.GetThirdPoint()  - int_line.GetFirstPoint());

    // Point project_p1_t2 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t2.GetFirstPoint()  - int_line.GetFirstPoint());

    // Point project_p2_t2 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t2.GetSecondPoint()  - int_line.GetFirstPoint());

    // Point project_p3_t2 = (int_line.GetSecondPoint() - int_line.GetFirstPoint()) * (t2.GetThirdPoint()  - int_line.GetFirstPoint());

    // std::cout << "\nпроекции точек на пряму\n";

    // project_p1_t1.PrintPoint();

    // project_p2_t1.PrintPoint();

    // project_p3_t1.PrintPoint();

    // project_p1_t2.PrintPoint();

    // project_p2_t2.PrintPoint();

    // project_p3_t2.PrintPoint();

    // std::cout << "konec\n\n";

    std::vector<double> dist_from_t1_to_points(3), dist_from_t2_to_points(3);

    dist_from_t1_to_points[0] = DistanceFromPointToTriangle(t1, t2.FirstPoint());

    dist_from_t1_to_points[1] = DistanceFromPointToTriangle(t1, t2.SecondPoint());

    dist_from_t1_to_points[2] = DistanceFromPointToTriangle(t1, t2.ThirdPoint());

    dist_from_t2_to_points[0] = DistanceFromPointToTriangle(t2, t1.FirstPoint());

    dist_from_t2_to_points[1] = DistanceFromPointToTriangle(t2, t1.SecondPoint());

    dist_from_t2_to_points[2] = DistanceFromPointToTriangle(t2, t1.ThirdPoint());

    std::cout << "The distances:" << std::endl;
    std::cout << "From t1 to points of t2:" << std::endl;
    std::cout << dist_from_t1_to_points[0] << std::endl;
    std::cout << dist_from_t1_to_points[1] << std::endl;
    std::cout << dist_from_t1_to_points[2] << std::endl;
    std::cout << "From t12 to points of t1:" << std::endl;
    std::cout << dist_from_t2_to_points[0] << std::endl;
    std::cout << dist_from_t2_to_points[1] << std::endl;
    std::cout << dist_from_t2_to_points[2] << std::endl;
    std::cout << "The end of distances"<< std::endl;

    std::cout << "Calling function for t options" << std::endl;

    std::vector<double> t_options_1 = GetOptionsOfLine(t1, int_line, dist_from_t2_to_points);

    std::vector<double> t_options_2 = GetOptionsOfLine(t2, int_line, dist_from_t1_to_points);

    for (auto x : t_options_1)
    {
        std::cout<< x << std::endl;
    }

    for (auto x : t_options_2)
    {
        std::cout<< x << std::endl;
    }

    return OverlapIntervals(t_options_1, t_options_2);

    // double t_0_1 = project_p1_t1.X() + ((project_p2_t1.X() - project_p1_t1.X()) * (DistanceFromPointToPlane(t2.GetTrianglePlane(), t1.GetFirstPoint())) / (DistanceFromPointToPlane(t2.GetTrianglePlane(), t1.GetFirstPoint()) - DistanceFromPointToPlane(t2.GetTrianglePlane(), t1.GetSecondPoint())));

    // std::cout << "The t for p1 in t1 is: " << t_0_1 << std::endl;

    // return false;
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

    double s1 = -p1.D();
    
    double s2 = -p2.D();

    double n1_n2_dot = p1.n().DotProduct(p1.n(), p2.n());

    double n1_sqr    = p1.n().DotProduct(p1.n(), p1.n());

    double n2_sqr    = p2.n().DotProduct(p2.n(), p2.n());

    double a = (s2 * n1_n2_dot - s1 * n2_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    double b = (s1 * n1_n2_dot - s2 * n1_sqr) / (n1_n2_dot * n1_n2_dot - n1_sqr * n2_sqr);

    Point line_point1(a * p1.A() + b * p2.A(), a * p1.B() + b * p2.B(), a * p1.C() + b * p2.C());

    // Point line_point2(line_point1.X() + direct_vector.X(),
    //                   line_point1.Y() + direct_vector.Y(),
    //                   line_point1.Z() + direct_vector.Z());

    Segment intersection_line(line_point1, direct_vector);

    intersection_line.PrintSegment();

    return intersection_line;
}

//-------------------------------------------------------------------------------//

std::vector<double> GetOptionsOfLine(const Triangle& t, const Segment& int_line, std::vector<double>& distance)
{
    double p0 = int_line.DirectionVector() * t.FirstPoint()  - int_line.DirectionVector() * int_line.FirstPoint();

    double p1 = int_line.DirectionVector() * t.SecondPoint() - int_line.DirectionVector() * int_line.FirstPoint();

    double p2 = int_line.DirectionVector() * t.ThirdPoint()  - int_line.DirectionVector() * int_line.FirstPoint();

    std::vector<double> t_options(2);

    if (distance[0] * distance[1] > 0)
    {
        t_options[0] = p0 + (p2 - p0) * ((distance[0]) / (distance[0]) - distance[2]);

        t_options[1] = p1 + (p2 - p1) * ((distance[1]) / (distance[1]) - distance[2]);

        if (t_options[0] > t_options[1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    if (distance[0] * distance[2] > 0)
    {
        t_options[0] = p0 + (p1 - p0) * ((distance[0]) / (distance[0]) - distance[1]);

        t_options[1] = p2 + (p1 - p2) * ((distance[2]) / (distance[2]) - distance[1]);

        if (t_options[0] > t_options [1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    if (distance[1] * distance[2] > 0)
    {
        t_options[0] = p1 + (p0 - p1) * ((distance[1]) / (distance[1] - distance[0]));

        t_options[1] = p2 + (p0 - p1) * ((distance[2]) / (distance[2] - distance[0]));

        if (t_options[0] > t_options[1])
            std::swap(t_options[0], t_options[1]);

        return t_options;
    }

    return t_options;
}

//-------------------------------------------------------------------------------//

bool OverlapIntervals(const std::vector<double>& t1, const std::vector<double>& t2)
{
    using namespace double_numbers;

    if (t1[0] <= t2[0] && t2[0] <= t1[1])
        return true;

    if (t2[0] <= t1[0] && t1[0] <= t2[1])
        return true;

    if (IsEqual(t2[0], t1[1]))
        return true;

    if (IsEqual(t2[1], t1[0]))
        return true;

    return false;
}

//-------------------------------------------------------------------------------//