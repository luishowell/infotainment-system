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
SOURCES         += ./SensorBoard_test.cpp  

#outputs
TARGET           = BoardTest
DESTDIR          = ../bin 
OBJECTS_DIR      = ../bin/src 
MOC_DIR          = moc