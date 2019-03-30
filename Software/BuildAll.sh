#!/bin/sh

#JB: runs qmake for each subdirectory

echo GENERATING MAKEFILES...
qmake
#cd ./GUI && qmake 
cd ./OBD2 && qmake -d
cd ../Sensors && qmake -d
cd ../Tests && qmake -d
cd ../MainApp && qmake -d
cd .. 

echo BUILDING...
make -j4

#exit 0