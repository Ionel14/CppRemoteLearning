#include "temperaturesensor.h"

namespace smart_home
{

TemperatureSensor::TemperatureSensor(const std::string &name, float temperature) : Sensor(name), temperature_{temperature} {};

float TemperatureSensor::GetTemperature()
{
    return temperature_;
}

void TemperatureSensor::SetTemperature(float temperature)
{
    temperature_ = temperature;
} 

Action TemperatureSensor::ActionNeeded() 
{
    if (temperature_ >= 28)
    {
        return Action::kLowerTheTemperature;
    }
    
    if (temperature_ <= 19)
    {
        return Action::kRaiseTheTemperature;
    }
    
    return Action::kNone;
}

const std::string TemperatureSensor::Status()
{
    return GetName() + ": Temperature is " + std::to_string(temperature_);
}

} // namespace smart_home
