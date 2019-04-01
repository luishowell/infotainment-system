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

#inputs
SOURCES         += ./MMA8652_Online_Test.cpp  

#outputs
DESTDIR          = ./bin 
OBJECTS_DIR      = ./bin/src 
MOC_DIR          = moc
