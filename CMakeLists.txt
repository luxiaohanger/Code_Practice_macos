cmake_minimum_required(VERSION 3.20)
project(code_practice)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求标准
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(code_practice main.cpp)
add_subdirectory(Leetcode)
add_subdirectory(Luogu)
