#!/bin/bash

echo "Installing the required packages for Let me infotain you!"

sudo apt update

sudo apt install qt5-default
sudo apt install qtdeclarative5-dev
sudo apt install qtmultimedia5-dev
sudo apt install qml-module-qtquick-dialogs
sudo apt install qml-module-qtquick-controls
sudo apt install qml-module-qtquick-extras
sudo apt install libglm-dev
sudo apt install zlib1g-dev
sudo apt install gstreamer1.0-plugins-ugly
sudo apt install bluez

sudo apt install git-core
sudo apt install cmake

git clone git://git.drogon.net/wiringPi -v
cd wiringPi/
./build
cd ..
rm -rf wiringPi/

git clone https://github.com/taglib/taglib.git
cd taglib/
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release .
make
sudo make install
cd ..
rm -rf taglib/