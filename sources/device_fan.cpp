#include "../headers/device_fan.h"

namespace smarthome {
  
DeviceFan::DeviceFan(const std::string& name, bool state) : Device(name, state) {}

DeviceFan::DeviceFan(const std::string& name, bool state, const std::vector<Sensor>& sensors) : 
  Device(name, state, sensors) {}

std::string DeviceFan::getType() {
  return type;
}

} // namespace smarthome