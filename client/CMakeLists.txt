cmake_minimum_required(VERSION 3.10)
project(nagarroRemoteLearningClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        nagarroRemoteLearningClient
        client.cc
        utils/clientUtils.h
)
