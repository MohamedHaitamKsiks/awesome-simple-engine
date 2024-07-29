cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

#generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories({ASENGINE_INCLUDE_PATH})
project(asengine-project)

add_library(
    asengine-project
    STATIC
    registry.cpp
    Example2D.cpp
    CameraController/CameraController.cpp
    CameraController/CameraControllerSystem.cpp
    BouncingFox/BouncingFox.cpp
    BouncingFox/BouncingFoxSpawner.cpp
)

target_link_libraries(
    asengine-project
)

set(PROJECT_LIBRARIES
    asengine-project
    PARENT_SCOPE
)
