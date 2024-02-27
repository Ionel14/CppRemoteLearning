#ifndef SMART_HOME_SERVICES_SERVICE_H_
#define SMART_HOME_SERVICES_SERVICE_H_

#include <vector>
#include <unordered_map>
#include <memory>
#include "sensors/sensor.h"
#include "devices/device.h"

namespace services {

// Rule of Zero

class Service {
    public:
      sensors::Sensor* GetSensor(rooms::Room* room);

      std::vector<sensors::Sensor*> GetSensors();

      std::vector<devices::Device*> GetDevices();

      void AddSensor(std::unique_ptr<sensors::Sensor> sensor);

      void AddDevice(std::unique_ptr<devices::Device> device);

      std::any GetSensorData(rooms::Room* room);

      void SetSensorData(rooms::Room* room, const std::any &data);

      virtual void Refresh() = 0;

    protected:
      std::unordered_map<std::unique_ptr<sensors::Sensor>, std::vector<std::unique_ptr<devices::Device>>> sensor_devices;

      void SetDevicesOnAuto();
};

} // namespace services

#endif // SMART_HOME_SERVICES_SERVICE_H_