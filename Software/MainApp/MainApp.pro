#setup
TEMPLATE    = app 
TARGET      = MainApp
QT          += widgets qml quick quickwidgets multimedia multimediawidgets testlib 

#includes
INCLUDEPATH += inc/
INCLUDEPATH += ../GUI/inc
INCLUDEPATH += ../OBD2/inc
INCLUDEPATH += ../Sensors/inc

#HEADERS     += ../GUI/inc/*.h
#HEADERS     += ./inc/*.h
HEADERS     += ./inc/CANThread.h 
HEADERS     += ./inc/CANWorker.h 
HEADERS     += ./inc/SensorThread.h 
HEADERS     += ./inc/SensorWorker.h 
HEADERS     += ./inc/AccThread.h
HEADERS     += ./inc/AccWorker.h





#libraries
DEPENDPATH  += . ../GUI/
DEPENDPATH  += . ../OBD2/
DEPENDPATH  += . ../Sensors/
PRE_TARGETDEPS += ../GUI/bin/libGUI.a
PRE_TARGETDEPS += ../OBD2/bin/libOBD2.a
PRE_TARGETDEPS += ../Sensors/bin/libSENSORS.a
LIBS        +=  -L../GUI/bin/ -lGUI
LIBS        +=  -L../OBD2/bin/ -lOBD2
LIBS        +=  -L../Sensors/bin/ -lSENSORS
#LIBS += -L/usr/local/lib -lwiringPi

#inputs

DESTDIR         = bin 
OBJECTS_DIR     = bin/src 

MOC_DIR         = ./moc

SOURCES     += src/main.cpp
SOURCES     += src/CANThread.cpp
SOURCES     += src/CANWorker.cpp
SOURCES    += src/SensorThread.cpp
SOURCES     += src/SensorWorker.cpp
SOURCES     += src/AccThread.cpp
SOURCES     += src/AccWorker.cpp



#DEFINES             += "RPI=1"

#SOURCES += ../GUI/src/*.cpp
#SOURCES += ../OBD2/src/obd2.cpp
#SOURCES += ../Sensors/src/sensor_board.cpp
#SOURCES += ../Sensors/src/ultrasonic_sensor.cpp
#SOURCES += ../Sensors/src/multiplexor.cpp
