#include "../headers/sensor.h"

namespace smarthome {
  
Sensor::Sensor(const std::string& name, int value) : name(name), value(value) {}
Sensor::Sensor(const Sensor& other) : type(other.type), name(other.name), value(other.value), 
  minValue(other.minValue), maxValue(other.maxValue) {}
Sensor::Sensor(const Sensor&& other) : type(other.type), name(other.name), value(other.value), 
  minValue(other.minValue), maxValue(other.maxValue) {}

Sensor& Sensor::operator=(const Sensor& other) {
  if (this != &other) {
    type = other.type;
    name = other.name;
    value = other.value;
  }
  return *this;
}

Sensor& Sensor::operator=(const Sensor&& other) {
  if (this != &other) {
    type = other.type;
    name = other.name;
    value = other.value;
  }
  return *this;
}

Sensor::~Sensor() {};

std::string Sensor::getName() const {
  return name;
}

int Sensor::getValue() const {
  return value;
}

std::string Sensor::getType() const {
  return type;
}

int Sensor::getMinValue() const {
  return minValue;
}

int Sensor::getMaxValue() const {
  return maxValue;
}

void Sensor::setValue(int value) {
  this->value = value;
}

} // namespace smarthome