#include "lightbulb.h"

namespace smart_home
{

LightBulb::LightBulb(const std::string &name, DeviceStatus status, std::string color): Device(name, status), color_{color} {}

LightBulb::LightBulb(tinyxml2::XMLElement *deviceElement): Device(deviceElement)
{
    if (const char* color = deviceElement->Attribute("color"))
    {
        color_ = color;
    }
    else
    {
        color_ = "white";
    }

}

const std::string LightBulb::Status()
{
    return GetName() + ": " + DeviceStatusToString(GetStatus()) + "\nColor: " + color_;
}

} // namespace smart_home
