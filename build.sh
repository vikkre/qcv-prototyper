#!/bin/bash

mkdir -p build
mkdir -p out

pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
popd
