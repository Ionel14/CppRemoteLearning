#include "../headers/sensor_humidity.h"

namespace smarthome {
  
SensorHumidity::SensorHumidity(const std::string& name, int value) : Sensor(name, value) {}

std::string SensorHumidity::getType() {
  return type;
}


} // namespace smarthome