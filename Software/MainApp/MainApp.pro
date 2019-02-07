#setup
TEMPLATE    = app 
TARGET      = MainApp
QT          += widgets qml quick quickwidgets testlib

#includes
INCLUDEPATH += inc/
INCLUDEPATH += ../GUI/inc

#libraries
DEPENDPATH  += . ../GUI/
LIBS        +=  ../GUI/bin/libGUI.a 

#inputs
SOURCES     = src/main.cpp
DESTDIR         = bin 
OBJECTS_DIR     = bin/src 