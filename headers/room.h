#ifndef SMARTHOME_ROOM_H_
#define SMARTHOME_ROOM_H_

#include "device.h"

#include <iostream>
#include <vector>

namespace smarthome {

class Room {
  std::string name;
  std::vector<Device> devices;

public:
  Room(const std::string& name);
  Room(const std::string& name, const std::vector<Device>& devices);

  std::string getName();
  std::vector<Device> getDevices();

  void addDevice(const Device& device);
};

} // namespace smarthome
#endif  // SMARTHOME_ROOM_H_