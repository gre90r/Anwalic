#!/bin/sh

if ! [ $(id -u) = 0 ]; then
  echo "root permission required"
  exit 1
fi

ICON_FILE_NAME=Anwalic.desktop
SYSTEM_DESKTOP_ICON_FOLDER=/usr/share/applications/

# unregister desktop icon file from menu
sudo rm $SYSTEM_DESKTOP_ICON_FOLDER/$ICON_FILE_NAME
