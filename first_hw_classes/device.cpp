#include "device.h"

namespace smart_home {

Device::Device(const std::string &name, const std::string &type, bool status): name_{name}, type_{type}, status_{status} {}

void Device::SetName(const std::string &name)
{
    name_ = name;
}

std::string& Device::GetName()
{
    return name_; 
}

void Device::SetType(const std::string &type)
{
    type_ = type;
}

std::string& Device::GetType()
{
    return type_;
}

void Device::SetStatus(bool status)
{
    status_ = status;
}

bool Device::GetStatus()
{
    return status_;
}
}