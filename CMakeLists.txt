cmake_minimum_required(VERSION 3.8)

project(Triangles LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_GEOMETRY ./Geometry/point.cpp ./Geometry/vector.cpp ./Geometry/line.cpp ./Geometry/plane.cpp ./Geometry/triangle.cpp)
set(SRC_INTERSECTION ./Intersection/intersection.cpp)
set(SRC_MATH ./MathLibs/double_numbers.cpp)

set(SRC_FILES main.cpp ${SRC_GEOMETRY} ${SRC_INTERSECTION} ${SRC_MATH})

add_executable(triangles ${SRC_FILES})