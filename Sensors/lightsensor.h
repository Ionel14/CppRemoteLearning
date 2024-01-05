#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "sensor.h"

namespace smart_home
{ 

class LightSensor : public Sensor
{
public:
    LightSensor(const std::string &name = "", float intensity = 0);
    float GetIntensity();
    void SetIntensity(float intensity);

    Action ActionNeeded() override;
    const std::string Status() override;

private:
    float intensity_;
};

} // namespace smart_home

#endif