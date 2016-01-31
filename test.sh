#!/usr/bin/env bash

# Build makefile
cmake .

# build the project
make

# run unit test
# make test also works
ctest

# TODO : memcheck with valgrind