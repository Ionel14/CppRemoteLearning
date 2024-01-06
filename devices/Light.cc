#include "Light.h"

namespace smart_home {
    Light::Light() : Device(DeviceType::LIGHT), brightness(0) {}

    void Light::setBrightness(int brightness) {
        this->brightness = brightness;
    }

    int Light::getBrightness() const {
        return brightness;
    }

    void Light::displayStatuses() const {
        std::cout << "Light status: " << getDeviceStatus() << ", Brightness: " << brightness << std::endl;
    }

     Light* Light::clone() const {
        return new Light(*this);
    }
    
}