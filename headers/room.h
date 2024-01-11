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
  Room(const std::string& name, const std::vector<Device*>& devices);

  std::string getName() const;
  std::vector<Device*> getDevices() const;

  void addDevice(Device* device);

private:
  std::string name;
  std::vector<Device*> devices;
};

} // namespace smarthome
#endif  // SMARTHOME_ROOM_H_