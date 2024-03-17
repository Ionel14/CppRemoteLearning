cmake_minimum_required(VERSION 3.10)

project(SmartHomeProject)

add_executable(
    SmartHomeProject 
    devices/device.cpp
    room.cpp 
    sensors/sensor.cpp 
    smarthome.cpp 
    sensors/motionsensor.cpp 
    devices/securitydevice.cpp 
    sensors/soundsensor.cpp 
    sensors/temperaturesensor.cpp 
    devices/thermostatdevice.cpp 
    devices/voicecontroldevice.cpp
    server.cpp
    client.cpp)
