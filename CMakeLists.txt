# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall)
add_compile_definitions(ASENINE_EXPORTS)

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

    #link static library into dynamc library for desktop
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

# add SPIRV-Cross
add_subdirectory(${DEPENDENCIES_DIRECTOY}/SPIRV-Cross)
include_directories(${DEPENDENCIES_DIRECTOY}/SPIRV-Cross)

# add miniaudio
add_subdirectory(${DEPENDENCIES_DIRECTOY}/miniaudio)
include_directories(${DEPENDENCIES_DIRECTOY}/miniaudio)

# add stb_image
add_subdirectory(${DEPENDENCIES_DIRECTOY}/stb_image)
include_directories(${DEPENDENCIES_DIRECTOY}/stb_image)

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
    #platform src
    ${PLATFORM_SPECIFIC_SOURCES}
)

if(ASENGINE_DESKTOP)
    message("Desktop Build")


    #build engine to dynamic library for desktop
    add_library(
        asengine
        SHARED
        ${SOURCE}
    )

    add_subdirectory(${DEPENDENCIES_DIRECTOY}/glfw-3.4)

    # add opengl
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
    
    include_directories(${DEPENDENCIES_DIRECTOY}/glew/include)
    add_definitions(-DGLEW_STATIC)
    add_library(
        glew
        STATIC
        dependencies/glew/src/glew.c
    )

    if(ASENGINE_WINDOWS)
        set_target_properties(asengine PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -static")
    endif()


    target_link_libraries(
        asengine
        PRIVATE stb_image
        PRIVATE miniaudio
        PRIVATE glfw
        PRIVATE glew
        PRIVATE spirv-cross-glsl
        OpenGL::GL
    )
endif()


if (ASENGINE_WEB)
    message("Web Build")    


    #build as static library for web
    add_library(
        asengine
        STATIC
        ${SOURCE}
    )

    target_link_libraries(
        asengine
        stb_image
        miniaudio
        spirv-cross-glsl
    )
    

endif()


