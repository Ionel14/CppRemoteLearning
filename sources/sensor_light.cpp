#include "../headers/sensor_light.h"

namespace smarthome {
  
SensorLight::SensorLight(const std::string& name, int value) : Sensor(name, value) {}

std::string SensorLight::getType() {
  return type;
}


} // namespace smarthome