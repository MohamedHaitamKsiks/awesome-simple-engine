cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(TestModule)

add_library(
    TestModule
    STATIC
    TestModule.cpp
    # add source files ...
)

target_link_libraries(
    TestModule
)