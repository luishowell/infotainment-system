#setup
TEMPLATE        = lib
CONFIG          += static
QT              += widgets qml quick quickwidgets multimedia multimediawidgets testlib qtquickcompiler

#includes
HEADERS         += ../OBD2/inc/*.hpp

HEADERS		+= ../GUI/inc/*.h
HEADERS		+= ../Sensors/inc/*.h
INCLUDEPATH     += ../OBD2/inc
INCLUDEPATH	+= ../GUI/inc
#INCLUDEPATH     += ../OBD2/
INCLUDEPATH     += ../MainApp/inc
INCLUDEPATH	+= ../Sensors/inc

#libraries
DEPENDPATH	+= . ../OBD2
LIBS            += ../OBD2/bin/libOBD2.a
DEPENDPATH	+= . ../Sensors
LIBS		+= ../Sensors/bin/libSensors.a


#inputs
SOURCES         = ./src/*.cpp

#outputs
TARGET          = GUI
DESTDIR         = bin 
OBJECTS_DIR     = bin/src
MOC_DIR         = moc







