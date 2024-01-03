#include "../headers/sensor_temperature.h"

namespace smarthome {
  
SensorTemperature::SensorTemperature(const std::string& name, int value) : Sensor(name, value) {}

std::string SensorTemperature::getType() {
  return type;
}

} // namespace smarthome