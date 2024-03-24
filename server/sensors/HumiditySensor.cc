#include "HumiditySensor.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace smart_home {
    HumiditySensor::HumiditySensor(const std::string &name)
            : Sensor(name, MeasureUnit::PERCENT) {
                 std::srand(static_cast<unsigned>(std::time(nullptr)));
            }

    void HumiditySensor::generateRandomValue() {
        *value = std::rand() % 100;
    }

    double HumiditySensor::getHumidityPercentage() const {
        return static_cast<double>(*value);
    }

    std::string HumiditySensor::displayStatus() const {
        std::cout << "Humidity: " << getHumidityPercentage() << "%" << std::endl;
        return "Humidity: " + std::to_string(getHumidityPercentage()) + "%";
    }
}