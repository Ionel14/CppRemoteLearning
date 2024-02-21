#include "../headers/sensor_humidity.h"

namespace smarthome {
  
SensorHumidity::SensorHumidity(const std::string& name, int value) : Sensor(name, value) {
  type = "Humidity";
  minValue = 0;
  maxValue = 100;

  if (value < minValue || value > maxValue) {
    throw std::invalid_argument("The " + name + " sensor value is not between " + std::to_string(minValue) + " and " + std::to_string(maxValue) + "\n");
  }
}

void SensorHumidity::printPurpose() const {
  std::cout << "This sensor measures the humidity level in a room\n";
}

} // namespace smarthome