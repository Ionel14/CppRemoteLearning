#include "Sensor.h"
#include <cstdlib>

namespace smart_home {
    Sensor::Sensor(const std::string &sensorName, MeasureUnit sensorUnit)
            : name(sensorName), value(new double(0)), unit(sensorUnit) {}

    Sensor::Sensor(const Sensor &other)
            : name(other.name), value(new double (*(other.value))), unit(other.unit) {}

    Sensor::Sensor(Sensor &&other)
            : name(std::move(other.name)), value(other.value), unit(other.unit) {
        other.value = nullptr;
    }

    Sensor &Sensor::operator=(const Sensor &other) {
        if (this != &other) {
            delete value;
            name = other.name;
            value = new double (*(other.value));
            unit = other.unit;
        }
        return *this;
    }

    Sensor &Sensor::operator=(Sensor &&other) {
        if (this != &other) {
            delete value;
            name = std::move(other.name);
            value = other.value;
            unit = other.unit;
            other.value = nullptr;
        }
        return *this;
    }

    Sensor::~Sensor() {
        delete value;
    }

    const std::string &Sensor::getName() const {
        return name;
    }

    double Sensor::getValue() const {
        return *value;
    }
}
