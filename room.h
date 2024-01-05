#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>

#include "Sensors/sensor.h"
#include "Devices/device.h"

namespace smart_home {

class Room
{
public:
    Room(const std::string &name = "");

    void AddSensor(std::unique_ptr<Sensor> &sensor);
    void DeleteSensor(const std::string &name);

    void AddDevice(std::unique_ptr<Device> &device);
    void DeleteDevice(const std::string &name);

    std::string& GetName();
    void SetName(const std::string &name);

    std::vector<std::unique_ptr<Sensor>>& GetSensors();
    std::vector<std::unique_ptr<Device>>& GetDevices();

private:
    std::string name_;
    std::vector<std::unique_ptr<Sensor>> sensors_;
    std::vector<std::unique_ptr<Device>> devices_;

    // I choosed vector because it's enough for what I need
    // List could be a good option too  
};
}
#endif