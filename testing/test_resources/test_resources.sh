#!/bin/bash
g++ -I../../core -I../../tools  -o test_resources test_resources.cpp ../../tools/reflector/reflector.cpp ../../tools/reflector/type_handle.cpp ../../core/data_structures/table.cpp ../../core/data_structures/table_collection.cpp ../../core/world/resources/resources.cpp ../../core/world/entities/entities.cpp
