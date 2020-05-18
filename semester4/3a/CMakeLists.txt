cmake_minimum_required(VERSION 3.15)
project(3a)

set(CMAKE_CXX_STANDARD 14)

add_executable(3a main.cpp FibonacciHeap.tpp FibonacciHeap.hpp Graph.tpp Graph.hpp algorithms.hpp)