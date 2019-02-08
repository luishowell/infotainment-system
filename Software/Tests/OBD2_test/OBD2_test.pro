#setup
TEMPLATE    =   app 
TARGET      =   OBD2Test
QT          +=  testlib

#includes
INCLUDEPATH +=  inc/
INCLUDEPATH +=  ../../OBD2/inc

#libraries
DEPENDPATH  += . ../../OBD2/
LIBS        +=  ../../OBD2/bin/libOBD2.a

#inputs
SOURCES         = ./OBD2_Test.cpp
DESTDIR         = ./bin 
OBJECTS_DIR     = ./bin/src 
MOC_DIR         = moc