#include <iostream>
#include "services/service.h"
#include "sensors/sensor.h"
#include "devices/device.h"

namespace services {

std::vector<sensors::Sensor*> Service::GetSensors() {
    std::vector<sensors::Sensor*> sensors;

    for (auto& sensor_device : sensor_devices) {
        sensors.push_back(sensor_device.first);
    }

    return sensors;
}

std::vector<devices::Device*> Service::GetDevices() {
    std::vector<devices::Device*> devices;

    for (auto& sensor_device : sensor_devices) {
        for (auto& device : sensor_device.second) {
            devices.push_back(device);
        }
    }

    return devices;
}

void Service::AddSensor(sensors::Sensor* sensor) {
    if (sensor == nullptr) {
            return;
    }

    for (auto& sensor_device : sensor_devices) {
        if (sensor_device.first == sensor or sensor_device.first->GetRoom() == sensor->GetRoom()) {
            std::cout << "Sensor already exists in the same room." << std::endl;
            return;
        }
    }

    sensor_devices.insert({sensor, std::vector<devices::Device*>()});
}

void Service::AddDevice(devices::Device* device) {
    for (auto& sensor_device : sensor_devices) {
        if (sensor_device.first->GetRoom() == device->GetRoom()) {
            sensor_device.second.push_back(device);
            return;
        }
    }
}

void Service::SetDevicesOnAuto() {
    for (auto& sensor_device : sensor_devices) {
        for (devices::Device* device : sensor_device.second) {
            device->SetOnAuto(sensor_device.first);
        }
    }
}

} // namespace services

