TEMPLATE    += app
QT          += widgets qml quick quickwidgets testlib
CONFIG      += qt sdk_no_version_check 

INCLUDEPATH += inc/
INCLUDEPATH += ../OBD2
HEADERS     += inc/*.h

SOURCES		+= src/*.cpp
#SOURCES     += ../OBD2/obd2.cpp 

#------UNIT TESTS---------#
#INCLUDEPATH += ./OBD2/tests/inc/
#INCLUDEPATH += ./Sensors/tests/inc/
#SOURCES     += ./OBD2/test/src/*.cpp
#SOURCES     += ./Sensors/test/src/*.cpp

TARGET		= QMakeTest
DESTDIR     = bin 
OBJECTS_DIR = bin/src 
MOC_DIR     = moc

