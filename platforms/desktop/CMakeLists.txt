
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(desktop)

#include the engine
include_directories(${ASENGINE_INCLUDE_PATH})
link_directories(${ASENGINE_LIB_PATH})
include(${ASENGINE_LIB_PATH}/asengine_libraries.cmake)

#add project
include_directories(${ASENGINE_PROJECT_PATH})
add_subdirectory(${ASENGINE_PROJECT_PATH} ${CMAKE_BINARY_DIR}/project_build)

add_executable(build  main.cpp)

target_link_libraries(
    build
    ${PROJECT_LIBRARIES}
    ${ASENGINE_LIBRARIES}
)
