#include "../headers/sensor_humidity.h"

namespace smarthome {
  
SensorHumidity::SensorHumidity(const std::string& name, int value) : Sensor(name, value) {
  type = "Humidity";
}

void SensorHumidity::printPurpose() const {
  std::cout << "This sensor measures the humidity level in a room\n";
}

} // namespace smarthome