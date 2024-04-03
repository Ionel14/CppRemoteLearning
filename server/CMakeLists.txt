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
    threadpool.cpp
    message.cpp
    server.cpp)

find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(SmartHomeProject Boost::serialization)