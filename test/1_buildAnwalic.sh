#!/bin/sh

###################################
# build Anwalic before build Test #
###################################

cd ..
QMAKE=$HOME/.Qt/5.14.2/gcc_64/bin/qmake
$QMAKE anwalic.pro -spec linux-g++
make