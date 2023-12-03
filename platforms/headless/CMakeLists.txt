
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

project(headless-desktop)

#include the engine 
include_directories(asengine/include/engine)
link_directories(asengine/lib)

#add project
include_directories(project-src)
add_subdirectory(project-src)

add_executable(build  main.cpp)

target_link_libraries(
    build
    ${PROJECT_LIBRARIES}
    asengine
)

message(">> " ${PROJECT_LIBRARIES})




