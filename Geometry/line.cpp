#include "line.hpp"

//-------------------------------------------------------------------------------//

bool LineSegment::DoesLineSegmentIntersect(const LineSegment &l1, const LineSegment &l2) const
{
    double drc1 = Direction(l2.FirstPoint_, l2.SecondPoint_, l1.FirstPoint_ );
    std::cout << drc1 << std::endl;
    
    double drc2 = Direction(l2.FirstPoint_, l2.SecondPoint_, l1.SecondPoint_);
    std::cout << drc2 << std::endl;
    
    double drc3 = Direction(l1.FirstPoint_, l1.SecondPoint_, l2.FirstPoint_ );
    std::cout << drc3 << std::endl;
    
    double drc4 = Direction(l1.FirstPoint_, l1.SecondPoint_, l2.SecondPoint_);
    std::cout << drc4 << std::endl;

    if ((drc1 * drc2 < 0) && (drc3 * drc4 < 0))
        return true;

    else if (drc1 == 0 && IsOnSegment(l2.FirstPoint_, l2.SecondPoint_, l1.FirstPoint_))
        return true;

    else if (drc2 == 0 && IsOnSegment(l2.FirstPoint_, l2.SecondPoint_, l1.SecondPoint_))
        return true;

    else if (drc3 == 0 && IsOnSegment(l1.FirstPoint_, l1.SecondPoint_, l2.FirstPoint_))
        return true;

    else if (drc4 == 0 && IsOnSegment(l1.FirstPoint_, l1.SecondPoint_, l2.SecondPoint_))
        return true;

    return false;
}

//-------------------------------------------------------------------------------//