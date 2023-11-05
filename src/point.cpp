#include "point.hpp"

//-------------------------------------------------------------------------------//

bool Point::IsEqual(const Point &point) const
{
    return (double_numbers::IsEqual(x_, point.x_) &&
            double_numbers::IsEqual(y_, point.y_) &&
            double_numbers::IsEqual(z_, point.z_));
}

//-------------------------------------------------------------------------------//

double Point::MinCoordinate(const Point& p1, const Point& p2, const int coordinate) const
{
    switch(coordinate)
    {
        case cords::X:
            return std::min(std::min(x_, p1.x_), p2.x_);

        case cords::Y:
            return std::min(std::min(y_, p1.y_), p2.y_);

        case cords::Z:
            return std::min(std::min(z_, p1.z_), p2.z_);
        
        default:
            std::cerr << "Incorrect coordinate " << coordinate << std::endl;
            return -1;
    }
}

//-------------------------------------------------------------------------------//

double Point::MaxCoordinate(const Point& p1, const Point& p2, const int coordinate) const
{
    switch(coordinate)
    {
        case cords::X:
            return std::max(std::max(x_, p1.x_), p2.x_);

        case cords::Y:
            return std::max(std::max(y_, p1.y_), p2.y_);

        case cords::Z:
            return std::max(std::max(z_, p1.z_), p2.z_);
        
        default:
            std::cerr << "Incorrect coordinate " << coordinate << std::endl;
            return -1;
    }
}

//-------------------------------------------------------------------------------//

bool Point::operator==(const Point p) const
{
    return (double_numbers::IsEqual(x_, p.x_) &&
            double_numbers::IsEqual(y_, p.y_) &&
            double_numbers::IsEqual(z_, p.z_));
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

Point& Point::operator*=(const Point& p)
{
    x_ *= p.X();
    y_ *= p.Y();
    z_ *= p.Z();

    return *this;
}

//-------------------------------------------------------------------------------//

Point Point::operator*(const Point& p) const
{
    return Point(x_ * p.X(), y_ * p.Y(), z_ * p.Z());
}

//-------------------------------------------------------------------------------//

Point Point::operator*(const double& n) const
{
    return Point(x_ * n, y_ * n, z_ * n);
}

//-------------------------------------------------------------------------------//

void Point::PrintPoint() const
{
    std::cout << "Point " << "(" << x_ << ";" << y_ << ";" << z_ << ")" << std::endl;
}

//-------------------------------------------------------------------------------//