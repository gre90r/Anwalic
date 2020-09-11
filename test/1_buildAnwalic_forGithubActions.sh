#!/bin/sh
# Qt5_DIR: /home/runner/work/Anwalic/Anwalic/Qt/5.14.2/gcc_64

# Qt bin directory is added to Path by github workflow install-qt-action
QMAKE=qmake

$QMAKE -o Makefile ../anwalic.pro -spec linux-g++ CONFIG+=qtquickcompiler
make