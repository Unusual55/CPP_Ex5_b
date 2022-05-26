cmake_minimum_required(VERSION 3.22)
project(CPP_Ex5_b)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP_Ex5_b
        sources/Node.hpp
        sources/Node.cpp
        sources/OrgChart.hpp
        sources/OrgChart.cpp
        sources/Demo.cpp)
