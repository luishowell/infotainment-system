TEMPLATE            = subdirs

CONFIG              += ordered

SUBDIRS             =   GUI        \
                        OBD2       \
                        Sensors    \
                        Tests      \
                        MainApp

GUI.depends         +=  OBD2
GUI.depends         +=  Sensors
Tests.depends       +=  OBD2  
Tests.depends       +=  Sensors
MainApp.depends		+=  OBD2
MainApp.depends     +=  GUI
MainApp.depends     +=  SENSORS

#comment out the following line if building for non raspberry pi
DEFINES             += RPI=1

QMAKE_CXX = clang++
QMAKE_LINK = clang++


