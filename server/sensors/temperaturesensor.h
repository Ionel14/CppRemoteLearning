#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "sensor.h"

namespace smartHome {
    class TemperatureSensor : public Sensor {
    public:
        TemperatureSensor(const std::string& sensorId, double value, bool isFunctional);

        void measure() override;
        
    };
}

#endif // TEMPERATURE_SENSOR_H
