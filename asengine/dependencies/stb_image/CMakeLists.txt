cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(stb_image)

add_library(
    stb_image
    STATIC
    stb_image.c
)

target_link_libraries(
    stb_image
)