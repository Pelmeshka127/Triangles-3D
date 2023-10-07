#include "plane.hpp"
#include "line.hpp"

//-------------------------------------------------------------------------------//

double Plane::A() const
{
    return A_;
}

//-------------------------------------------------------------------------------//

double Plane::B() const
{
    return B_;
}

//-------------------------------------------------------------------------------//

double Plane::C() const
{
    return C_;
}

//-------------------------------------------------------------------------------//

double Plane::D() const
{
    return D_;
}


Vector Plane::n() const
{
    return normal_vector_;
}

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

void Plane::PlaneDump() const
{
    std::cout << "//=====Plane Equation=====//\n"
              << A_ << "x + " << B_ << "y + " << C_ << "z + " << D_ << std::endl
              << "//========================//\n";
}

//-------------------------------------------------------------------------------//