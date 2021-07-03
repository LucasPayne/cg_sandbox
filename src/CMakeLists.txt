cmake_minimum_required(VERSION 3.1)

include_directories(../include ../lib)

add_library(cg_sandbox
    world/world.cpp
    world/entity_system/entity_system.cpp
    world/entity_system/standard_aspects/Behaviour.cpp
    world/entity_system/standard_aspects/Camera.cpp
    world/entity_system/standard_aspects/Transform.cpp
    world/resources/resources.cpp

    world/graphics/graphics.cpp
    # world/graphics/painting/painting.cpp
    # world/graphics/painting/2D/circles.cpp
    # world/graphics/painting/2D/curves.cpp
    # world/graphics/painting/2D/lines.cpp
    # world/graphics/painting/2D/sprites.cpp
    # world/graphics/painting/3D/lines.cpp
    # world/graphics/painting/3D/spheres.cpp
    # world/graphics/painting/3D/wireframes.cpp
)
