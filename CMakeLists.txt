# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall)
add_compile_definitions(ASENINE_EXPORTS)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -msse2")

#generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#create project
project(asengine)
include_directories(asengine)

# get asengine os
if(ASENGINE_OS STREQUAL "LINUX")
    set (ASENGINE_LINUX TRUE)
    add_compile_definitions(ASENGINE_LINUX)
endif()

if(ASENGINE_OS STREQUAL "WINDOWS")
    set (ASENGINE_WINDOWS TRUE)
    add_compile_definitions(ASENGINE_WINDOWS)
endif()

if(ASENGINE_OS STREQUAL "WEB")
    set (ASENGINE_WEB TRUE)
    add_compile_definitions(ASENGINE_WEB)
endif()


# desktop
if (ASENGINE_WINDOWS OR ASENGINE_LINUX)
    set (ASENGINE_DESKTOP TRUE)
    add_compile_definitions(ASENGINE_DESKTOP)
endif()


#platform specific sources
set(PLATFORM_SPECIFIC_SOURCES)
if (ASENGINE_DESKTOP)
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES}
        asengine/Display/Backend/Desktop/DesktopDisplay.cpp
        asengine/Display/Backend/Desktop/DesktopDisplayCreate.cpp
    )
endif()

if (ASENGINE_WEB)
    set(PLATFORM_SPECIFIC_SOURCES ${PLATFORM_SPECIFIC_SOURCES}
        asengine/Display/Backend/Web/WebDisplay.cpp
        asengine/Display/Backend/Web/WebDisplayCreate.cpp
    )
endif()

#set dependencies dir
set (DEPENDENCIES_DIRECTOY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

# add SPIRV-Cross
add_subdirectory(${DEPENDENCIES_DIRECTOY}/SPIRV-Cross)
include_directories(${DEPENDENCIES_DIRECTOY}/SPIRV-Cross)

# add miniaudio
add_subdirectory(${DEPENDENCIES_DIRECTOY}/miniaudio)
include_directories(${DEPENDENCIES_DIRECTOY}/miniaudio)

# add stb_image
add_subdirectory(${DEPENDENCIES_DIRECTOY}/stb_image)
include_directories(${DEPENDENCIES_DIRECTOY}/stb_image)

# add freetype
include_directories(${DEPENDENCIES_DIRECTOY}/freetype-2.10.0/include)
add_subdirectory(${DEPENDENCIES_DIRECTOY}/freetype-2.10.0)

#source
set (SOURCE
    #Application
    asengine/Core/ASEngine/ASEngine.cpp
    #Settings
    asengine/Core/Settings/Settings.cpp
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
    #memory
    asengine/Core/Memory/ByteBuffer.cpp
    #math
    asengine/Core/Math/Random.cpp
    asengine/Core/Math/Matrix3x3.cpp
    asengine/Core/Math/Vector2.cpp
    asengine/Core/Math/Matrix4x4.cpp
    asengine/Core/Math/Vector3.cpp
    asengine/Core/Math/Quaternion.cpp
    #inpute
    asengine/Core/InputSystem/InputEvent.cpp
    #class
    asengine/Class/ClassManager.cpp
    #ecs
    asengine/ECS/EntityManager.cpp
    asengine/ECS/Archetype.cpp
    asengine/ECS/ComponentManager.cpp
    asengine/ECS/SystemManager.cpp
    asengine/ECS/ArchetypeManager.cpp
    asengine/ECS/EntityBuilder.cpp
    asengine/ECS/ComponentClass.cpp
    #scene manager
    asengine/Scene/Scene.cpp
    asengine/Scene/SceneManager.cpp
    #resourcem_PositionY
    asengine/Resource/IResourceClass.cpp
    asengine/Resource/Resource.cpp
    asengine/Resource/ResourceManager.cpp
    # display
    asengine/Display/Display.cpp
    #rendering
    asengine/Renderer/Renderer.cpp
    #color
    asengine/Renderer/Color.cpp
    # shaders
    asengine/Renderer/Shader/ShaderSource.cpp
    asengine/Renderer/Shader/ShaderParams.cpp
    asengine/Renderer/Shader/Shader.cpp
    #materials
    asengine/Renderer/Material/Material.cpp
    #vertex input
    asengine/Renderer/VertexInput/VertexInput.cpp
    asengine/Renderer/VertexInput/VertexInputDescriptor.cpp
    # gpu-buffers
    asengine/Renderer/Buffer/Buffer.cpp
    #viewport
    asengine/Renderer/Viewport/Viewport.cpp
    # textures
    asengine/Renderer/Texture/Image.cpp
    asengine/Renderer/Texture/Texture.cpp
    #renderer backends
    asengine/Renderer/Backend/RendererBackend.cpp
    #opengl renderer
    asengine/Renderer/Backend/OpenGL/OpenGLRenderer.cpp
    asengine/Renderer/Backend/OpenGL/Buffer/OpenGLBuffer.cpp
    asengine/Renderer/Backend/OpenGL/Texture/OpenGLTexture.cpp
    asengine/Renderer/Backend/OpenGL/Shader/OpenGLShader.cpp
    asengine/Renderer/Backend/OpenGL/VertexInput/OpenGLVertexInputDescriptor.cpp
    asengine/Renderer/Backend/OpenGL/Viewport/OpenGLViewport.cpp
    #testing
    asengine/UnitTest/UnitTest.cpp
    asengine/UnitTest/UnitTestSystem.cpp
    #2d
    asengine/2D/Transform2D/Transform2D.cpp
    asengine/2D/Quad2D/Quad2D.cpp
    asengine/2D/Layer2D/Layer2D.cpp
    asengine/2D/Camera2D/Camera2D.cpp
    asengine/2D/Renderer2D/Renderer2D.cpp
    asengine/2D/Sprite/Sprite.cpp
    asengine/2D/Font/Font.cpp
    asengine/2D/Module2D.cpp
    #audio
    asengine/Audio/AudioEngine/AudioEngine.cpp
    asengine/Audio/AudioSource/AudioSource.cpp
    asengine/Audio/AudioOutput/AudioOutput.cpp
    asengine/Audio/AudioPlayer/AudioPlayer.cpp
    asengine/Audio/AudioModule.cpp
    #animations
    asengine/Animation/Interpolation.cpp
    #platform src
    ${PLATFORM_SPECIFIC_SOURCES}
)


#build engine to static library
add_library(
    asengine-core
    STATIC
    ${SOURCE}
)

# set asengine libraries for the asengine_libraries.cmake
set(ASENGINE_LIBRARIES
    asengine-core
    stb_image
    miniaudio
    spirv-cross-core
    spirv-cross-glsl
    spirv-cross-util
    freetype
)

set (AENGINE_INTERFACE_CMAKE "cmake_minimum_required(VERSION 3.22.1)\n")

if(ASENGINE_DESKTOP)
    message("Desktop Build")

    # add glfw
    add_subdirectory(${DEPENDENCIES_DIRECTOY}/glfw-3.4)

    # add glew
    include_directories(${DEPENDENCIES_DIRECTOY}/glew/include)
    add_definitions(-DGLEW_STATIC)
    add_library(
        glew
        STATIC
        dependencies/glew/src/glew.c
    )

    #link libraries for web
    target_link_libraries(
        asengine-core
        stb_image
        miniaudio
        glfw
        glew
        spirv-cross-glsl
        freetype
    )

    #create cmake list of libraries
    set (AENGINE_INTERFACE_CMAKE "${AENGINE_INTERFACE_CMAKE}
    # add opengl
    find_package(OpenGL REQUIRED)

    set (ASENGINE_LIBRARIES
        ${ASENGINE_LIBRARIES}
        glew
        glfw3
        OpenGL::GL
    )")

endif()


if (ASENGINE_WEB)
    message("Web Build")

    #link libraries for web
    target_link_libraries(
        asengine-core
        stb_image
        miniaudio
        spirv-cross-glsl
        freetype
    )

    #create cmake list of libraries
    set (AENGINE_INTERFACE_CMAKE "${AENGINE_INTERFACE_CMAKE}
    set (ASENGINE_LIBRARIES
        ${ASENGINE_LIBRARIES}
    )")

endif()

#save asengien_libraries.cmake
file(WRITE "${CMAKE_BINARY_DIR}/asengine_libraries.cmake" "${AENGINE_INTERFACE_CMAKE}")
