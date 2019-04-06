#-----------------------------------#
#---------------SETUP---------------#
#-----------------------------------#
TEMPLATE    = app 
TARGET      = MainApp
QT          += widgets qml quick quickwidgets multimedia multimediawidgets testlib  

CONFIG              += c++11
QMAKE_CXXFLAGS += -std=c++11

#-----------------------------------#
#-------------INCLUDES--------------#
#-----------------------------------#
INCLUDEPATH += inc/
#INCLUDEPATH += ../GUI/inc
INCLUDEPATH += ../OBD2/inc
INCLUDEPATH += ../Sensors/inc

#-----------------------------------#
#-------PATHS TO MOC HEADERS--------#
#-----------------------------------#
HEADERS     += ./inc/*.h
#HEADERS     += ./inc/CANThread.h 
#HEADERS     += ./inc/CANWorker.h 
#HEADERS     += ./inc/SensorThread.h 
#HEADERS     += ./inc/SensorWorker.h 
#HEADERS     += ./inc/AccThread.h
#HEADERS     += ./inc/AccWorker.h
#HEADERS     += ./inc/*.h

#-----------------------------------#
#-------------LIBRARIES-------------#
#-----------------------------------#
DEPENDPATH  += . ../OBD2/
DEPENDPATH  += . ../Sensors/
PRE_TARGETDEPS += ../OBD2/bin/libOBD2.a
PRE_TARGETDEPS += ../Sensors/bin/libSENSORS.a
# local libs
LIBS        +=  -L../OBD2/bin/ -lOBD2
LIBS        +=  -L../Sensors/bin/ -lSENSORS
# system-wide libs
#LIBS += -L/usr/local/lib -lwiringPi
LIBS        += -L/usr/local/lib/taglib/taglib -ltag
LIBS        += -lz

#-----------------------------------#
#--------------OUTPUTS--------------#
#-----------------------------------#
DESTDIR         = bin 
OBJECTS_DIR     = bin/src 
MOC_DIR         = ./src/moc

#-----------------------------------#
#--------------INPUTS---------------#
#-----------------------------------#
SOURCES     += src/AccGauge.cpp
SOURCES     += src/AccThread.cpp
SOURCES     += src/AccWorker.cpp
SOURCES     += src/CANThread.cpp
SOURCES     += src/CANWorker.cpp
SOURCES     += src/Diagnostics.cpp
SOURCES     += src/ErrorCodes.cpp
SOURCES     += src/Hash.cpp
SOURCES     += src/LoggerWindow.cpp
SOURCES     += src/main.cpp
SOURCES     += src/MainMenu.cpp
SOURCES     += src/Media.cpp
SOURCES     += src/MediaControls.cpp
SOURCES     += src/Mutex.cpp
SOURCES     += src/Parking.cpp
SOURCES     += src/PlaylistModel.cpp
SOURCES     += src/SensorThread.cpp
SOURCES     += src/SensorWorker.cpp
SOURCES     += src/StateManager.cpp

#DEFINES             += "RPI=1"


