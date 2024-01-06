#include "AirConditioner.h"

namespace smart_home {
    AirConditioner::AirConditioner() : Device(DeviceType::AIR_CONDITIONER), temperature(0), mode(ACMode::COOLING) {}

    void AirConditioner::setTemperature(int temperature) {
        this->temperature = temperature;
    }

    void AirConditioner::setMode(ACMode mode) {
        this->mode = mode;
    }

    int AirConditioner::getTemperature() const {
        return temperature;
    }

    ACMode AirConditioner::getMode() const {
        return mode;
    }

    void AirConditioner::displayStatuses() const {
        std::string modeStr = mode == ACMode::COOLING ? "Cooling" : "Heating";
        std::cout << "Air Conditioner status: " << getDeviceStatus() << ", Mode: " << modeStr << ", Temperature: " << temperature << std::endl;
    }

     AirConditioner* AirConditioner::clone() const {
        return new AirConditioner(*this);
    }
}