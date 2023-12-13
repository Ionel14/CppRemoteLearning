#include "../headers/device.h"

namespace smarthome {
  
Device::Device(const std::string& name, bool state) {
  this->name = name;  
  this->state = state;
}

Device::Device(const std::string& name, bool state, const std::vector<Sensor>& sensors) {
  this->name = name;
  this->state = state;
  this->sensors = sensors;
}

std::string Device::getName() {
  return name;
}

bool Device::getState() {
 return state;
}

std::vector<Sensor> Device::getSensors() {
  return sensors;
}

void Device::setState(bool state) {
  this->state = state;
}

void Device::addSensor(const Sensor& sensor){
  sensors.push_back(sensor);
}

} // namespace smarthome