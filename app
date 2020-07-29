#!/bin/bash
#
# This is just a helper script for building applications in the apps/ directory.
# cg_sandbox is just a library, and projects just need to link to it and include relevant header files.

if [ "$#" -lt 1 ] ; then
    echo "give good args"
else
    # First make sure the cg_sandbox library is up to date.
    ./create
    app_name=$1
    shift
    g++ -Icore -Ilib -o "apps_build/$app_name" "apps/$app_name/$app_name.cpp" -lcg_sandbox -lm -ldl -lglfw -Lbuild -Lbuild/lib/model_loader -Lbuild/lib/spatial_algebra\
        -lmodel_loader -lspatial_algebra
    if [ "$?" -eq 0 ] ; then
        "apps_build/$app_name" $@
    fi
fi

