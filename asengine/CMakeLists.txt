# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(asengine)
include_directories(engine)

#platform specific sources
set(PLATFORM_SPECIFIC_SOURCES)
if (ANDROID)
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES} 
        engine/Core/FileSystem/FileAndroid.cpp
        engine/Core/Debug/DebugAndroid.cpp
    )
else() 
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES}
        engine/Core/FileSystem/FileDesktop.cpp
        engine/Core/Debug/DebugDesktop.cpp
    )
endif()

# add SPIRV-Cross
add_subdirectory(dependencies/SPIRV-Cross)
include_directories(dependencies/SPIRV-Cross)

# add miniaudio
add_subdirectory(dependencies/miniaudio)
include_directories(dependencies/miniaudio)

# add stb_image
add_subdirectory(dependencies/stb_image)
include_directories(dependencies/stb_image)

add_library(
    asengine
    STATIC
    #Application
    engine/Core/Application/Application.cpp
    #Debug
    engine/Core/Debug/Debug.cpp
    #errors
    engine/Core/Error/Assertion.cpp
    engine/Core/Error/Exception.cpp
    #strings
    engine/Core/String/UniqueString.cpp
    engine/Core/String/UniqueStringManager.cpp
    #serialization
    engine/Core/Serialization/Serializer.cpp
    #file system
    engine/Core/FileSystem/File.cpp
    #modules
    engine/Module/ModuleManager.cpp
    #time 
    engine/Core/Time/Time.cpp
    #memory
    engine/Core/Memory/PoolAllocator.cpp
    engine/Core/Memory/ByteBuffer.cpp
    #math
    engine/Core/Math/Random.cpp
    engine/Core/Math/Matrix3x3.cpp
    engine/Core/Math/Vector2.cpp
    engine/Core/Math/Matrix4x4.cpp
    engine/Core/Math/Vector3.cpp
    engine/Core/Math/Quaternion.cpp
    #window
    engine/Core/Window/Window.cpp
    #input
    engine/Core/InputSystem/InputEvent.cpp
    #app
    #engine/Core/Application/Application.cpp
    #log
    #files
    #ecs
    engine/ECS/EntityManager.cpp
    engine/ECS/Archetype.cpp
    engine/ECS/ComponentManager.cpp
    engine/ECS/SystemManager.cpp
    engine/ECS/ArchetypeManager.cpp
    engine/ECS/EntityBuilder.cpp
    #resource
    #engine/Resource/Material.cpp
    #engine/Resource/Shader.cpp
    #engine/Resource/Scene.cpp
    #engine/Resource/Audio.cpp
    #rendering
    #engine/Renderer/Image.cpp
    #engine/Renderer/Viewport.cpp
    #audio
    #engine/Audio/AudioEngine.cpp
    #testing
    engine/UnitTest/UnitTest.cpp
    #platform src
    ${PLATFORM_SPECIFIC_SOURCES}
)

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
        stb_Image
        miniaudio
        glew
        spirv_cross_glsl
        OpenGL::GL
    )

else()
    target_link_libraries(
        asengine
        spirv_cross_glsl
    )

endif()



