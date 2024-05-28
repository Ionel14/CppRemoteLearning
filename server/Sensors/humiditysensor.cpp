#include "humiditysensor.h"

namespace smart_home
{
    
HumiditySensor::HumiditySensor(const std::string &name, float humidity) : Sensor(name), humidity_{humidity} {}

HumiditySensor::HumiditySensor(tinyxml2::XMLElement *sensorElement): Sensor(sensorElement)
{
    humidity_ = GetAFloatValue(sensorElement, "humidity");
}

float HumiditySensor::GetHumidity()
{
    return humidity_;
}

void HumiditySensor::SetHumidity(float humidity)
{
    humidity_ = humidity;
}

Action HumiditySensor::ActionNeeded()
{
    if (humidity_ >= 600)
    {
        return Action::kTooMuchHumidity;
    }
    
    return Action::kNone;
}

const std::string HumiditySensor::Status()
{
    return GetName() + ": Humidity is " + std::to_string(humidity_);
}

} // namespace smart_home
