#setup
TEMPLATE    = app 
TARGET      = MainApp
QT          += widgets qml quick quickwidgets testlib

#includes
INCLUDEPATH += inc/
INCLUDEPATH += ../GUI/inc
INCLUDEPATH += ../OBD2/inc
INCLUDEPATH += ../Sensors/inc


#libraries
DEPENDPATH  += . ../GUI/
LIBS        +=  ../GUI/bin/libGUI.a 
LIBS += -L/usr/local/lib -lwiringPi

#inputs
SOURCES     += src/main.cpp
DESTDIR         = bin 
OBJECTS_DIR     = bin/src 



SOURCES += ../GUI/src/*.cpp
SOURCES += ../OBD2/src/obd2.cpp
SOURCES += ../Sensors/src/sensor_board.cpp
SOURCES += ../Sensors/src/ultrasonic_sensor.cpp
SOURCES += ../Sensors/src/multiplexor.cpp
