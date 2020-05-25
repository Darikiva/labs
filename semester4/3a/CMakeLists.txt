cmake_minimum_required(VERSION 3.15)

project(3a)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TEST "Tefdfsd fst" ON)

add_executable(main main.cpp Graph.tpp algorithms.hpp multiTheadAlgorithms.hpp)

if(BUILD_TEST)
    add_executable(test test.cpp multiThreadTest.cpp)
endif()