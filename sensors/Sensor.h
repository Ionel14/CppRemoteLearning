#ifndef NAGARROREMOTELEARNING_SENSOR_H
#define NAGARROREMOTELEARNING_SENSOR_H

#include <string>
#include "../utils/enums.h"

namespace smart_home {
    class Sensor {
    public:
        Sensor(const std::string &sensorName, MeasureUnit sensorUnit);
        Sensor(const Sensor &other);
        Sensor(Sensor &&other);
        Sensor &operator=(const Sensor &other);
        Sensor &operator=(Sensor &&other);
        virtual ~Sensor();
        const std::string &getName() const;
        int getValue() const;
        MeasureUnit getUnit() const;

        virtual void generateRandomValue() = 0;

    protected:
        std::string name;
        double *value;
        MeasureUnit unit;
    };
}

#endif
