#ifndef DOOR_H
#define DOOR_H

#include "device.h"

namespace smart_home
{
    
class Door : public Device
{
public:
    Door(const std::string &name = "", DeviceStatus status = DeviceStatus::kOff);
    Door(tinyxml2::XMLElement *deviceElement);
    const std::string Status() override;
private:

};

} // namespace smart_home

#endif