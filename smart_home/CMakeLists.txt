cmake_minimum_required(VERSION 3.10)

project(smart_home)

add_executable(smart_home src/main.cc src/rooms/room.cc src/services/temperature_service.cc src/services/presence_service.cc src/services/service.cc
src/services/light_service.cc src/services/status_service.cc src/devices/ac_unit.cc src/devices/device.cc src/devices/fan.cc
src/devices/light_bulb.cc src/sensors/sensor.cc)

set(THIRD_PARTY_DIR ${CMAKE_BINARY_DIR}/third_party)

include(FetchContent)

FetchContent_Declare(
    TinyXML2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG master
)

FetchContent_GetProperties(TinyXML2)

if(NOT TinyXML2_POPULATED)
    FetchContent_Populate(TinyXML2)

    add_library(tinyxml2 STATIC
        ${tinyxml2_SOURCE_DIR}/tinyxml2.cpp
        ${tinyxml2_SOURCE_DIR}/tinyxml2.h
    )

    target_include_directories(tinyxml2 PUBLIC ${tinyxml2_SOURCE_DIR})
endif()

target_link_libraries(smart_home PRIVATE tinyxml2)

target_include_directories(smart_home PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include)