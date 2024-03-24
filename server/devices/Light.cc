#include "Light.h"

namespace smart_home {
    Light::Light() : Device(DeviceType::LIGHT), brightness(0) {}

    void Light::setBrightness(int brightness) {
        this->brightness = brightness;
    }

    int Light::getBrightness() const {
        return brightness;
    }

    std::string Light::displayStatuses() const {
        std::cout << "Light status: " << getDeviceStatus() << ", Brightness: " << brightness << std::endl;
        return "Light status: " + getDeviceStatus() + ", Brightness: " + std::to_string(brightness);
    }

     Light* Light::clone() const {
        return new Light(*this);
    }
    
}