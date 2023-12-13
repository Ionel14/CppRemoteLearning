#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include "sensor.h"

namespace smartHome{
class Device {
public:
    Device(const std::string& type, const std::string& deviceId, bool status, const std::vector<Sensor>& sensors);

    const std::string& getType() const;
    const std::string& getId() const;
    bool getStatus() const;
    const std::vector<Sensor>& getSensors() const;

    void setType(const std::string& newType);
    void setStatus(bool newStatus);
    void setSensors(const std::vector<Sensor>& sensors);

private:
    std::string type;
    const std::string deviceId;
    bool status;
    std::vector<Sensor> sensors;
};
}
#endif // DEVICE_H
