#include "door.h"

namespace smart_home
{
 
Door::Door(const std::string &name, DeviceStatus status): Device(name, status){}

Door::Door(tinyxml2::XMLElement *deviceElement): Device(deviceElement){}

const std::string Door::Status()
{
    return GetName() + ": " + DeviceStatusToString(GetStatus());
}

} // namespace smart_home
