#include "MonoxidSensor.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace smart_home {
    MonoxideSensor::MonoxideSensor(const std::string &name)
            : Sensor(name, MeasureUnit::UNKNOWN) {
                std::srand(static_cast<unsigned>(std::time(nullptr)));
            }

    void MonoxideSensor::generateRandomValue() {
        *value = std::rand() % 100;
    }

    double MonoxideSensor::getMonoxideLevel() const {
        return static_cast<double>(*value);
    }

    bool MonoxideSensor::isDangerousLevel() const {
        return getMonoxideLevel() > DANGER_LEVEL;
    }

    std::string MonoxideSensor::displayStatus() const {
        std::cout << "Monoxide Level: " << getMonoxideLevel() << " ppm" << std::endl;
        return "Monoxide Level: " + std::to_string(getMonoxideLevel()) + " ppm";
    }
}
