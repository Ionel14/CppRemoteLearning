cmake_minimum_required(VERSION 3.10)

project(smart_home)

add_executable(smart_home src/main.cc src/services/temperature_service.cc src/devices/ac_unit.cc src/devices/device.cc src/tiny_xml/tinyxml2.cpp)

target_include_directories(smart_home PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include)