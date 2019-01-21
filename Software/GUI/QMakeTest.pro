TEMPLATE    += app
QT          += widgets
CONFIG      += qt sdk_no_version_check 
INCLUDEPATH += inc/
HEADERS     += inc/*.h
SOURCES		+= src/*.cpp
TARGET		= QMakeTest
DESTDIR     = bin 
OBJECTS_DIR = bin/src 
MOC_DIR     = moc

