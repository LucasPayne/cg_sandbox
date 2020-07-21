# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt
# Use of bison and flex
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
add_executable(main
    src/main.cpp
    src/data_structures/table.cpp
    src/cg_sandbox.cpp
    src/resource_model/resource_model.cpp
    src/rendering/rendering.cpp
    src/entity_model/entity_model.cpp
    src/standard_aspects/Transform.cpp
    src/standard_aspects/Camera.cpp
    src/gl/gl.cpp
    src/gl/gl_input.cpp
    src/gl/gl_shader_program.cpp
    ${BISON_shading_file_parser_OUTPUTS}
    ${FLEX_shading_file_lexer_OUTPUTS}
    lib/glad/glad.c
)
# set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# External libraries
#================================================================================
# GLFW
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)
