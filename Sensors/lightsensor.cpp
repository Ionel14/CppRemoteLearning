#include "lightsensor.h"

namespace smart_home
{

LightSensor::LightSensor(const std::string &name, float intensity): Sensor(name), intensity_{intensity} {}

float LightSensor::GetIntensity()
{
    return intensity_;
}

void LightSensor::SetIntensity(float intensity)
{
    intensity_ = intensity;
}

Action LightSensor::ActionNeeded()
{
    if (intensity_ <= 200)
    {
        return Action::kNeedMoreLight;
    }
    return Action::kNone;
}

const std::string LightSensor::Status()
{
    return GetName() + ": The intensity of light is " + std::to_string(intensity_);
}

} // namespace smart_home