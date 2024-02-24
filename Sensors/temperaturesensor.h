#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H
#include "sensor.h"

namespace smart_home
{

class TemperatureSensor : public Sensor
{
public:
    TemperatureSensor(const std::string &name = "", float temperature = 0);
    TemperatureSensor(tinyxml2::XMLElement *sensorElement);
    float GetTemperature();
    void SetTemperature(float temperature);

    Action ActionNeeded() override;
    const std::string Status() override;

private:
    float temperature_;
};
    
} // namespace smart_home

#endif