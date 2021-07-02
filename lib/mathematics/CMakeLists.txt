cmake_minimum_required(VERSION 3.1)

add_subdirectory(spatial_algebra)

add_library(mathematics
    mathematics.cpp
    ray.cpp
)
target_link_libraries(mathematics spatial_algebra)
