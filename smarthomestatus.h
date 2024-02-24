#ifndef SMARTHOMESTATUS_H
#define SMARTHOMESTATUS_H

#include <iostream>

#include "smart_home.h"
#include "andreea_unique_ptr"

namespace smart_home
{


class SmartHomeStatus
{
public:
    static void PrintStatus(const std::vector<StatusObject*> &objects);

};
    
} // namespace smart_home

#endif