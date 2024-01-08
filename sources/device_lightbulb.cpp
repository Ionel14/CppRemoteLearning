#include "../headers/device_lightbulb.h"

namespace smarthome {
  
DeviceLightbulb::DeviceLightbulb(const std::string& name, bool state) : Device(name, state) {
  type = "Lightbulb";
}

DeviceLightbulb::DeviceLightbulb(const std::string& name, bool state, const std::vector<Sensor*>& sensors) : 
  Device(name, state, sensors) {
  type = "Lightbulb";
}

void DeviceLightbulb::printPurpose() const {
  std::cout << "This device lights up a room\n";
}

} // namespace smarthome