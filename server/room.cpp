#include "room.h"

namespace smart_home
{

Room::Room(const std::string &name): name_{name} {}

void Room::AddSensor(MyUniquePtr<Sensor> &&sensor)
{
    sensors_.emplace_back(std::move(sensor));

}

bool Room::DeleteSensor(const std::string &name)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensors_[i]->GetName() == name)
        {
            sensors_.erase(sensors_.begin() + i);
            return true;
        }
        
    }
    
    return false;
}

void Room::AddDevice(MyUniquePtr<Device> &&device)
{
    devices_.emplace_back(std::move(device));
}

bool Room::DeleteDevice(const std::string &name)
{
    for (int i = 0; i < devices_.size(); i++)
    {
        if (devices_[i]->GetName() == name)
        {
            devices_.erase(devices_.begin() + i);
            return true;
        }
    }

    return false;
}


std::string& Room::GetName()
{
    return name_;
}

void Room::SetName(const std::string &name)
{
    name_ = name;
}

const std::vector<StatusObject*> Room::GetSensors()
{
    std::vector<StatusObject*> rawPtrs;
    for (MyUniquePtr<Sensor>& ptr : sensors_) {
        rawPtrs.push_back(ptr.get());
    }

    return rawPtrs;
}

const std::vector<StatusObject*> Room::GetDevices()
{
    std::vector<StatusObject*> rawPtrs;
    for (MyUniquePtr<Device>& ptr : devices_) {
        rawPtrs.push_back(ptr.get());
    }

    return rawPtrs;
}

const std::optional<Sensor*> Room::GetSensor(const std::string &name)
{
    for (int i = 0; i < sensors_.size(); i++)
    {
        if (sensors_[i]->GetName() == name)
        {
            return sensors_[i].get();
        }
    }

    return std::nullopt;
}

const std::optional<Device*> Room::GetDevice(const std::string &name)
{
    for (int i = 0; i < devices_.size(); i++)
    {
        if (devices_[i]->GetName() == name)
        {
            return devices_[i].get();
        }
    }

    return std::nullopt;
}

const std::string Room::Status()
{
    std::string status = "Room " + name_ + "\n\n" + "Sensors:\n\n";
    for(MyUniquePtr<Sensor>& sensor : sensors_)
    {
        status += sensor->Status() + '\n';
    }

    status+= "\nDevices:\n\n";

    for(MyUniquePtr<Device>& device : devices_)
    {
        status += device->Status() + '\n';
    }

    return status;
}

} // namespace smart_home