#include "room.h"

namespace smart_home
{

Room::Room(const std::string &name): name_{name} {}

void Room::AddSensor(Sensor &sensor)
{
    sensors_.push_back(sensor);
}

void Room::DeleteSensor(const std::string &name)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensors_[i].GetName() == name)
        {
            sensors_.erase(sensors_.begin() + i);
            return;
        }
        
    }
}

Sensor* Room::GetSensor(const std::string &name)
{
    for (auto &sensor : sensors_)
    {
        if (sensor.GetName() == name)
        {
            return &sensor;
        }
    }

    return nullptr;
}

void Room::AddDevice(Device &device)
{
    devices_.push_back(device);
}

void Room::DeleteDevice(const std::string &name)
{
    for (int i = 0; i < devices_.size(); i++)
    {
        if (devices_[i].GetName() == name)
        {
            devices_.erase(devices_.begin() + i);
            return;
        }
    }
}

Device* Room::GetDevice(const std::string &name)
{
    for (auto &device : devices_)
    {
        if (device.GetName() == name)
        {
            return &device;
        }
    }
    return nullptr;
}

std::string& Room::GetName()
{
    return name_;
}

void Room::SetName(const std::string &name)
{
    name_ = name;
}

std::vector<Sensor>& Room::GetSensors()
{
    return sensors_;
}

std::vector<Device>& Room::GetDevices()
{
    return devices_;
}
} // namespace smart_home