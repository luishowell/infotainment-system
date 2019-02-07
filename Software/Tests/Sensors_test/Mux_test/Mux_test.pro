#setup
TEMPLATE         =   app 
QT              +=  testlib
DEFINES += QT_DEPRECATED_WARNINGS

#includes
INCLUDEPATH     +=  .
#HEADERS         =  

#libraries
#DEPENDPATH  += . ../../Sensors/
#LIBS        +=  ../../Sensors/bin/libSensors.a

#inputs
SOURCES         += ./Multiplexor_test.cpp  

#outputs
TARGET           = MuxTest
DESTDIR          = bin 
OBJECTS_DIR      = bin/src 
MOC_DIR          = moc