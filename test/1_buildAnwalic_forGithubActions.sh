#!/bin/sh

###################################
# build Anwalic before build Test #
###################################

QMAKE=$QTDIR/bin/qmake

cd ..
$QMAKE anwalic.pro
make