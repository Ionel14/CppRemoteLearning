#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>

#include "Sensors/sensor.h"
#include "Devices/device.h"
#include "andreea_unique_ptr"

namespace smart_home {

class Room
{
public:
    Room(const std::string &name = "");

    void AddSensor(MyUniquePtr<Sensor> &&sensor);
    void DeleteSensor(const std::string &name);

    void AddDevice(MyUniquePtr<Device> &&device);
    void DeleteDevice(const std::string &name);

    std::string& GetName();
    void SetName(const std::string &name);

    const std::vector<StatusObject*> GetSensors();
    const std::vector<StatusObject*> GetDevices();

private:
    std::string name_;
    std::vector<MyUniquePtr<Sensor>> sensors_;
    std::vector<MyUniquePtr<Device>> devices_;

    // I choosed vector because it's enough for what I need
    // List could be a good option too  
};
}
#endif