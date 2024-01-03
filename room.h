#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "devices/device.h"
#include "devices/securitydevice.h"
#include "devices/thermostatdevice.h"
#include "devices/voicecontroldevice.h"

namespace smartHome{
class Room {
public:
    Room(const std::string& name, const std::string& roomId, const std::vector<Device>& devices);

    const std::string& getName() const;
    const std::string& getId() const;
    const std::vector<Device>& getDevices() const;

    void setName(const std::string& newName);
    void setDevices(const std::vector<Device>& newDevices);

private:
    std::string name;
    const std::string roomId;
    std::vector<Device> devices;
};
}
#endif // ROOM_H