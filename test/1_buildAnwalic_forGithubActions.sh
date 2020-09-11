#!/bin/sh

###################################
# build Anwalic before build Test #
###################################

cd ..
QMAKE=qmake
$QMAKE anwalic.pro
make