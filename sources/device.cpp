#include "../headers/device.h"

namespace smarthome {
  
Device::Device(const std::string& name, bool state) : name(name), state(state) {}

Device::Device(const std::string& name, bool state, const std::vector<Sensor*>& sensors) : 
  name(name), state(state), sensors(sensors) {}

std::string Device::getName() {
  return name;
}

bool Device::getState() {
 return state;
}

std::vector<Sensor*> Device::getSensors() {
  return sensors;
}

std::string Device::getType() {
  return type;
}

void Device::setState(bool state) {
  this->state = state;
}

void Device::addSensor(Sensor* sensor){
  sensors.push_back(sensor);
}

} // namespace smarthome