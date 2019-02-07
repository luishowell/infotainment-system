#setup
TEMPLATE        = lib
CONFIG          += static
QT              += widgets qml quick quickwidgets testlib

#includes
HEADERS         = inc/*.h
INCLUDEPATH     += inc/
#INCLUDEPATH     += ../OBD2/
INCLUDEPATH     += ../MainApp/inc

#libraries
#LIBS            = ../OBD2/bin/libOBD2.a
#DEPENDS

#inputs
SOURCES         = ./src/*.cpp

#outputs
TARGET          = GUI
DESTDIR         = bin 
OBJECTS_DIR     = bin/src
MOC_DIR         = moc







