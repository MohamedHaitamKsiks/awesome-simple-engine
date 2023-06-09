
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

project(desktop)

#include glfw
#find_package(glfw3 3.3 REQUIRED)
add_subdirectory(dependencies/glfw-3.3.8)
include_directories(asengine/dependencies/glew/include)

#include the engine 
include_directories(asengine)
add_subdirectory(asengine)


add_executable(build main.cpp DesktopApplication.cpp)

target_link_libraries(
    build
    asengine
    glfw
)




