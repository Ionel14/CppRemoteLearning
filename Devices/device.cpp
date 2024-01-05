#include "device.h"

namespace smart_home {

Device::Device(const std::string &name, DeviceStatus status): name_{name}, status_{status} {}

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