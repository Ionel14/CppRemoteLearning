cmake_minimum_required(VERSION 3.10)
project(nagarroRemoteLearning)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        nagarroRemoteLearning
        main.cc
        utils/enums.h
        devices/Device.h
        devices/Device.cc
        devices/Sensor.h
        devices/Sensor.cc
        house/Room.h
        house/Room.cc
        house/House.h
        house/House.cc
        user/User.h
        user/User.cc
)
