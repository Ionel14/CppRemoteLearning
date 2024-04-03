#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#include "sensor.h"

namespace smartHome {
    class SoundSensor : public Sensor {
    public:
        SoundSensor(const std::string& sensorId, double value, bool isFunctional);

        void measure() override;
        double generateRandomSoundLevel() const;
    };
}

#endif // SOUND_SENSOR_H