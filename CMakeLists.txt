cmake_minimum_required(VERSION 3.10)
project(oj_problem_124 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

add_executable(code main.cpp)

target_compile_options(code PRIVATE -O2 -pipe)
