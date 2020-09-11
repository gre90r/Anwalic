#!/bin/sh

###################################
# build Anwalic before build Test #
###################################

cd ..
QMAKE=$Qt5_DIR/bin/qmake
$QMAKE anwalic.pro
make