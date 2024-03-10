#include "HumiditySensor.h"
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
}