cmake_minimum_required(VERSION 3.8)

project(Triangles LANGUAGES CXX)

add_executable(triangles double_numbers.cpp point.cpp vector.cpp line.cpp
                plane.cpp triangle.cpp double_intersection.cpp octree.cpp
                intersection.cpp main.cpp)