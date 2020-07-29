#!/bin/bash
g++ -I../../src -o test_models test_models.cpp -L../../lib/spatial_algebra/build -L../../lib/model_loader/build -lspatial_algebra -lmodel_loader
