cmake_minimum_required(VERSION 3.10) 

project(homework) 

set(CMAKE_CXX_STANDARD 17)
add_executable(homework client-factory.cc client.cc test-client.cc)
target_include_directories(homework PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})