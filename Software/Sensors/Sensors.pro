#setup
TEMPLATE        = lib
CONFIG          += staticlib

#includes
INCLUDEPATH     += ./inc/
INCLUDEPATH     += ../MainApp/inc
INCLUDEPATH     += ../GUI/inc/

#libraries
LIBS += -L/usr/local/lib -lwiringPi

#inputs
SOURCES         += ./src/multiplexor.cpp        
SOURCES         += ./src/sensor_board.cpp       
SOURCES         += ./src/ultrasonic_sensor.cpp  
SOURCES         += ./src/MMA8652FCR1.cpp

#outputs
TARGET          = SENSORS
DESTDIR         = bin  
OBJECTS_DIR     = bin/src







