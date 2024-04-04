cmake_minimum_required(VERSION 3.0.0)
project(smart_home)

set(CMAKE_CXX_FLAGS "-lboost_serialization")
set(Boost_INCLUDE_DIR /home/lowlimb/Downloads/boost_1_70_0)
set(Boost_LIBRARY_DIR /home/lowlimb/Downloads/boost_1_70_0/stage/lib)
find_package(Boost 1.74.0 COMPONENTS system filesystem serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# add_executable(smart_home
#   main.cpp
#   sources/smart_home.cpp
#   sources/room.cpp
#   sources/device.cpp
#   sources/sensor.cpp
#   sources/device_ac_unit.cpp
#   sources/device_fan.cpp
#   sources/device_lightbulb.cpp
#   sources/sensor_humidity.cpp
#   sources/sensor_light.cpp
#   sources/sensor_temperature.cpp
#   sources/smart_home_manager.cpp
#   headers/smart_home.h
#   headers/room.h
#   headers/device.h
#   headers/sensor.h
#   headers/device_ac_unit.h
#   headers/device_fan.h
#   headers/device_lightbulb.h
#   headers/sensor_humidity.h
#   headers/sensor_light.h
#   headers/sensor_temperature.h
#   headers/smart_home_manager.h
#   headers/unique_ptr.h
#   headers/unique_ptr_colleague.h
#   headers/deleter.h
# )

add_executable(server 
  server.cpp 
  sources/smart_home.cpp
  sources/room.cpp
  sources/device.cpp
  sources/sensor.cpp
  sources/device_ac_unit.cpp
  sources/device_fan.cpp
  sources/device_lightbulb.cpp
  sources/sensor_humidity.cpp
  sources/sensor_light.cpp
  sources/sensor_temperature.cpp
  sources/smart_home_manager.cpp
  sources/thread_pool.cpp
  sources/message_manager.cpp
  headers/smart_home.h
  headers/room.h
  headers/device.h
  headers/sensor.h
  headers/device_ac_unit.h
  headers/device_fan.h
  headers/device_lightbulb.h
  headers/sensor_humidity.h
  headers/sensor_light.h
  headers/sensor_temperature.h
  headers/smart_home_manager.h
  headers/unique_ptr.h
  headers/unique_ptr_colleague.h
  headers/deleter.h
  headers/thread_pool.h
  headers/message.h
  headers/message_manager.h
  nrOfRequestsToday.sh
)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES})

add_executable(client client.cpp headers/message.h)
target_link_libraries(client PRIVATE ${Boost_LIBRARIES})
