#ifndef SMARTHOME_DEVICE_FAN_H_
#define SMARTHOME_DEVICE_FAN_H_

#include "device.h"

#include <iostream>
#include <vector>

namespace smarthome {

class DeviceFan : public Device {
public:
  DeviceFan(const std::string& name, bool state);
  DeviceFan(const std::string& name, bool state, const std::vector<Sensor*>& sensors);

  void printPurpose();
};

} // namespace smarthome
#endif  // SMARTHOME_DEVICE_FAN_H_