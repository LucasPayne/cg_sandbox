cmake_minimum_required(VERSION 3.1)
project(cg_sandbox)

# Compile completely separated libraries.
#------------------------------------------------------------
include_directories(lib)
add_subdirectory(lib/opengl_utilities)
add_subdirectory(lib/interactive_graphics_context)
add_subdirectory(lib/reflector)
add_subdirectory(lib/table)

# # Compile the cg_sandbox library.
# #------------------------------------------------------------
# include_directories(include lib)
# aux_source_directory(src CG_SANDBOX_SRC_LIST)
# add_library(cg_sandbox ${CG_SANDBOX_SRC_LIST})
# target_link_libraries(cg_sandbox interactive_graphics_context)
# 
# 
# # Compile example applications
# #------------------------------------------------------------
# include_directories(include)
# add_executable(basic_application examples/basic_application/basic_application.cpp)
# target_compile_definitions(basic_application PRIVATE PATH="examples/basic_application")
