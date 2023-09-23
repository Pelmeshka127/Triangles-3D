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

double Point::GetDistance(const Point &point) const
{
    return (std::sqrt(  (x_ - point.x_) * (x_ - point.x_) +
                        (y_ - point.y_) * (y_ - point.y_) +
                        (z_ - point.z_) * (z_ - point.z_)  ));
}

//-------------------------------------------------------------------------------//

double Point::CrossProductValue(const Point &point) const
{
    double first_value  = y_ * point.z_ - z_ * point.y_;
    double second_value = z_ * point.x_ - x_ * point.z_;
    double third_value  = x_ * point.y_ - y_ * point.x_;

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