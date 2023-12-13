#include "sensor.h"

namespace smartHome{
// Constructor
Sensor::Sensor(const std::string& type, const std::string& sensorId, double value, bool isFunctional)
    : type(type), sensorId(sensorId), value(value), isFunctional(isFunctional) {}

// Getter for sensor's type
const std::string& Sensor::getType() const {
    return type;
}

// Getter for sensor's id
const std::string& Sensor::getID() const {
    return sensorId;
}

// Getter for sensor's value
double Sensor::getValue() const {
    return value;
}

// Getter for sensor's state of functionality
bool Sensor::getIsFunctional() const {
    return isFunctional;
}

void Sensor::setType(const std::string& newType){
    type = newType;
}

void Sensor::setValue(double newValue){
    value = newValue;
}

void Sensor::setIsFunctional(bool newValue){
    isFunctional = newValue;
}
}
