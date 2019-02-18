#setup
TEMPLATE         =   app 
QT              +=  core testlib
DEFINES += QT_DEPRECATED_WARNINGS

#includes
INCLUDEPATH     +=  .
#HEADERS         =  

#libraries
#DEPENDPATH  += . ../../Sensors/
#LIBS        +=  ../../Sensors/bin/libSensors.a

#inputs
SOURCES         += ./UltrasonicSensor_test.cpp  

#outputs
TARGET           = UltrasonicTest
DESTDIR          = ../bin 
OBJECTS_DIR      = ../bin/src 
MOC_DIR          = moc