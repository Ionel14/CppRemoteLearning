#include "device.h"

// Constructor
Device::Device(const std::string& type, const std::string& deviceId, bool status, const std::vector<Sensor> sensors)
    : type(type), deviceId(deviceId), status(status), sensors(sensors) {}

// Getter for device's type
const std::string Device::getType() const {
    return type;
}

// Getter for device's id
const std::string Device::getId() const {
    return deviceId;
}

// Getter for device's status
bool Device::getStatus() const {
    return status;
}

// Getter for device's list of sensors
const std::vector<Sensor> Device::getSensors() const {
    return sensors;
}
