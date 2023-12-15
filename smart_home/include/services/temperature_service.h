#ifndef SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_
#define SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_

#include "service.h"
#include "../sensors/temperature_sensor.h"

namespace services {

// Rule of Zero

class TemperatureService : public Service {
  public:
    inline std::vector<sensors::Sensor*> GetSensors() override {
        return sensors;
    }

    inline std::vector<devices::Device*> GetDevices() override {
        return devices;
    }

    void AddSensor(sensors::TemperatureSensor* sensor);

    void AddDevice(devices::Device* device);

    void Refresh();

    private:
      std::vector<devices::Device*> FindCorrespondingDevices(sensors::Sensor* sensor);
};

}

#endif // SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_