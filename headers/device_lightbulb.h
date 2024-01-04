#ifndef SMARTHOME_DEVICE_LIGHTBULB_H_
#define SMARTHOME_DEVICE_LIGHTBULB_H_

#include "device.h"

#include <iostream>
#include <vector>

namespace smarthome {

class DeviceLightbulb : public Device {
public:
  DeviceLightbulb(const std::string& name, bool state);
  DeviceLightbulb(const std::string& name, bool state, const std::vector<Sensor*>& sensors);

  void printPurpose();
};

} // namespace smarthome
#endif  // SMARTHOME_DEVICE_LIGHTBULB_H_