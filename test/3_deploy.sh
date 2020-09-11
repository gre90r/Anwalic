#!/bin/bash
#################################################################
# before: install CQtDeployer from source to ~/.CQtDeployer     #
# see: https://github.com/QuasarApp/CQtDeployer#build-for-linux #
#################################################################

APP_NAME=AnwalicTest
CQTDEPLOYER="$HOME/.CQtDeployer/1.5/cqtdeployer.sh"
QMAKE="$HOME/Qt/5.14.2/gcc_64/bin/qmake"
DEPLOY_DIR=./deploy

##############################################
# deploy application. create all needed libs #
##############################################
$CQTDEPLOYER -bin $APP_NAME \
             -qmake $QMAKE \
             -targetDir $DEPLOY_DIR \
             -name $APP_NAME \
             -publisher gre90r
