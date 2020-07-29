cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(model_loader)

include_directories(../../lib)

add_library(model_loader
    model_loader.cpp
    model_file_formats/OFF.cpp
    model_file_formats/Obj.cpp
)
target_compile_options(model_loader PRIVATE -Wall -g)
