cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(asengine-project)


FILE(GLOB_RECURSE SRCFILES *.cpp)


add_library(
    asengine-project
    STATIC
    ${SRCFILES}
)

target_link_libraries(
    asengine-project
)