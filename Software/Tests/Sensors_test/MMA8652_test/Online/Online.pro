#setup
TEMPLATE         =   app 
QT              +=  core testlib
DEFINES += QT_DEPRECATED_WARNINGS
TARGET           = MMA8652OnlineTest

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
SOURCES         += ./MMA8652_Online_Test.cpp  
SOURCES		    += ../../../../Sensors/src/MMA8652FCR1.cpp

#outputs
DESTDIR          = ./bin 
OBJECTS_DIR      = ./bin/src 
MOC_DIR          = moc
