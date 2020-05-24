cmake_minimum_required(VERSION 3.15)

project(3a)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TEST "Tefdfsd fst" ON)
option(BUILD_MAIN "Build main" OFF)

add_executable(3a main.cpp Graph.tpp algorithms.hpp)
if(BUILD_TEST)
    add_executable(test graph_test.cpp Graph.tpp algorithms.hpp)
endif()