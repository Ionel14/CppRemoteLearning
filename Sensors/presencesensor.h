#ifndef PRESENCESENSOR_H
#define PRESENCESENSOR_H

#include "sensor.h"

namespace smart_home
{

class PresenceSensor : public Sensor
{
public:
    PresenceSensor(const std::string &name = "", bool is_presence = "");
    PresenceSensor(tinyxml2::XMLElement *sensorElement);
    bool GetIsPresence(); 
    void SetIsPresence(bool is_presence);

    Action ActionNeeded() override;
    const std::string Status() override;
private:
    bool is_presence_;
    
};
    
} // namespace smart_home

#endif