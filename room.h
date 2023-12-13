#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "device.h"

namespace smartHome{
class Room {
public:
    Room(const std::string& name, const std::string& roomId, const std::vector<Device> devices);

    const std::string getName() const;
    const std::string getId() const;
    const std::vector<Device> getDevices() const;

private:
    std::string name;
    std::string roomId;
    std::vector<Device> devices;
};
}
#endif // ROOM_H