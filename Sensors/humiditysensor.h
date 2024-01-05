#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "sensor.h"

namespace smart_home
{

class HumiditySensor: public Sensor
{
public:
    HumiditySensor(const std::string &name = "", float humidity = 0);
    float GetHumidity();
    void SetHumidity(float humidity);

    Action ActionNeeded() override;
    const std::string Status() override;

private:
    float humidity_;

};
    
} // namespace smart_home

#endif