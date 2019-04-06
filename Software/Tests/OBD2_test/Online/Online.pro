#setup
TEMPLATE    =   app 
TARGET      =   OBD2OnlineTest
QT          +=  testlib

CONFIG              += c++11
QMAKE_CXXFLAGS += -std=c++11

#includes
INCLUDEPATH +=  inc/
INCLUDEPATH +=  ../../../OBD2/inc

#libraries
DEPENDPATH  += . ../../../OBD2/inc
LIBS        +=   ../../../OBD2/bin/libOBD2.a

#inputs
SOURCES         =   ./OBD2_Online_Test.cpp 
                    
DESTDIR         = ./bin 
OBJECTS_DIR     = ./bin/src 
MOC_DIR         = moc