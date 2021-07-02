cmake_minimum_required(VERSION 3.1)

include_directories(../include ../lib)

add_library(cg_sandbox
    world/world.cpp
    world/entity_system/entity_system.cpp
    world/entity_system/standard_aspects/Behaviour.cpp
    world/entity_system/standard_aspects/Camera.cpp
    world/entity_system/standard_aspects/Transform.cpp
    world/resources/resources.cpp
    mathematics/mathematics.cpp
    mathematics/ray.cpp
)
