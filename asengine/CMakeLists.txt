# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)


project(asengine)
include_directories(engine)

#file system source system
set(FILESYSTEM_SOURCES engine/Core/FileSystem/File.cpp)
if (ANDROID)
    set(FILESYSTEM_SOURCES ${FILESYSTEM_SOURCES} engine/Core/FileSystem/FileAndroid.cpp)
else() 
    set(FILESYSTEM_SOURCES ${FILESYSTEM_SOURCES} engine/Core/FileSystem/FileDesktop.cpp)
endif()


add_library(
    asengine
    STATIC
    #serialization
    engine/Core/Serialization/Serializer.cpp
    #memory
    engine/Core/Memory/PoolAllocator.cpp
    #strings
    engine/Core/String/UniqueString.cpp
    engine/Core/String/UniqueStringManager.cpp
    #math
    engine/Core/Math/Random.cpp
    engine/Core/Math/mat3.cpp
    engine/Core/Math/vec2.cpp
    #window
    engine/Core/Window/Window.cpp
    #input
    engine/Core/InputSystem/InputEvent.cpp
    #app
    engine/Core/Application/Application.cpp
    #log
    engine/Core/Log/Log.cpp
    #files
    ${FILESYSTEM_SOURCES}
    #ecs
    engine/ECS/World.cpp
    engine/ECS/Archetype.cpp
    engine/ECS/ComponentManager.cpp
    engine/ECS/SystemManager.cpp
    engine/ECS/ArchetypeManager.cpp
    engine/ECS/EntityBuilder.cpp
    #shapes
    engine/Shape/Rectangle.cpp
    #resource
    engine/Resource/Image.cpp
    engine/Resource/Sprite.cpp
    engine/Resource/Material.cpp
    engine/Resource/Shader.cpp
    engine/Resource/Font.cpp
    engine/Resource/Scene.cpp
    engine/Resource/Audio.cpp
    #rendering
    engine/Renderer/TextureManager.cpp
    engine/Renderer/Viewport.cpp
    engine/Renderer/ShaderProgram.cpp
    engine/Renderer/ShaderUniform.cpp
    engine/Renderer/2D/Quad2D.cpp
    engine/Renderer/2D/Renderer2D.cpp
    engine/Renderer/2D/VertexBufferObject2D.cpp
    #tween
    engine/Animation/Interpolation/Interpolate.cpp
    #audio
    engine/Audio/AudioEngine.cpp
    #thirdparty
    engine/Thirdparty/miniaudio.c
)

include_directories(dependencies/freetype/include)
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



