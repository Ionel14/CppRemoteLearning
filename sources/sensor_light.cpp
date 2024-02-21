#include "../headers/sensor_light.h"

namespace smarthome {
  
SensorLight::SensorLight(const std::string& name, int value) : Sensor(name, value) {
  type = "Light";
  minValue = 0;
  maxValue = 100;

  if (value < minValue || value > maxValue) {
    throw std::invalid_argument("The " + name + " sensor value is not between " + std::to_string(minValue) + " and " + std::to_string(maxValue) + "\n");
  }
}

void SensorLight::printPurpose() const {
  std::cout << "This sensor checks whether a room is lit up\n";
}

} // namespace smarthome