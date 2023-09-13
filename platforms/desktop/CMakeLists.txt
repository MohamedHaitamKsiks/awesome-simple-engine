
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

project(desktop)

#include glfw
add_subdirectory(dependencies/glfw-3.3.8)

# add opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
else()
    message("FOUND:" ${OPENGL_INCLUDE_DIR})
endif()

add_compile_definitions(GLEW_STATIC GLEW_BUILD)

#include the engine 
include_directories(asengine/include/engine)
include_directories(asengine/include/dependencies/glew)
include_directories(asengine/include/dependencies/freetype)
link_directories(asengine/lib)

#add project
include_directories(project-src)
add_subdirectory(project-src)


add_executable(build  main.cpp DesktopApplication.cpp )

target_link_libraries(
    build
    asengine-project
    asengine
    OpenGL::GL
    glfw
)




