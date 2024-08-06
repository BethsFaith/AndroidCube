cmake_minimum_required(VERSION 3.22.1)

project("Cube")

# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        main.cpp
        render/buffers/ARaiiBuffer.cpp
        render/buffers/Vao.cpp
        render/buffers/Vbo.cpp
        render/buffers/Ebo.cpp
        render/buffers/Vertex.cpp
        render/primitives/Primitive.cpp
        render/primitives/PCube.cpp
        render/techniques/ATechnique.cpp
        render/techniques/TransformTechnique.cpp
        render/techniques/Transform3dTechnique.cpp
        render/Object.cpp
        render/shaders/ShaderProgram.cpp
        render/shaders/Shader.cpp
        RenderProgram.cpp
)

include_directories(render)
add_subdirectory(glm)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log
        EGL
        GLESv3
        glm)