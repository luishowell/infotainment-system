#setup
TEMPLATE    =   app 
TARGET      =   OBD2OfflineTest
QT          +=  testlib

#includes
INCLUDEPATH +=  inc/
INCLUDEPATH +=  ../../../OBD2/inc

#libraries
DEPENDPATH  += . ../../../OBD2/inc
LIBS        +=   ../../../OBD2/bin/libOBD2.a

#inputs
SOURCES         =   ./OBD2_Offline_Test.cpp 
                    
DESTDIR         = ./bin 
OBJECTS_DIR     = ./bin/src 
MOC_DIR         = moc