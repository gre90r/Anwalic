#!/bin/bash
#################################################################
# before: install CQtDeployer from source to ~/.CQtDeployer     #
# see: https://github.com/QuasarApp/CQtDeployer#build-for-linux #
#################################################################

CQTDEPLOYER="$HOME/.CQtDeployer/1.5/cqtdeployer.sh"
DEPLOY_DIR=./deploy/linux
DEPLOY_INSTALLER_DIR=./installer/linux
ANWALIC_VERSION=1.4-DevBuild-2
QMAKE="$HOME/.Qt/5.14.2/gcc_64/bin/qmake"

##############################################
# deploy application. create all needed libs #
##############################################
$CQTDEPLOYER -bin anwalic \
             -qmake $QMAKE \
             -targetDir $DEPLOY_DIR \
             -name Anwalic \
             -icon ./icon/Anwalic_icon_1.png \
             -publisher gre90r

##################
# copy resources #
##################
# app window background image
if [ ! -d "$DEPLOY_DIR/backgrounds" ]; then
    mkdir $DEPLOY_DIR/backgrounds
fi
cp ./backgrounds/anime_background_1.jpg $DEPLOY_DIR/backgrounds
# app icon
cp -r ./icon $DEPLOY_DIR

####################
# create gzip file #
####################
CURRENT_DIR=`pwd`
cd $DEPLOY_DIR
rm Anwalic-$ANWALIC_VERSION.tar.gz
tar czf Anwalic-$ANWALIC_VERSION.tar.gz *
cd $CURRENT_DIR
