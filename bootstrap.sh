#!/bin/bash
sudo apt-get update
sudo apt-get install -y git g++ cmake libssl-dev
sudo apt-get install -y qt5-default qttools5-dev-tools libgmp-dev

# Download QT Cryptographic Architecture
mkdir -p ~/Downloads
cd ~/Downloads
git clone git://anongit.kde.org/qca.git
cd ~/Downloads/qca

# Build QT Cryptographic Architecture
cmake .
make
sudo make install
