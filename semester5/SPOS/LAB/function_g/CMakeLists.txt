cmake_minimum_required(VERSION 3.17)
project(function_g)

set(CMAKE_CXX_STANDARD 20)
find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams)

add_executable(function_g main.cpp)
target_link_libraries(function_g Boost::filesystem)