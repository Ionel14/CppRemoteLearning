cmake_minimum_required(VERSION 3.10) 
project(SmartHomeClient) 

add_executable(smart_home 
main.cpp 
smarthomeconnect.cpp
message.cpp
)

find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(smart_home Boost::serialization)
