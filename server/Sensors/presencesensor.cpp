#include "presencesensor.h"

namespace smart_home
{

PresenceSensor::PresenceSensor(const std::string &name, bool is_presence) : Sensor(name), is_presence_{is_presence} {}

PresenceSensor::PresenceSensor(tinyxml2::XMLElement *sensorElement): Sensor(sensorElement) {
    bool is_presence;

    if (sensorElement->QueryBoolAttribute("is_presence", &is_presence) == tinyxml2::XMLError::XML_NO_ATTRIBUTE)
    {
        is_presence_ = false;
    }
    else
    {
        is_presence_ = is_presence;
    }
}

bool PresenceSensor::GetIsPresence()
{
    return is_presence_;
}

void PresenceSensor::SetIsPresence(bool is_presence)
{
    is_presence_ = is_presence;
}

Action PresenceSensor::ActionNeeded()
{
    if (is_presence_)
    {
        return Action::kIsAPresence;
    }
    return Action::kNone;
}

const std::string PresenceSensor::Status()
{
    std::string status = GetName() + ": ";
    if (is_presence_)
    {
        status+= "Person Detected";
    }
    else
    {
        status+= "Nothing detected";
    }

    return status;
}

} // namespace smart_home