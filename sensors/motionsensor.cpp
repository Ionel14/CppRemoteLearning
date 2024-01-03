#include "motionsensor.h"
#include <iostream>

namespace smartHome {
    MotionSensor::MotionSensor(const std::string& sensorId, double value, bool isFunctional)
        : Sensor("Motion", sensorId, value, isFunctional) {}

    void MotionSensor::measure() {

        if(!getIsFunctional()){
            std::cout << "The sensor is not working properly!!" << std::endl;
            return;
        }

        std::cout << "Detecting motion..." << std::endl;
        
        // Assume a simple simulation where the sensor value is toggled between 0 and 1
        if (getValue() == 0.0) {
            setValue(1.0);
            std::cout << "Motion detected!" << std::endl;
        } else {
            setValue(0.0);
            std::cout << "No motion detected." << std::endl;
        }
    }
}
