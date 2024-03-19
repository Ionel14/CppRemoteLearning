#include "device.h"

namespace smart_home {

Device::Device(const std::string &name, DeviceStatus status): name_{name}, status_{status} {}

Device::Device(tinyxml2::XMLElement *deviceElement)
{
    if (const char* name = deviceElement->Attribute("name"))
    {
        name_ = name;
    }
    else
    {
        throw std::invalid_argument("Device name wasn't found!");
    }

    status_ = DeviceStatus::kOff;
    if (const char* statusStr = deviceElement->Attribute("status"))
    {
        DeviceStatus status_ = StringToDeviceStatus(statusStr);  
    }

}

void Device::SetName(const std::string &name)
{
    name_ = name;
}

std::string& Device::GetName()
{
    return name_; 
}

void Device::SetStatus(DeviceStatus status)
{
    status_ = status;
}

DeviceStatus Device::GetStatus()
{
    return status_;
}
}