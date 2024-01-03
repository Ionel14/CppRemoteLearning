#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include "sensor.h"

namespace smartHome {
    class MotionSensor : public Sensor {
    public:
        MotionSensor(const std::string& sensorId, double value, bool isFunctional);

        void measure() override;
        
    };
}

#endif // MOTION_SENSOR_H