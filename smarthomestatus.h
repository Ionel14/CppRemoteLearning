#ifndef SMARTHOMESTATUS_H
#define SMARTHOMESTATUS_H

#include <iostream>

#include "smart_home.h"
namespace smart_home
{


class SmartHomeStatus
{
public:
    static void PrintSensorsStatus(std::vector<StatusObject*> &objects);

};
    
} // namespace smart_home

#endif