cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project(asengine-project)

add_library(
    asengine-project
    STATIC
    registry.cpp
)

target_link_libraries(
    asengine-project
)

set(PROJECT_LIBRARIES 
    asengine-project
    PARENT_SCOPE
)
