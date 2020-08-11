# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt
# Use of flex and bison
# https://gist.github.com/scan/3179356
# https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS FALSE)
project(cg_sandbox)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
include_directories(core lib tools dependencies ${CMAKE_CURRENT_BINARY_DIR})

# flex and bison, generated lexers and parsers.
flex_target(
    shading_file_lexer
    core/graphics_resources/shading_file.l
    ${CMAKE_CURRENT_BINARY_DIR}/shading_file.yy.cc
    COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/shading_file.yy.hh"
)
bison_target(
    shading_file_parser
    core/graphics_resources/shading_file.y
    ${CMAKE_CURRENT_BINARY_DIR}/shading_file.tab.cc
)
# The lexer needs the tokens file generated when the parser is generated. This means tokens need only be defined
# in the bison parser file.
add_flex_bison_dependency(shading_file_lexer shading_file_parser)

# Executable
#================================================================================
add_library(cg_sandbox
    core/data_structures/table.cpp

    core/gl/glsl.cpp
    core/gl/gl_shader_program.cpp

    core/graphics_resources/shading.cpp
    core/graphics_resources/vertex_arrays.cpp
    ${BISON_shading_file_parser_OUTPUTS}
    ${FLEX_shading_file_lexer_OUTPUTS}

    core/mathematics/mathematics.cpp

    core/world/world.cpp
    core/world/entity_model/entity_model.cpp
    core/world/resource_model/resource_model.cpp
    core/world/standard_aspects/standard_aspects.cpp
    core/world/standard_aspects/Transform.cpp
    core/world/standard_aspects/Camera.cpp
    core/world/standard_aspects/Drawable.cpp
    core/world/assets/assets.cpp
    core/world/assets/model_assets.cpp
    core/world/assets/shading_assets.cpp
    core/world/graphics/graphics.cpp
    core/world/graphics/drawing.cpp

    dependencies/glad/glad.c
    tools/reflector/reflector.cpp
)
target_compile_options(cg_sandbox PRIVATE -Wall -g)

# Internal libraries
# These provide some functionality the core uses, but are separated from the core code.
#======================================================================================
# https://stackoverflow.com/questions/16991225/cmake-and-static-linking
# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# set_target_properties(cg_sandbox PROPERTIES LINK_SEARCH_START_STATIC 1)
# set_target_properties(cg_sandbox PROPERTIES LINK_SEARCH_END_STATIC 1)

add_subdirectory(lib/spatial_algebra)
target_link_libraries(cg_sandbox spatial_algebra)
# target_link_libraries(cg_sandbox STATIC libspatial_algebra.a)

# set_target_properties(cg_sandbox PROPERTIES LINK_SEARCH_START_STATIC 1)
# set_target_properties(cg_sandbox PROPERTIES LINK_SEARCH_END_STATIC 1)

add_subdirectory(lib/model_loader)
target_link_libraries(cg_sandbox model_loader)
# target_link_libraries(cg_sandbox STATIC libmodel_loader.a)

add_subdirectory(lib/interactive_graphics_context)
target_link_libraries(cg_sandbox interactive_graphics_context)

# External dependencies
#--------------------------------------------------------------------------------
add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)
target_link_libraries(cg_sandbox glfw)

