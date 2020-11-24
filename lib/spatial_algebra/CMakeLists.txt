cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(spatial_algebra)

include_directories(../../lib ../../tools)

add_library(spatial_algebra
    spatial_algebra.cpp
)
target_compile_options(spatial_algebra PRIVATE -Wall -Werror -g)
