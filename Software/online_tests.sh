#!/bin/sh

sudo ./Tests/OBD2_test/Online/bin/OBD2OnlineTest
sleep 3s
./Tests/Sensors_test/Board_test/Online/bin/SensorBoardOnlineTest
sleep 3s
./Tests/Sensors_test/MMA8652_test/Online/bin/MMA8652OnlineTest
sleep 3s
./Tests/Sensors_test/Mux_test/Online/bin/MuxOnlineTest
sleep 3s
./Tests/Sensors_test/Ultrasonic_test/Online/bin/UltrasonicOnlineTest 