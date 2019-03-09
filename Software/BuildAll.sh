#!/bin/sh

#JB: runs qmake for each subdirectory

echo GENERATING MAKEFILES...
qmake
cd ./GUI && qmake 
cd ../OBD2 && qmake
cd ../Sensors && qmake
cd ../Tests && qmake
cd .. 

echo BUILDING...
make

#exit 0