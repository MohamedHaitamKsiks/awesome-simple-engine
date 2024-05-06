# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

project(asengine)
include_directories(asengine)

#platform specific sources
set(PLATFORM_SPECIFIC_SOURCES)
if (ANDROID)
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES} 
        asengine/Core/FileSystem/FileAndroid.cpp
        asengine/Core/Debug/DebugAndroid.cpp
    )
else() 
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES}
        asengine/Core/FileSystem/FileDesktop.cpp
        asengine/Core/Debug/DebugDesktop.cpp
    )
endif()

# add SPIRV-Cross
add_subdirectory(dependencies/SPIRV-Cross)
include_directories(dependencies/SPIRV-Cross)

# add miniaudio
#add_subdirectory(dependencies/miniaudio)
#include_directories(dependencies/miniaudio)

# add stb_image
add_subdirectory(dependencies/stb_image)
include_directories(dependencies/stb_image)

add_library(
    asengine
    STATIC
    #Application
    asengine/Core/ASEngine/ASEngine.cpp
    #Debug
    asengine/Core/Debug/Debug.cpp
    #errors
    asengine/Core/Error/Assertion.cpp
    asengine/Core/Error/Exception.cpp
    #strings
    asengine/Core/String/UniqueString.cpp
    asengine/Core/String/UniqueStringManager.cpp
    #serialization
    asengine/Core/Serialization/Serializer.cpp
    #file system
    asengine/Core/FileSystem/File.cpp
    #modules
    asengine/Module/ModuleManager.cpp
    #time 
    asengine/Core/Time/Time.cpp
    #memory
    asengine/Core/Memory/PoolAllocator.cpp
    asengine/Core/Memory/ByteBuffer.cpp
    #class management
    asengine/Object/Class.cpp
    asengine/Object/ClassManager.cpp
    #math
    asengine/Core/Math/Random.cpp
    asengine/Core/Math/Matrix3x3.cpp
    asengine/Core/Math/Vector2.cpp
    asengine/Core/Math/Matrix4x4.cpp
    asengine/Core/Math/Vector3.cpp
    asengine/Core/Math/Quaternion.cpp
    #window
    asengine/Core/Window/Window.cpp
    #input
    asengine/Core/InputSystem/InputEvent.cpp
    #ecs
    asengine/ECS/EntityManager.cpp
    asengine/ECS/Archetype.cpp
    asengine/ECS/ComponentManager.cpp
    asengine/ECS/SystemManager.cpp
    asengine/ECS/ArchetypeManager.cpp
    asengine/ECS/EntityBuilder.cpp
    #rendering
    asengine/Renderer/Image.cpp
    #resource
    #asengine/Resource/Material.cpp
    #asengine/Resource/Shader.cpp
    #asengine/Resource/Scene.cpp
    #asengine/Resource/Audio.cpp
    #asengine/Renderer/Viewport.cpp
    #audio
    #asengine/Audio/AudioEngine.cpp
    #testing
    asengine/UnitTest/UnitTest.cpp
    asengine/UnitTest/UnitTestSystem.cpp
    #platform src
    ${PLATFORM_SPECIFIC_SOURCES}
)

if(NOT ANDROID)
    # add opengl
    #find_package(OpenGL REQUIRED)
    #include_directories(${OPENGL_INCLUDE_DIRS})

    #include_directories(dependencies/glew/include)
    #add_library(
    #    glew
    #    STATIC
    #    dependencies/glew/src/glew.c
    #)
    #add_compile_definitions(GLEW_STATIC GLEW_BUILD)

    target_link_libraries(
        asengine
        stb_Image
        #miniaudio
        #glew
        spirv_cross_glsl
        #OpenGL::GL
    )

else()
    target_link_libraries(
        asengine
        spirv_cross_glsl
    )

endif()



