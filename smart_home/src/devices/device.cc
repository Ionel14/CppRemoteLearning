#include <iostream>
#include "devices/device.h"

namespace devices
{

void Device::SetIsOn(bool value) {
    if (is_on != value) {
        std::cout << "Turning device " << (value ? "on" : "off") << "..." << std::endl;
        is_on = value;
    }
    else {
        std::cout << "Device already turned " << (value ? "on" : "off") << "." << std::endl;
    }
}

} // namespace devices