# Example CMakeLists files for reference:
# https://github.com/mmp/pbrt-v3/blob/master/CMakeLists.txt
# https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
project(cg_sandbox)

include_directories(src)

add_executable(cg_sandbox
    src/main.cpp
)
set_property(TARGET cg_sandbox PROPERTY CXX_STANDARD 11)
target_compile_options(cg_sandbox PRIVATE -Wall)

# EXCLUDE_FROM_ALL means that this won't be included in the "all" target.
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(cg_sandbox PRIVATE glfw)
