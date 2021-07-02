cmake_minimum_required(VERSION 3.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(table
    table.cpp
    table_collection.cpp
)

