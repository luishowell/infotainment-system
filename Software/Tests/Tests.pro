TEMPLATE                = subdirs

CONFIG                  += ordered

SUBDIRS        =    OBD2_test   \
                    #Sensors_test  
                 

OBD2.depends           +=  ../OBD2
#Sensors.depends        +=  ../Sensors
