
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

project(desktop)

# add opengl
find_package(OpenGL REQUIRED)

# Find the X11 package
find_package(X11 REQUIRED)

#include the engine 
include_directories(${ASENGINE_INCLUDE_PATH})
link_directories(${ASENGINE_LIB_PATH})

#add project
include_directories(${ASENGINE_PROJECT_PATH})
add_subdirectory(${ASENGINE_PROJECT_PATH} ${CMAKE_BINARY_DIR}/project_build)

add_executable(build  main.cpp DesktopApplication.cpp)

target_link_libraries(
    build
    ${PROJECT_LIBRARIES}
    asengine
    ${X11_LIBRARIES}
    OpenGL::GL
)


