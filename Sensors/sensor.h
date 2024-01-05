#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "action.h"
#include "../statusobject.h"

namespace smart_home
{

class Sensor : public StatusObject
{
public:
    Sensor(const std::string &name = "");

    Sensor(const Sensor &sensor);
    Sensor& operator = (const Sensor &sensor); 
    
    Sensor(Sensor &&sensor);
    Sensor& operator = (Sensor &&sensor); 

    std::string& GetName();
    void SetName(const std::string &name);

    virtual Action ActionNeeded() = 0;
    const std::string Status() = 0;
    
    virtual ~Sensor() = default;

private:
    std::string name_;
};

} // namespace smart_home

#endif