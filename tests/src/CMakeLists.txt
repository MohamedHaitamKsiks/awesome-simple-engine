cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(asengine-project)

add_library(
    asengine-project
    STATIC
    registry.cpp
    ASEngineTestSystem/ASEngineTestSystem.cpp
    Core/UniqueStringTest.cpp
    Core/PoolAllocatorTest.cpp
    Core/VectorTest.cpp
    Object/ClassManagerTest.cpp
)

target_link_libraries(
    asengine-project
)

set(PROJECT_LIBRARIES 
    asengine-project
    PARENT_SCOPE
)
