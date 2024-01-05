#include "../headers/sensor_temperature.h"

namespace smarthome {
  
SensorTemperature::SensorTemperature(const std::string& name, int value) : Sensor(name, value) {
  type = "Temperature";
}

void SensorTemperature::printPurpose() {
  std::cout << "This sensor measures the temperature in a room\n";
}

} // namespace smarthome