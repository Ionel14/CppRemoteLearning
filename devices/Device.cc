#include "Device.h"

namespace SmartHome {
    Device::Device(DeviceType deviceType) : type(deviceType) {}

    std::string Device::getDeviceType() const {
        switch (type) {
            case LIGHT:
                return "Light";
            case HEATER:
                return "Heater";
            default:
                return "ERROR";
        }
    }

    std::string Device::getDeviceStatus() const {
        if (status == 1)
            return "On";
        else if (status == 0)
            return "Off";
        else
            return "ERROR";
    }

    void Device::setDeviceStatus(int status) {
        this->status = status;
    }

    void Device::setDeviceType(DeviceType deviceType) {
        this->type = deviceType;
    }

    void Device::turnOn() {
        std::cout << "Turning on " << getDeviceType() << std::endl;
        status = 1;
    }

    void Device::turnOff() {
        std::cout << "Turning off " << getDeviceType() << std::endl;
        status = 0;
    }

    void Device::displayStatuses() const {
        std::cout << "Device Type: " << getDeviceType() << std::endl;
        std::cout << "Device Status: " << getDeviceStatus() << std::endl;
    }
}