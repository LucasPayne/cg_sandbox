cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(model_loader)

add_library(model_loader
    model_loader.cpp
)
target_compile_options(model_loader PRIVATE -Wall -g)
