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

    // плоскости равны, если коллинераны векторы нормали и точка, принадлежащая первой плоскости
    // удовлетворяет уравнению второй плоскости

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

void Plane::PlaneDump() const
{
    std::cout << "//=====Plane Equation=====//\n"
              << A_ << "x + " << B_ << "y + " << C_ << "z + " << D_ << std::endl
              << "//========================//\n";
}

//-------------------------------------------------------------------------------//