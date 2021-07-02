cmake_minimum_required(VERSION 3.1)
project(opengl_utilities)

add_library(opengl_utilities
    glad/glad.c
    gl_shader_program.cpp
    glsl.cpp
)
target_compile_options(opengl_utilities PRIVATE -Wall -Werror -g)
