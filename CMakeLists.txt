cmake_minimum_required(VERSION 3.27)
project(ogl)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
add_subdirectory(glfw-3.4)
include_directories(
        glfw-3.4/include
        glad/include
)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

add_executable(ogl
        src/main.cpp
        glad/src/glad.c
        src/shader.h
        src/shader.cpp
        src/FilePWD.cpp
        src/FilePWD.h)

target_link_libraries(ogl glfw ${OPENGL_LIBRARIES})
