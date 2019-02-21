TEMPLATE            = subdirs

CONFIG              += ordered

#SUBDIRS             =   #GUI         \
                        #OBD2       \
                        #Sensors    \
#SUBDIRS =                       Tests      \
SUBDIRS           =            MainApp

#GUI.depends        +=  OBD2
#GUI.depends        +=  Sensors
#Tests.depends       +=  OBD2  
#Tests.depends       +=  Sensors
#MainApp.depends		+= OBD2
#MainApp.depends     +=   GUI


QMAKE_CXX = clang++
QMAKE_LINK = clang++


