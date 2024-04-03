#include "soundsensor.h"
#include <iostream>

namespace smartHome {
    SoundSensor::SoundSensor(const std::string& sensorId, double value, bool isFunctional)
        : Sensor("Sound", sensorId, value, isFunctional) {}

    void SoundSensor::measure() {
        
        std::cout << "Measuring sound levels..." << std::endl;
        
        // Assume a simple simulation where the sensor value is updated with a random value
        setValue(generateRandomSoundLevel());
        
        std::cout << "Sound level measured: " << getValue() << " dB." << std::endl;
    }

    double SoundSensor::generateRandomSoundLevel() const {
        // Generate a random sound level between 30 and 100 dB (example range)
        return 30.0 + static_cast<double>(rand()) / RAND_MAX * (100.0 - 30.0);
    }
}
