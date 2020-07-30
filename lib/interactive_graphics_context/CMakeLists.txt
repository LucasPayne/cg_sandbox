cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(interactive_graphics_context)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(interactive_graphics_context
    interactive_graphics_context.cpp
    input.cpp
    platform/platform_glfw.cpp
)
target_compile_options(interactive_graphics_context PRIVATE -Wall -g)

# add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)
# target_link_libraries(interactive_graphics_context glfw)
