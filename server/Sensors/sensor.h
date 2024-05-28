#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <stdexcept>

#include "action.h"
#include "../statusobject.h"
#include "../TinyXml/tinyxml2.h"
#include "../andreea_unique_ptr"

namespace smart_home
{

class Sensor : public StatusObject
{
public:
    Sensor(const std::string &name = "");
    Sensor(tinyxml2::XMLElement *sensorElement);

    Sensor(const Sensor &sensor);
    Sensor& operator = (const Sensor &sensor); 
    
    Sensor(Sensor &&sensor);
    Sensor& operator = (Sensor &&sensor); 

    std::string& GetName();
    void SetName(const std::string &name);

    virtual Action ActionNeeded() = 0;
    const std::string Status() = 0;
    
    virtual ~Sensor() = default;

protected:
    float GetAFloatValue(tinyxml2::XMLElement *sensorElement, const char* name);

private:
    std::string name_;
};

} // namespace smart_home

#endif