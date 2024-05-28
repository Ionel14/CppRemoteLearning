#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "device.h"

namespace smart_home
{

class LightBulb : public Device
{
public:
    LightBulb(const std::string &name = "", DeviceStatus status = DeviceStatus::kOff, std::string Color = "white");
    LightBulb(tinyxml2::XMLElement *deviceElement);
    const std::string Status() override;
private:
    std::string color_;
};

} // namespace smart_home

#endif