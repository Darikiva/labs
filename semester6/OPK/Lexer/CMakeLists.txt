cmake_minimum_required(VERSION 3.0.0)
project(Lexer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


set(TOP_DIR ${CMAKE_SOURCE_DIR})
set(INC_DIR ${TOP_DIR}/include)

include_directories(${INC_DIR})

file(GLOB_RECURSE FILESYSTEM_SRC *.cpp)
add_library(src_files STATIC ${FILESYSTEM_SRC})

add_executable(Lexer main.cpp)
target_link_libraries(Lexer PRIVATE src_files)
