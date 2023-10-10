#include "line.hpp"

//-------------------------------------------------------------------------------//

Point Segment::Point1() const
{
    return FirstPoint_;
}

//-------------------------------------------------------------------------------//

Point Segment::Point2() const
{
    return SecondPoint_;
}

//-------------------------------------------------------------------------------//

Vector Segment::DirVector() const
{
    return DirectionVector_;
}

//-------------------------------------------------------------------------------//

void Segment::PrintSegment() const
{
    std::cout << "//----line----//" << std::endl;
    
    FirstPoint_.PrintPoint();
    
    SecondPoint_.PrintPoint();
    
    std::cout << "//------------//" << std::endl;
}

//-------------------------------------------------------------------------------//