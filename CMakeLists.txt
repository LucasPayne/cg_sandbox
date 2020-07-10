# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
project(cg_sandbox)

include_directories(src)
include_directories(lib)

# Executable
add_executable(cg_sandbox
    src/main.cpp
    lib/glad/glad.c
)
set_property(TARGET cg_sandbox PROPERTY CXX_STANDARD 11)
target_compile_options(cg_sandbox PRIVATE -Wall)

# Internal libraries
add_library(gl STATIC
    src/gl/gl.cpp
    src/gl/gl_input.cpp
    src/gl/gl_shader_program.cpp
)
target_link_libraries(cg_sandbox PRIVATE gl)

# External libraries
# GLFW
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(cg_sandbox PRIVATE glfw)

# If glad subdirectory has a CMakeLists.txt file, use this.
# add_subdirectory(lib/glad EXCLUDE_FROM_ALL)
# target_link_libraries(cg_sandbox PRIVATE glad)

# Adding a separate library.
# add_library(glad STATIC
#     lib/glad/glad.c
#     lib/glad/glad.h
# )
# target_link_libraries(cg_sandbox PRIVATE glad)
