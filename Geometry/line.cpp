#include "line.hpp"
#include "../Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

Point Segment::FirstPoint() const
{
    return FirstPoint_;
}

//-------------------------------------------------------------------------------//

Point Segment::SecondPoint() const
{
    return SecondPoint_;
}

//-------------------------------------------------------------------------------//

Vector Segment::DirectionVector() const
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