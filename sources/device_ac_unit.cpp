#include "../headers/device_ac_unit.h"

namespace smarthome {
  
DeviceAcUnit::DeviceAcUnit(const std::string& name, bool state) : Device(name, state) {
  type = "AC";
}

DeviceAcUnit::DeviceAcUnit(const std::string& name, bool state, const std::vector<Sensor*>& sensors) : 
  Device(name, state, sensors) {
  type = "AC";
}

void DeviceAcUnit::printPurpose() {
  std::cout << "This device cools down a room\n";
}

} // namespace smarthome