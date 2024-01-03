#include "../headers/device_ac_unit.h"

namespace smarthome {
  
DeviceAcUnit::DeviceAcUnit(const std::string& name, bool state) : Device(name, state) {}

DeviceAcUnit::DeviceAcUnit(const std::string& name, bool state, const std::vector<Sensor>& sensors) : 
  Device(name, state, sensors) {}

std::string DeviceAcUnit::getType() {
  return type;
}

} // namespace smarthome