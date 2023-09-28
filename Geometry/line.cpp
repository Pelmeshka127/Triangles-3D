#include "line.hpp"
#include "../Intersection/intersection.hpp"

//-------------------------------------------------------------------------------//

bool Segment::IsSegmentIntersect(const Segment &line) const
{
    double drc1 = Direction(line.FirstPoint_, line.SecondPoint_, FirstPoint_ );
    // std::cout << drc1 << std::endl;
    
    double drc2 = Direction(line.FirstPoint_, line.SecondPoint_, SecondPoint_);
    // std::cout << drc2 << std::endl;
    
    double drc3 = Direction(FirstPoint_, SecondPoint_, line.FirstPoint_ );
    // std::cout << drc3 << std::endl;
    
    double drc4 = Direction(FirstPoint_, SecondPoint_, line.SecondPoint_);
    // std::cout << drc4 << std::endl;

    if ((drc1 * drc2 < 0) && (drc3 * drc4 < 0))
        return true;

    else if (drc1 == 0 && IsOnSegment(line.FirstPoint_, line.SecondPoint_, FirstPoint_))
        return true;

    else if (drc2 == 0 && IsOnSegment(line.FirstPoint_, line.SecondPoint_, SecondPoint_))
        return true;

    else if (drc3 == 0 && IsOnSegment(FirstPoint_, SecondPoint_, line.FirstPoint_))
        return true;

    else if (drc4 == 0 && IsOnSegment(FirstPoint_, SecondPoint_, line.SecondPoint_))
        return true;

    return false;
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