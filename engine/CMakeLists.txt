# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(engine)

add_library(
    engine
    #game object
    GameObject/GameObject.cpp
    GameObject/Instance.cpp
    #shapes
    Shape/Rectangle.cpp
    #resource
    Resource/Image.cpp
    Resource/Resource.cpp
    Resource/Sprite.cpp
    Resource/Material.cpp
    Resource/Font.cpp
    Resource/Scene.cpp
    #rendering
    Renderer/Renderer.cpp
    Renderer/Texture.cpp
    Renderer/Screen.cpp
    Renderer/Camera.cpp
    Renderer/Color.cpp
    Renderer/Graphics.cpp
    Renderer/Vertex.cpp
    Renderer/Quad.cpp
    Renderer/VertexBufferObject.cpp
    #math
    Math/Random.cpp
    #input
    InputEvent/InputEvent.cpp
    #tween
    Interpolation/Interpolate.cpp
    #particles
    Particles/ParticleEmitter.cpp
    #app
    Application/Application.cpp
    #log
    Log/Log.cpp
)

add_subdirectory(Thirdparty/freetype)

target_link_libraries(
    engine
    GLESv2 
    freetype
)