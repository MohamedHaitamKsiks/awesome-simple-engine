# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(asengine)

#file system source system
set(FILESYSTEM_SOURCES engine/FileSystem/File.cpp)
if (ANDROID)
    set(FILESYSTEM_SOURCES ${FILESYSTEM_SOURCES} engine/FileSystem/FileAndroid.cpp)
else() 
    set(FILESYSTEM_SOURCES ${FILESYSTEM_SOURCES} engine/FileSystem/FileDesktop.cpp)
endif()


add_library(
    asengine
    STATIC
    #memory
    engine/Memory/BasePoolAllocator.cpp
    #ecs
    engine/ECS/World.cpp
    engine/ECS/Archetype.cpp
    engine/ECS/ComponentManager.cpp
    engine/ECS/SystemManager.cpp
    engine/ECS/ArchetypeManager.cpp
    #shapes
    engine/Shape/Rectangle.cpp
    #resource
    engine/Resource/Image.cpp
    engine/Resource/Sprite.cpp
    engine/Resource/Material.cpp
    engine/Resource/Font.cpp
    engine/Resource/Scene.cpp
    #strings
    engine/String/UniqueString.cpp
    engine/String/UniqueStringManager.cpp
    #rendering
    #engine/Renderer/Renderer.cpp
    #engine/Renderer/Shader.cpp
    #engine/Renderer/Texture.cpp
    #engine/Renderer/Screen.cpp
    #engine/Renderer/Camera.cpp
    #engine/Renderer/Color.cpp
    #engine/Renderer/Graphics.cpp
    #engine/Renderer/Vertex.cpp
    #engine/Renderer/Quad.cpp
    #engine/Renderer/VertexBufferObject.cpp
    #window
    engine/Window/Window.cpp
    #math
    engine/Math/Random.cpp
    engine/Math/mat3.cpp
    engine/Math/vec2.cpp
    #files
    ${FILESYSTEM_SOURCES}
    #input
    engine/InputEvent/InputEvent.cpp
    #tween
    engine/Interpolation/Interpolate.cpp
    #app
    engine/Application/Application.cpp
    #log
    engine/Log/Log.cpp
)

add_subdirectory(dependencies/freetype)


if(NOT ANDROID)
    # add opengl
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})

    include_directories(dependencies/glew/include)
    add_library(
        glew
        STATIC
        dependencies/glew/src/glew.c
    )
    add_compile_definitions(GLEW_STATIC GLEW_BUILD)

    target_link_libraries(
        asengine
        glew
        OpenGL::GL
        freetype
    )


else()
    target_link_libraries(
        asengine
        freetype
    )

endif()



