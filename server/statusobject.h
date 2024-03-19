#ifndef STATUSOBJECT_H
#define STATUSOBJECT_H

#include <string>

namespace smart_home
{

class StatusObject
{
public:
    virtual const std::string Status() = 0;
};
    
} // namespace smart_home

#endif