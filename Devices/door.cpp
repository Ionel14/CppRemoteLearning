#include "door.h"

namespace smart_home
{
 
Door::Door(const std::string &name, DeviceStatus status): Device(name, status){}

const std::string Door::Status()
{
    return GetName() + ": " + DeviceStatusToString(GetStatus());
}

} // namespace smart_home
