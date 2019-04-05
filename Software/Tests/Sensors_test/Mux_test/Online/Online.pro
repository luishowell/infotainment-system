#setup
TEMPLATE         =   app 
QT              +=  core testlib
DEFINES += QT_DEPRECATED_WARNINGS
TARGET           = MuxOnlineTest

#includes
INCLUDEPATH     +=  ../../../../Sensors/inc
INCLUDEPATH     += ../../../../MainApp/inc

#libraries
DEPENDPATH  += . ../../../../Sensors/
LIBS        +=  ../../../../Sensors/bin/libSENSORS.a
#comment out if not on the pi
#LIBS        += -L/usr/local/lib -lwiringPi

#inputs
SOURCES         += ./Multiplexor_Online_Test.cpp  
SOURCES		    += ../../../../Sensors/src/multiplexor.cpp

#outputs
DESTDIR          = ./bin 
OBJECTS_DIR      = ./bin/src 
MOC_DIR          = moc
