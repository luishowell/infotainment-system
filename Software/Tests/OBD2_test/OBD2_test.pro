#setup
TEMPLATE    =   app 
TARGET      =   OBD2Test
QT          +=  testlib

#includes
INCLUDEPATH +=  inc/

#libraries
DEPENDPATH  += . ../../OBD2/
LIBS        +=  ../../OBD2/bin/libOBD2.a

#inputs
SOURCES         = src/OBD2_Test.cpp
DESTDIR         = bin 
OBJECTS_DIR     = bin/src 