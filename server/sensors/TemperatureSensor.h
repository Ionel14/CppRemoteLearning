#ifndef NAGARROREMOTELEARNING_TEMPERATURESENSOR_H
#define NAGARROREMOTELEARNING_TEMPERATURESENSOR_H
#include "Sensor.h"

namespace smart_home {
    class TemperatureSensor : public Sensor {
    public:
        TemperatureSensor(const std::string &name);

        void generateRandomValue() override;
        double readTemperature() const;
        std::string displayStatus() const override;

    private:
        double convertToFahrenheit() const;
    };
}
#endif
