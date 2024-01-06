#include "TemperatureSensor.h"
#include <cstdlib>

namespace smart_home {
    TemperatureSensor::TemperatureSensor(const std::string &name)
            : Sensor(name, MeasureUnit::CELSIUS) {}

    void TemperatureSensor::generateRandomValue() {
        *value = std::rand() % 30 + 10;
    }

    double TemperatureSensor::readTemperature() const {
        return static_cast<double>(*value);
    }

    double TemperatureSensor::convertToFahrenheit() const {
        return (readTemperature() * 9.0 / 5.0) + 32.0;
    }
}
