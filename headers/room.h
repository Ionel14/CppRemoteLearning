#ifndef SMARTHOME_ROOM_H_
#define SMARTHOME_ROOM_H_

#include "device.h"
#include "device_ac_unit.h"
#include "device_fan.h"
#include "device_lightbulb.h"

#include <iostream>
#include <vector>

namespace smarthome {

class Room {
public:
  Room(const std::string& name);
  Room(const std::string& name, std::vector<UniquePointer<Device>>& devices);

  std::string getName() const;
  std::vector<UniquePointer<Device>>& getDevices();

  void addDevice(UniquePointer<Device> device);

private:
  std::string name;
  std::vector<UniquePointer<Device>> devices;
};

} // namespace smarthome
#endif  // SMARTHOME_ROOM_H_