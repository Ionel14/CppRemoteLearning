#include "lightbulb.h"

namespace smart_home
{

LightBulb::LightBulb(const std::string &name, DeviceStatus status, std::string color): Device(name, status), color_{color} {}

const std::string LightBulb::Status()
{
    return GetName() + ": " + DeviceStatusToString(GetStatus()) + "\nColor: " + color_;
}

} // namespace smart_home
