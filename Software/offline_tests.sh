#!/bin/sh

sudo ./Tests/OBD2_test/Offline/bin/OBD2OfflineTest
sleep 3s
./Tests/Sensors_test/Board_test/Offline/bin/SensorBoardOfflineTest
sleep 3s
./Tests/Sensors_test/MMA8652_test/Offline/bin/MMA8652OfflineTest
sleep 3s
./Tests/Sensors_test/Mux_test/Offline/bin/MuxOfflineTest
sleep 3s
./Tests/Sensors_test/Ultrasonic_test/Offline/bin/UltrasonicOfflineTest 