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

double Plane::DistanceFromPointToPlane(const Point& point) const
{
    if (double_numbers::IsEqual(A_ * A_ + B_ * B_ + C_ * C_, 0))
    {
        std::cerr << "Plane has zero normal vector in " << __PRETTY_FUNCTION__ << std::endl;
        return -1;
    }

    // unnecessary if we know that points aren't in the plane
    // could be deleted for optimizing
    if (double_numbers::IsEqual(A_ * point.GetX() + B_ * point.GetY() + C_ * point.GetZ() + D_, 0))
        return 0;

    double normal_length = std::sqrt(A_*A_ + B_*B_ + C_*C_);

    double distance = double ((A_ * point.GetX() + B_ * point.GetY() + C_ * point.GetZ() + D_) / normal_length);

    return distance;
}

//-------------------------------------------------------------------------------//

bool Plane::AllDistancesHaveOneSign(const Point& p1, const Point& p2, const Point &p3) const
{
    std::cout << "\nThe distances from points to plane:" << std::endl;
    std::cout << DistanceFromPointToPlane(p1) << std::endl;
    std::cout << DistanceFromPointToPlane(p2) << std::endl;
    std::cout << DistanceFromPointToPlane(p3) << std::endl;
    std::cout << "End of distances\n\n";

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