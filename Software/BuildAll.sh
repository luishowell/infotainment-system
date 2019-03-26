#!/bin/sh

#JB: runs qmake for each subdirectory

echo GENERATING MAKEFILES...
qmake
#cd ./GUI && qmake 
cd ./OBD2 && qmake
cd ../Sensors && qmake
cd ../Tests && qmake
cd ../MainApp && qmake
cd .. 

echo BUILDING...
make -j4

#exit 0