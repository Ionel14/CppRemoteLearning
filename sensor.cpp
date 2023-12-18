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

std::string& Sensor::GetType()
{
    return type_;
}

void Sensor::SetType(const std::string &type)
{
    type_ = type;
}

float Sensor::GetValue()
{
    return value_;
}

void Sensor::SetValue(float value)
{
    value_ = value;
}
    

Sensor::Sensor(const std::string &name, const std::string &type, float value): name_{name}, type_{type}, value_{value} {};

} // namespace smart_home
