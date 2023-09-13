#include "point.hpp"

void Point::PrintPoint() const
{
    std::cout << "(" << x_ << ";" << y_ << ";" << z_ << ")" << std::endl;
}

bool Point::IsEqual(const Point &point) const
{
    return (std::abs(x_ - point.x_) < Epsilon && 
            std::abs(y_ - point.y_) < Epsilon &&
            std::abs(z_ - point.z_) < Epsilon);
}