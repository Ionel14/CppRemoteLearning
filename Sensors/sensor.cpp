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
    

Sensor::Sensor(const std::string &name): name_{name} {}

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
