
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(index)

#include the engine
include_directories(${ASENGINE_INCLUDE_PATH})
link_directories(${ASENGINE_LIB_PATH})

#add project
add_subdirectory(${ASENGINE_PROJECT_PATH} ${CMAKE_BINARY_DIR}/project_build)

add_executable(index main.cpp)
set (CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ALLOW_MEMORY_GROWTH -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 --preload-file assets/ ")


target_link_libraries(
    index
    PRIVATE ${PROJECT_LIBRARIES}
    PRIVATE asengine
    PRIVATE stb_image
    PRIVATE miniaudio
    PRIVATE spirv-cross-glsl
    PRIVATE spirv-cross-core
    PRIVATE spirv-cross-util
    PRIVATE freetype
)
