################################################################################
# @author gre90r
# link all .o files which have been generated with qmake (buildAnwalic.sh) into
# test application. Only link what has already been built.
################################################################################

CXX=g++
CXXFLAGS=-g -Wall -std=c++11 -fPIC -Wtrigraphs
TARGET=AnwalicTest
OBJECTS_PATH=..
SRC_PATH=../src

# selects all .o files, but is also has main.o which needs to be excluded
#OBJECTS=$(wildcard $(OBJECTS_PATH)/*.o)

# all object files except main.o
OBJECTS=$(OBJECTS_PATH)/aboutwindow.o \
	$(OBJECTS_PATH)/FilterByTag.o \
	$(OBJECTS_PATH)/moc_aboutwindow.o \
	$(OBJECTS_PATH)/addnewanime.o \
	$(OBJECTS_PATH)/FilterHideAnimesWithNameOnly.o \
	$(OBJECTS_PATH)/moc_addnewanime.o \
	$(OBJECTS_PATH)/AnimelistManager.o \
	$(OBJECTS_PATH)/FilterHideMovies.o \
	$(OBJECTS_PATH)/moc_editanimewindow.o \
	$(OBJECTS_PATH)/animelist.o \
	$(OBJECTS_PATH)/FilterHideOpenEndedAnimes.o \
	$(OBJECTS_PATH)/moc_mainwindow.o \
	$(OBJECTS_PATH)/AnimeListViewHelper.o \
	$(OBJECTS_PATH)/FilterShowMovies.o \
	$(OBJECTS_PATH)/moc_preferenceswindow.o \
	$(OBJECTS_PATH)/anime.o \
	$(OBJECTS_PATH)/FilterShowOpenEndedAnimes.o \
	$(OBJECTS_PATH)/preferences.o \
	$(OBJECTS_PATH)/anwalic_plugin_import.o \
	$(OBJECTS_PATH)/FilterShowStartedAnimes.o \
	$(OBJECTS_PATH)/preferenceswindow.o \
	$(OBJECTS_PATH)/AnwalicService.o \
	$(OBJECTS_PATH)/InternetUtilities.o \
	$(OBJECTS_PATH)/saveload.o \
	$(OBJECTS_PATH)/editanimewindow.o \
	$(OBJECTS_PATH)/StringUtils.o \
	$(OBJECTS_PATH)/errorview.o \
	$(OBJECTS_PATH)/mainwindow.o \
	$(OBJECTS_PATH)/FilterAnimelist.o \
	$(OBJECTS_PATH)/memory.o
QT_PATH=../../../Qt/5.14.2/gcc_64
INCPATH=-I/usr/include \
	-I$(SRC_PATH) \
	-I../../build-anwalic-Desktop_Qt_5_14_2_GCC_64bit-Release \
	-I$(QT_PATH)/include \
	-I$(QT_PATH)/include/QtWidgets \
	-I$(QT_PATH)/include/QtGui \
	-I$(QT_PATH)/include/QtCore
QT_SO_FILES=$(QT_PATH)/lib/libQt5Core.so \
	$(QT_PATH)/lib/libQt5Gui.so \
	$(QT_PATH)/lib/libQt5Widgets.so
LIBS=-lGL -pthread -lgtest


all : $(TARGET)

$(TARGET).o : AnwalicTest.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(TARGET) : $(OBJECTS) AnwalicTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -L /usr/lib $(INCPATH) $(QT_SO_FILES) $(LIBS)

clean:
	rm $(TARGET)
	rm $(TARGET).o

