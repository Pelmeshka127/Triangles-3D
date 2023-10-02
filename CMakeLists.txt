cmake_minimum_required(VERSION 3.8)

project(Triangles LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(./mathlibs)

add_subdirectory(./geometry)

add_subdirectory(./intersection)