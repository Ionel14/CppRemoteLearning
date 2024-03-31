cmake_minimum_required(VERSION 3.10)
project(nagarroRemoteLearningServer)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR /opt/local/include)
set(Boost_LIBRARY_DIR /opt/local/lib)

find_package(Boost 1.76.0 REQUIRED COMPONENTS serialization)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

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
        utils/serverUtils.h
        utils/serverUtils.cc
        serialization/Message.h
        server/Server.h
        server/Server.cc
        server/ClientHandler.cc
        server/ClientHandler.h
        main.cc
)

if(Boost_FOUND)
    target_link_libraries(nagarroRemoteLearningServer ${Boost_LIBRARIES})
endif()