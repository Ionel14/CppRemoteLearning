#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

namespace smart_home
{

enum class DeviceStatus{
    kOff = 0,
    kOn,
    kOutOfOrder,
};

inline const char* DeviceStatusToString(DeviceStatus v)
{
    switch (v)
    {
        case (smart_home::DeviceStatus::kOff):   return "Off";
        case (smart_home::DeviceStatus::kOn):   return "On";
        case (smart_home::DeviceStatus::kOutOfOrder): return "OutOfOrder";
        default:    return "[Unknown type]";
    }
}

} // namespace smart_home

#endif