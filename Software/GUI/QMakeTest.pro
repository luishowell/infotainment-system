TEMPLATE    += app
QT          += widgets qml quick quickwidgets 
CONFIG      += qt sdk_no_version_check 
INCLUDEPATH += inc/
INCLUDEPATH += ../OBD2
HEADERS     += inc/*.h
SOURCES		+= src/*.cpp
#SOURCES     += ../OBD2/obd2.cpp
TARGET		= QMakeTest
DESTDIR     = bin 
OBJECTS_DIR = bin/src 
MOC_DIR     = moc

