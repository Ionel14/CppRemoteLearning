#ifndef SMARTHOME_DEVICE_AC_UNIT_H_
#define SMARTHOME_DEVICE_AC_UNIT_H_

#include "device.h"

#include <iostream>
#include <vector>

namespace smarthome {

class DeviceAcUnit : public Device {
public:
  DeviceAcUnit(const std::string& name, bool state);
  DeviceAcUnit(const std::string& name, bool state, const std::vector<Sensor*>& sensors);

  void printPurpose() const;
};

} // namespace smarthome
#endif  // SMARTHOME_DEVICE_AC_UNIT_H_