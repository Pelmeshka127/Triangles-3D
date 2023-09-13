#include "vector.hpp"

double Vector::Length() const
{
    return (std::sqrt(x_ * x_ + y_ * y_ + z_ * z_));
}