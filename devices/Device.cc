#include "Device.h"

namespace smart_home {
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
        if (status > 1 || status < 0){
            std::cout << "Cannot set this status, command ignored!" << std::endl;
            return; 
        }
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
}