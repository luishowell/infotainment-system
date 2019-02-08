TEMPLATE            = subdirs

CONFIG              += ordered

SUBDIRS             =   GUI         \
                        OBD2       \
                        #Sensors    \
                        Tests      \
                        MainApp

#GUI.depends        +=  OBD2
#GUI.depends        +=  Sensors
Tests.depends       +=  OBD2  
#Tests.depends       +=  Sensors
MainApp.depends     =   GUI

QMAKE_CXX = clang++
QMAKE_LINK = clang++


