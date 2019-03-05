#setup
TEMPLATE    = app 
TARGET      = MainApp
QT          += widgets qml quick quickwidgets multimedia multimediawidgets testlib 

#includes
INCLUDEPATH += inc/
INCLUDEPATH += ../GUI/inc
INCLUDEPATH += ../OBD2/inc
INCLUDEPATH += ../Sensors/inc

HEADERS     += ../GUI/inc/*.h
#HEADERS     += ./inc/*.h
HEADERS     += ./inc/CANThread.h 
HEADERS     += ./inc/CANWorker.h 
HEADERS     += ./inc/SensorThread.h 



#libraries
#DEPENDPATH  += . ../GUI/
#LIBS        +=  ../GUI/bin/libGUI.a 
LIBS += -L/usr/local/lib -lwiringPi

#inputs

DESTDIR         = bin 
OBJECTS_DIR     = bin/src 

MOC_DIR         = ./moc

SOURCES     += src/main.cpp
SOURCES     += src/CANThread.cpp
SOURCES     += src/CANWorker.cpp
SOURCES    += src/SensorThread.cpp
SOURCES += ../GUI/src/*.cpp
SOURCES += ../OBD2/src/obd2.cpp
SOURCES += ../Sensors/src/sensor_board.cpp
SOURCES += ../Sensors/src/ultrasonic_sensor.cpp
SOURCES += ../Sensors/src/multiplexor.cpp
