#setup
TEMPLATE         =   app 
QT              +=  core testlib
DEFINES += QT_DEPRECATED_WARNINGS
TARGET           = SensorBoardOnlineTest

#includes
INCLUDEPATH     +=  ../../../../Sensors/inc
INCLUDEPATH     += ../../../../MainApp/inc

#libraries
DEPENDPATH  += . ../../../../Sensors/
LIBS        +=  ../../../../Sensors/bin/libSENSORS.a
#comment out if not on the pi
LIBS        += -L/usr/local/lib -lwiringPi
LIBS += -lcrypt
LIBS += -lrt

#inputs
SOURCES         += ./SensorBoard_Online_Test.cpp  
SOURCES		+= ../../../../Sensors/src/sensor_board.cpp
SOURCES		+= ../../../../Sensors/src/multiplexor.cpp
SOURCES		+= ../../../../Sensors/src/ultrasonic_sensor.cpp

#outputs
DESTDIR          = ./bin 
OBJECTS_DIR      = ./bin/src 
MOC_DIR          = moc
