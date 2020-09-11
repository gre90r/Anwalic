#!/bin/sh
wget https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz
tar -xvf boost_1_74_0.tar.gz
cd boost_1_74_0/
./bootstrap.sh
./b2