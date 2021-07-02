cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0079 NEW) # Allow linking between subdirectory libraries.
project(cg_sandbox)

# Compile completely separated libraries.
#------------------------------------------------------------
include_directories(lib)
add_subdirectory(lib/opengl_utilities)
add_subdirectory(lib/interactive_graphics_context)
add_subdirectory(lib/reflector)
add_subdirectory(lib/table)
add_subdirectory(lib/mathematics)

# add_executable(test test.cpp)
# target_link_libraries(test opengl_utilities)
# target_link_libraries(test interactive_graphics_context)
# target_link_libraries(test reflector)
# target_link_libraries(test table)
# target_link_libraries(test mathematics)


# Compile the cg_sandbox library.
#------------------------------------------------------------
add_subdirectory(src)
target_link_libraries(cg_sandbox opengl_utilities)
target_link_libraries(cg_sandbox interactive_graphics_context)
target_link_libraries(cg_sandbox reflector)
target_link_libraries(cg_sandbox table)
 
# Compile example applications
#------------------------------------------------------------
include_directories(include)
add_executable(basic_application examples/basic_application/basic_application.cpp)
target_compile_definitions(basic_application PRIVATE PATH="examples/basic_application")
target_link_libraries(basic_application cg_sandbox)
