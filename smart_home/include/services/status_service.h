#ifndef SMART_HOME_SERVICES_STATUS_SERVICE_H_
#define SMART_HOME_SERVICES_STATUS_SERVICE_H_

#include <vector>
#include "sensors/sensor.h"
#include "devices/device.h"

namespace services {

// Rule of Zero

class StatusService {
    public:
      std::vector<sensors::Sensor*> GetSensors() {
        return sensors;
      }

      std::vector<devices::Device*> GetDevices() {
        return devices;
      }

      void AddSensor(sensors::Sensor* sensor);

      void AddDevice(devices::Device* device);

      void PrintStatus();

    private:
      std::vector<sensors::Sensor*> sensors;
      std::vector<devices::Device*> devices;
};

} // namespace services

#endif // SMART_HOME_SERVICES_STATUS_SERVICE_H_