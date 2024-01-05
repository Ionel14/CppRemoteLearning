#include "room.h"

namespace smart_home
{

Room::Room(const std::string &name): name_{name} {}

void Room::AddSensor(std::unique_ptr<Sensor> &sensor)
{
    sensors_.emplace_back(std::move(sensor));

}

void Room::DeleteSensor(const std::string &name)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensors_[i]->GetName() == name)
        {
            sensors_.erase(sensors_.begin() + i);
            return;
        }
        
    }
}

void Room::AddDevice(std::unique_ptr<Device> &device)
{
    devices_.emplace_back(std::move(device));
}

void Room::DeleteDevice(const std::string &name)
{
    for (int i = 0; i < devices_.size(); i++)
    {
        if (devices_[i]->GetName() == name)
        {
            devices_.erase(devices_.begin() + i);
            return;
        }
    }
}


std::string& Room::GetName()
{
    return name_;
}

void Room::SetName(const std::string &name)
{
    name_ = name;
}

std::vector<std::unique_ptr<Sensor>>& Room::GetSensors()
{
    return sensors_;
}

std::vector<std::unique_ptr<Device>>& Room::GetDevices()
{
    return devices_;
}
} // namespace smart_home