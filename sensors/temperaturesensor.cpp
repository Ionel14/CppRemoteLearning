#include "temperaturesensor.h"
#include <iostream>

namespace smartHome {
    TemperatureSensor::TemperatureSensor(const std::string& sensorId, double value, bool isFunctional)
        : Sensor("Temperature", sensorId, value, isFunctional) {}

    void TemperatureSensor::measure() {
        if(!getIsFunctional()){
            std::cout << "The sensor is not working properly!!" << std::endl;
            return;
        }
        std::cout << "Measuring temperature..." << std::endl;
        // Assume a simple simulation where the temperature increases by 1 degree in each measurement
        setValue(getValue() + 1.0);
        std::cout << "Temperature measured: " << getValue() << " degrees Celsius." << std::endl;
    }
}