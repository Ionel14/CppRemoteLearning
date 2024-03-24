cmake_minimum_required(VERSION 3.10)
project(nagarroRemoteLearningServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        nagarroRemoteLearningServer
        utils/enums.h
        devices/Device.h
        devices/Device.cc
        sensors/Sensor.h
        sensors/Sensor.cc
        house/Room.h
        house/Room.cc
        house/House.h
        house/House.cc
        user/User.h
        user/User.cc
        devices/Light.cc
        devices/Light.h
        devices/Heater.cc
        devices/Heater.h
        devices/AirConditioner.cc
        devices/AirConditioner.h
        utils/StatusPrinter.cc
        utils/StatusPrinter.h
        sensors/TemperatureSensor.cc
        sensors/TemperatureSensor.h
        sensors/HumiditySensor.cc
        sensors/HumiditySensor.h
        sensors/MonoxidSensor.cc
        sensors/MonoxidSensor.h
        server.cc
        utils/serverUtils.h
)
