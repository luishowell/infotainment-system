#setup
TEMPLATE        = lib
CONFIG          += static
CONFIG              += c++11
QMAKE_CXXFLAGS += -std=c++11

#includes
INCLUDEPATH     += ./inc
HEADERS         += ./inc/*.hpp

#libraries

#inputs
SOURCES         = ./src/obd2.cpp

#outputs
TARGET          = OBD2
DESTDIR         = bin 
OBJECTS_DIR     = bin/src







