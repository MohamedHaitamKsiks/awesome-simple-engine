cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project(miniaudio)

add_library(
    miniaudio
    STATIC
    miniaudio.c
)

target_link_libraries(
    miniaudio
)