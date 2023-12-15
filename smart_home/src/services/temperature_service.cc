#include <iostream>
#include "../../include/services/temperature_service.h"
#include "../../include/sensors/temperature_sensor.h"
#include "../../include/devices/ac_unit.h"

namespace services {

void TemperatureService::AddSensor(sensors::TemperatureSensor* sensor) {
    sensors.push_back(sensor);
}

void TemperatureService::AddDevice(devices::Device* device) {
    devices.push_back(device);
}

void TemperatureService::Refresh() {
    for (sensors::Sensor* sensor : sensors) {
        std::cout << "Refreshing..." << std::endl;
        std::vector<devices::Device*> corresponding_devices = FindCorrespondingDevices(sensor);

        for (devices::Device* device : corresponding_devices) {
            device->SetOnAuto(sensor);
        }
    }
}

std::vector<devices::Device*> TemperatureService::FindCorrespondingDevices(sensors::Sensor* sensor) {
    std::vector<devices::Device*> corresponding_devices;

    for (devices::Device* device : devices) {
        if (device->GetRoom() == sensor->GetRoom()) {
            corresponding_devices.push_back(device);
        }
    }

    return corresponding_devices;
}

} // namespace services

