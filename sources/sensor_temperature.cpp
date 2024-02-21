#include "../headers/sensor_temperature.h"

namespace smarthome {
  
SensorTemperature::SensorTemperature(const std::string& name, int value) : Sensor(name, value) {
  type = "Temperature";
  minValue = 0;
  maxValue = 50;

  if (value < minValue || value > maxValue) {
    throw std::invalid_argument("The " + name + " sensor value is not between " + std::to_string(minValue) + " and " + std::to_string(maxValue) + "\n");
  }
}

void SensorTemperature::printPurpose() const {
  std::cout << "This sensor measures the temperature in a room\n";
}

} // namespace smarthome