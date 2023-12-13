cmake_minimum_required(VERSION 3.0.0)
project(smart_home)
add_executable(smart_home main.cpp sources/smart_home.cpp sources/room.cpp sources/device.cpp sources/sensor.cpp headers/smart_home.h headers/room.h headers/device.h headers/sensor.h)