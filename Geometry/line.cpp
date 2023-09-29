#include "line.hpp"
#include "../Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

Point Segment::GetFirstPoint() const
{
    return FirstPoint_;
}

//-------------------------------------------------------------------------------//

Point Segment::GetSecondPoint() const
{
    return SecondPoint_;
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