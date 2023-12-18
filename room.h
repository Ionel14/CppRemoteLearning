#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "sensor.h"
#include "device.h"

namespace smart_home {

class Room
{
public:
    Room(const std::string &name = "");

    void AddSensor(Sensor &sensor);
    void DeleteSensor(const std::string &name);
    Sensor* GetSensor(const std::string &name);

    void AddDevice(Device &device);
    void DeleteDevice(const std::string &name);
    Device* GetDevice(const std::string &name);

    std::string& GetName();
    void SetName(const std::string &name);

    std::vector<Sensor>& GetSensors();
    std::vector<Device>& GetDevices();


private:
    std::string name_;
    std::vector<Sensor> sensors_;
    std::vector<Device> devices_;
    // I choosed vector because it's enough for what I need
    // List could be a good option too  
};
}
#endif