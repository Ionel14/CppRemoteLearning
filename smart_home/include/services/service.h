#ifndef SMART_HOME_SERVICES_SERVICE_H_
#define SMART_HOME_SERVICES_SERVICE_H_

#include <vector>
#include <unordered_map>
#include "sensors/sensor.h"
#include "devices/device.h"

namespace services {

// Rule of Zero

class Service {
    public:
      std::vector<sensors::Sensor*> GetSensors();

      std::vector<devices::Device*> GetDevices();

      void AddSensor(sensors::Sensor* sensor);

      void AddDevice(devices::Device* device);

      virtual void Refresh() = 0;

    protected:
      std::unordered_map<sensors::Sensor*, std::vector<devices::Device*>> sensor_devices;

      void SetDevicesOnAuto();
};

} // namespace services

#endif // SMART_HOME_SERVICES_SERVICE_H_