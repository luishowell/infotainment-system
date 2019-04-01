TEMPLATE                =   subdirs

CONFIG                  +=  ordered

SUBDIRS                 =   Ultrasonic_test \
                            Mux_test        \
                            Board_test      \
                            MMA8652_test  

Sensors_test.depends           +=  ../Sensors
Mux_test.depends               +=  ../Sensors
Board_test.depends             +=  ../Sensors
MMA8652_test.depends           +=  ../Sensors