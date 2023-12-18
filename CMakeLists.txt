cmake_minimum_required(VERSION 3.10) 
project(SmartHome) 

add_executable(smart_home main.cpp sensor.cpp device.cpp room.cpp smart_home.cpp TinyXml/tinyxml2.cpp)

target_include_directories(smart_home PRIVATE TinyXml)
