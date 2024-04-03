cmake_minimum_required(VERSION 3.10) 
project(SmartHome) 

add_executable(smart_home 
main.cpp 
Sensors/sensor.cpp Sensors/humiditysensor.cpp Sensors/lightsensor.cpp Sensors/presencesensor.cpp Sensors/temperaturesensor.cpp 
Devices/device.cpp Devices/acunit.cpp Devices/door.cpp Devices/lightbulb.cpp
room.cpp 
smart_home.cpp 
smarthomestatus.cpp
smarthomemanager.cpp 
uniqueptr.h
thread_pool.cpp
TinyXml/tinyxml2.cpp
message.cpp
)

target_include_directories(smart_home PRIVATE TinyXml)
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(smart_home Boost::serialization)
