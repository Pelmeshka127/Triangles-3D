#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <iostream>
#include <fstream>


namespace testgen
{

class testgen_t
{
    double minimum = -327;

    public:
        testgen_t()
        {
            size_t tests_count_ = 0;

            std::cout << "Enter the number of tests" << std::endl;

            std::cin >> tests_count_;

            std::ofstream test_files[tests_count_];

            for (size_t test = 0; test < tests_count_; test++)
            {
                size_t triangles_number = 0;

                std::cout << "Enter the number of triangles" << std::endl;

                std::cin >> triangles_number;

                std::string file_name = "../../Tests/" + std::to_string(test + 1) + "test.txt";

                test_files[test].open(file_name);

                std::cout << file_name << std::endl;

                test_files[test] << triangles_number << std::endl << std::endl;

                for (size_t triangle = 0; triangle < triangles_number; triangle++)
                {
                    double points[9] = {};

                    points[0] = double (std::rand() % 265 + minimum);

                    points[1] = double (std::rand() % 321 + minimum);

                    points[2] = double (std::rand() % 667 + minimum);

                    points[3] = double (std::rand() % 228 + minimum);

                    points[4] = double (std::rand() % 1488 + minimum);

                    points[5] = double (std::rand() % 993 + minimum);

                    points[6] = double (std::rand() % 32 + minimum);

                    points[7] = double (std::rand() % 127 + minimum);

                    points[8] = double (std::rand() % 666 + minimum);

                    test_files[test] << points[0] << " " << points[1] << " " << points[2] << std::endl;

                    test_files[test] << points[3] << " " << points[4] << " " << points[5] << std::endl;
                    
                    test_files[test] << points[6] << " " << points[7] << " " << points[8] << std::endl;

                    test_files[test] << std::endl;
                }

                test_files[test].close();
            }
        }
};

}

#endif