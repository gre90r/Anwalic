######################################################################
# Automatically generated by qmake (3.1) Fri Jul 26 17:04:13 2019
######################################################################

TEMPLATE = app
TARGET = anwalic
INCLUDEPATH += src/
CONFIG += static
CONFIG += release c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix {

}
win32 {

}

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/aboutwindow.h \
           src/addnewanime.h \
           src/anime.h \
           src/animelist.h \
           src/AnimelistManager.h \
           src/AnimeListViewHelper.h \
           src/AnwalicService.h \
           src/editanimewindow.h \
           src/errorview.h \
           src/FilterAnimelist.h \
           src/FilterByTag.h \
           src/FilterHideAnimesWithNameOnly.h \
           src/FilterHideMovies.h \
           src/FilterHideOpenEndedAnimes.h \
           src/FilterShowMovies.h \
           src/FilterShowOpenEndedAnimes.h \
           src/FilterShowStartedAnimes.h \
           src/globals.h \
           src/InternetUtilities.h \
           src/ListType.h \
           src/mainwindow.h \
           src/memory.h \
           src/preferences.h \
           src/preferenceswindow.h \
           src/resource.h \
           src/resource1.h \
           src/resource2.h \
           src/saveload.h \
           src/stringsDE.h \
           src/stringsEN.h \
           src/StringUtils.h \
           src/GeneratedFiles/ui_aboutwindow.h \
           src/GeneratedFiles/ui_addnewanime.h \
           src/GeneratedFiles/ui_editanimewindow.h \
           src/GeneratedFiles/ui_mainwindow.h \
           src/GeneratedFiles/ui_preferenceswindow.h
FORMS += src/aboutwindow.ui \
         src/addnewanime.ui \
         src/editanimewindow.ui \
         src/mainwindow.ui \
         src/preferenceswindow.ui
SOURCES += src/aboutwindow.cpp \
           src/addnewanime.cpp \
           src/anime.cpp \
           src/animelist.cpp \
           src/AnimelistManager.cpp \
           src/AnimeListViewHelper.cpp \
           src/anwalic_plugin_import.cpp \
           src/AnwalicService.cpp \
           src/editanimewindow.cpp \
           src/errorview.cpp \
           src/FilterAnimelist.cpp \
           src/FilterByTag.cpp \
           src/FilterHideAnimesWithNameOnly.cpp \
           src/FilterHideMovies.cpp \
           src/FilterHideOpenEndedAnimes.cpp \
           src/FilterShowMovies.cpp \
           src/FilterShowOpenEndedAnimes.cpp \
           src/FilterShowStartedAnimes.cpp \
           src/InternetUtilities.cpp \
           src/main.cpp \
           src/mainwindow.cpp \
           src/memory.cpp \
           src/preferences.cpp \
           src/preferenceswindow.cpp \
           src/saveload.cpp \
           src/StringUtils.cpp \
           # src/AnwalicUnitTests/AnwalicUnitTests.cpp

DISTFILES += \
  runTests.sh \
  test/Makefile
