#!/bin/sh

# Qt bin directory is added to Path by github workflow install-qt-action
QMAKE=qmake

cd ..
$QMAKE anwalic.pro -spec linux-g++
make