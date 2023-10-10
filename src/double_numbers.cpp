#include "double_numbers.hpp"

namespace double_numbers
{

bool IsEqual(double a, double b)
{
    return (std::abs(a - b) < Epsilon);
}

}