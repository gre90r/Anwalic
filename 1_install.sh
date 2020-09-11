#!/bin/sh

#########
# usage #
#########
# check invalid argument
if [ $# -eq 1 ] && [ "$1" != "-noicon" ]; then
  echo "invalid argument $1"
  echo "available arguments: -noicon"
  exit 2
fi
# check if user is root. root priviliges are necessary to install
# the desktop icon file.
if [ "$1" != "-noicon" ]; then
  if ! [ $(id -u) = 0 ]; then
    echo "usage: sudo install.sh"
    echo "   or: install.sh -noicon"
    echo -n "This script must be run as root in order to create the desktop icon. "
    echo -n "If you don't want the desktop icon file enter -noicon as argument. "
    echo -n "You can manually copy the desktop icon file in "
    echo "./icon/desktop-icon/Anwalic.desktop to /usr/share/applications"
    exit 1
  fi
fi

#############
# variables #
#############
QMAKE=$HOME/.Qt/5.14.2/gcc_64/bin/qmake
ICON_FILE_NAME=Anwalic.desktop
ICON_FILE=icon/desktop-icon/$ICON_FILE_NAME
SYSTEM_DESKTOP_ICON_FOLDER=/usr/share/applications

#####################
# build application #
#####################
#$QMAKE -config release -o Makefile anwalic.pro || return
$QMAKE anwalic.pro -spec linux-g++ CONFIG+=qtquickcompiler
make
echo "--- clean ---"
make clean
echo "--- build end ---"

#######################
# create desktop icon #
#######################
# the user is advised to copy the application to folder ".Anwalic" in home folder
APP_INSTALL_DIR=$HOME/.Anwalic
EXEC_PATH=$APP_INSTALL_DIR/anwalic.sh
# create icon file
touch $ICON_FILE
echo "" > $ICON_FILE
# write icon file
echo "[Desktop Entry]" >> $ICON_FILE
echo "Encoding=UTF-8" >> $ICON_FILE
echo "Type=Application" >> $ICON_FILE
echo "Name=Anwalic" >> $ICON_FILE
echo "GenericName=anwalic" >> $ICON_FILE
echo "Comment=Anime Watch List Creator" >> $ICON_FILE
echo "NoDsiplay=true" >> $ICON_FILE
echo "Exec=$EXEC_PATH" >> $ICON_FILE
echo "Icon=$APP_INSTALL_DIR/icon/Anwalic_icon_1.png" >> $ICON_FILE
echo "Terminal=false" >> $ICON_FILE
echo "StartupNotify=false" >> $ICON_FILE
echo "Categories=other;" >> $ICON_FILE
echo "created desktop icon file in $ICON_FILE"
if [ "$1" != "-noicon" ]; then
    # copy icon file to folder where the other icon files are
    cp $ICON_FILE $SYSTEM_DESKTOP_ICON_FOLDER/$ICON_FILE_NAME || \
        echo "root permission needed to copy desktop icon file"
    echo "registered desktop icon file in menu"
fi
echo -n "if you want to use the .desktop icon file, you are advised to copy the application to folder '.Anwalic' in your home folder. "
echo "Otherwise change the paths in the .desktop file."
