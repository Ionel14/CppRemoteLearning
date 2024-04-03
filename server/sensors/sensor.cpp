#include "sensor.h"
#include <iostream>

namespace smartHome{
    // Constructor
    Sensor::Sensor(const std::string& type, const std::string& sensorId, double value, bool isFunctional)
        : type(type), sensorId(sensorId), value(value), isFunctional(isFunctional) {}

    // Copy constructor
    Sensor::Sensor(const Sensor& other)
        : type(other.type), sensorId(other.sensorId), value(other.value), isFunctional(other.isFunctional) {
        std::cout << "Sensor Copy Constructor" << std::endl;
    }

    // Copy assignment operator
    Sensor& Sensor::operator=(const Sensor& other) {
        if (this != &other) {
            type = other.type;
            value = other.value;
            isFunctional = other.isFunctional;
        }
        std::cout << "Sensor Copy Assignment Operator" << std::endl;
        return *this;
    }

    // Move constructor
    Sensor::Sensor(Sensor&& other) noexcept
        : type(std::move(other.type)), sensorId(std::move(other.sensorId)),
          value(std::move(other.value)), isFunctional(std::move(other.isFunctional)) {
        std::cout << "Sensor Move Constructor" << std::endl;
    }

    // Move assignment operator
    Sensor& Sensor::operator=(Sensor&& other) noexcept {
        if (this != &other) {
            type = std::move(other.type);
            value = std::move(other.value);
            isFunctional = std::move(other.isFunctional);
        }
        std::cout << "Sensor Move Assignment Operator" << std::endl;
        return *this;
    }

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
