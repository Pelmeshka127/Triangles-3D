#include "triangle.hpp"
#include "coordinates.hpp"

//-------------------------------------------------------------------------------//

TriangleType Triangle::GetType() const
{
    using namespace double_numbers;

    if (p1_ == p2_ && p1_ == p3_)
        return Point_t;

    else if (v1_.CrossProductVector(v1_, v2_) ==  NullVec ||
             v2_.CrossProductVector(v2_, v3_) ==  NullVec ||
             v3_.CrossProductVector(v3_, v1_) ==  NullVec)
    {
        return Segment_t;
    }

    return Triangle_t;
}

//-------------------------------------------------------------------------------//

Segment Triangle::GetNotZeroLine() const
{
    double v1_length  = v1_.SqrtLength();

    double v2_length  = v2_.SqrtLength();

    double v3_length  = v3_.SqrtLength();

    double max_length = std::max(v1_length, std::max(v2_length, v3_length));

    using namespace double_numbers;

    if (IsEqual(v1_length, max_length))
        return l1_;

    if (IsEqual(v2_length, max_length))
        return l2_;

    if (IsEqual(v3_length, max_length))
        return l3_;

    return l1_;
}

//-------------------------------------------------------------------------------//

bool Triangle::IsPointInTriangle(const Point& point) const
{
    Vector AP(p1_, point);
    Vector BP(p2_, point);
    Vector CP(p3_, point);

    double d1 = AP.CrossProductValue(v1_, AP);

    double d2 = BP.CrossProductValue(v2_, BP);

    double d3 = CP.CrossProductValue(v3_, CP);

    if (d1 * d2 < 0 || d1 * d3 < 0 || d2 * d3 < 0)
        return false;
    
    return true;
}

//-------------------------------------------------------------------------------//

bool Triangle::TrianglePointIntersection(const Point& p) const
{
    using namespace double_numbers;

    if (!IsEqual(GetPlane().A() * p.X() + GetPlane().B() * p.Y() + GetPlane().C() * p.Z() + GetPlane().D(), 0))
        return false;

    if (!IsPointInTriangle(p))
        return false;

    return true;
}

//-------------------------------------------------------------------------------//

bool Triangle::TriangleSegmentIntersection(const Segment& l) const
{
    if (TrianglePointIntersection(l.Point1()) || TrianglePointIntersection(l.Point2()))
        return true;

    if (l.SegmentSegmentIntersection(l1_) ||
        l.SegmentSegmentIntersection(l2_) ||
        l.SegmentSegmentIntersection(l3_))
    {
        return true;
    }

    Point plane_point = GetPlane().PlaneSegmentIntersection(l);

    if (!plane_point.IsValid())
        return false;

    if (l.PointSegmentIntersection(plane_point) && TrianglePointIntersection(plane_point))
        return true;

    return false;
}

//-------------------------------------------------------------------------------//

bool Triangle::CoplanarTrianglesIntersection(const Triangle& t) const
{
    // Проверка всех отрезков одного треугольника на пересечние
    // Со всеми отрезками другого треугольника

    if (Line1().SegmentSegmentIntersection (t.Line1())  || 
        Line1().SegmentSegmentIntersection (t.Line2())  || 
        Line1().SegmentSegmentIntersection (t.Line3())  ||
        Line2().SegmentSegmentIntersection (t.Line1())  || 
        Line2().SegmentSegmentIntersection (t.Line2())  || 
        Line2().SegmentSegmentIntersection (t.Line3())  ||
        Line3().SegmentSegmentIntersection (t.Line1())  || 
        Line3().SegmentSegmentIntersection (t.Line2())  || 
        Line3().SegmentSegmentIntersection (t.Line3())  ) 
    {
        // std::cout << "Segments intersect" << std::endl;
        return true;
    }

    // Достаточно проверить одну точку каждого треугольника 
    // Чтобы понять не находится ли один треугольник внутри другого

    else if (TrianglePointIntersection(t.P1()) || t.TrianglePointIntersection(P1()))
    {
        // std::cout << "One is in another" << std::endl;
        return true;
    }


    return false;
}

//-------------------------------------------------------------------------------//

double Triangle::DistanceFromPointToTriangle(const Point& p) const
{
    return (GetPlane().n() * p + GetPlane().D());
}

//-------------------------------------------------------------------------------//

std::vector<double> Triangle::GetLineOptions(const std::vector<double>& dis, const Segment& int_line) const
{
    double p0 = int_line.DirVector() * P1()  - int_line.DirVector() * int_line.Point1();

    double p1 = int_line.DirVector() * P2()  - int_line.DirVector() * int_line.Point1();

    double p2 = int_line.DirVector() * P3()  - int_line.DirVector() * int_line.Point1();

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

bool Triangle::FindTrianglesIntersectionByLine(const Triangle& t) const
{
    Segment int_line = GetPlane().SegmentOfPlanesIntersection(t.GetPlane());

    std::vector<double> dist_from_t1_to_points(3), dist_from_t2_to_points(3);

    dist_from_t1_to_points[0] = DistanceFromPointToTriangle(t.P1());

    dist_from_t1_to_points[1] = DistanceFromPointToTriangle(t.P2());

    dist_from_t1_to_points[2] = DistanceFromPointToTriangle(t.P3());

    dist_from_t2_to_points[0] = t.DistanceFromPointToTriangle(P1());

    dist_from_t2_to_points[1] = t.DistanceFromPointToTriangle(P2());

    dist_from_t2_to_points[2] = t.DistanceFromPointToTriangle(P3());

    std::vector<double> t_options_1 = GetLineOptions(dist_from_t2_to_points, int_line);

    std::vector<double> t_options_2 = t.GetLineOptions(dist_from_t1_to_points, int_line);

    return IntervalOverlap(t_options_1, t_options_2);
}

//-------------------------------------------------------------------------------//

bool Triangle::TriangleTriangleIntersection(const Triangle& t) const
{
    // сначала рассмотрим случай треугольников, лежащих в параллельных
    // или совпадающих плоскостях

    if (GetPlane().ArePlanesEqual(t.GetPlane()))
    {
        // std::cout << "Coplanar triangles" << std::endl;
        return CoplanarTrianglesIntersection(t);
    }

    // если все точки одного треугольника лежат по одну сторону от плоскости
    // другого тругольника, то пересечение невозможно

    if (GetPlane().DistancesFromPointsToPlaneHaveOneSign(t.P1(), t.P2(), t.P3()) ||
        t.GetPlane().DistancesFromPointsToPlaneHaveOneSign(P1(), P2(), P3()) )
    {
        // std::cout << "All distances from T1 points to P2 have one sign" << std::endl;
        return false;        
    }

    // рассматриваем случай пересечния тругольников по линии
    // пересечения их плоскостей

    else
    {
        // std::cout << "Triangles segment" << std::endl;
        return FindTrianglesIntersectionByLine(t);
    }

    return false;
}

//-------------------------------------------------------------------------------//

bool Triangle::TriangleIntersection(const Triangle& t) const
{
    TriangleType t1_type = GetType();

    TriangleType t2_type = t.GetType();

    switch (t1_type)
    {
        case Point_t:
        {
            switch (t2_type)
            {
                case Point_t:
                    // std::cout << "PointPoint for " << number << " and " << t.number<< std::endl;
                    return P1().PointPointIntersection(P1());
                
                case Segment_t:
                // std::cout << "PointSegment for " << number << " and " << t.number<< std::endl;
                    return t.GetNotZeroLine().PointSegmentIntersection(P1());

                case Triangle_t:
                // std::cout << "PointTrinagle for " << number << " and " << t.number<< std::endl;
                    return t.TrianglePointIntersection(P1());
            }
        }
        
        break;

        case Segment_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "SegmentPoint for " << number << " and " << t.number<< std::endl;
                    return GetNotZeroLine().PointSegmentIntersection(t.P1());

                case Segment_t:
                // std::cout << "SegmentSegment for " << number << " and " << t.number<< std::endl;
                    return GetNotZeroLine().SegmentSegmentIntersection(t.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "SegmentTriangle for " << number << " and " << t.number<< std::endl;
                    return t.TriangleSegmentIntersection(GetNotZeroLine());
            }
        }

        break;

        case Triangle_t:
        {
            switch (t2_type)
            {
                case Point_t:
                // std::cout << "TrianglePoint for " << number << " and " << t.number<< std::endl;
                    return TrianglePointIntersection(t.P1());

                case Segment_t:
                // std::cout << "TriangleSegment for " << number << " and " << t.number<< std::endl;
                    return TriangleSegmentIntersection(t.GetNotZeroLine());

                case Triangle_t:
                // std::cout << "TriangleTriangle for " << number << " and " << t.number<< std::endl;
                    return TriangleTriangleIntersection(t);
            }
        }

        break;
    }

    return false;
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
        
void Triangle::TriangleDump() const
{
    std::cout << "\n\n//---------Triangle DUMP---------//\n";

    std::cout << "The triangle has coordinates:" << std::endl;
    
    p1_.PrintPoint();
    
    p2_.PrintPoint();
    
    p3_.PrintPoint();

    std::cout << "The line segments of triangle are:" << std::endl;

    l1_.PrintSegment();

    l2_.PrintSegment();

    l3_.PrintSegment();

    std::cout << "The vectors of triangle are:" << std::endl;

    v1_.PrintVector();

    v2_.PrintVector();

    v3_.PrintVector();

    std::cout << "Triangle has number " << number << std::endl;

    std::cout << "Triangle has type " << type_ << std::endl;

    std::cout << "Plane equation of the triangle" << std::endl;
    
    triangle_plane_.PlaneDump();

    std::cout << "//----------------------------------//\n\n";
}

//-------------------------------------------------------------------------------//