cmake_minimum_required(VERSION 3.23)
project(chapter5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(chapter5
        disjointSetTest.cpp)
