#ifndef SMART_HOME_SERVICES_SERVICE_H_
#define SMART_HOME_SERVICES_SERVICE_H_

#include <vector>
#include "../sensors/sensor.h"
#include "../devices/device.h"

namespace services {

// Rule of Zero

class Service {
    public:
      virtual std::vector<sensors::Sensor*> GetSensors() = 0;
      
      virtual std::vector<devices::Device*> GetDevices() = 0;

    protected:
      std::vector<sensors::Sensor*> sensors;
      std::vector<devices::Device*> devices;
};

} // namespace services

#endif // SMART_HOME_SERVICES_SERVICE_H_