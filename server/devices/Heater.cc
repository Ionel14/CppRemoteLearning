#include "Heater.h"

namespace smart_home {
    Heater::Heater() : Device(DeviceType::HEATER), temperature(0) {}

    void Heater::setTemperature(int temperature) {
        this->temperature = temperature;
    }

    int Heater::getTemperature() const {
        return temperature;
    }

    std::string Heater::displayStatuses() const {
        std::cout << "Heater status: " << getDeviceStatus() << ", Temperature: " << temperature << std::endl;
        return "Heater status: " + getDeviceStatus() + ", Temperature: " + std::to_string(temperature);
    }

     Heater* Heater::clone() const {
        return new Heater(*this);
    }
}
