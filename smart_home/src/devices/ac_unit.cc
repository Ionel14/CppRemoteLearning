#include <iostream>
#include <stdexcept>
#include "devices/ac_unit.h"

namespace devices {

void AcUnit::SetIsOn(bool value) {
    std::lock_guard<std::mutex> data_lock(is_on_mutex);
    if (is_on != value) {
        std::cout << "Turning AC unit " << (value ? "on" : "off") << "..." << std::endl;
        is_on = value;
    }
    else {
        std::cout << "AC unit already turned " << (value ? "on" : "off") << "." << std::endl;
    }
}

void AcUnit::SetFanSpeed(uint8_t value) {
    if (fan_speed != value) {
        std::cout << "Setting fan speed to " << +value << "%." << std::endl;
        fan_speed = value;
    }
    else {
        std::cout << "Fan speed already set to " << +value << "%." << std::endl;
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
    if (!sensor) {
        return;
    }

    if (std::any_cast<float>(sensor->GetData()) > 28) {
        SetIsOn(true);
        SetFanSpeed((uint8_t)100);
        SetDesiredTemperature(21);
    }
    else if (std::any_cast<float>(sensor->GetData()) > 25) {
        SetIsOn(true);
        SetFanSpeed((uint8_t)50);
        SetDesiredTemperature(21);
    }
    else if (is_on) {
        SetIsOn(false);
        SetFanSpeed((uint8_t)0);
    }
}   

} // namespace devices