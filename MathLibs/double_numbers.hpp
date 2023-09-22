#ifndef DOUBLE_NUMBERS_HPP_
#define DOUBLE_NUMBERS_HPP_

#include <iostream>
#include <cmath>

namespace double_numbers
{

const double Epsilon = 0.00001;

inline bool IsEqual(double a, double b)
{
    return (std::abs(a - b) < Epsilon);
}

// inline bool IsValueBetween(double a, double b, double c)
// {
//     return 
// }

}

#endif