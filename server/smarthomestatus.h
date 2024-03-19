#ifndef SMARTHOMESTATUS_H
#define SMARTHOMESTATUS_H

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

#include "smart_home.h"
#include "andreea_unique_ptr"

namespace smart_home
{


class SmartHomeStatus
{
public:
    SmartHomeStatus(std::shared_ptr<std::mutex> mutex);
    void PrintStatus(const std::vector<StatusObject*> &objects, std::string title);
    void PrintSmartHomeStatus(SmartHome &smartHome);

private:
    std::shared_ptr<std::mutex> mutex_;
};
    
} // namespace smart_home

#endif