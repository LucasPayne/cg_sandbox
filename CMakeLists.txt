# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt
# Use of flex and bison
# https://gist.github.com/scan/3179356
# https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(cg_sandbox)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
include_directories(src lib ${CMAKE_CURRENT_BINARY_DIR})

# flex and bison, generated lexers and parsers.
flex_target(
    shading_file_lexer
    src/rendering/shading_file.l
    ${CMAKE_CURRENT_BINARY_DIR}/shading_file.yy.cc
    COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/shading_file.yy.hh"
)
bison_target(
    shading_file_parser
    src/rendering/shading_file.y
    ${CMAKE_CURRENT_BINARY_DIR}/shading_file.tab.cc
)
# The lexer needs the tokens file generated when the parser is generated. This means tokens need only be defined
# in the bison parser file.
add_flex_bison_dependency(shading_file_lexer shading_file_parser)

# Executable
#================================================================================
add_library(cg_sandbox
    src/main.cpp
    src/data_structures/table.cpp
    src/mathematics/mathematics.cpp
    src/input/input.cpp
    src/world/world.cpp
    src/resource_model/resource_model.cpp
    src/rendering/rendering.cpp
    src/rendering/shading.cpp
    src/rendering/vertex_arrays.cpp
    src/rendering/drawing.cpp
    src/assets/models.cpp
    src/entity_model/entity_model.cpp
    src/world/standard_aspects/Transform.cpp
    src/world/standard_aspects/Camera.cpp
    src/world/standard_aspects/Drawable.cpp
    src/world/standard_aspects/Behaviour.cpp
    src/gl/gl.cpp
    src/gl/glsl.cpp
    src/gl/gl_shader_program.cpp
    ${BISON_shading_file_parser_OUTPUTS}
    ${FLEX_shading_file_lexer_OUTPUTS}
    lib/glad/glad.c
)
target_compile_options(cg_sandbox PRIVATE -Wall -g)

# Internal libraries
# These provide some functionality the core uses, but are separated from the core code.
#======================================================================================
add_subdirectory(lib/model_loader)
target_link_libraries(cg_sandbox STATIC model_loader)

# External dependencies
#================================================================================
# GLFW
add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)
target_link_libraries(cg_sandbox STATIC glfw)
