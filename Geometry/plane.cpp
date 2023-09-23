#include "plane.hpp"

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
    return (ArePlanesParallel(plane) && double_numbers::IsEqual(D_, plane.D_));
}

//-------------------------------------------------------------------------------//

void Plane::PlaneDump() const
{
    std::cout << "//=====Plane Equation=====//\n"
              << A_ << "x + " << B_ << "y + " << C_ << "z + " << D_ << std::endl
              << "//========================//\n";
}

//-------------------------------------------------------------------------------//