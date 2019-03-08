#setup
TEMPLATE        = lib
CONFIG          += static

#includes
INCLUDEPATH     += ./inc/

#libraries
LIBS += -L/usr/local/lib -lwiringPi

#inputs
SOURCES         += ./src/multiplexor.cpp        \
                += ./src/sensor_board.cpp       \
                += ./src/ultrasonic_sensor.cpp  \
                += ./src/MMA8652FCR1.cpp

#outputs
TARGET          = SENSORS
DESTDIR         = bin  
OBJECTS_DIR     = bin/src







