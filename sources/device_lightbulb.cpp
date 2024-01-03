#include "../headers/device_lightbulb.h"

namespace smarthome {
  
DeviceLightbulb::DeviceLightbulb(const std::string& name, bool state) : Device(name, state) {}

DeviceLightbulb::DeviceLightbulb(const std::string& name, bool state, const std::vector<Sensor>& sensors) : 
  Device(name, state, sensors) {}

std::string DeviceLightbulb::getType() {
  return type;
}

} // namespace smarthome