#include <iostream>
#include "../../include/devices/ac_unit.h"

namespace devices {

void AcUnit::SetFanSpeed(int value) {
    if (fan_speed != value) {
        std::cout << "Setting fan speed to " << value << "%." << std::endl;
        fan_speed = value;
    }
    else {
        std::cout << "Fan speed already set to " << value << "%." << std::endl;
    }
}

void AcUnit::SetDesiredTemperature(float value) {
    if (desired_temperature != value) {
        std::cout << "Setting desired temperature to " << value << " degrees." << std::endl;
        desired_temperature = value;
    }
    else {
        std::cout << "Desired temperature already set to " << value << " degrees." << std::endl;
    }
}

void AcUnit::SetOnAuto(sensors::Sensor* sensor) {

    if (std::any_cast<float>(sensor->GetData()) > 28) {
        SetIsOn(true);
        SetFanSpeed(100);
        SetDesiredTemperature(21);
    }
    else if (std::any_cast<float>(sensor->GetData()) > 25) {
        SetIsOn(true);
        SetFanSpeed(50);
        SetDesiredTemperature(21);
    }
    else if (is_on) {
        SetIsOn(false);
        SetFanSpeed(0);
    }
}   

} // namespace devices