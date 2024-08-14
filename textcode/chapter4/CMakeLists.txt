cmake_minimum_required(VERSION 3.23)
project(chapter4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(chapter4
        priorityQueueTest.cpp)
