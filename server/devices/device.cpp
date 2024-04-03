#include "device.h"

namespace smartHome{
    // Constructor
    Device::Device(const std::string& type, const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors)
        : type(type), deviceId(deviceId), status(status), sensors(sensors) {}

    // Getter for device's type
    const std::string& Device::getType() const {
        return type;
    }

    // Getter for device's id
    const std::string& Device::getId() const {
        return deviceId;
    }

    // Getter for device's status
    bool Device::getStatus() const {
        return status;
    }

    // Getter for device's list of sensors
    const std::vector<Sensor*>& Device::getSensors() const {
        return sensors;
    }

    //Setters
    void Device::setType(const std::string& newType){
        type = newType;
    }

    void Device::setStatus(bool newStatus){
        status = newStatus;
    }

    void Device::setSensors(const std::vector<Sensor*>& newSensors){
        sensors = newSensors;
    }

    void Device::addSensor(Sensor* sensor){
        sensors.push_back(sensor);
    }

    void Device::removeSensor(std::string sensorID) {
        for (auto it = sensors.begin(); it != sensors.end();) {
            if ((*it)->getID() == sensorID) {
                it = sensors.erase(it);
            } else {
                ++it;
            }
        }
    }

}