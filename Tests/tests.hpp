#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <iostream>
#include <fstream>

namespace testgen
{

class testgen_t
{
    private:
        const size_t triangles_number_;

        const size_t tests_count_;

    public:
        testgen_t(const size_t num, const size_t count) : triangles_number_{num}, tests_count_{count} {}
};

}

#endif