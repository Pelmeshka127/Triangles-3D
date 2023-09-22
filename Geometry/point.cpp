#include "point.hpp"

//-------------------------------------------------------------------------------//

double Point::GetX() const
{
    return x_;
}

//-------------------------------------------------------------------------------//

double Point::GetY() const
{
    return y_;
}

//-------------------------------------------------------------------------------//

double Point::GetZ() const
{
    return z_;
}

//-------------------------------------------------------------------------------//

bool Point::IsEqual(const Point &point) const
{
    return (double_numbers::IsEqual(x_, point.x_) &&
            double_numbers::IsEqual(y_, point.y_) &&
            double_numbers::IsEqual(z_, point.z_));
}

//-------------------------------------------------------------------------------//

double Point::GetDistance(const Point &p1, const Point &p2) const
{
    return (std::sqrt(  (p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
                        (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()) +
                        (p1.GetZ() - p2.GetZ()) * (p1.GetZ() - p2.GetZ())   ));
}

//-------------------------------------------------------------------------------//

double Point::CrossProductValue(const Point &p1, const Point &p2) const
{
    double first_value  = p1.y_ * p2.z_ - p1.z_ * p2.y_;
    double second_value = p1.z_ * p2.x_ - p1.x_ * p2.z_;
    double third_value  = p1.x_ * p2.y_ - p1.y_ * p2.x_;

    return first_value + second_value + third_value;
}

//-------------------------------------------------------------------------------//

Point Point::operator=(const Point p) const
{
    return Point(p.x_, p.y_, p.z_);
}

//-------------------------------------------------------------------------------//

Point Point::operator+(const Point &p) const
{
    return Point(p.x_ + x_, p.y_ + y_, p.z_ + z_);
}

//-------------------------------------------------------------------------------//

Point Point::operator-(const Point &p) const
{
    return Point(p.x_ - x_, p.y_ - y_, p.z_ - z_);
}

//-------------------------------------------------------------------------------//

void Point::PrintPoint() const
{
    std::cout << "Point " << "(" << x_ << ";" << y_ << ";" << z_ << ")" << std::endl;
}

//-------------------------------------------------------------------------------//