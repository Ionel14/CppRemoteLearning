#include <iostream>
#include <stdexcept>
#include "devices/device.h"

namespace devices
{

void Device::SetIsOn(bool value) {
    std::lock_guard<std::mutex> data_lock(is_on_mutex);
    if (is_on != value) {
        std::cout << "Turning device " << (value ? "on" : "off") << "..." << std::endl;
        is_on = value;
    }
    else {
        std::cout << "Device already turned " << (value ? "on" : "off") << "." << std::endl;
    }
}

Device::Device(std::shared_ptr<rooms::Room> room): room(room) {
    if (!room) {
        throw std::runtime_error("Room is null.\n");
    }
}

} // namespace devices