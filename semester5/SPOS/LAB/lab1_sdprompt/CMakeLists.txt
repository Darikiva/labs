cmake_minimum_required(VERSION 3.17)
project(lab1_sdprompt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lncurses -pthread")
find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams)

add_executable(lab1_sdprompt main.cpp)
target_link_libraries(lab1_sdprompt Boost::filesystem)