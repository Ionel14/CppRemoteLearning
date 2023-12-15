#include <iostream>
#include "../../include/devices/device.h"

namespace devices
{

void Device::SetIsOn(bool value) {
    if (is_on != value) {
        std::cout << "Turning AC unit " << (value ? "on" : "off") << "..." << std::endl;
        is_on = value;
    }
    else {
        std::cout << "AC unit already turned " << (value ? "on" : "off") << "." << std::endl;
    }
}

} // namespace devices