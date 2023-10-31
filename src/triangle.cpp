#include "triangle.hpp"
#include "coordinates.hpp"
#include "double_intersection.hpp"

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

bool Triangle::FindTrianglesIntersectionByLine(const Triangle& t) const
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

    if (DistancesFromPointsToPlaneHaveOneSign(GetPlane(), t.P1(), t.P2(), t.P3()) ||
        DistancesFromPointsToPlaneHaveOneSign(t.GetPlane(), P1(), P2(), P3()) )
    {
        // std::cout << "All distances from T1 points to P2 have one sign" << std::endl;
        return false;        
    }

    // рассматриваем случай пересечния тругольников по линии
    // пересечения их плоскостей

    else
    {
        // std::cout << "Triangles segment" << std::endl;
        return FindTrianglesIntersectionByLine(*this, t);
    }

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