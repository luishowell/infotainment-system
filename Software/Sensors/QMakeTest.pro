INCLUDEPATH += inc/
INCLUDEPATH += ../MainApp/inc/
HEADERS += inc/*.h

SOURCES += src/*.cpp
LIBS += -L/usr/local/lib -lwiringPi
TARGET = SensorTest