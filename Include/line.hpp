#ifndef LINE_HPP_
#define LINE_HPP_

#include <iostream>
#include <cmath>

#include "vector.hpp"

// (x - x1) / (x1 - x2) = (y - y1) / (y1 - y2) = (z - z1) / (z - z2)

// (x - x1) / p = (y - y1) / q = (z - z1) / s


class Line 
{
    private:
        Point   ZeroPoint_;
        
        Vector  GuideVector_;

    public:
        Line(const Point &p, const Vector &v) : ZeroPoint_(p), GuideVector_(v) {}

        ~Line() {}

        void PrintLine() const
        {
            ZeroPoint_.PrintPoint();

            GuideVector_.PrintVector();
        }
};

#endif