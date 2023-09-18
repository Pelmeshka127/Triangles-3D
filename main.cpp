#include "Include/line.hpp"

int main()
{
    Point p1(1,2,3);;

    Vector v1(-4, 1, 2);

    // Vector v2(4, 5, -3);

    // std::cout << &v1 << std::endl;

    // std::cout << &v2 << std::endl;

    // Vector v = v1 + v2;

    // std::cout << &v << std::endl;

    // v.PrintVector();

    Line l(p1, v1);

    l.PrintLine();

    return 0;
}