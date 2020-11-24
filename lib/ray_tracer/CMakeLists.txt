cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
project(ray_tracer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(ray_tracer
    src/aggregates/bvh.cpp
    src/aggregates/primitive_list.cpp
    src/illumination/light.cpp
    src/illumination/point_light.cpp
    src/imaging/camera.cpp
    src/imaging/framebuffer.cpp
    src/mathematics/geometry.cpp
    src/mathematics/numerics.cpp
    src/mathematics/transform.cpp
    src/models/models.cpp
    src/primitives/primitives.cpp
    src/scene/scene.cpp
    src/shapes/shapes.cpp
    src/shapes/plane.cpp
    src/shapes/sphere.cpp
    src/shapes/triangle_mesh.cpp
)
target_compile_options(ray_tracer PRIVATE -Wall -g)
