#include "../headers/device_fan.h"

namespace smarthome {
  
DeviceFan::DeviceFan(const std::string& name, bool state) : Device(name, state) {
  type = "Fan";
}

DeviceFan::DeviceFan(const std::string& name, bool state, std::vector<UniquePointer<Sensor>>& sensors) : 
  Device(name, state, sensors) {
  type = "Fan";
}

void DeviceFan::printPurpose() const {
  std::cout << "This device controls the air circulation in a room\n";
}

} // namespace smarthome