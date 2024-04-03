cmake_minimum_required(VERSION 3.10)

project(SmartHomeClient)

add_executable(
    SmartHomeClient
    client.cpp
    message.cpp)

find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(SmartHomeClient Boost::serialization)