# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(cg_sandbox)

include_directories(src)
include_directories(lib)

# Executable
#================================================================================
add_executable(main
    src/main.cpp
    lib/glad/glad.c
    src/cg_sandbox.cpp
    src/rendering/rendering.cpp
    src/parallel/parallel.cpp
    src/entity_model/entity_model.cpp
)
# set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# Internal libraries
#================================================================================
add_library(gl STATIC
    src/gl/gl.cpp
    src/gl/gl_input.cpp
    src/gl/gl_shader_program.cpp
)
target_link_libraries(main PRIVATE gl)

# find_package(BISON)
# find_package(FLEX)
# FLEX_TARGET(shading_file_lexer src/rendering/shading_file/shading_file.l ${CMAKE_CURRENT_BINARY_DIR}/shading_file_lexer.cpp)
# add_library(shading_file STATIC
#     ${FLEX_shading_file_lexer_OUTPUTS}
# )
# target_link_libraries(main PRIVATE shading_file)

# BISON_TARGET(
# ADD_FLEX_BISON_DEPENDENCY

# External libraries
#================================================================================
# GLFW
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)
