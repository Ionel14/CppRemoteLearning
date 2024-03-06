#include <iostream>
#include "devices/light_bulb.h"

namespace devices {

void LightBulb::SetIsOn(bool value) {
    std::lock_guard<std::mutex> data_lock(is_on_mutex);
    if (is_on != value) {
        std::cout << "Turning light bulb " << (value ? "on" : "off") << "..." << std::endl;
        is_on = value;
    }
    else {
        std::cout << "Light bulb already turned " << (value ? "on" : "off") << "." << std::endl;
    }
}

void LightBulb::SetOnAuto(sensors::Sensor* sensor) {
    if (!sensor) {
        return;
    }

    if (std::any_cast<bool>(sensor->GetData())) {
        SetIsOn(true);
    }
    else {
        SetIsOn(false);
    }
}   

} // namespace devices