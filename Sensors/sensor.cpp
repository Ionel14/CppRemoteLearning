#include "sensor.h"

namespace smart_home
{

std::string& Sensor::GetName()
{
    return name_;
}

void Sensor::SetName(const std::string &name)
{
    name_ = name;
}

float Sensor::GetAFloatValue(tinyxml2::XMLElement *sensorElement, const char* name) {
    float value;

    if (sensorElement->QueryFloatAttribute(name, &value) == tinyxml2::XMLError::XML_NO_ATTRIBUTE)
    {
        return 0;
    }
    else
    {
        return value;
    }
}
    

Sensor::Sensor(const std::string &name): name_{name} {}

Sensor::Sensor(tinyxml2::XMLElement *sensorElement){

    if (const char* name = sensorElement->Attribute("name"))
    {
        name_ = name;
    }
    else
    {
        throw std::invalid_argument("Sensor name wasn't found!");
    }

} 

Sensor::Sensor(const Sensor &sensor): name_{sensor.name_} {}
Sensor &Sensor::operator=(const Sensor &sensor){
    if (this != &sensor)
    {
        name_ = sensor.name_;
    }
    
    return *this;
}

Sensor::Sensor(Sensor &&sensor): name_{std::move(sensor.name_)}{}

Sensor &Sensor::operator=(Sensor &&sensor){
    if (this != &sensor)
    {
        name_ = std::move(sensor.name_);
    }
    
    return *this;
};

} // namespace smart_home
