cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(TestSystem)

add_library(
    TestSystem
    STATIC
    TestSystem.cpp
)

target_link_libraries(
    TestSystem
)