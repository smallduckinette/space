#!/bin/bash

SRC=$(dirname $0)
BUILD=$(dirname $0)/build

export CC=gcc-10
export CXX=g++-10
mkdir -p build
cmake -S $SRC -B $BUILD -G Ninja
