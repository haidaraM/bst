#!/usr/bin/env bash

# install valgrind
sudo apt-get install -y valgrind

# install cmake 3.4.3
wget --no-check-certificate https://cmake.org/files/v3.4/cmake-3.4.3.tar.gz
tar xf cmake-3.4.3.tar.gz
cd cmake-3.4.3
./configure
make
sudo make install