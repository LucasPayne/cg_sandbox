cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW) # Allow linking between subdirectory libraries.
project(cg_sandbox)

# External system libraries
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
# External submodule libraries
add_subdirectory(dependencies/glfw)
include_directories(dependencies/glfw/include)
add_subdirectory(dependencies/mesh_processing)
include_directories(dependencies/mesh_processing/include)

# assimp ---- todo
set(ASSIMP_SOURCE_DIR /home/lucas/computer_graphics/assimp)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_SOURCE_DIR}/include)
set(ASSIMP_LIBRARY_PATH ${ASSIMP_SOURCE_DIR}/bin/libassimp.so)


# Compile completely separated libraries.
#------------------------------------------------------------
include_directories(lib)
add_subdirectory(lib/opengl_utilities)
add_subdirectory(lib/interactive_graphics_context)
add_subdirectory(lib/reflector)
add_subdirectory(lib/table)
add_subdirectory(lib/mathematics)

# Compile the cg_sandbox library.
#------------------------------------------------------------
add_subdirectory(src)
target_compile_definitions(cg_sandbox PRIVATE RESOURCE_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/resources/\")
target_link_libraries(cg_sandbox opengl_utilities)
target_link_libraries(cg_sandbox interactive_graphics_context)
target_link_libraries(cg_sandbox reflector)
target_link_libraries(cg_sandbox table)
target_link_libraries(cg_sandbox mathematics)
target_link_libraries(cg_sandbox mesh_processing)
target_link_libraries(cg_sandbox glfw)
target_link_libraries(cg_sandbox Eigen3::Eigen)
add_library(assimp SHARED IMPORTED GLOBAL)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${ASSIMP_LIBRARY_PATH})
message(STATUS "assimp path: ${ASSIMP_LIBRARY_PATH}")
target_link_libraries(cg_sandbox assimp)
 
# Compile example applications
#------------------------------------------------------------
include_directories(include lib dependencies)
add_executable(basic_application
    examples/basic_application/basic_application.cpp
)
target_include_directories(basic_application PRIVATE examples/basic_application)
target_include_directories(basic_application PRIVATE /home/lucas/computer_graphics/assimp/include) #------
target_compile_definitions(basic_application PRIVATE PATH="${CMAKE_CURRENT_SOURCE_DIR}/examples/basic_application/")
target_link_libraries(basic_application cg_sandbox)
