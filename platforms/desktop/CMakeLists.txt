
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(desktop)

#include glfw
find_package(glfw3 3.3 REQUIRED)

add_library(
    desktop
    SHARED
    src/DesktopApplication.cpp

)

add_executable(build src/main.cpp)

#include the engine 
include_directories(src/engine)
add_subdirectory(src/engine)

target_link_libraries(
    build
    desktop
    engine
    glfw
    
)




