cmake_minimum_required(VERSION 4.1)
project(code_practice)

set(CMAKE_CXX_STANDARD 23)

add_executable(code_practice main.cpp)
add_subdirectory(Leetcode)
add_subdirectory(Luogu)
