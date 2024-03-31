cmake_minimum_required(VERSION 3.10)
project(nagarroRemoteLearningClient)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR /opt/local/include)
set(Boost_LIBRARY_DIR /opt/local/lib)

find_package(Boost 1.76.0 REQUIRED COMPONENTS serialization)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_executable(
        nagarroRemoteLearningClient
        client.cc
        utils/clientUtils.h
        serialization/Message.h
        serialization/Message.h
)

if(Boost_FOUND)
    target_link_libraries(nagarroRemoteLearningClient ${Boost_LIBRARIES})
endif()