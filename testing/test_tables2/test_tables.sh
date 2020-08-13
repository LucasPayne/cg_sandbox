#!/bin/bash
g++ -I../../core -I../../tools  -o test_tables test_tables.cpp ../../tools/reflector/reflector.cpp ../../tools/reflector/type_handle.cpp ../../core/data_structures/table.cpp
