cmake_minimum_required(VERSION 3.17)
project(function_f)

set(CMAKE_CXX_STANDARD 20)
find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams)

add_executable(function_f main.cpp)
target_link_libraries(function_f Boost::filesystem)