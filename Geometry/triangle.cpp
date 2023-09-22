#include "triangle.hpp"

//-------------------------------------------------------------------------------//
        
void Triangle::Dump() const
{
    std::cout << "The triangle has coordinates:" << std::endl;
    p1_.PrintPoint();
    p2_.PrintPoint();
    p3_.PrintPoint();
}

//-------------------------------------------------------------------------------//