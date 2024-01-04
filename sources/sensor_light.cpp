#include "../headers/sensor_light.h"

namespace smarthome {
  
SensorLight::SensorLight(const std::string& name, int value) : Sensor(name, value) {
  type = "Light";
}

void SensorLight::printPurpose() {
  std::cout << "This sensor checks whether a room is lit up\n";
}

} // namespace smarthome