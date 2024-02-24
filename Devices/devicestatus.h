#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

namespace smart_home
{

enum class DeviceStatus{
    kOff = 0,
    kOn,
    kOutOfOrder,
    kUndefined,
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

inline DeviceStatus StringToDeviceStatus(const char* v)
{
    if (v == "Off")   return smart_home::DeviceStatus::kOff;
    if (v == "On")   return smart_home::DeviceStatus::kOn;
    if (v == "OutOfOrder") return smart_home::DeviceStatus::kOutOfOrder;
    return smart_home::DeviceStatus::kUndefined;
}

} // namespace smart_home

#endif