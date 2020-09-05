cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(opengl_utilities)

include_directories(../../lib)

add_library(opengl_utilities
    glad/glad.c
    gl_shader_program.cpp
    glsl.cpp
)
target_compile_options(opengl_utilities PRIVATE -Wall -Werror -g)
