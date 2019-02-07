#setup
TEMPLATE         =   app 
QT              +=  testlib

#includes
INCLUDEPATH     +=  inc/

#libraries
DEPENDPATH  += . ../../Sensors/
LIBS        +=  ../../Sensors/bin/libSensors.a

#inputs
SOURCES         += ./src/Multiplexor_test.cpp        \
                += ./src/SensorBoard_test.cpp       \
                += ./src/UltrasonicSensor_Test.cpp   

#outputs
TARGET           = SensorsTest
DESTDIR          = bin 
OBJECTS_DIR      = bin/src 