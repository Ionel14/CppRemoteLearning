#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <memory>
#include <optional>
#include "Sensors/sensor.h"
#include "Devices/device.h"
#include "andreea_unique_ptr"

namespace smart_home {

class Room : public StatusObject
{
public:
    Room(const std::string &name = "");

    void AddSensor(MyUniquePtr<Sensor> &&sensor);
    bool DeleteSensor(const std::string &name);

    void AddDevice(MyUniquePtr<Device> &&device);
    bool DeleteDevice(const std::string &name);

    std::string& GetName();
    void SetName(const std::string &name);

    const std::vector<StatusObject*> GetSensors();
    const std::vector<StatusObject*> GetDevices();

    const std::optional<Sensor*> GetSensor(const std::string& name);
    const std::optional<Device*> GetDevice(const std::string& name);

    const std::string Status() override;

private:
    std::string name_;
    std::vector<MyUniquePtr<Sensor>> sensors_;
    std::vector<MyUniquePtr<Device>> devices_;

    // I choosed vector because it's enough for what I need
    // List could be a good option too  
};
}
#endif