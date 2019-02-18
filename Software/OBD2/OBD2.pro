#setup
TEMPLATE        = lib
CONFIG          += static

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







